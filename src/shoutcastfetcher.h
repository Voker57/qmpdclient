#ifndef SHOUCASTFETCHER_H_
#define SHOUCASTFETCHER_H_

#include "shoutcaststation.h"
#include <QStringList>
#include <QMap>
#include <QSet>
#include <QUrl>

class ShoutcastFetcher : public QObject {
	Q_OBJECT
public:
	ShoutcastFetcher(QObject * parent = 0);
	QStringList genres() const;
	ShoutcastStationList stationsForKeyword(const QString & keyWord) const;
	bool hasStationsForKeyword(const QString & keyWord) const;
	void fetch(const QString & keyWord, const QUrl & uri);
public slots:
	void genresAvailable(QIODevice * openInputDevice);
	void newStationsAvailable(QIODevice * openInputDevice, const QString & keyword);
private:
	QStringList m_genres;
	QMap<QString, ShoutcastStationList> m_keywordStationMapping;
	QMap<QUrl, QString> m_pendingUrlAndKeyWords;
	bool m_success;
};

#endif /* SHOUCASTFETCHER_H_ */
