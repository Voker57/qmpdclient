/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Håvard Tautra Knutsen <havtknut@tihlde.org>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "passivepopup.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QTimer>

QPointer<PassivePopup> PassivePopup::visible;

PassivePopup::PassivePopup(const QString &caption, const QString &text, const QPixmap &pixmap,
        PassivePopup::Position pos, int timeout) : QFrame(0, Qt::X11BypassWindowManagerHint
#ifndef Q_WS_X11
	| Qt::SplashScreen
#endif
| Qt::WindowStaysOnTopHint) {
	setObjectName("passivepopup");
	setFrameStyle(QFrame::Box | QFrame::Plain);
	setLineWidth(1);

	QLabel *textLabel = new QLabel(text, this);
	QLabel *captionLabel = new QLabel("<b>"+caption+"</b>", this);
	captionLabel->setAlignment(Qt::AlignHCenter);
	QLabel *pixmapLabel = new QLabel(this);
	pixmapLabel->setPixmap(pixmap);

	QGridLayout *grid = new QGridLayout(this);
	grid->addWidget(pixmapLabel, 0, 0, 2, 1);
	grid->addWidget(captionLabel, 0, 1);
	grid->addWidget(textLabel, 1, 1, Qt::AlignTop);

	resize(sizeHint());
	QRect geom = QApplication::desktop()->screenGeometry();

	int x = geom.width() - width();
	int y = geom.height() - height();
	if (pos == TopLeft || pos == TopRight || pos == Top)
		y = 0;
	else if (pos == Right || pos == Left)
		y = (geom.height()/2) - (height()/2);

	if (pos == TopLeft || pos == Left || pos == BottomLeft)
		x = 0;
	else if (pos == Top || pos == Bottom)
		x = (geom.width()/2) - (width()/2);

	move(x, y);
	show();

	QTimer::singleShot(timeout*1000, this, SLOT(deleteLater()));

	// Delete previous notification first.
	if (visible)
		delete visible;
	visible = this;
}

void PassivePopup::mousePressEvent(QMouseEvent *e) {
	hide();
	deleteLater();
	QFrame::mousePressEvent(e);
}

