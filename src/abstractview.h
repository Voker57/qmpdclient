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

#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QListView>
#include <QTreeView>

class AbstractTree  : public QTreeView {
	Q_OBJECT

public slots:
	void connected();
	void disconnected();

private slots:
	void activated(const QModelIndex &);
	void enqueue();
	void information();
	void play();
#ifndef Q_MOC_RUN
#define TYPE AbstractTree
#include "abstractview_defn.h"
#undef TYPE
#endif
};

class AbstractList : public QListView {
	Q_OBJECT

public slots:
	void connected();
	void disconnected();

private slots:
	void activated(const QModelIndex &);
	void enqueue();
	void information();
	void play();
#ifndef Q_MOC_RUN
#define TYPE AbstractList
#include "abstractview_defn.h"
#undef TYPE
#endif
};
#endif
