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
#include "libmpdclient.h"
#include "mpdconnection.h"
#include "mpdentities.h"
#include "mpdoutput.h"
#include "mpdstats.h"
#include "mpdstatus.h"
#include "serverinfo.h"

#define ASSERT Q_ASSERT(d); Q_ASSERT(d->connection)

struct MPDConnectionPrivate {
	bool connected;
	mpd_Connection *connection;
	ServerInfo server;
	int version;
	QString caller, command;
	MPDConnectionPrivate() :
			connected(false),
			connection(0),
			version(0) {}
};

MPDConnection *MPDConnection::m_instance = 0;

MPDConnection::MPDConnection() : d(new MPDConnectionPrivate) {
	setObjectName("MPDConnection");
}

MPDConnection *MPDConnection::instance() {
	if (!m_instance)
		m_instance = new MPDConnection;
	return m_instance;
}

MPDConnection::~MPDConnection() {
	Q_ASSERT(d);
	delete d;
}

bool MPDConnection::isConnected() const {
	return d->connection && d->connected;
}

mpd_Connection *MPDConnection::connection() const {
	ASSERT;
	return d->connection;
}

void MPDConnection::connectToMPD(const ServerInfo &server) {
	if (d->connected) {
		if (d->server == server) // Trying to reconncet to same server, ignore
			return;
		// Trying to connect to another server. disconnect, then connect to it.
		disconnectFromMPD();
	}

	setCaller("MPDConnection::connectToMPD", "mpd_newConnection");
	d->connection = mpd_newConnection(server.address().toUtf8(), server.port(), Config::instance()->timeoutTime());
	if (!finishCommand()) {
		disconnectFromMPD(tr("Could not connect to server %1:%2").arg(server.address()).arg(server.port()));
		return;
	}

	if (!server.password().isEmpty()) {
		mpd_call(MPDConnection::connectToMPD, Password, server.password().toUtf8());
		if (!finishCommand()) {
			disconnectFromMPD(tr("Authentication failed"));
			return;
		}
	}

	d->connected = true;
	d->server = server;
	emit connected(server);
}

void MPDConnection::disconnectFromMPD(const QString &reason) {
	Q_ASSERT(d);
	d->connected = false;
	if (d->connection)
		mpd_closeConnection(d->connection);
	d->connection = 0;
	d->server = ServerInfo();
	emit disconnected(reason);
}

ServerInfo MPDConnection::server() const {
	return isConnected() ? d->server : ServerInfo();
}

int MPDConnection::version() const {
	return d->connection ? d->connection->version[1] : 0;
}

void MPDConnection::setCaller(const QString &caller, const QString &cmd) {
	d->caller = caller;
	d->command = cmd;
}

QStringList MPDConnection::albums() const {
	ASSERT;
	QStringList ret;
	for (char *a; (a = mpd_getNextAlbum(d->connection)) != NULL; ) {
		ret << QString::fromUtf8(a);
	}
	return ret;
}

QStringList MPDConnection::artists() const {
	ASSERT;
	QStringList ret;
	for (char *a; (a = mpd_getNextArtist(d->connection)) != NULL; ) {
		ret << QString::fromUtf8(a);
	}
	return ret;
}

MPDEntities MPDConnection::entities() const {
	ASSERT;
	MPDEntities ret;

	for (mpd_InfoEntity *entity; (entity = mpd_getNextInfoEntity(d->connection)) != NULL; ) {
		if (entity->type == MPD_INFO_ENTITY_TYPE_SONG) {
			ret.appendSong(MPDSong(entity));
		} else if (entity->type == MPD_INFO_ENTITY_TYPE_DIRECTORY) {
			ret.appendDirectory(QString::fromUtf8(entity->info.directory->path));
		} else if (entity->type == MPD_INFO_ENTITY_TYPE_PLAYLISTFILE) {
			ret.appendPlaylist(MPDSong(entity));
		} else {
			qWarning("MPDConnection::availableEntities() Unknown entity type: %d", entity->type);
		}
		mpd_freeInfoEntity(entity);
	}

	return ret;
}

MPDStats MPDConnection::stats() {
	if (!isConnected())
		return MPDStats();

	Q_ASSERT(d->connection);
	mpd_call(MPDConnection::stats, Stats);
	mpd_Stats *stats = mpd_getStats(d->connection);
	if (!finishCommand() || !stats)
		return MPDStats();

	MPDStats ret(stats);
	mpd_freeStats(stats);
	return ret;
}

MPDStatus MPDConnection::status() {
	if (!isConnected())
		return MPDStatus();

	Q_ASSERT(d->connection);
	mpd_call(MPDConnection::status, Status);
	mpd_Status *status = mpd_getStatus(d->connection);
	if (!finishCommand() || !status)
		return MPDStatus();

	MPDStatus ret(status);
	mpd_freeStatus(status);
	return ret;
}

QList<MPDOutput> MPDConnection::outputs() {
	QList<MPDOutput> outputs;
	if (!isConnected() || version() < 12)
		return outputs;

	Q_ASSERT(d->connection);
	mpd_call(MPDConnection::outputs, Outputs);
	for (mpd_OutputEntity *output; (output = mpd_getNextOutput(d->connection)) != NULL; ) {
		outputs << MPDOutput(output);
		mpd_freeOutputElement(output);
	}
	if (!finishCommand())
		outputs.clear();

	return outputs;
}

bool MPDConnection::finishCommand() {
	if (d->connection->error)
	 {
		QString errormsg = QString::fromUtf8(d->connection->errorStr).replace("\n", "");
		switch (d->connection->error) {
			case MPD_ERROR_TIMEOUT:
			case MPD_ERROR_SYSTEM:
			case MPD_ERROR_UNKHOST:
			case MPD_ERROR_CONNPORT:
			case MPD_ERROR_NOTMPD:
			case MPD_ERROR_NORESPONSE:
			case MPD_ERROR_SENDING:
			case MPD_ERROR_CONNCLOSED:
				// These are the serious errors. Set errormsg.
				qWarning("Error: `%s (error code %d). Disconnecting.", qPrintable(errormsg), d->connection->error);
				disconnectFromMPD(errormsg);
				return false;
			default:
				// Just warnings. We ignore them.
				qWarning("Warning: `%s (error code %d). Ignoring.", qPrintable(errormsg), d->connection->error);
		}
		qWarning("Problem occured while executing command: %s, called from: %s", qPrintable(d->command), qPrintable(d->caller));
		d->caller = d->command = QString();
		mpd_clearError(d->connection);
		return false;
	} else
		mpd_finishCommand(d->connection);
	// Clear error code, just in case.
	mpd_clearError(d->connection);
	return true;
}
