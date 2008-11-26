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

#include "iconmanager.h"
#include "config.h"
#include "debug.h"
#include <QDir>
#include <QIcon>

QMap<QString, QString> IconManager::actionIconMap;
QString IconManager::descriptionString;

void IconManager::update() {
	actionIconMap.clear();
	QString path = Config::instance()->iconSetPath();
	QString confFile = path + "/iconset.conf";
	if (!QFile::exists(confFile)) {
		qWarning("Could not find 'iconset.conf' in iconset %s", qPrintable(path));
		return;
	}

	// Read action filenames
	QSettings conf(confFile, QSettings::IniFormat);
	conf.beginGroup("Icons");
	foreach(QString key, conf.allKeys()) {
		QString value = conf.value(key).toString();
		if (value.isEmpty())
			continue;
		actionIconMap.insert(key, path + "/" + value);
	}
	conf.endGroup();

	// Read description
	conf.beginGroup("Iconset");
	QString title = conf.value("Name").toString();
	QString desc = conf.value("Description").toString();
	conf.endGroup();
	if (title.isEmpty())
		title = QFileInfo(path).baseName();

	descriptionString = "<b>" + title + "</b>";
	if (!desc.isEmpty())
		descriptionString += "<br>" + desc;
}

QString IconManager::description() {
	return descriptionString;
}

QString IconManager::filename(const QString &action) {
	QString filename = actionIconMap.value(action.toLower());
	if (filename.isEmpty()) {
		return QString();
	}
	if (!QFile::exists(filename)) {
		qWarning("Icon file %s does not exist.", qPrintable(filename));
		return QString();
	}
	return filename;
}

QIcon IconManager::icon(const QString &action, int size) {
	return QIcon(pixmap(action, size));
}

QPixmap IconManager::pixmap(const QString &action, int size) {
	QString fn = filename(action);
	if (fn.isEmpty())
		return QPixmap();
	QPixmap pix = QPixmap(fn);
	if (pix.width() == size && pix.height() == size)
		return pix;
	if (pix.width() > pix.height())
		return pix.scaledToWidth(size, Qt::SmoothTransformation);
	return pix.scaledToHeight(size, Qt::SmoothTransformation);
}
