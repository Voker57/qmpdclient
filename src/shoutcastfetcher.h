#ifndef SHOUCASTFETCHER_H_
#define SHOUCASTFETCHER_H_

#include "shoutcaststation.h"
#include <QStringList>
#include <QMap>
#include <QSet>
#include <QUrl>
#include <QNetworkReply>
class QNetworkAccessManager;

class ShoutcastFetcher : public QObject {
	Q_OBJECT
public:
	ShoutcastFetcher(QObject * parent = 0);
	QStringList genres() const;
	ShoutcastStationList stationsForKeyword(const QString & keyWord) const;
	bool hasStationsForKeyword(const QString & keyWord) const;
	void fetchStations(const QString & keyWord, const QUrl & uri);
	void fetchGenres(const QUrl & uri);

signals:
	void genresAvailable();
	void newStationsAvailable(const QString & keyWord);
	void errorFetching(QNetworkReply::NetworkError error, const QString & errorString);

public slots:
	void genresAvailable(QIODevice * openInputDevice);
	void newStationsAvailable(QIODevice * openInputDevice, const QString & keyword);
private slots:
	void replyFinished(QNetworkReply * reply);
private:
	QStringList m_genres;
	QMap<QString, ShoutcastStationList> m_keywordStationMapping;
	QMap<QUrl, QString> m_pendingUrlAndKeyWords;
	bool m_success;
	QNetworkAccessManager * m_networkManager;
};

#endif /* SHOUCASTFETCHER_H_ */
