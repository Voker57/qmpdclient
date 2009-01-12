/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Håvard Tautra Knutsen <havtknut@tihlde.org>
 * Copyright (C) 2009 Voker57 <voker57@gmail.com>
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

#ifndef LASTFMSUBMITTER_H
#define LASTFMSUBMITTER_H

#include "mpdsong.h"

#include <QString>
#include <QQueue>
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;
class QTimer;

class LastFmSubmitter : public QObject
{
	Q_OBJECT
	enum {State_Null, State_Handshake, State_Idle, State_Scrobbling};
public:
	LastFmSubmitter(QObject * parent = 0);
	void setSong(const MPDSong & s);
protected:
	void doHandshake();
	void ensureHandshaked();
	void sendNowPlaying();
	void scrobbleNp(MPDSong & s);
	QString m_session;
	QString m_npUrl;
	QString m_subUrl;
	int m_state;
	QNetworkAccessManager * m_netAccess;
	QQueue<MPDSong> songQueue;
	MPDSong m_currentSong;
	QTimer * m_scrobbleTimer;
protected slots:
	void gotNetReply(QNetworkReply *);
};

#endif // LASTFMSUBMITTER_H
