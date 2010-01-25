/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2009 Voker57 <voker57@gmail.com>
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

#ifndef QDBUS_ADAPTOR_H
#define QDBUS_ADAPTOR_H

#include "qmpdclient.h"
#include <QDBusAbstractAdaptor>
#include <QString>

class MainApplicationAdaptor: public QDBusAbstractAdaptor {
	Q_OBJECT
 	Q_CLASSINFO("D-Bus Interface", "net.bitcheese.QMPDClient")
// 	Q_PROPERTY(QString caption READ caption WRITE setCaption)
	Q_PROPERTY(QString organizationName READ organizationName)
	Q_PROPERTY(QString organizationDomain READ organizationDomain)

private:
	QMPDClient *app;
public:
	MainApplicationAdaptor(QMPDClient * application);
	QString organizationName();
	QString organizationDomain();
signals:
	void aboutToQuit();
public slots:
	void quit();
	void toggleMainWindow();
};
#endif
