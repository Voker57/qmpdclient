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

#include "shortcuts.h"
#include "config.h"
#include <QAbstractButton>
#include <QAction>
#include <QShortcut>

Shortcuts *Shortcuts::m_instance = 0;

Shortcuts::Shortcuts(QObject *parent) : QObject(parent) {
	updateTranslation();
	m_instance = this;
}

Shortcuts *Shortcuts::instance() {
	return m_instance;
}

#define LOAD(GET, SET, OBJ) \
do { \
    Config::instance()->setOriginalShortcut(OBJ->objectName(), OBJ->GET().toString()); \
OBJ->SET(Config::instance()->shortcut(OBJ->objectName())); \
m_objects << OBJ; \
} while (0)

void Shortcuts::updateTranslation() {
	// When translation changes, some shortcuts are also retranslated. Read originals again.
	m_objects.clear();
	foreach(QShortcut *shortcut, parent()->findChildren<QShortcut*>()) {
		LOAD(key, setKey, shortcut);
	}
	foreach(QAbstractButton *button, parent()->findChildren<QAbstractButton*>()) {
		if (button->text().isEmpty() && !button->shortcut().isEmpty()) {
			LOAD(shortcut, setShortcut, button);
		}
	}
	foreach(QAction *action, parent()->findChildren<QAction*>(QRegExp("Menu$"))) {
		LOAD(shortcut, setShortcut, action);
	}
}

QList<QObject*> Shortcuts::objects() {
	return m_objects;
}

void Shortcuts::setShortcut(QObject *o, const QString &s) {
	Config::instance()->setShortcut(o->objectName(), s);
	// Read back incase blank (default) was set
	QString sc = Config::instance()->shortcut(o->objectName());
	if (!o->setProperty("shortcut", sc)) {
		if (!o->setProperty("key", sc))
			qWarning("Could set neither shortcut nor key property of %s", qPrintable(o->objectName()));
	}
}

QString Shortcuts::description(QObject *o) {
	return o->property("whatsThis").toString();
}

QIcon Shortcuts::decoration(QObject *o) {
	QVariant v = o->property("icon");
	if (v.isValid())
		return QIcon(qvariant_cast<QIcon>(v).pixmap(12, 12));
	return QIcon();
}

QString Shortcuts::shortcut(QObject *o) {
	QVariant v = o->property("shortcut");
	if (!v.isValid()) {
		v = o->property("key");
		if (!v.isValid())
			qWarning("Could get neither shortcut nor key property of %s", qPrintable(o->objectName()));
	}
	return v.toString();
}
