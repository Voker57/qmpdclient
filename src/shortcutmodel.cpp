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

#include "shortcutmodel.h"
#include "shortcuts.h"
#include <QAbstractButton>
#include <QShortcut>

ShortcutModel::ShortcutModel(QObject *parent) : QAbstractTableModel(parent) {
	setObjectName("shortcutmodel");
}

int ShortcutModel::columnCount(const QModelIndex &) const {
	return 2;
}

QVariant ShortcutModel::data(const QModelIndex &index, int role) const {
	if (role == Qt::DecorationRole && index.isValid() && index.column() == 0)
		return Shortcuts::instance()->decoration(Shortcuts::instance()->objects().at(index.row()));

	if ((role != Qt::DisplayRole && role != Qt::EditRole) || !index.isValid())
		return QVariant();

	QObject *object = Shortcuts::instance()->objects().at(index.row());
	if (index.column() == 0)
		return Shortcuts::instance()->description(object);
	else if (index.column() == 1)
		return Shortcuts::instance()->shortcut(object);

	return QVariant();
}

bool ShortcutModel::setData(const QModelIndex &idx, const QVariant &value, int role) {
	if (role != Qt::EditRole || !idx.isValid() || idx.column() != 1)
		return false;

	QObject *object = Shortcuts::instance()->objects().at(idx.row());
	QString newShortcut = value.toString();
	Shortcuts::instance()->setShortcut(object, newShortcut);

	emit dataChanged(index(idx.row(), 0), index(idx.row(), 1));
	return true;
}

Qt::ItemFlags ShortcutModel::flags(const QModelIndex &index) const {
	if (!index.isValid())
		return QAbstractTableModel::flags(index);
	if (index.column() == 1)
		return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
	return Qt::ItemIsEnabled;
}

QVariant ShortcutModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
		if (section == 0)
			return QObject::tr("Action");
		else if (section == 1)
			return QObject::tr("Shortcut");
	}
	return QVariant();
}

int ShortcutModel::rowCount(const QModelIndex &index) const {
	if (index.isValid()) // Valid index, meaning a server item. They have no children.
		return 0;
	return Shortcuts::instance()->objects().size();
}
