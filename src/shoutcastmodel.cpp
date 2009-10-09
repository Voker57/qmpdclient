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

#include "shoutcastmodel.h"
#include "shoutcastfetcher.h"
#include "shoutcaststation.h"
#include "mpdsong.h"
#include "mpdsonglist.h"
#include <QList>
#include <QDebug>
#include <QUrl>
#include <QEvent>
#include <QMimeData>

namespace
{
	int maxSize = 200000;
	const QString genresURL = "http://yp.shoutcast.com/sbin/newxml.phtml";
	const QString stationsForGenreURL = "http://yp.shoutcast.com/sbin/newxml.phtml?genre=";
}

ShoutcastModel::ShoutcastModel(QObject *parent)
: QStandardItemModel(parent), m_fetcher(new ShoutcastFetcher(this)) {
	setObjectName("shoutcastmodel");
	connect(m_fetcher, SIGNAL(genresAvailable()), this, SLOT(genresAvailable()));
	connect(m_fetcher, SIGNAL(newStationsAvailable(const QString &)),
			this, SLOT(newStationsAvailable(const QString &)));
	connect(m_fetcher, SIGNAL(playlistAvailable(const ShoutcastStation&)),
			this, SLOT(playlistAvailable(const ShoutcastStation&)));
	setColumnCount(3);
	setHorizontalHeaderLabels(QStringList() << tr("Name") << tr("Bitrate") << tr("Listeners"));
	qRegisterMetaType<ShoutcastStation>("ShoutcastStation");
}

void ShoutcastModel::genresAvailable() {
	foreach(const QString & genre, m_fetcher->genres()) {
		QStandardItem * i = new QStandardItem(genre);
		i->appendRow(new QStandardItem(tr("Please wait...")));
		appendRow(i);
	}
}

void ShoutcastModel::newStationsAvailable(const QString & keyWord) {
	QList<QStandardItem *> genreItemList = findItems(keyWord);
	Q_ASSERT(genreItemList.count() == 1);
	QStandardItem * genreItem = genreItemList[0];
	genreItem->removeRows(0, genreItem->rowCount());
	foreach(const ShoutcastStation & station, m_fetcher->stationsForKeyword(keyWord)) {
		QStandardItem * bitRate = new QStandardItem(QString::number(station.bitRate()) + tr(" bps"));
		QStandardItem * listeners = new QStandardItem(QString::number(station.listeners()));
		QStandardItem * name = new QStandardItem(station.name());
		name->setData(qVariantFromValue(station), StationRole);
		genreItem->appendRow(QList<QStandardItem * >() << name << bitRate << listeners);
		name->appendRow(new QStandardItem(tr("Please wait")));
	}
}

void ShoutcastModel::playlistAvailable(const ShoutcastStation & station) {
	QList<QStandardItem*> stdItems = findItems("*", Qt::MatchWildcard|Qt::MatchRecursive, 0);
	qDebug() << Q_FUNC_INFO << stdItems.count();
	QStandardItem * stationItem = 0;
	qDebug() << "Looking for " << station.name() << station.id();
	foreach(QStandardItem * item, stdItems) {
		ShoutcastStation s = qvariant_cast<ShoutcastStation>(item->data(StationRole));
		if (!s.isValid())
			continue;
		qDebug() << s.name() << s.id();
		if (s == station) {
			qDebug() << "Match";
			stationItem = item;
			break;
		}
	}
	qDebug() << "Playlist available for station " << station.name();
	Q_ASSERT(stationItem);
	if (!stationItem)
		return;
	stationItem->removeRows(0, stationItem->rowCount());
	foreach(const QUrl & url, m_fetcher->playlistForStation(station))
	{
		qDebug() << url;
		QStandardItem * playListItem = new QStandardItem(url.toString());
		playListItem->setDragEnabled(true);
		stationItem->appendRow(playListItem);
	}
}

void ShoutcastModel::downloadGenres() {
	m_fetcher->fetchGenres(QUrl(genresURL));
}

void ShoutcastModel::downloadStationsForGenre(const QString & genre) {
	m_fetcher->fetchStations(genre, stationsForGenreURL + genre);
}

void ShoutcastModel::downloadPlaylistForStation(const ShoutcastStation & station)
{
	m_fetcher->fetchPlaylistsForStation(station);
}

MPDSongList ShoutcastModel::songs(const QModelIndexList & list) const {
	MPDSongList l;
	foreach(const QModelIndex & index, list) {
		QString str = data(index).toString();
		if (QUrl(str).toString().contains("http://")) {
			qDebug() << "Found URL " << str;
			l << MPDSong::createStream(str, str);
		}
	}
	return l;
}

QMimeData *ShoutcastModel::mimeData(const QModelIndexList &indexes) const {
	if (isDragDisabled())
		return 0;
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);
	MPDSongList songsFromIndexes = songs(indexes);
	if (songsFromIndexes.empty())
		return 0;
	foreach (MPDSong song, songsFromIndexes) {
		stream << song;
	}
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("qmpdclient/song", encodedData);
	return mimeData;
}
