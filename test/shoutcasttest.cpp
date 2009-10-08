//#include <shoutcastmodel.h>
//#include <shoutcastview.h>
#include "shoutcastfetcher.h"
#include "shoutcaststation.h"
#include "plsfile.h"
#include <QTest>
#include <QFile>
#include <QStringList>
#include <QSignalSpy>

class ShoutcastTest : public QObject {
	Q_OBJECT
private slots:
	void requireGenreParsingToWork();
	void requireStationListParsingToWork();
	void requireQueryingAStationURIDownloadsTheStationList();
	void requireThatFetchingAGenreURIResultsInAGenreListDownload();
	void requireThatURLsGetScrapedFromPlaylistFilesAfterDownload();
	void requireThatFetchingAPlaylistForAStationResultsInThePlaylistBeingDownloaded();
};

void ShoutcastTest::requireGenreParsingToWork() {
	QFile file(":genres.xml");
	file.open(QIODevice::ReadOnly);
	ShoutcastFetcher f;
	f.genresAvailable(&file);
	QStringList expected;
	expected << "Web" << "Whatever" << "Wir" << "Word";
	QCOMPARE(expected, f.genres());
}

void ShoutcastTest::requireStationListParsingToWork() {
	QFile file(":stations.xml");
	file.open(QIODevice::ReadOnly);
	ShoutcastFetcher f;
	f.newStationsAvailable("domain.com", &file, "Rock");
	ShoutcastStationList l = f.stationsForKeyword("Rock");

	ShoutcastStation s = l.takeFirst();
	QCOMPARE(s.name(), QString(".977 The Hitz Channel"));
	QCOMPARE(s.id(), 6956);
	QCOMPARE(s.bitRate(), 128);
	QCOMPARE(s.genre(), QString("Pop Rock Top 40"));
	QCOMPARE(s.listeners(), 8483);
	QCOMPARE(s.mimeType(), QString("audio/mpeg"));
	QCOMPARE(s.currentTrack(), QString("Flo rida - Low"));
	QCOMPARE(s.tuneIn(), QString("http://domain.com/sbin/tunein-station.pls"));

	s = l.takeFirst();
	QCOMPARE(s.name(), QString("#MUSIK.MAIN"));
	QCOMPARE(s.id(), 491);
	QCOMPARE(s.bitRate(), 128);
	QCOMPARE(s.genre(), QString("80S POP ROCK TOP 40 WORLD"));
	QCOMPARE(s.listeners(), 6124);
	QCOMPARE(s.mimeType(), QString("audio/mpeg"));
	QCOMPARE(s.currentTrack(), QString(""));
	QCOMPARE(s.tuneIn(), QString("http://domain.com/sbin/tunein-station.pls"));
}

void ShoutcastTest::requireQueryingAStationURIDownloadsTheStationList()
{
	ShoutcastFetcher f;
	f.fetchStations("Pop", QUrl(":stations.xml"));
	QSignalSpy spy(&f, SIGNAL(newStationsAvailable(const QString &)));
	int i = 100;
	while (spy.count() == 0 && --i)
		QTest::qWait(1);
	QVERIFY(i);
	QCOMPARE(spy[0][0].toString(), QString("Pop"));
	ShoutcastStationList l = f.stationsForKeyword("Pop");
	ShoutcastStation s = l.takeFirst();
	QCOMPARE(s.name(), QString(".977 The Hitz Channel"));
}

void ShoutcastTest::requireThatFetchingAGenreURIResultsInAGenreListDownload()
{
	ShoutcastFetcher f;
	f.fetchGenres(QUrl(":genres.xml"));
	QSignalSpy spy(&f, SIGNAL(genresAvailable()));
	int i = 100;
	while (spy.count() == 0 && --i)
		QTest::qWait(1);
	QVERIFY(i);

	QStringList expected;
	expected << "Web" << "Whatever" << "Wir" << "Word";
	QCOMPARE(expected, f.genres());
}

void ShoutcastTest::requireThatURLsGetScrapedFromPlaylistFilesAfterDownload()
{
	PlsFile p(QUrl(":playlist.txt"));
	QCOMPARE(p.url(), QUrl(":playlist.txt"));
	QSignalSpy spy(&p, SIGNAL(ready(PlsFile*)));
	int i = 100;
	while (spy.count() == 0 && --i)
		QTest::qWait(1);
	QVERIFY(i);
	QCOMPARE(p.urls().count(), 22);
	QCOMPARE(p.urls().at(0), QUrl("http://scfire-ntc-aa04.stream.aol.com:80/stream/1074"));
	QCOMPARE(p.urls().at(21), QUrl("http://scfire-ntc-aa02.stream.aol.com:80/stream/1074"));
}

void ShoutcastTest::requireThatFetchingAPlaylistForAStationResultsInThePlaylistBeingDownloaded()
{
	ShoutcastStation s("NRK", 3, 128, "Rock", 3, "audio/mpeg", "Metallica - Barbiegirl",
			":playlist.txt");
	ShoutcastFetcher f;
	f.fetchPlaylistsForStation(s);
	QSignalSpy spy(&f, SIGNAL(playlistAvailable()));
	int i = 100;
	while (spy.count() == 0 && --i)
		QTest::qWait(1);
	QVERIFY(i);

	QList<QUrl> pl = f.playlistForStation(s);
	QCOMPARE(pl.count(), 22);
}

#include "shoutcasttest.moc"
QTEST_MAIN(ShoutcastTest)
