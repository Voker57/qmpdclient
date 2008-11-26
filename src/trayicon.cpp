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

#include "trayicon.h"
#include "config.h"
#include "iconmanager.h"
#include "mpd.h"
#include "mpdconnection.h"
#include "mpdsong.h"
#include "richtext.h"
#include <QApplication>
#include <QBoxLayout>
#include <QMenu>
#include <QPainter>
#include <QSlider>
#include <QWheelEvent>
#ifndef Q_WS_X11
#include "macroexpander.h"
#endif

struct VolumeMenu : QMenu {
	VolumeMenu(QWidget *parent) : QMenu(parent) {
		QFrame *w = new QFrame(this);
		QLabel *min = new QLabel("-", w);
		QLabel *max = new QLabel("+", w);
		QSlider *s = new QSlider(w);

		min->setAlignment(Qt::AlignHCenter);
		max->setAlignment(Qt::AlignHCenter);

		QVBoxLayout *l = new QVBoxLayout(w);
		l->setMargin(3);
		l->addWidget(max);
		l->addWidget(s);
		l->addWidget(min);

		layout = new QHBoxLayout(this);
		layout->setMargin(0);
		layout->addWidget(w);

		connect(MPD::instance(), SIGNAL(volumeUpdated(int)), s, SLOT(setValue(int)));
		connect(s, SIGNAL(valueChanged(int)), MPD::instance(), SLOT(setVolume(int)));
	}

	QSize sizeHint() const {
		return layout->sizeHint();
	}

private:
	QHBoxLayout *layout;
};


TrayIcon::TrayIcon(QWidget *parent) : QSystemTrayIcon(parent),
#ifndef Q_WS_X11
		m_connected(":/icons/qmpdclient16.png"),
		m_disconnected(":/icons/qmpdclient16d.png")
#else
		m_connected(":/icons/qmpdclient22.png"),
		m_disconnected(":/icons/qmpdclient22d.png")
#endif
{
	setObjectName("trayicon");
	setIcon(m_disconnected);

	QMenu *menu = new QMenu(parent);
	m_showHideAction = menu->addAction("", parent, SLOT(showHide()));
	menu->addSeparator();
	m_prevAction = menu->addAction("", MPD::instance(), SLOT(prev()));
	m_playAction = menu->addAction("", MPD::instance(), SLOT(play()));
	m_pauseAction = menu->addAction("", MPD::instance(), SLOT(pause()));
	m_stopAction = menu->addAction("", MPD::instance(), SLOT(stop()));
	m_nextAction = menu->addAction("", MPD::instance(), SLOT(next()));
	menu->addSeparator();
	menu->addMenu(m_volumeMenu = new VolumeMenu(menu));
	menu->addSeparator();
	m_quitAction = menu->addAction("", qApp, SLOT(quit()));
	setContextMenu(menu);

	// For icon changes
	m_showHideAction->setObjectName("showHideAction");
	m_prevAction->setObjectName("prevAction");
	m_playAction->setObjectName("playAction");
	m_pauseAction->setObjectName("pauseAction");
	m_stopAction->setObjectName("stopAction");
	m_nextAction->setObjectName("nextAction");
	m_quitAction->setObjectName("quitAction");
	m_volumeMenu->setObjectName("volumeMenu");

	connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(action(QSystemTrayIcon::ActivationReason)));
	connect(menu, SIGNAL(aboutToShow()), this, SLOT(menuAboutToShow()));
	connect(MPD::instance(), SIGNAL(playingSongUpdated(const MPDSong &)), this, SLOT(setSong(const MPDSong &)));
	connect(MPDConnection::instance(), SIGNAL(connected(const ServerInfo &)), this, SLOT(connected()));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(disconnected()));

	MPDConnection::instance()->isConnected() ? connected() : disconnected();

	setToolTip(NAMEVER);
}

void TrayIcon::menuAboutToShow() {
	Q_ASSERT(m_showHideAction);
	if (qobject_cast<QWidget*>(parent())->isVisible())
		m_showHideAction->setText(tr("Hide"));
	else
		m_showHideAction->setText(tr("Show"));
}

void TrayIcon::updateTranslation() {
	Q_ASSERT(m_prevAction);
	Q_ASSERT(m_playAction);
	Q_ASSERT(m_pauseAction);
	Q_ASSERT(m_stopAction);
	Q_ASSERT(m_nextAction);
	Q_ASSERT(m_quitAction);
	Q_ASSERT(m_volumeMenu);
	m_prevAction->setText(tr("Previuos"));
	m_playAction->setText(tr("Play"));
	m_pauseAction->setText(tr("Pause"));
	m_stopAction->setText(tr("Stop"));
	m_nextAction->setText(tr("Next"));
	m_quitAction->setText(tr("Quit"));
	m_volumeMenu->setTitle(tr("Volume"));
}

void TrayIcon::action(QSystemTrayIcon::ActivationReason reason) {
	if (reason == QSystemTrayIcon::MiddleClick)
		MPD::instance()->togglePlay();
	else if (reason != QSystemTrayIcon::Context)
		emit clicked();
}

void TrayIcon::setSong(const MPDSong &s) {
	if (s.isNull()) {
		QString msg = tr("Not playing", "This is for the trayicon tooltip, indicating that no song is playing");
#ifndef Q_WS_X11
		// Win32 and OSX does not seem to support richtext in tooltips
		setToolTip(msg);
#else
		QString tooltip = "<html><body>";
		tooltip += "<table><tr><td><img src=':/icons/qmpdclient48.png'></td><td valign='middle'>";
		tooltip += QString("&nbsp;%1</td></tr></table>").arg(NAMEVER);
		tooltip += QString("<b>%1</b>").arg(msg);
		tooltip += "</body></html>";
		setToolTip(tooltip);
#endif
		return;
	}

#ifndef Q_WS_X11
	// Win32 and OSX does not seem to support richtext in tooltips
	setToolTip(expandMacros(s, Config::instance()->playlistPattern()));
#else
	QString tooltip = "<html><body><table>";
	tooltip += "<tr><td rowspan='%1' valign='middle'><img src=':/icons/qmpdclient48.png' /></td>";
	tooltip += "<td valign='middle' align='center'>%2</td></tr>";

	// Make nice tooltip
	QString album = elideRichText("", s.album(), "", 175);
	QString artist = elideRichText("", s.artist(), "", 175);
	QString title;
	if (s.title().isEmpty())
		title = s.filename();
	else
		title = s.title();
	title = elideRichText("<b>", title, "</b>", 175);

	int rows = 2;
	tooltip += QString("<tr><td>%1</td></tr>").arg(title.isEmpty() ? QObject::tr("Not tagged") : title);

	if (!artist.isEmpty()) {
		tooltip += QString("<tr><td>%1</td></tr>").arg(artist);
		rows++;
	}
	if (!album.isEmpty()) {
		tooltip += QString("<tr><td>%1</td></tr>").arg(album);
		rows++;
	}
	tooltip += "</table></body></html>";

	setToolTip(tooltip.arg(rows).arg(NAMEVER));
#endif
}

void TrayIcon::connected() {
	setIcon(m_connected);
	toggleEnabled(true);
}

void TrayIcon::disconnected() {
	setIcon(m_disconnected);
	toggleEnabled(false);
}

void TrayIcon::toggleEnabled(bool enabled) {
	foreach(QAction *w, contextMenu()->findChildren<QAction*>(QRegExp("Action$"))) {
		w->setEnabled(enabled);
	}
	m_volumeMenu->setEnabled(enabled);
	m_showHideAction->setEnabled(true);
	m_quitAction->setEnabled(true);
}

bool TrayIcon::event(QEvent *event) {
	if (event->type() == QEvent::Wheel) {
		QWheelEvent *e = static_cast<QWheelEvent*>(event);
		const int numDegrees = e->delta() / 8;
		const int numSteps = numDegrees / 15;

		if (e->orientation() == Qt::Horizontal) {
			if (numSteps > 0)
				MPD::instance()->seekForward();
			else if (numSteps < 0)
				MPD::instance()->seekBackward();
		} else {
			if (numSteps > 0)
				MPD::instance()->volumeUp(5*numSteps);
			else if (numSteps < 0)
				MPD::instance()->volumeDown(5*numSteps);
		}
		return true;
	}
	return QSystemTrayIcon::event(event);
}
