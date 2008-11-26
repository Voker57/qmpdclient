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

#include "headerview.h"
#include "mpdsongmodel.h"
#include <QMimeData>

MPDSongModel::MPDSongModel(QObject *parent, HeaderView *hv, const MPDSongList &songs) : QAbstractTableModel(parent),
		m_header(hv) {
	setObjectName("mpdsongmodel");
	setSongs(songs);
}

QVariant MPDSongModel::data(const QModelIndex &index, int role) const {
	Q_ASSERT(m_header);
	if (!index.isValid() || index.row() < 0 || index.row() >= m_visible.size() || index.column() >= m_header->columns().size())
		return QVariant();

	MPDSong song = m_visible.at(index.row());
	if (song.isNull())
		return QVariant();

	if (role == Qt::DisplayRole) {
		switch (m_header->columns().at(index.column())) {
			case HeaderView::TRACK:
				return song.track();
			case HeaderView::TITLE:
				return song.title();
			case HeaderView::LENGTH:
				return song.time();
			case HeaderView::ALBUM:
				return song.album();
			case HeaderView::ARTIST:
				return song.artist();
			case HeaderView::FILENAME:
				return song.filename();
			case HeaderView::URL:
				return song.url();
			case HeaderView::GENRE:
				return song.genre();
			case HeaderView::DATE:
				return song.date();
			case HeaderView::COMPOSER:
				return song.composer();
			case HeaderView::PERFORMER:
				return song.performer();
			case HeaderView::COMMENT:
				return song.comment();
			case HeaderView::DISC:
				return song.disc();
			default:
				return "?";
		}
	}

	if (role == Qt::TextAlignmentRole && m_header->columns().at(index.column()) == HeaderView::LENGTH)
		return Qt::AlignRight;

	return QVariant();
}

QVariant MPDSongModel::headerData(int section, Qt::Orientation orientation, int role) const {
	Q_ASSERT(m_header);
	if (role != Qt::DisplayRole || section >= m_header->columns().size() || section < 0 || orientation != Qt::Horizontal)
		return QVariant();
	return m_header->columnName(m_header->columns().at(section));
}

void MPDSongModel::setFilter(const QString &a) {
	m_filter = QRegExp(a, Qt::CaseInsensitive);
	filter();
}

int MPDSongModel::columnCount(const QModelIndex &) const {
	Q_ASSERT(m_header);
	return m_header->columns().size();
}

int MPDSongModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid()) // Valid items does not have children
		return 0;
	return m_visible.size();
}

Qt::ItemFlags MPDSongModel::flags(const QModelIndex &index) const {
	if (!index.isValid()) // Dropping must always be enabled (only for the playlist though) for DnD to work
		return Qt::ItemIsDropEnabled;
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

void MPDSongModel::setSongs(const MPDSongList &s) {
	m_all = s;
	filter();
}

MPDSong MPDSongModel::song(const QModelIndex &index) const {
	if (!index.isValid() || index.row() < 0 || m_visible.count() <= index.row())
		return MPDSong();
	return m_visible.at(index.row());
}

MPDSongList MPDSongModel::songs() const {
	return m_visible;
}

MPDSongList MPDSongModel::songs(const QModelIndex &index) const {
	QModelIndexList indexes;
	indexes.append(index);
	return songs(indexes);
}

MPDSongList MPDSongModel::songs(const QModelIndexList &indexes) const {
	MPDSongList songs;
	foreach (QModelIndex index, indexes) {
		MPDSong s = song(index);
		if (!s.isNull() && !songs.contains(s))
			songs << s;
	}
	return songs;
}

void MPDSongModel::filter() {
	if (m_filter.isEmpty()) {
		m_visible = m_all;
	} else {
		m_visible.clear();
		for (QListIterator<MPDSong> it(m_all); it.hasNext(); ) {
			MPDSong s = it.next();
			if (m_filter.isEmpty() || s.contains(m_filter))
				m_visible << s;
		}
	}
	reset();
}

void MPDSongModel::sort(int column, Qt::SortOrder order) {
	Q_ASSERT(m_header);
	if (column < 0 || column >= m_header->columns().size())
		return;

	m_all.sort(m_header->columns().at(column), order);
	filter();
}

// DND
QStringList MPDSongModel::mimeTypes() const {
	return QStringList() << "qmpdclient/song";
}

QMimeData *MPDSongModel::mimeData(const QModelIndexList &indexes) const {
	if (m_dragDisabled)
		return 0;
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);
	foreach (MPDSong song, songs(indexes)) {
		stream << song;
	}

	QMimeData *mimeData = new QMimeData;
	mimeData->setData("qmpdclient/song", encodedData);
	return mimeData;
}
