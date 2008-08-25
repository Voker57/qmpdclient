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

#ifndef MPDSONGMODEL_H
#define MPDSONGMODEL_H

#include "abstractmodel.h"
#include "mpdsonglist.h"
#include <QAbstractTableModel>
#include <QRegExp>

class HeaderView;

class MPDSongModel : public QAbstractTableModel, public AbstractModel {
public:
	MPDSongModel(QObject *, HeaderView *, const MPDSongList & = MPDSongList());
	int columnCount(const QModelIndex & = QModelIndex()) const;
	int rowCount(const QModelIndex & = QModelIndex()) const;
	QVariant data(const QModelIndex &, int) const;
	QVariant headerData(int, Qt::Orientation, int = Qt::DisplayRole) const;
	Qt::ItemFlags flags(const QModelIndex &) const;

	virtual void setFilter(const QString &);
	void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);

	void setSongs(const MPDSongList &);
	MPDSongList songs() const;
	MPDSongList songs(const QModelIndexList &) const;
	MPDSongList songs(const QModelIndex &) const;

	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &) const;

protected:
	virtual void filter();
	MPDSong song(const QModelIndex &) const;

	HeaderView *m_header;
	MPDSongList m_all, m_visible;
	QRegExp m_filter;
};
#endif
