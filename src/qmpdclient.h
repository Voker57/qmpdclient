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

#ifndef QMPDCLIENT_H
#define QMPDCLIENT_H

#include <QApplication>
#include <QPointer>
#include <QSessionManager>

class MainWindow;
class QTranslator;

class QMPDClient : public QApplication {
	Q_OBJECT
public:
	QMPDClient(int &, char **);
	~QMPDClient();
#ifdef Q_WS_X11
	bool x11EventFilter(XEvent *);
#else
	bool eventFilter(QObject *, QEvent *);
#endif
#ifdef Q_WS_WIN
	bool winEventFilter(MSG *, long *);
#endif
	void commitData(QSessionManager & manager);

public slots:
	void toggleMainWindow();

private slots:
	void alternatingChanged(bool);
	void fontChanged(const QFont &);
	void iconSetChanged();
	void localeChanged(const QString &);
	void opaqueResizeChanged(bool);
private:
	QList<QPointer<QObject> > safeChildren();
	void grabKeys();
	void ungrabKeys();

	MainWindow *m_mainWindow;
	QTranslator *m_translator, *m_qtTranslator;
};
#endif
