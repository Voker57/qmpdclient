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

#ifndef PLAYLISTMODEL_H
#define PLAYLISTMODEL_H

#include "abstractmodel.h"
#include "mpdsongmodel.h"
#include "mpdsong.h"

class PlaylistModel : public MPDSongModel {
public:
	PlaylistModel(QObject *);
	int columnCount(const QModelIndex & = QModelIndex()) const;
	QVariant data(const QModelIndex &, int) const;

	QModelIndex indexOfSong(const MPDSong &) const;
	MPDSong lastSong() const;
	QString pattern() const;
	MPDSong playingSong() const;
	void setFilter(const QString &);
	void setPattern(const QString &);
	void setPlaying(const MPDSong &);
	void setTopDrop(bool);
	MPDSongList unSelectedSongs(const QModelIndexList &) const;

	bool dropMimeData(const QMimeData *, Qt::DropAction, int, int, const QModelIndex &);
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &) const;

	void addToQueue(const QModelIndexList &);
	void removeFromQueue(const QModelIndexList &);
	void advanceQueue();
	QList<MPDSong> queue() const;

private:
	MPDSongList decodeSongs(const QMimeData *, QString) const;
	void filter();
	MPDSong song(const QModelIndex &) const;

	bool m_topDrop;
	MPDSong m_playingSong;
	QList<MPDSong> m_queue;
	QString m_pattern;
};
#endif
