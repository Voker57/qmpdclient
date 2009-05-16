#include "traysonginfo.h"
#include <QGridLayout>
#include <QLabel>
#include <QProgressBar>
#include "mpd.h"
#include "mpdsong.h"
#include <QTime>
//
TraySongInfo::TraySongInfo() {
	initializeGui();

	setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

void TraySongInfo::initializeGui() {
	QGridLayout *ly = new QGridLayout(this);
	//
	lblMpdClientLogo = new QLabel(this);
	lblMpdClientLogo->setPixmap(QPixmap(":/icons/qmpdclient48.png"));
	ly->addWidget(lblMpdClientLogo, 0, 0, 2, 1);

	lblSongInfo = new QLabel(this);
	ly->addWidget(lblSongInfo, 0, 1);
	//
	pbPosition = new QProgressBar(this);
	pbPosition->setTextVisible(false);
	connect(MPD::instance(), SIGNAL(timeUpdated(int, int)), this, SLOT(updatePosition(int, int)));
	ly->addWidget(pbPosition, 1, 1);

	lblPosition = new QLabel(this);
	ly->addWidget(lblPosition, 1, 1, Qt::AlignCenter);
}

void TraySongInfo::updatePosition(int elapsed, int /* maximum */) {
	QTime position = QTime().addSecs(elapsed);
	pbPosition->setValue(elapsed);
	lblPosition->setText(position.toString((position.hour() ? QString("hh:") : QString("")) + "mm:ss"));

	pbPosition->update();
}

void TraySongInfo::setSong(const MPDSong &song) {
	pbPosition->setVisible(!song.isNull());
	lblPosition->setVisible(!song.isNull());

	if (song.isNull()) {
		lblSongInfo->setText(QString("%1<p><b>%2</b>").arg(NAMEVER).arg(tr("Not playing")));
		pbPosition->setValue(0);
		lblPosition->clear();

		return;
	}

	lblSongInfo->setText(QString("%1<p><b>%2</b> - %3<br>%4 <i>%5</i>").arg(NAMEVER).arg(song.artist()).arg(song.title())
			.arg(tr("from", "Means some song `from` some album")).arg(song.album()));
	pbPosition->setMaximum(song.secs());

	layout()->update();
}
