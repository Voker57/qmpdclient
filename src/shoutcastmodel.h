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

#ifndef SHOUTCASTMODEL_H
#define SHOUTCASTMODEL_H

class QShowEvent;
class ShoutcastFetcher;
#include "shoutcaststation.h"
#include "abstractmodel.h"
#include <QStandardItemModel>
#include <QPointer>
class MPDSongList;
class MPDSong;
class QMimeData;

class ShoutcastModel : public QStandardItemModel, public AbstractModel {
	Q_OBJECT
public:
	enum
	{
		StationRole = Qt::UserRole + 1
	};
	ShoutcastModel(QObject *parent = 0);
	void downloadGenres();
	void downloadStationsForGenre(const QString & genre);
	void downloadPlaylistForStation(const ShoutcastStation & station);
	MPDSongList songs(const QModelIndexList & list) const;
	virtual QMimeData *mimeData(const QModelIndexList &indexes) const;

private slots:
	void genresAvailable();
	void newStationsAvailable(const QString & keyWord);
	void playlistAvailable(const ShoutcastStation & station);
private:
	ShoutcastFetcher * m_fetcher;
};

#endif
