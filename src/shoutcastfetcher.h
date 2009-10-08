#ifndef SHOUCASTFETCHER_H_
#define SHOUCASTFETCHER_H_

#include "shoutcaststation.h"
#include "plsfile.h"
#include <QStringList>
#include <QSharedPointer>
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
	QList<QUrl> playlistForStation(const ShoutcastStation & station) const;
	bool hasStationsForKeyword(const QString & keyWord) const;
	bool hasPlaylistsForStation(const ShoutcastStation & station) const;
	void fetchStations(const QString & keyWord, const QUrl & uri);
	void fetchGenres(const QUrl & uri);
	void fetchPlaylistsForStation(const ShoutcastStation & station);

signals:
	void genresAvailable();
	void newStationsAvailable(const QString & keyWord);
	void playlistAvailable(const ShoutcastStation & station);
	void errorFetching(QNetworkReply::NetworkError error, const QString & errorString);

public slots:
	void genresAvailable(QIODevice * openInputDevice);
	void newStationsAvailable(const QString & host,
			QIODevice * openInputDevice, const QString & keyword);
private slots:
	void replyFinished(QNetworkReply * reply);
	void playlistDownloaded(PlsFile * file);
private:
	QStringList m_genres;
	QMap<QString, ShoutcastStationList> m_keywordStationMapping;
	QMap<QUrl, QString> m_pendingUrlAndKeyWords;
	QMap<ShoutcastStation, QSharedPointer<PlsFile> > m_stationPlaylistMapping;
	QMap<QUrl, ShoutcastStation> m_pendingPlaylistUrlsForStation;
	bool m_success;
	QNetworkAccessManager * m_networkManager;
};

#endif /* SHOUCASTFETCHER_H_ */
