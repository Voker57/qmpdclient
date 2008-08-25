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

#include <QDesktopWidget>
#include <QX11Info>
#include <X11/Xlib.h>
#define XF86AUDIO_VOLUP 176
#define XF86AUDIO_VOLDN 174
#define XF86AUDIO_MEDIA 129
#define XF86AUDIO_PLAY 162
#define XF86AUDIO_STOP 164
#define XF86AUDIO_NEXT 153
#define XF86AUDIO_PREV 144

static int XGrabErrorHandler(Display *, XErrorEvent *e) {
	if (e->error_code != BadAccess)
		qWarning("grabKey: got X error %d instead of BadAccess", e->type);
	return 0;
}

void QMPDClient::grabKeys() {
	Display *dpy = QX11Info::display();
	XSync(dpy, 0);
	XErrorHandler savedErrorHandler = XSetErrorHandler(XGrabErrorHandler);
	WId rootWindowId = QApplication::desktop()->winId();

	// Grab multimedia keys
	XGrabKey(dpy, XF86AUDIO_PLAY, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XF86AUDIO_STOP, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XF86AUDIO_PREV, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XF86AUDIO_NEXT, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XF86AUDIO_MEDIA, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XF86AUDIO_VOLUP, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XGrabKey(dpy, XF86AUDIO_VOLDN, 0, rootWindowId, 1, GrabModeAsync, GrabModeAsync);
	XSync(dpy, 0);

	XSetErrorHandler(savedErrorHandler);
}

void QMPDClient::ungrabKeys() {
	// Ungrab multimedia keys
	Display *dpy = QX11Info::display();
	WId rootWindowId = QApplication::desktop()->winId();
	XUngrabKey(dpy, XF86AUDIO_PLAY, 0, rootWindowId);
	XUngrabKey(dpy, XF86AUDIO_STOP, 0, rootWindowId);
	XUngrabKey(dpy, XF86AUDIO_PREV, 0, rootWindowId);
	XUngrabKey(dpy, XF86AUDIO_NEXT, 0, rootWindowId);
	XUngrabKey(dpy, XF86AUDIO_MEDIA, 0, rootWindowId);
	XUngrabKey(dpy, XF86AUDIO_VOLUP, 0, rootWindowId);
	XUngrabKey(dpy, XF86AUDIO_VOLDN, 0, rootWindowId);
}

bool QMPDClient::x11EventFilter(XEvent *xevent) {
	Q_ASSERT(m_mainWindow);
	XKeyEvent *keyevent = (XKeyEvent *)xevent;

	if (xevent->type != KeyRelease)
		return false;

	switch (keyevent->keycode) {
	case XF86AUDIO_PLAY:
		MPD::instance()->togglePlay();
		return true;
	case XF86AUDIO_STOP:
		MPD::instance()->stop();
		return true;
	case XF86AUDIO_NEXT:
		MPD::instance()->next();
		return true;
	case XF86AUDIO_PREV:
		MPD::instance()->prev();
		return true;
	case XF86AUDIO_MEDIA:
		m_mainWindow->showHide();
		return true;
	case XF86AUDIO_VOLUP:
		MPD::instance()->volumeUp();
		return true;
	case XF86AUDIO_VOLDN:
		MPD::instance()->volumeDown();
		return true;
	}

	return false;
}
