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
#include "mpdconnection.h"
#include "reconnect.h"
#include <QTimer>

Reconnect::Reconnect(QObject *parent) : QObject(parent),
		m_reconnectTimer(0) {
	setObjectName("reconnect");
	connect(MPDConnection::instance(), SIGNAL(connected(const ServerInfo &)), this, SLOT(connected(const ServerInfo &)));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(disconnected(const QString &)));
}

Reconnect::~Reconnect() {
	if (m_reconnectTimer)
		delete m_reconnectTimer;
}

void Reconnect::connected(const ServerInfo &si) {
	m_server = si;
	// We regained connection, delete timer
	if (m_reconnectTimer)
		delete m_reconnectTimer;
	m_reconnectTimer = 0;
}

void Reconnect::disconnected(const QString &error) {
	if (error.isEmpty() || !Config::instance()->reconnect())
		return;
	// We lost connection involuntarily
	if (m_reconnectTimer)
		delete m_reconnectTimer;
	m_reconnectTimer = new QTimer;
	connect(m_reconnectTimer, SIGNAL(timeout()), this, SLOT(reconnect()));
	m_reconnectTimer->start(Config::instance()->reconnectTime() * 1000);
}

void Reconnect::reconnect() {
	MPDConnection::instance()->connectToMPD(m_server);
}
