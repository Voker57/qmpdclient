/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Håvard Tautra Knutsen <havtknut@tihlde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "libmpdclient.h"
#include "mpdsong.h"
#include "config.h"
#include "tagguesser.h"
#include <QDataStream>
#include <QStringList>
#include <QTime>

struct MPDSongPrivate : public QSharedData {
	qint32 pos, secs, id;
	MPDSong::Type type;
	QString album, artist, comment, composer, date, disc, genre, performer, time, title, track, url;
	QStringList haystack;

	MPDSongPrivate() :
			pos(0),
			secs(0),
			id(-1),
			type(MPDSong::UNKNOWN) {}

	void finalize() {
		haystack << album << artist << comment << composer << date << disc << genre << performer << time << title << track << url;
	}
};

MPDSong::MPDSong() : d(0) {}
MPDSong::MPDSong(const MPDSong &other) : d(other.d) {}
MPDSong::~MPDSong() {}

MPDSong::MPDSong(mpd_InfoEntity *entity) : d(new MPDSongPrivate) {
	Q_ASSERT(d);
	if (entity->type == MPD_INFO_ENTITY_TYPE_PLAYLISTFILE) {
		d->title = d->url = QString::fromUtf8(entity->info.playlistFile->path);
		d->type = MPDSong::PLAYLIST;
	} else if (entity->type == MPD_INFO_ENTITY_TYPE_SONG) {
		mpd_Song *song = entity->info.song;
		d->url = QString::fromUtf8(song->file);
		d->track = QString::fromUtf8(song->track);
		if (song->id > -1 && d->url.contains("://"))
			d->type = MPDSong::PLAYLISTSTREAM;
		else if (song->id > -1)
			d->type = MPDSong::PLAYLISTSONG;
		else
			d->type = MPDSong::SONG;
		d->pos = song->pos;
		d->secs = song->time;
		d->id = song->id;
		d->title = QString::fromUtf8(song->title);
		d->artist = QString::fromUtf8(song->artist);
		d->album = QString::fromUtf8(song->album);
		d->performer = QString::fromUtf8(song->performer);
		d->composer = QString::fromUtf8(song->composer);
		d->comment = QString::fromUtf8(song->comment);
		d->genre = QString::fromUtf8(song->genre);
		d->date = QString::fromUtf8(song->date);
		QTime t = QTime(0, 0).addSecs(d->secs);
		d->time = t.toString(t.hour() > 0 ? "h:mm:ss" : "m:ss");
	} else
		qWarning("MPDSong::MPDSong() unknown entity type");

	if (Config::instance()->tagGuesserEnabled())
		TagGuesser::guessTags(*this);

	d->finalize();
}

/**
 * Create new MPDSong stream.
 * @param title Title of stream.
 * @param url URL of stream.
 * @return MPDSong.
 */
MPDSong MPDSong::createStream(const QString &title, const QString &url) {
	MPDSong song;
	song.d = new MPDSongPrivate;
	song.d->title = title;
	song.d->url = url;
	song.d->finalize();
	song.d->type = STREAM;
	return song;
}

/**
 * Create dummy MPDSong for testing tag-guesser.
 * @param url URL to guess on.
 * @return MPDSong.
 */
MPDSong MPDSong::createTest(const QString &url) {
	MPDSong song;
	song.d = new MPDSongPrivate;
	song.d->url = url;
	song.d->finalize();
	return song;
}

MPDSong::Type MPDSong::type() const {
	Q_ASSERT(d);
	return d->type;
}

bool MPDSong::isNull() const {
	return d == NULL;
}

int MPDSong::pos() const {
	Q_ASSERT(d);
	return d->pos;
}

int MPDSong::secs() const {
	Q_ASSERT(d);
	return d->secs;
}

int MPDSong::id() const {
	Q_ASSERT(d);
	return d->id;
}

void MPDSong::setArtist(const QString &a) {
	Q_ASSERT(d);
	d->artist = a;
}

QString MPDSong::artist() const {
	Q_ASSERT(d);
	return d->artist;
}

void MPDSong::setAlbum(const QString &a) {
	Q_ASSERT(d);
	d->album = a;
}

QString MPDSong::album() const {
	Q_ASSERT(d);
	return d->album;
}

void MPDSong::setTrack(const QString &t) {
	Q_ASSERT(d);
	d->track = t;
}

QString MPDSong::track() const {
	Q_ASSERT(d);
	return d->track;
}

QString MPDSong::filename() const {
	return url().section('/', -1, -1);
}

QString MPDSong::url() const {
	Q_ASSERT(d);
	return d->url;
}

/**
 * Get hh:mm formatted time.
 * @return formatted time string.
 */
QString MPDSong::time() const {
	if (type() == STREAM || url().contains("://"))
		return QString();
	Q_ASSERT(d);
	return d->time;
}

void MPDSong::setTitle(const QString &t) {
	Q_ASSERT(d);
	d->title = t;
}

QString MPDSong::title() const {
	Q_ASSERT(d);
	return d->title;
}

QString MPDSong::date() const {
	Q_ASSERT(d);
	return d->date;
}

QString MPDSong::genre() const {
	Q_ASSERT(d);
	return d->genre;
}

QString MPDSong::composer() const {
	Q_ASSERT(d);
	return d->composer;
}

QString MPDSong::comment() const {
	Q_ASSERT(d);
	return d->comment;
}

QString MPDSong::disc() const {
	Q_ASSERT(d);
	return d->disc;
}

QString MPDSong::performer() const {
	Q_ASSERT(d);
	return d->performer;
}

QString MPDSong::directory() const {
	if (url().contains('/'))
		return url().section('/', 0, -2);
	return "";
}

// Check if any of the song's fields contains the regexp
bool MPDSong::contains(const QRegExp &needle) const {
	Q_ASSERT(d);
	Q_ASSERT(!d->haystack.isEmpty());
	foreach(QString hay, d->haystack) {
		if (!hay.isEmpty() && hay.contains(needle))
			return true;
	}
	return false;
}

/*
 * Warning: this operator just checks if url is less than other url,
 * this should always guarantee a certain sort order, however it
 * might not always be the sort order you want.
 */
bool MPDSong::operator<(const MPDSong &other) const {
	if (url().localeAwareCompare(other.url()) < 0)
		return true;
	return false;
}

/**
 * Equality check
 * @param other MPDSong to compare this one to.
 * @return true if equal, else false.
 */
bool MPDSong::operator==(const MPDSong &other) const {
	if (isNull() && other.isNull())
		return true;
	if (isNull() || other.isNull())
		return false;
	if (type() != other.type())
		return false;
	if (type() == PLAYLISTSONG)
		return url() == other.url() && id() == other.id();
	return url() == other.url();
}

bool MPDSong::operator!=(const MPDSong &other) const {
	return !operator==(other);
}

MPDSong &MPDSong::operator=(const MPDSong &other) {
	d = other.d;
	return *this;
}

QDataStream &operator<<(QDataStream &s, const MPDSong &p) {
	s << p.pos();
	s << p.secs();
	s << p.id();
	s << static_cast<qint32>(p.type());
	s << p.album();
	s << p.artist();
	s << p.track();
	s << p.date();
	s << p.disc();
	s << p.genre();
	s << p.comment();
	s << p.composer();
	s << p.performer();
	s << p.title();
	s << p.time();
	s << p.url();
	return s;
}

QDataStream &operator>>(QDataStream &s, MPDSong &p) {
	if (!p.d)
		p.d = new MPDSongPrivate;
	qint32 tmp;
	s >> p.d->pos;
	s >> p.d->secs;
	s >> p.d->id;
	s >> tmp;
	p.d->type = static_cast<MPDSong::Type>(tmp);
	s >> p.d->album;
	s >> p.d->artist;
	s >> p.d->track;
	s >> p.d->date;
	s >> p.d->disc;
	s >> p.d->genre;
	s >> p.d->comment;
	s >> p.d->composer;
	s >> p.d->performer;
	s >> p.d->title;
	s >> p.d->time;
	s >> p.d->url;
	p.d->finalize();
	return s;
}
