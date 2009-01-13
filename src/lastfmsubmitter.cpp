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

#include "lastfmsubmitter.h"
#include "config.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QStringList>
#include <QCryptographicHash>
#include <QTimer>

#include <QDebug>

LastFmSubmitter::LastFmSubmitter(QObject * parent) : QObject(parent)
{
	m_session = "";
	m_npUrl = "";
	m_subUrl = "";
	m_state = State_Null;
	m_scrobbleTimer = new QTimer();
	m_scrobbleTimer->setSingleShot(true);
	m_netAccess = new QNetworkAccessManager(this);
	connect(m_netAccess, SIGNAL(finished(QNetworkReply *)), this, SLOT(gotNetReply(QNetworkReply *)));
	connect(m_scrobbleTimer, SIGNAL(timeout()), this, SLOT(stageCurrentTrack()));
}

void LastFmSubmitter::setSong(const MPDSong & s)
{
	if(m_currentSong != s)
	{
		m_currentSong = s;
		m_currentStarted = time(NULL);
		if(s.secs() > 30)
		{
			m_scrobbleTimer->setInterval((s.secs() < 480 ? s.secs()/2 : 240) * 1000);
			qDebug() << "starting scrobble timer" << m_scrobbleTimer->interval();
			m_scrobbleTimer->start();
		}
		if(!songQueue.isEmpty())
		{
			scrobbleSong(songQueue.head());
			songQueue.clear();
		}
		sendNowPlaying();
	}
}

void LastFmSubmitter::sendNowPlaying()
{
	// FIXME: sometimes np is lost
	if(m_state == State_Null)
		doHandshake();
	else
		scrobbleNp(m_currentSong);
}

void LastFmSubmitter::scrobbleNp(MPDSong & s)
{
	// kinda ugly code
	QString data = QString("s=%1&").arg(m_session);
	data += QString("a=%1&").arg(QString(QUrl::toPercentEncoding(s.artist())));
	data += QString("t=%1&").arg(QString(QUrl::toPercentEncoding(s.title())));
	data += QString("b=%1&").arg(QString(QUrl::toPercentEncoding(s.album())));
	data += QString("l=%1&").arg(s.secs());
	data += QString("n=%1").arg(QString(QUrl::toPercentEncoding(s.track())));
	qDebug() << data;
	m_netAccess->post(QNetworkRequest(QUrl(m_npUrl)), data.toAscii());
}

void LastFmSubmitter::stageCurrentTrack()
{
	qDebug() << "timer fired";
	songQueue.enqueue(m_currentSong);
}

void LastFmSubmitter::scrobbleSong(MPDSong & s)
{
	// this is even uglier, i'll better go get some sleep after it
	// TODO: make use of mass submission
	QString data = QString("s=%1&o[0]=P&r[0]=&m[0]=&").arg(m_session);
	data += QString("a[0]=%1&").arg(QString(QUrl::toPercentEncoding(s.artist())));
	data += QString("t[0]=%1&").arg(QString(QUrl::toPercentEncoding(s.title())));
	data += QString("b[0]=%1&").arg(QString(QUrl::toPercentEncoding(s.album())));
	data += QString("l[0]=%1&").arg(s.secs());
	data += QString("i[0]=%1&").arg(m_currentStarted);
	data += QString("n[0]=%1").arg(QString(QUrl::toPercentEncoding(s.track())));
	m_state=State_Scrobbling;
	qDebug() << data;
	m_netAccess->post(QNetworkRequest(QUrl(m_subUrl)), data.toAscii());
}

void LastFmSubmitter::ensureHandshaked()
{
	if(m_session.isEmpty())
		doHandshake();
}

void LastFmSubmitter::doHandshake()
{
	if(m_state == State_Handshake) return;
	QUrl hsUrl = QUrl("http://post.audioscrobbler.com/");
	hsUrl.addQueryItem("hs", "true");
	hsUrl.addQueryItem("p", "1.2.1");
	hsUrl.addQueryItem("c", "qmn");
	hsUrl.addQueryItem("v", "1.0.9");
	hsUrl.addQueryItem("u", Config::instance()->lastFmUsername());
	hsUrl.addQueryItem("t", QString::number(time(NULL)));
	// Epic call
	hsUrl.addQueryItem("a",
		QCryptographicHash::hash(
			QCryptographicHash::hash(
				Config::instance()->lastFmPassword().toAscii(),
				QCryptographicHash::Md5).toHex() +
			QByteArray::number((uint)time(NULL)),
		QCryptographicHash::Md5).toHex()
	);
	qDebug() << hsUrl.toString();
	m_state = State_Handshake;
	m_netAccess->get(QNetworkRequest(hsUrl));
}

void LastFmSubmitter::gotNetReply(QNetworkReply * reply)
{
	QStringList data = QString(reply->readAll()).split("\n");
	// Is this is a handshake reply?
	if(data.size() >= 4 && m_state == State_Handshake)
	{
		m_session=data[1];
		m_npUrl=data[2];
		m_subUrl=data[3];
		m_state=State_Idle;
	}
	// Ok... maybe we were scrobbling something?
	else if(m_state==State_Scrobbling)
	{
		// TODO: Add tracking stuff there
		m_state=State_Idle;
	} // Was i bad player and now there's bad session?
	else if(data.size()>0)
	{
		if(data[0] == "BADSESSION")
		{
			m_state = State_Null;
			doHandshake();
		}
	}
	// What are you talking about then?
	qDebug() << "Reply:" << data;
}
