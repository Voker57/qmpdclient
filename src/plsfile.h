#ifndef PLSFILE_H_
#define PLSFILE_H_

#include <QObject>
#include <QUrl>
#include <QMetaType>
class QNetworkReply;

class PlsFile : public QObject {
	Q_OBJECT
public:
	PlsFile(const QUrl & url, QObject * parent = 0);
	PlsFile();
	PlsFile(const PlsFile & rhs);
	QList<QUrl> urls() const;
	QUrl url() const;
signals:
	void ready(PlsFile * file);
private slots:
	void newDataAvailable(QNetworkReply * reply);
private:
	QList<QUrl> m_urls;
	QUrl m_url;
};

Q_DECLARE_METATYPE(PlsFile)

#endif /* PLSFILE_H_ */
