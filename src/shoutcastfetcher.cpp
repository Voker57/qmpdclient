#include "shoutcastfetcher.h"
#include "shoutcaststation.h"
#include <QIODevice>
#include <QXmlQuery>
#include <QByteArray>
#include <QBuffer>
#include <QUrl>
#include <QDebug>

namespace
{
const int maxSize = 1000000;
}

ShoutcastFetcher::ShoutcastFetcher(QObject * parent)
: QObject(parent)
{
}

void ShoutcastFetcher::fetch(const QString & keyWord, const QUrl & uri)
{
	if (m_pendingUrlAndKeyWords.contains(uri) && m_pendingUrlAndKeyWords[uri] != keyWord)
	{
		Q_ASSERT(!"Asked twice for same uri with different keywords");
		return;
	}
	m_pendingUrlAndKeyWords[uri] = keyWord;
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
}

void ShoutcastFetcher::newStationsAvailable(QIODevice * openInputDevice, const QString & keyword)
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
	ShoutcastStationList & sl = m_keywordStationMapping[keyword];
	for (QStringList::const_iterator iter = strings.constBegin(); iter != strings.constEnd(); iter += 8)
	{
		ShoutcastStation s(*iter, (*(iter + 1)).toInt(), (*(iter + 2)).toInt(),
						   *(iter + 3), (*(iter + 4)).toInt(), *(iter + 5), *(iter + 6), *(iter + 7));
		sl.append(s);
	}
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
