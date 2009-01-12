#ifndef LASTFMSUBMITTER_H
#define LASTFMSUBMITTER_H

#include "mpdsong.h"

#include <QString>
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class LastFmSubmitter : public QObject
{
	Q_OBJECT
public:
	LastFmSubmitter(QObject * parent = 0);
	void setSong(const MPDSong & s);
	void doHandshake();
	void ensureHandshaked();
protected:
	QString m_session;
	QString m_npUrl;
	QString m_subUrl;
	QNetworkAccessManager * m_netAccess;
protected slots:
	void gotNetReply(QNetworkReply *);
};

#endif // LASTFMSUBMITTER_H
