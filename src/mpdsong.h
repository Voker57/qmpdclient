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

#ifndef MPDSONG_H
#define MPDSONG_H

#include <QSharedData>

class QRegExp;
struct MPDSongPrivate;
struct mpd_InfoEntity;

class MPDSong {
public:
	enum Type { ERROR, SONG, STREAM, PLAYLIST, PLAYLISTSONG, PLAYLISTSTREAM, UNKNOWN };
	MPDSong();
	MPDSong(mpd_InfoEntity *);
	MPDSong(const MPDSong &);
	~MPDSong();
	// Create stream song, just url and title
	static MPDSong createStream(const QString &title, const QString &url);
	// This one is for creating dummy songs for pattern testing
	static MPDSong createTest(const QString &url);

	Type type() const;
	bool isNull() const;
	QString album() const;
	QString artist() const;
	QString comment() const;
	QString composer() const;
	QString date() const;
	QString directory() const;
	QString disc() const;
	QString filename() const;
	QString genre() const;
	int id() const;
	QString performer() const;
	int pos() const;
	int secs() const;
	QString time() const;
	QString title() const;
	QString track() const;
	QString url() const;
	void setAlbum(const QString &);
	void setArtist(const QString &);
	void setTitle(const QString &);
	void setTrack(const QString &);

	bool contains(const QRegExp &) const;
	bool operator<(const MPDSong &other) const;
	bool operator==(const MPDSong &other) const;
	bool operator!=(const MPDSong &other) const;
	MPDSong &operator=(const MPDSong &);

private:
	friend QDataStream &operator>>(QDataStream &, MPDSong &);
	friend QDataStream &operator<<(QDataStream &, const MPDSong &);

	QSharedDataPointer<MPDSongPrivate> d;
};

QDataStream &operator>>(QDataStream &, MPDSong &);
QDataStream &operator<<(QDataStream &, const MPDSong &);
#endif
