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

#include "serverinfo.h"

class ServerInfoPrivate : public QSharedData {
public:
	QString name, address, password;
	int port;
	ServerInfoPrivate(const QString &n, const QString &a = "127.0.0.1", int p = 6600, const QString &w = QString()) :
			name(n),
			address(a),
			password(w),
			port(p) {}

};

ServerInfo::ServerInfo() : d(0) {}
ServerInfo::ServerInfo(const QString &n, const QString &a, int p, const QString &w) : d(new ServerInfoPrivate(n, a, p, w)) {}
ServerInfo::ServerInfo(const ServerInfo &other) : d(other.d) {}
ServerInfo::~ServerInfo() {}

bool ServerInfo::isNull() const {
	return d == NULL;
}

QString ServerInfo::address() const {
	Q_ASSERT(d);
	return d->address;
}

void ServerInfo::setAddress(const QString &a) {
	Q_ASSERT(d);
	d->address = a;
}

QString ServerInfo::name() const {
	Q_ASSERT(d);
	return d->name;
}

void ServerInfo::setName(const QString &n) {
	Q_ASSERT(d);
	d->name = n;
}

QString ServerInfo::password() const {
	Q_ASSERT(d);
	return d->password;
}

void ServerInfo::setPassword(const QString &p) {
	Q_ASSERT(d);
	d->password = p;
}

int ServerInfo::port() const {
	Q_ASSERT(d);
	return d->port;
}
	
void ServerInfo::setPort(int p) {
	Q_ASSERT(d);
	d->port = p;
}

bool ServerInfo::operator==(const ServerInfo &o) const {
	return o.port() == port() && o.address() == address() && o.password() == password();
}

ServerInfo &ServerInfo::operator=(const ServerInfo &other) {
	d = other.d;
	return *this;
}
