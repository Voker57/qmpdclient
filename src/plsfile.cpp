#include "plsfile.h"
#include <QNetworkAccessManager>
#include <QRegExp>
//#include <QDebug>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QStringList>

namespace
{
const int maxSize = 100000;
}

PlsFile::PlsFile(const QUrl & url, QObject * parent) : QObject(parent), m_url(url) {
	QNetworkAccessManager * manager = new QNetworkAccessManager(this);
	connect(manager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(newDataAvailable(QNetworkReply*)));
	manager->get(QNetworkRequest(url));
	qRegisterMetaType<PlsFile>();
}

PlsFile::PlsFile(const PlsFile & rhs)
: m_urls(rhs.m_urls)
{
	qRegisterMetaType<PlsFile>();
}

PlsFile::PlsFile()
{
	qRegisterMetaType<PlsFile>();
}

QUrl PlsFile::url() const
{
	return m_url;
}

QList<QUrl> PlsFile::urls() const
{
	return m_urls;
}

void PlsFile::newDataAvailable(QNetworkReply * reply)
{
	QString plsContent(reply->read(maxSize));
	QRegExp re("File[0-9]+=([^\n\r]*)");
	int pos = 0;
	while ((pos = re.indexIn(plsContent, pos)) != -1) {
	     m_urls << QUrl(re.cap(1));
	     pos += re.matchedLength();
	}
	emit ready(this);
}
