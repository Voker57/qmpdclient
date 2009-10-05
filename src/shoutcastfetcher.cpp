#include "shoutcastfetcher.h"
#include "shoutcaststation.h"
#include <QIODevice>
#include <QXmlQuery>
#include <QByteArray>
#include <QBuffer>
#include <QUrl>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

namespace
{
const int maxSize = 1000000;
}

ShoutcastFetcher::ShoutcastFetcher(QObject * parent)
: QObject(parent), m_networkManager(new QNetworkAccessManager(this))
{
	connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(replyFinished(QNetworkReply*)));
}

void ShoutcastFetcher::fetch(const QString & keyWord, const QUrl & uri)
{
	if (m_pendingUrlAndKeyWords.contains(uri) && m_pendingUrlAndKeyWords[uri] != keyWord)
	{
		Q_ASSERT(!"Asked twice for same uri with different keywords");
		return;
	}
	m_pendingUrlAndKeyWords[uri] = keyWord;
	m_networkManager->get(QNetworkRequest(uri));
}

void ShoutcastFetcher::replyFinished(QNetworkReply * reply)
{
	QNetworkReply::NetworkError e = reply->error();
	if (e != QNetworkReply::NoError)
	{
		emit errorFetching(e, reply->errorString());
		qDebug() << e << reply->errorString();
	}
	else if (!m_pendingUrlAndKeyWords.contains(reply->url()))
	{
		genresAvailable(reply);
	}
	else
	{
		QString keyWord = m_pendingUrlAndKeyWords.take(reply->url());
		newStationsAvailable(reply, keyWord);
	}
}

void ShoutcastFetcher::genresAvailable(QIODevice * openInputDevice)
{
	// Using read() putting the content into a QBuffer to workaround
	// some strange hang if passing IO device directly into
	// QXmlQuery object.
	QByteArray content = openInputDevice->read(maxSize);
	QBuffer buf(&content);
	buf.open(QIODevice::ReadOnly);
	QXmlQuery q;
	q.bindVariable("glist", &buf);
	q.setQuery("for $i in doc($glist)/genrelist/genre/@name return string($i)");
	m_success = q.evaluateTo(&m_genres);
	emit genresAvailable();
}

void ShoutcastFetcher::newStationsAvailable(QIODevice * openInputDevice, const QString & keyWord)
{
	// Using read() putting the content into a QBuffer to workaround
	// some strange hang if passing IO device directly into
	// QXmlQuery object.
	QByteArray content = openInputDevice->read(maxSize);
	QBuffer buf(&content);
	buf.open(QIODevice::ReadOnly);
	QXmlQuery q;
	q.bindVariable("stations", &buf);
	q.setQuery("for $i in doc($stations)/stationlist/station " \
			   "let $tunein := doc($stations)/stationlist/tunein/@base " \
			   "return (string($i/@name), string($i/@id), string($i/@br), string($i/@genre)," \
			   "        string($i/@lc), string($i/@mt), string($i/@ct), string($tunein))");
	QStringList strings;
	q.evaluateTo(&strings);
	ShoutcastStationList & sl = m_keywordStationMapping[keyWord];
	for (QStringList::const_iterator iter = strings.constBegin(); iter != strings.constEnd(); iter += 8)
	{
		ShoutcastStation s(*iter, (*(iter + 1)).toInt(), (*(iter + 2)).toInt(),
						   *(iter + 3), (*(iter + 4)).toInt(), *(iter + 5), *(iter + 6), *(iter + 7));
		sl.append(s);
	}
	emit newStationsAvailable(keyWord);
}

QStringList ShoutcastFetcher::genres() const
{
	return m_genres;
}

bool ShoutcastFetcher::hasStationsForKeyword(const QString & key) const
{
	return m_keywordStationMapping.contains(key);
}

ShoutcastStationList ShoutcastFetcher::stationsForKeyword(const QString & key) const
{
	Q_ASSERT(hasStationsForKeyword(key));
	return m_keywordStationMapping[key];
}
