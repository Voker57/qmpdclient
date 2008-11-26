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

#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include <QObject>
#include <QStringList>
#include <QMap>

class QIcon;

class Shortcuts : public QObject {
	Q_OBJECT
public:
	Shortcuts(QObject *);
	static Shortcuts *instance();
	QList<QObject*> objects();
	void setShortcut(QObject *, const QString &);
	QIcon decoration(QObject *);
	QString description(QObject *);
	QString shortcut(QObject *);

public slots:
	void updateTranslation();

private:
	Shortcuts();
	static Shortcuts *m_instance;
	QList<QObject*> m_objects;
};

#endif
