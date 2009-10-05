#ifndef PLSFILE_H_
#define PLSFILE_H_

#include <QObject>
#include <QUrl>
class QNetworkReply;

class PlsFile : public QObject {
	Q_OBJECT
public:
	PlsFile(const QUrl & url);
	QList<QUrl> urls() const;
signals:
	void ready();
private slots:
	void newDataAvailable(QNetworkReply * reply);
private:
	QList<QUrl> m_urls;
};

#endif /* PLSFILE_H_ */
