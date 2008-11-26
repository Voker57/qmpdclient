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

#ifndef TRAYICON_H
#define TRAYICON_H

#include <QSystemTrayIcon>

class MPDSong;
class QAction;
class VolumeMenu;

class TrayIcon : public QSystemTrayIcon {
	Q_OBJECT

public:
	TrayIcon(QWidget *);

public slots:
	void updateTranslation();

signals:
	void clicked();

private:
	bool event(QEvent *);
	void toggleEnabled(bool);

	VolumeMenu *m_volumeMenu;
	QAction *m_prevAction, *m_playAction, *m_pauseAction, *m_stopAction, *m_nextAction, *m_showHideAction, *m_quitAction;
	QColor m_prevColor;
	QPixmap m_connected, m_disconnected;

private slots:
	void action(QSystemTrayIcon::ActivationReason);
	void connected();
	void disconnected();
	void menuAboutToShow();
	void setSong(const MPDSong &);
};
#endif
