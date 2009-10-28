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

#include "mainwindow.h"
#include "mpd.h"
#include "qmpdclient.h"

#include <windows.h>
#define VK_VOLUME_DOWN 0xAE
#define VK_VOLUME_UP 0xAF
#define VK_MEDIA_NEXT_TRACK 0xB0
#define VK_MEDIA_PREV_TRACK 0xB1
#define VK_MEDIA_STOP 0xB2
#define VK_MEDIA_PLAY_PAUSE 0xB3
#define VK_LAUNCH_MEDIA_SELECT 0xB5

void QMPDClient::grabKeys() {
	Q_ASSERT(m_mainWindow);
	if(!RegisterHotKey(m_mainWindow->winId(), 1, 0, VK_MEDIA_PLAY_PAUSE))
		qWarning("Could not register hotkey VK_MEDIA_PLAY_PAUSE");
	if(!RegisterHotKey(m_mainWindow->winId(), 2, 0, VK_MEDIA_STOP))
		qWarning("Could not register hotkey VK_MEDIA_STOP");
	if(!RegisterHotKey(m_mainWindow->winId(), 3, 0, VK_MEDIA_NEXT_TRACK))
		qWarning("Could not register hotkey VK_MEDIA_NEXT_TRACK");
	if(!RegisterHotKey(m_mainWindow->winId(), 4, 0, VK_MEDIA_PREV_TRACK))
		qWarning("Could not register hotkey VK_MEDIA_PREV_TRACK");
	if(!RegisterHotKey(m_mainWindow->winId(), 5, 0, VK_LAUNCH_MEDIA_SELECT))
		qWarning("Could not register hotkey VK_LAUNCH_MEDIA_SELECT");
	if(!RegisterHotKey(m_mainWindow->winId(), 6, 0, VK_VOLUME_UP))
		qWarning("Could not register hotkey VK_VOLUME_UP");
	if(!RegisterHotKey(m_mainWindow->winId(), 7, 0, VK_VOLUME_DOWN))
		qWarning("Could not register hotkey VK_VOLUME_DOWN");
}

void QMPDClient::ungrabKeys() {
	Q_ASSERT(m_mainWindow);
	if(!UnregisterHotKey(m_mainWindow->winId(), 1))
		qWarning("Could not unregister hotkey VK_MEDIA_PLAY_PAUSE");
	if(!UnregisterHotKey(m_mainWindow->winId(), 2))
		qWarning("Could not unregister hotkey VK_MEDIA_STOP");
	if(!UnregisterHotKey(m_mainWindow->winId(), 3))
		qWarning("Could not unregister hotkey VK_MEDIA_NEXT_TRACK");
	if(!UnregisterHotKey(m_mainWindow->winId(), 4))
		qWarning("Could not unregister hotkey VK_MEDIA_PREV_TRACK");
	if(!UnregisterHotKey(m_mainWindow->winId(), 5))
		qWarning("Could not register hotkey VK_LAUNCH_MEDIA_SELECT");
	if(!UnregisterHotKey(m_mainWindow->winId(), 6))
		qWarning("Could not unregister hotkey VK_VOLUME_UP");
	if(!UnregisterHotKey(m_mainWindow->winId(), 7))
		qWarning("Could not unregister hotkey VK_VOLUME_DOWN");
}

bool QMPDClient::winEventFilter(MSG *m, long *result) {
	if(m->message != WM_HOTKEY)
		return false;

	switch (m->wParam) {
	case 1:
		MPD::instance()->togglePlay();
		return true;
	case 2:
		MPD::instance()->stop();
		return true;
	case 3:
		MPD::instance()->next();
		return true;
	case 4:
		MPD::instance()->prev();
		return true;
	case 5:
		m_mainWindow->showHide();
		return true;
	case 6:
		MPD::instance()->volumeUp();
		return true;
	case 7:
		MPD::instance()->volumeDown();
		return true;
	}
	return false;
}
