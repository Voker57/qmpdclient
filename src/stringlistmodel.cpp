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

#include "stringlistmodel.h"
#include "aafilter.h"
#include "config.h"
#include "stringlistview.h"
#include <QMimeData>

StringListModel::StringListModel(QObject *parent) : QAbstractListModel(parent),
		m_view(qobject_cast<StringListView*>(parent)),
		m_showAll(Config::instance()->showAll()) {
	setObjectName("stringlistmodel");
}

void StringListModel::setShowAll(bool a) {
	m_showAll = a;
	reset();
}

QVariant StringListModel::data(const QModelIndex &index, int role) const {
	if (!index.isValid() || index.row() < 0 || index.row() > m_list.size())
		return QVariant();

	if (role == Qt::DisplayRole) {
		if (!m_showAll) {
			if (m_list.at(index.row()).isEmpty())
				return QObject::tr("Not tagged", "This is the second item in the artist and album views, meaning \"Songs belonging to no artist or no albums\"");
			return m_list.at(index.row());
		}

		if (index.row() == 0)
			return QObject::tr("All", "This is the first item in the artist and album views, meaning \"All artists\" or \"All albums\"");
		if (m_list.at(index.row() - 1).isEmpty())
			return QObject::tr("Not tagged", "This is the second item in the artist and album views, meaning \"Songs belonging to no artist or no albums\"");
		return m_list.at(index.row() - 1);
	} else if (role == Qt::FontRole) {
		if ((m_showAll && (index.row() == 0 || m_list.at(index.row() - 1).isEmpty()))
				|| (!m_showAll && m_list.at(index.row()).isEmpty())) {
			QFont font = Config::instance()->font();
			font.setBold(true);
			return font;
		}
	}
	return QVariant();
}

Qt::ItemFlags StringListModel::flags(const QModelIndex &index) const {
	if (!index.isValid())
		return QAbstractItemModel::flags(index);
	return QAbstractItemModel::flags(index) | Qt::ItemIsDragEnabled;
}

QString StringListModel::string(const QModelIndex &index) const {
	if (index.isValid()) {
		if (!m_showAll) {
			if (m_list.at(index.row()).isEmpty())
				return QString("");
			return data(index, Qt::DisplayRole).toString();
		}
		// If "All" is shown
		if (index.row() == 0)
			return QString();
		if (m_list.at(index.row() - 1).isEmpty())
			return QString("");
		return data(index, Qt::DisplayRole).toString();
	}
	return QString();
}

QStringList StringListModel::stringList(const QModelIndexList &indexes) const {
	QStringList ret;
	foreach(QModelIndex index, indexes) {
		ret << string(index);
	}
	return ret;
}

QStringList StringListModel::stringList() const {
	return m_list;
}

void StringListModel::setStringList(const QStringList &strings) {
	m_list = strings;
	reset();
}

int StringListModel::rowCount(const QModelIndex &index) const {
	if (index.isValid()) // Valid index means no children.
		return 0;
	if (m_showAll) // If "All" is shown
		return m_list.size() + 1;
	return m_list.size();
}

QStringList StringListModel::mimeTypes() const {
	return QStringList() << "qmpdclient/aa";
}

QMimeData *StringListModel::mimeData(const QModelIndexList &) const {
	if (m_dragDisabled)
		return 0;
	Q_ASSERT(m_view);
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);
	stream << m_view->aaFilter();
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("qmpdclient/aa", encodedData);
	return mimeData;
}
