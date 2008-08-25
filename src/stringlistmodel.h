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

#ifndef STRINGLISTMODEL_H
#define STRINGLISTMODEL_H

#include <QAbstractListModel>
#include <QStringList>
#include "abstractmodel.h"

class StringListView;

class StringListModel : public QAbstractListModel, public AbstractModel {
public:
	StringListModel(QObject *);
	QVariant data(const QModelIndex &, int) const;
	Qt::ItemFlags flags(const QModelIndex &) const;
	QString string(const QModelIndex &) const;
	QStringList stringList(const QModelIndexList &) const;
	QStringList stringList() const;
	void setStringList(const QStringList &);
	void setShowAll(bool);
	int rowCount(const QModelIndex & = QModelIndex()) const;
	QStringList mimeTypes() const;
	QMimeData *mimeData(const QModelIndexList &) const;

private:
	QStringList m_list;
	StringListView *m_view;
	bool m_showAll;
};
#endif
