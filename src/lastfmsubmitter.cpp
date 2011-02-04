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
#include "mpd.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QStringList>
#include <QCryptographicHash>
#include <QTimer>
#include <QFile>
#include <QDir>

#include <QDebug>

LastFmSubmitter::LastFmSubmitter(QObject * parent) : QObject(parent) {
	m_npPending = false;
	m_awaitingHS = false;
	m_awaitingScrob = false;	
	m_failed = 0;
	m_session = "";
	m_npUrl = ""; // we will get it after handshake
	m_subUrl = ""; // we will get it after handshake
	m_hardFailTimer = new QTimer(this);
	m_hardFailTimer->setInterval(60*1000);
	m_hardFailTimer->setSingleShot(true);
	m_scrobbleTimer = new PausableTimer();
	m_scrobbleTimer->setInterval(9000000); // huge number to avoid scrobbling just started song start (rare case)
	m_scrobbleTimer->setSingleShot(true);
	m_npTimer = new PausableTimer();
	m_npTimer->setSingleShot(true);
	m_npTimer->setInterval(5000);
	m_scrobbleRetryTimer = new QTimer(this);
	m_scrobbleRetryTimer->setSingleShot(true);
	m_scrobbleRetryTimer->setInterval(10000);
	m_netAccess = new QNetworkAccessManager(this);
	connect(m_netAccess, SIGNAL(finished(QNetworkReply *)), this, SLOT(gotNetReply(QNetworkReply *)));
	connect(m_scrobbleTimer, SIGNAL(timeout()), this, SLOT(scrobbleCurrent()));
	connect(m_scrobbleRetryTimer, SIGNAL(timeout()), this, SLOT(scrobbleQueued()));
	connect(m_npTimer, SIGNAL(timeout()), this, SLOT(sendNowPlaying()));
	connect(m_hardFailTimer, SIGNAL(timeout()), this, SLOT(doHandshake()));
	connect(MPD::instance(), SIGNAL(stateUpdated(bool)), this, SLOT(mpdStateUpdated(bool)));
	createScrobblerCacheFileIfRequired();
	readScrobblerCache();
	if (!m_songQueue.isEmpty()) {
		scrobbleQueued();
	}
}

LastFmSubmitter::~LastFmSubmitter() {
	delete m_hardFailTimer;
	delete m_scrobbleTimer;
	delete m_npTimer;
	delete m_scrobbleRetryTimer;
	delete m_netAccess;
	writeScrobblerCache();
}

void LastFmSubmitter::setSong(const MPDSong & s) {
	m_npTimer->setInterval(5000);
	m_scrobbleTimer->setInterval(s.secs() < 480 ? s.secs()*Config::instance()->lastFmScrobblerTimer()*10 : 240000);
	if (m_currentSong != s) {
		m_currentSong = s;
		if (MPD::instance()->isPlaying()) {
			if (s.type() == MPDSong::PLAYLISTSTREAM) {
				m_scrobbleTimer->setInterval(60*1000); // How else should i handle _stream_?
				// qDebug() << "starting scrobble timer" << m_scrobbleTimer->interval();
				mpdStateUpdated(true);
			}
			else if (s.secs() > 30) {
				mpdStateUpdated(true);
			}
		}
	}
}

void LastFmSubmitter::sendNowPlaying() {
	m_npPending = true;
	if (ensureHandshaked()) {
		scrobbleNp(m_currentSong);
		m_npPending = false;
	}
}

void LastFmSubmitter::scrobbleNp(MPDSong & s) {
	// kinda ugly code
	QString data = QString("s=%1&").arg(m_session);
	data += QString("a=%1&").arg(QString(QUrl::toPercentEncoding(s.artist())));
	data += QString("t=%1&").arg(QString(QUrl::toPercentEncoding(s.title())));
	data += QString("b=%1&").arg(QString(QUrl::toPercentEncoding(s.album())));
	data += QString("l=%1&").arg(s.secs() >0 ? QString::number(s.secs()) : "100");
	data += QString("n=%1").arg(QString(QUrl::toPercentEncoding(s.track())));
	//qDebug() << data;
	m_netAccess->post(QNetworkRequest(QUrl(m_npUrl)), data.toAscii());
}

void LastFmSubmitter::scrobbleCurrent() {
	m_songQueue.enqueue(QPair<MPDSong, int>(m_currentSong, m_currentStarted));
	emit infoMsg(tr("Will scrobble this track."));
	scrobbleQueued();
}

void LastFmSubmitter::scrobbleQueued() {
	if (!ensureHandshaked() || m_awaitingScrob) {
		if (!m_scrobbleRetryTimer->isActive())
			m_scrobbleRetryTimer->start();
		return;
	}

	QString data = QString("s=%1&").arg(m_session);
	int i = 0;
	emit infoMsg(tr("Scrobbling %1 songs...").arg(m_songQueue.size()));
	//qDebug() << "trying scrobble "<< m_songQueue.size() << " songs";
	while(!m_songQueue.isEmpty())
	{
		QPair<MPDSong, int> sPair = m_songQueue.dequeue();
		data += QString("r[%2]=&m[%2]=&a[%2]=%1&").arg(QString(QUrl::toPercentEncoding(sPair.first.artist())), QString::number(i));
		data += QString("o[%2]=%1&").arg(
			(
		(sPair.first.type() == MPDSong::STREAM) || (sPair.first.type() == MPDSong::PLAYLISTSTREAM)) ? "E" : "P",
			QString::number(i)
			);
		data += QString("t[%2]=%1&").arg(QString(QUrl::toPercentEncoding(sPair.first.title())), QString::number(i));
		data += QString("b[%2]=%1&").arg(QString(QUrl::toPercentEncoding(sPair.first.album())), QString::number(i));
		data += QString("l[%2]=%1&").arg(sPair.first.secs() >0 ? QString::number(sPair.first.secs()) : "", QString::number(i));
		data += QString("i[%2]=%1&").arg(QString::number(sPair.second), QString::number(i));
		data += QString("n[%2]=%1&").arg(QString(QUrl::toPercentEncoding(sPair.first.track())), QString::number(i));
		m_lastScrobbledSongs.enqueue(sPair);
		++i;
	}
	if (i>0) {
		//qDebug() << "sending scrobble to " << m_subUrl.toAscii();
		//qDebug() << "data: " << data.toAscii();
		m_netAccess->post(QNetworkRequest(QUrl(m_subUrl)), data.toAscii());
		m_awaitingScrob = true;
	}
}

bool LastFmSubmitter::ensureHandshaked() {
	if(!m_session.isEmpty())
		return true;
	doHandshake();
	return false;
}

QByteArray LastFmSubmitter::getPasswordHash() {
	QByteArray passwordHash;
	if (Config::instance()->lastFmHashedPassword())
		passwordHash = Config::instance()->lastFmPassword().toAscii();
	else
		passwordHash = QCryptographicHash::hash(
			Config::instance()->lastFmPassword().toAscii(),
			QCryptographicHash::Md5).toHex();

	//accomplish it with current time
	passwordHash = QCryptographicHash::hash(
			passwordHash + QByteArray::number((uint)time(NULL)),
			QCryptographicHash::Md5);

	return passwordHash;
}

QUrl LastFmSubmitter::handshakeUrl() {
	QUrl url = QUrl();
	url.setScheme("http");
	url.setHost(Config::instance()->lastFmServer());
	url.setPath("/");
	return url;
}

void LastFmSubmitter::doHandshake() {
	if (m_hardFailTimer->isActive() || m_awaitingHS) {
		//qDebug("handshaking delayed");
		return;
	}
	QUrl hsUrl = handshakeUrl();
	hsUrl.addQueryItem("hs", "true");
	hsUrl.addQueryItem("p", "1.2.1");
	hsUrl.addQueryItem("c", "qmn");
	hsUrl.addQueryItem("v", VERSION);
	hsUrl.addQueryItem("u", Config::instance()->lastFmUsername());
	hsUrl.addQueryItem("t", QString::number(time(NULL)));
	hsUrl.addQueryItem("a", getPasswordHash().toHex());

	m_netAccess->get(QNetworkRequest(hsUrl));
	//qDebug() << "handshake sent to " << hsUrl.toString();

	m_awaitingHS = true;
}

void LastFmSubmitter::gotNetReply(QNetworkReply * reply) {
	//qDebug("gotNetReply...");

	if (reply->error() != QNetworkReply::NoError)
	{
		//qDebug() << "Error:" << reply->errorString();
		return;
	}

	QStringList data = QString(reply->readAll()).split("\n");
	if(data.size()==0)
		return;
	QUrl reqUrl = reply->url();
	reqUrl.setQueryItems(QList<QPair<QString, QString> >());
	//qDebug( (QString("reply from ")+reqUrl.toString()).toAscii().data());

	bool handled= false;
	// Is this is a handshake reply?
	if(reqUrl==handshakeUrl())
	{
		m_awaitingHS = false;
		if(data.size() >= 4 && data[0]=="OK")
		{
			handled = true;
			m_session=data[1];
			m_npUrl=data[2];
			m_subUrl=data[3];
			//qDebug( (QString("hsake result: npurl: ")+m_npUrl+" suburl: "+m_subUrl).toAscii().data());
			if(m_npPending)
				sendNowPlaying();
		} else if(data[0]=="BADAUTH")
		{
			handled = true;
			emit infoMsg(tr("Last.Fm authentication failed: check your credentials"));
		} else if(data[0]=="BADTIME")
		{
			handled = true;
			emit infoMsg(tr("Cannot submit to Last.Fm: system clock is skewed"));
		}
	}
	else
	// Ok... maybe we were scrobbling something?
	if (reqUrl.toString() == m_subUrl) {
		m_awaitingScrob = false;
		if (data[0] == "OK") {
			handled = true;
			m_lastScrobbledSongs.clear();
			emit infoMsg(tr("Successfully scrobbled"));
		}
		else {
			m_songQueue << m_lastScrobbledSongs;
			m_lastScrobbledSongs.clear();
		}

	}
	else if(reqUrl.toString() == m_npUrl && data[0] == "OK") {
		handled=true;
		emit infoMsg(tr("Now Playing sent"));
		m_npTimer->setInterval(5000); // refreshes the interval, because previous song could  be paused
	}
	// Was i bad player and now there's bad session?
	if(data[0] == "BADSESSION")
	{
		handled = true;
		m_session.clear();
		doHandshake();
	}
	if(data[0].startsWith("FAILED"))
	{
		QStringList dat = data[0].split(" ");
		if(dat.size() >1) emit infoMsg(tr("Last.Fm error: %1").arg(dat.join(" ")));
	}

	if(!handled)
	{
		m_failed++;
		//qDebug() << "Failed Reply:" << reqUrl.toString() << data;
	}
	else m_failed=0;

	if(m_failed > 2 && !m_hardFailTimer->isActive())
	{
		m_session.clear();
		m_hardFailTimer->setInterval((m_failed > 120 ? 120 : m_failed)*60*1000);
		m_hardFailTimer->start();
	}
}

void LastFmSubmitter::createScrobblerCacheFileIfRequired() {
	if (!QFile::exists(QDir::toNativeSeparators(QDir::homePath() + "/.config/QMPDClient/scrobbler.cache"))) {
		QFile scrobblerCacheFile(QDir::toNativeSeparators(QDir::homePath() + "/.config/QMPDClient/scrobbler.cache"));
		if (scrobblerCacheFile.open(QIODevice::WriteOnly)) {
			scrobblerCacheFile.close();
		}
	}
}

void LastFmSubmitter::readScrobblerCache() {
	QFile scrobblerCacheFile(QDir::toNativeSeparators(QDir::homePath() + "/.config/QMPDClient/scrobbler.cache"));
	if (scrobblerCacheFile.open(QIODevice::ReadOnly)) {
		QDataStream in(&scrobblerCacheFile);
		in >> m_songQueue;
		scrobblerCacheFile.resize(0);
		scrobblerCacheFile.close();
	}
}

void LastFmSubmitter::writeScrobblerCache() {
	bool sqEmpty = m_songQueue.isEmpty(), lssEmpty = m_lastScrobbledSongs.isEmpty();

	if (!lssEmpty || !sqEmpty) {
		QFile scrobblerCacheFile(QDir::toNativeSeparators(QDir::homePath() + "/.config/QMPDClient/scrobbler.cache"));
		if (scrobblerCacheFile.open(QIODevice::WriteOnly)) {
			QDataStream out(&scrobblerCacheFile);
			if (!lssEmpty) {
				out << m_lastScrobbledSongs;
			}
			if (!sqEmpty) {
				out << m_songQueue;
			}
			scrobblerCacheFile.close();
		}
	}
}

void LastFmSubmitter::mpdStateUpdated(bool b) {
	if (Config::instance()->submitSongsToLastFm()) {
		if (MPD::instance()->isPaused()) {
			m_scrobbleTimer->pause();
			m_npTimer->pause();
		}
		else if (b) {
			m_currentStarted = time(NULL);
			m_scrobbleTimer->start();
			m_npTimer->start();
		}
		else if (!b) {
			m_scrobbleTimer->stop();
			m_npTimer->stop();
			m_npTimer->setInterval(5000);
		}
	}
}
