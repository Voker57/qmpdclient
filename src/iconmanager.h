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

#ifndef ICONMANAGER_H
#define ICONMANAGER_H

#include <QMap>
class QIcon;
class QPixmap;

class IconManager {
public:
	static void update();
	static QString description();
	static QIcon icon(const QString &, int size = 16);
	static QPixmap pixmap(const QString &, int size = 16);

private:
	static QString filename(const QString &);
	static QMap<QString, QString> actionIconMap;
	static QString descriptionString;
};
#endif
