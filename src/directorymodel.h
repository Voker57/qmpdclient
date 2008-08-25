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

#ifndef DIRECTORYMODEL_H
#define DIRECTORYMODEL_H

#include <QAbstractItemModel>
#include "abstractmodel.h"
#include "mpddirectory.h"

class DirectoryModel : public QAbstractItemModel, public AbstractModel {
public:
	DirectoryModel(QObject *);
	int rowCount(const QModelIndex & = QModelIndex()) const;
	int columnCount(const QModelIndex & = QModelIndex()) const;
	QVariant data(const QModelIndex &, int) const;
	Qt::ItemFlags flags(const QModelIndex &) const;
	bool hasChildren(const QModelIndex & = QModelIndex()) const;
	QVariant headerData(int, Qt::Orientation, int = Qt::DisplayRole) const;
	QModelIndex index(int, int, const QModelIndex & = QModelIndex()) const;
	QModelIndex parent(const QModelIndex &) const;

	QModelIndex createIndex(int, int, const MPDDirectory &) const;
	QList<MPDDirectory> directories(const QModelIndexList &) const;
	MPDDirectory directory(const QModelIndex &) const;
	void setRoot(const MPDDirectory &);
	
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &) const;

private:
	MPDDirectory m_root;
	QString m_search;
};
#endif
