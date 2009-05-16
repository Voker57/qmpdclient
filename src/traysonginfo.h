#ifndef TRAYSONGINFO_H
#define TRAYSONGINFO_H
//
#include <QWidget>
class QLabel;
class QProgressBar;
class MPDSong;
//
class TraySongInfo: public QWidget
{
	Q_OBJECT
private:
	QLabel *lblMpdClientLogo, *lblSongInfo;

	QProgressBar *pbPosition;
	QLabel *lblPosition;

	void initializeGui();
private slots:
	void updatePosition(int elapsed, int maximum);
public:
	TraySongInfo();
public slots:
	void setSong(const MPDSong &song);
};
//
#endif // TRAYSONGINFO_H
