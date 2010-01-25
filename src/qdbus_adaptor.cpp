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

#include "qdbus_adaptor.h"

MainApplicationAdaptor::MainApplicationAdaptor(QMPDClient *application) : QDBusAbstractAdaptor(application), app(application)
{
	connect(app, SIGNAL(aboutToQuit()), SIGNAL(aboutToQuit()));
	connect(application, SIGNAL(aboutToQuit()), SIGNAL(aboutToQuit()));
//       connect(application, SIGNAL(focusChanged(QWidget*, QWidget*)),
//                          SLOT(focusChangedSlot(QWidget*, QWidget*)));
}

QString MainApplicationAdaptor::organizationName()
{
	return app->organizationName();
}

QString MainApplicationAdaptor::organizationDomain()
{
	return app->organizationDomain();
}

void MainApplicationAdaptor::quit()
{
	app->quit();
}

void MainApplicationAdaptor::toggleMainWindow()
{
	app->toggleMainWindow();
}