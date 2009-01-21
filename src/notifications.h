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

#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <QObject>

#include "coverartdialog.h"

class MPDSong;
class QDBusInterface;
class CoverArtDialog;

class Notifications
	: public QObject
{
	Q_OBJECT

public:
	Notifications(QObject *);
	enum Type { CUSTOM = 0, FREEDESKTOP = 1 };
	static QList<Type> notifiers();
	static QString name(Type);

private slots:
	void setSong(const MPDSong &);

private:
	bool notifyDBus(const QString &);
	bool notifyCustom(const QString &);
	void notify(const QString &);
	QString makeTitle(const MPDSong &);

	bool m_dbus;
	QDBusInterface *m_interface;
	QString m_previousUrl;
	CoverArtDialog *m_coverArt;
};

#endif
