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

#ifndef SERVERINFO_H
#define SERVERINFO_H

#include <QSharedData>
#include <QString>

class ServerInfoPrivate;

class ServerInfo {
public:
	ServerInfo();
	ServerInfo(const QString &, const QString & = "127.0.0.1", int = 6600, const QString & = QString());
	ServerInfo(const ServerInfo &);
	~ServerInfo();
	bool isNull() const;
	QString address() const;
	void setAddress(const QString &);
	QString name() const;
	void setName(const QString &);
	QString password() const;
	void setPassword(const QString &);
	int port() const;
	void setPort(int);
	bool operator==(const ServerInfo &) const;
	ServerInfo &operator=(const ServerInfo &);

private:
	QSharedDataPointer<ServerInfoPrivate> d;
};

#endif
