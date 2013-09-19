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

#include "config.h"
#include "servermodel.h"
#include "serverinfo.h"

ServerModel::ServerModel(QObject *parent) : QAbstractTableModel(parent),
		m_servers(Config::instance()->servers()) {
	setObjectName("servermodel");
}

int ServerModel::columnCount(const QModelIndex &) const {
	return 4;
}

QVariant ServerModel::data(const QModelIndex &index, int role) const {
	if ((role != Qt::DisplayRole && role != Qt::EditRole) || !index.isValid())
		return QVariant();

	ServerInfo si = m_servers.at(index.row());
	switch (index.column()) {
		case 0:
			return si.name();
		case 1:
			return si.address();
		case 2:
			return si.port();
		case 3:
			return role == Qt::EditRole ? "" : si.password().isEmpty() ? "" : "********";
	}
	return QVariant();
}

bool ServerModel::setData(const QModelIndex &idx, const QVariant &value, int role) {
	if (role != Qt::EditRole || !idx.isValid())
		return false;
	ServerInfo si = m_servers.at(idx.row());

	bool ok = false;
	switch (idx.column()) {
		case 0:
			si.setName(value.toString());
			ok = true;
			break;
		case 1:
			si.setAddress(value.toString());
			ok = true;
			break;
		case 2:
			si.setPort(value.toInt(&ok));
			break;
		case 3:
			si.setPassword(value.toString());
			ok = true;
			break;
	}

	if (ok) {
		m_servers.replace(idx.row(), si);
		Config::instance()->setServers(m_servers);
		emit dataChanged(index(idx.row(), 0), index(idx.row(), 3));
		return true;
	}

	return false;
}

Qt::ItemFlags ServerModel::flags(const QModelIndex &index) const {
	if (!index.isValid())
		return QAbstractTableModel::flags(index);
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable;
}

QVariant ServerModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role == Qt::DisplayRole && section < 4 && section > -1 && orientation == Qt::Horizontal) {
		switch (section) {
			case 0:
				return QObject::tr("Name");
			case 1:
				return QObject::tr("Address");
			case 2:
				return QObject::tr("Port");
			case 3:
				return QObject::tr("Password");
		}
	}
	return QVariant();
}

int ServerModel::rowCount(const QModelIndex &index) const {
	if (index.isValid()) // Valid index, meaning a server item. They have no children.
		return 0;
	return m_servers.size();
}

void ServerModel::addServer() {
	m_servers << ServerInfo("New server");
	Config::instance()->setServers(m_servers);
    beginResetModel();
    endResetModel();
}

int ServerModel::size() const {
	return m_servers.size();
}

void ServerModel::deleteServer(const QModelIndex &in) {
	if (!in.isValid())
		return;
	m_servers.removeAt(in.row());
	Config::instance()->setServers(m_servers);
    beginResetModel();
    endResetModel();
}

bool ServerModel::moveUp(const QModelIndex &idx) {
	if (!idx.isValid() || idx.row() - 1 < 0)
		return false;
	m_servers.swap(idx.row(), idx.row() - 1);
	Config::instance()->setServers(m_servers);
	emit dataChanged(index(idx.row() - 1, 0), index(idx.row(), 3));
	return true;
}

bool ServerModel::moveDown(const QModelIndex &idx) {
	if (!idx.isValid() || idx.row() + 1 >= m_servers.size())
		return false;
	m_servers.swap(idx.row(), idx.row() + 1);
	Config::instance()->setServers(m_servers);
	emit dataChanged(index(idx.row(), 0), index(idx.row() + 1, 3));
	return true;
}
