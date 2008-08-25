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

#ifndef MPDCONNECTION_H
#define MPDCONNECTION_H

#include <QObject>

class MPDEntities;
class MPDOutput;
class MPDStats;
class MPDStatus;
class ServerInfo;
struct MPDConnectionPrivate;
struct _mpd_Connection;

class MPDConnection : public QObject {
	Q_OBJECT
public:
	static MPDConnection *instance();
	~MPDConnection();
	bool isConnected() const;
	ServerInfo server() const;
	int version() const;

	QStringList albums() const;
	QStringList artists() const;
	MPDEntities entities() const;
	bool finishCommand();
	QList<MPDOutput> outputs();
	MPDStats stats();
	MPDStatus status();
	void setCaller(const QString &, const QString &);
	_mpd_Connection *connection() const;

public slots:
	void connectToMPD(const ServerInfo &);
	void disconnectFromMPD(const QString & = QString());

signals:
	void connected(const ServerInfo &) const;
	void disconnected(const QString &error) const;

private:
	MPDConnection();

	MPDConnectionPrivate *d;
	static MPDConnection *m_instance;
};

#define mpd_caller(A, B) MPDConnection::instance()->setCaller(A, B)
#define mpd_cleanup() MPDConnection::instance()->finishCommand()
#define mpd_beginList() mpd_sendCommandListBegin(MPDConnection::instance()->connection())
#define mpd_endList() mpd_sendCommandListEnd(MPDConnection::instance()->connection())
#define mpd_call(CALLER, CMD, ...) \
	do { \
		MPDConnection::instance()->setCaller(#CALLER, QString("mpd_send%1Command").arg(#CMD)); \
		mpd_send ## CMD ## Command(MPDConnection::instance()->connection(), ##__VA_ARGS__); \
} while (0)

#endif
