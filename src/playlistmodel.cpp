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

#include "playlistmodel.h"
#include "aafilter.h"
#include "macroexpander.h"
#include "mpd.h"
#include "mpdcache.h"
#include <QApplication>
#include <QFont>
#include <QMimeData>

PlaylistModel::PlaylistModel(QObject *p) : MPDSongModel(p, 0),
		m_topDrop(false) {
	setObjectName("playlistmodel");
	m_pattern = "%b - %t";
}

void PlaylistModel::setPattern(const QString &p) {
	m_pattern = p;
	reset();
}

QString PlaylistModel::pattern() const {
	return m_pattern;
}

void PlaylistModel::setTopDrop(bool t) {
	m_topDrop = t;
}

QVariant PlaylistModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() < 0 || index.row() > m_visible.size())
		return QVariant();

	MPDSong s = m_visible.at(index.row());
	if (s.isNull())
		return QVariant();


	if (role == Qt::DisplayRole) {
		if (m_queue.contains(s))
			return QString("[%1] %2. %3|%4").arg(m_queue.indexOf(s)).arg(s.pos() + 1).arg(expandMacros(s, m_pattern)).arg(s.time());
		else
			return QString("%1. %2|%3").arg(s.pos() + 1).arg(expandMacros(s, m_pattern)).arg(s.time());
	} else if (role == Qt::FontRole && s == m_playingSong) {
		QFont font = QApplication::font();
		font.setBold(true);
		return font;
	} else if (role == Qt::ToolTipRole) {
		return QString("%1 - %2").arg(s.artist(), s.title());
	}
	return QVariant();
}

int PlaylistModel::columnCount(const QModelIndex &) const {
	return 1;
}

MPDSongList PlaylistModel::unSelectedSongs(const QModelIndexList &selectedIndexes) const {
	MPDSongList selected = songs(selectedIndexes);
	MPDSongList ret;
	foreach(MPDSong song, m_visible) {
		if (selected.contains(song))
			continue;
		ret << song;
	}
	return ret;
}

MPDSong PlaylistModel::lastSong() const {
	if (m_visible.isEmpty())
		return MPDSong();
	return m_visible.last();
}

void PlaylistModel::setPlaying(const MPDSong &song) {
	if (!song.isNull() && m_playingSong == song)
		return;
	QModelIndex oldidx = indexOfSong(m_playingSong);
	m_playingSong = song;
	QModelIndex idx = index(indexOfSong(m_playingSong).row(), 0);
	emit dataChanged(oldidx, idx);
}

MPDSong PlaylistModel::playingSong() const {
	return m_playingSong;
}

QModelIndex PlaylistModel::indexOfSong(const MPDSong &s) const {
	const int pos = m_visible.indexOf(s);
	if (pos > -1)
		return index(pos, 0);
	return QModelIndex();
}

void PlaylistModel::setFilter(const QString &a) {
	m_filter = QRegExp(a, Qt::CaseInsensitive);
	filter();
}

void PlaylistModel::filter() {
	if (m_filter.isEmpty()) {
		m_visible = m_all;
		reset();
		return;
	}

	m_visible.clear();
	for (QListIterator<MPDSong> it(m_all); it.hasNext();) {
		MPDSong s = it.next();
		if ((m_pattern.contains("%n") && s.track().contains(m_filter))
		        || (m_pattern.contains("%t") && s.title().contains(m_filter))
		        || (m_pattern.contains("%b") && s.artist().contains(m_filter))
		        || (m_pattern.contains("%a") && s.album().contains(m_filter))
		        || (m_pattern.contains("%g") && s.genre().contains(m_filter))
		        || (m_pattern.contains("%c") && s.composer().contains(m_filter))
		        || (m_pattern.contains("%d") && s.date().contains(m_filter))
		        || (m_pattern.contains("%f") && s.filename().contains(m_filter))
		        || (m_pattern.contains("%u") && s.url().contains(m_filter))
		        || s.time().contains(m_filter))
			m_visible << s;
	}
	reset();
}

/*
 * DND
 */
MPDSongList PlaylistModel::decodeSongs(const QMimeData *m, QString format) const {
	Q_ASSERT(m);
	if (format == "qmpdclient/aa") {
		QByteArray encodedData = m->data(format);
		QDataStream stream(&encodedData, QIODevice::ReadOnly);
		AAFilter aa;
		while (!stream.atEnd()) {
			stream >> aa;
		}
		return MPDCache::instance()->songsByAA(aa);
	}
	MPDSongList res;
	QByteArray encodedData = m->data(format);
	QDataStream stream(&encodedData, QIODevice::ReadOnly);
	while (!stream.atEnd()) {
		MPDSong s;
		stream >> s;
		res << s;
	}
	return res;
}

bool PlaylistModel::dropMimeData(const QMimeData *data, Qt::DropAction, int row, int, const QModelIndex &index) {
	Q_ASSERT(data);
	QString format;
	foreach(QString m, mimeTypes()) {
		if (data->hasFormat(m)) {
			format = m;
			break;
		}
	}
	if (format.isEmpty())
		return false;

	int dropPos;
	if (row != -1)
		dropPos = row;
	else if (index.isValid())
		dropPos = index.row();
	else
		dropPos = -1;

	MPDSongList songs = decodeSongs(data, format);
	if (format == "qmpdclient/move") {
		// drop pos special for moves
		if (dropPos == -1)
			dropPos = lastSong().pos();

		if (!songs.isEmpty() && songs.first().pos() > dropPos)
			++dropPos;// ++ when moving songs upwards

		MPD::instance()->moveSongs(songs, dropPos);
	} else {
		if (m_topDrop) // Add to top.
			dropPos = 0;
		else if (dropPos != -1) // ++ when adding, but not when adding to end
			++dropPos;
		MPD::instance()->addSongs(songs, true, dropPos);
	}
	return true;
}

QStringList PlaylistModel::mimeTypes() const {
	return QStringList() << "qmpdclient/song" << "qmpdclient/move" << "qmpdclient/aa";
}

QMimeData *PlaylistModel::mimeData(const QModelIndexList &indexes) const {
	if (m_dragDisabled)
		return 0;

	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);
	foreach(MPDSong song, songs(indexes)) {
		stream << song;
	}

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("qmpdclient/move", encodedData);
	return mimeData;
}

/*
 * Playlist queue
 */
void PlaylistModel::addToQueue(const QModelIndexList &s) {
	foreach(QModelIndex i, s) {
		MPDSong s = m_visible.at(i.row());
		m_queue.removeAll(s);
		m_queue.append(s);
	}
}

void PlaylistModel::removeFromQueue(const QModelIndexList &s) {
	foreach(QModelIndex i, s) {
		m_queue.removeAll(m_visible.at(i.row()));
	}
}

void PlaylistModel::advanceQueue() {
	if (!m_queue.isEmpty())
		setPlaying(m_queue.takeFirst());
}

QList<MPDSong> PlaylistModel::queue() const {
	return m_queue;
}
