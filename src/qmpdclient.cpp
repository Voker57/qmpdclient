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

#include "config.h"
#include "debug.h"
#include "dynamicplaylist.h"
#include "iconmanager.h"
#include "mainwindow.h"
#include "mpd.h"
#include "mpdconnection.h"
#include "notifications.h"
#include "qmpdclient.h"
#include "reconnect.h"
#include "shortcuts.h"
#include <QAbstractItemView>
#include <QFile>
#include <QLibraryInfo>
#include <QTranslator>
#include <QWheelEvent>

QMPDClient::QMPDClient(int &argc, char **argv) : QApplication(argc, argv),
		m_mainWindow(0),
		m_translator(0),
		m_qtTranslator(0) {
	setObjectName("qmpdclient");
	setApplicationName("QMPDClient");
	setOrganizationName("QMPDClient");

	// Install initial translators
	localeChanged(Config::instance()->localeFile());

	// Create mainwin
	m_mainWindow = new MainWindow;
	connect(this, SIGNAL(lastWindowClosed()), this, SLOT(quit()));
	alternatingChanged(Config::instance()->alternatingRowColors());
	fontChanged(Config::instance()->font());
	iconSetChanged();
	localeChanged(Config::instance()->localeFile()); // Retranslate dynamic parts
	opaqueResizeChanged(Config::instance()->opaqueResize());
	setStyleSheet(Config::instance()->style());

	connect(Config::instance(), SIGNAL(alternatingChanged(bool)), this, SLOT(alternatingChanged(bool)));
	connect(Config::instance(), SIGNAL(fontChanged(const QFont &)), this, SLOT(fontChanged(const QFont &)));
	connect(Config::instance(), SIGNAL(iconSetChanged()), this, SLOT(iconSetChanged()));
	connect(Config::instance(), SIGNAL(localeChanged(const QString &)), this, SLOT(localeChanged(const QString &)));
	connect(Config::instance(), SIGNAL(opaqueResizeChanged(bool)), this, SLOT(opaqueResizeChanged(bool)));
	connect(Config::instance(), SIGNAL(styleChanged(const QString &)), this, SLOT(setStyleSheet(const QString &)));

	// Services
	new DynamicPlaylist(this);
	new Notifications(this);
	new Reconnect(this);
	new Shortcuts(m_mainWindow);
	grabKeys();

	// Install event filter to pick up wheel over tray icon
	installEventFilter(this);

	if (Config::instance()->autoconnect()) // Autoconnect?
		MPDConnection::instance()->connectToMPD(Config::instance()->servers().first());
}

QMPDClient::~QMPDClient() {
	ungrabKeys();
	delete m_mainWindow;
	delete MPD::instance();
	delete Config::instance();
}

void QMPDClient::alternatingChanged(bool a) {
	Q_ASSERT(m_mainWindow);
	foreach(QAbstractItemView *view, m_mainWindow->findChildren<QAbstractItemView*>(QString())) {
		if (!view->setProperty("alternatingRowColors", a))
			qWarning("Couldn't set alternatingRowColors for view: %s", qPrintable(view->objectName()));
	}
}

void QMPDClient::fontChanged(const QFont &font) {
	Q_ASSERT(m_mainWindow);
	setFont(font);
	m_mainWindow->setFont(font);
}

void QMPDClient::iconSetChanged() {
	foreach(QPointer<QObject> child, safeChildren()) {
		if (!child || child->objectName().isEmpty())
			continue;
		const bool icon = child->metaObject()->indexOfProperty("icon") > -1;
		const bool pixmap = child->metaObject()->indexOfProperty("pixmap") > -1;
		if (icon || pixmap) {
			QString name = child->objectName();
			name.remove(QRegExp("^m_"));
			name.remove(QRegExp("Button$"));
			name.remove(QRegExp("Action$"));
			name.remove(QRegExp("Menu$"));
			name.remove(QRegExp("Tab$"));
			name.remove(QRegExp("Item$"));
			name.remove(QRegExp("Label$"));
			name = name.toLower();
			if (icon) {
				QIcon icn = IconManager::icon(name);
				if (icn.isNull())
					continue;
				if (!child->setProperty("icon", icn)) {
					qWarning("Could not set icon for %s", qPrintable(child->objectName()));
				}
			} else if (pixmap) {
				QPixmap pix = IconManager::pixmap(name);
				if (pix.isNull())
					continue;
				if (!child->setProperty("pixmap", pix)) {
					qWarning("Could not set pixmap for %s", qPrintable(child->objectName()));
				}
			}
		}
	}
}

void QMPDClient::localeChanged(const QString &locale) {
	if (!Config::instance()->translate() || !QFile::exists(locale)) {
		if (m_translator)
			delete m_translator;
		if (m_qtTranslator)
			delete m_qtTranslator;
		m_translator = 0;
		m_qtTranslator = 0;
	} else {
		if (!m_translator)
			m_translator = new QTranslator(this);
		if (!m_qtTranslator)
			m_qtTranslator = new QTranslator(this);

		if (m_translator->load(locale))
			installTranslator(m_translator);
		// Get country code
		const QString cc = locale.section('_', -1, -1).remove(".qm");
		if (m_qtTranslator->load(QString("qt_") + cc, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
			installTranslator(m_qtTranslator);
	}

	const QByteArray normalizedSignature = QMetaObject::normalizedSignature("updateTranslation()");
	foreach(QPointer<QObject> child, safeChildren()) {
		if (child && child->metaObject()->indexOfMethod(normalizedSignature) > -1) {
			if (!QMetaObject::invokeMethod(child, "updateTranslation"))
				qWarning("Could not invoke updateTranslation on '%s'", qPrintable(child->objectName()));
		}
	}
}

void QMPDClient::opaqueResizeChanged(bool a) {
	Q_ASSERT(m_mainWindow);
	foreach(QSplitter *splitter, m_mainWindow->findChildren<QSplitter*>(QString())) {
		if (!splitter->setProperty("opaqueResize", a))
			qWarning("Could not set opaqueResize for splitter '%s'", qPrintable(splitter->objectName()));
	}
}

/*
 * This event filter detects wheelEvents over the tray icon.
 * If the object which recieves the wheelEvent has no parent it is
 * either the main window or the tray icon. So, if the wheelEvents
 * position is outside the mainwindow frame, it must be the tray icon.
 */
#ifndef Q_WS_X11
bool QMPDClient::eventFilter(QObject *watched, QEvent *event) {
	if (event->type() == QEvent::Wheel) {
		QWheelEvent *e = static_cast<QWheelEvent*>(event);
		Q_ASSERT(m_mainWindow);
		if (!watched->parent() && !m_mainWindow->frameGeometry().contains(e->globalPos())) {
			// No parent, and outside mainwindow, should be trayicon.
			const int numDegrees = e->delta() / 8;
			const int numSteps = numDegrees / 15;
			if (e->orientation() == Qt::Vertical) {
				if (numSteps > 0)
					MPD::instance()->volumeUp(5*numSteps);
				else if (numSteps < 0)
					MPD::instance()->volumeDown(5*numSteps);
				return true;
			}
		}
	}
	return QApplication::eventFilter(watched, event);
}
#endif

QList<QPointer<QObject> > QMPDClient::safeChildren() {
	if (!m_mainWindow)
		return QList<QPointer<QObject> > ();

	// Guard against dangling pointers by using QPointer
	QList<QPointer<QObject> > safeChildren;
	foreach(QObject *child, m_mainWindow->findChildren<QObject*>(QString())) {
		safeChildren << QPointer<QObject>(child);
	}
	safeChildren << QPointer<QObject>(m_mainWindow);
	return safeChildren;
}

int g_debugLevel = 0; // Reference to global debug variable declared in debug.h

int main(int argc, char **argv) {
	QMPDClient app(argc, argv);
	for (int i = 0; i < argc; i++) {
		const QString arg = QString::fromLocal8Bit(argv[i]);
		if (arg.startsWith("-v")) {
			g_debugLevel = arg.count('v');
			qWarning("Debug output enabled, level: %d", g_debugLevel);
			break;
		}
	}
	return app.exec();
}
