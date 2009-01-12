#include "lastfmsubmitter.h"
#include "config.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QCryptographicHash>

#include <QDebug>

LastFmSubmitter::LastFmSubmitter(QObject * parent) : QObject(parent)
{
	m_session = "";
	m_npUrl = "";
	m_subUrl = "";
	m_netAccess = new QNetworkAccessManager(this);
	connect(m_netAccess, SIGNAL(finished(QNetworkReply *)), this, SLOT(gotNetReply(QNetworkReply *)));
}

void LastFmSubmitter::setSong(const MPDSong & s)
{
	Q_UNUSED(s);
	ensureHandshaked();
}

void LastFmSubmitter::ensureHandshaked()
{
	if(m_session.isEmpty())
		doHandshake();
}

void LastFmSubmitter::doHandshake()
{
	QUrl hsUrl = QUrl("http://post.audioscrobbler.com/");
	hsUrl.addQueryItem("hs", "true");
	hsUrl.addQueryItem("p", "1.2.1");
	// Until qmpdc-ne gets client ID
	hsUrl.addQueryItem("c", "tst");
	hsUrl.addQueryItem("v", "1.0");
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
	m_netAccess->get(QNetworkRequest(hsUrl));
}

void LastFmSubmitter::gotNetReply(QNetworkReply * reply)
{
	qDebug() << reply->readAll();
	// Is this is a handshake reply? GTFO otherwise

}
