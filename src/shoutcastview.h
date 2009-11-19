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

#ifndef SHOUTCASTVIEW_H
#define SHOUTCASTVIEW_H

#include "abstractview.h"
#include <QTreeView>

class ShoutcastModel;
class QAction;

class ShoutcastView : public AbstractTree {
	Q_OBJECT
public:
	ShoutcastView(QWidget *);
public slots:
	void updateTranslation();
private slots:
	void expanded(const QModelIndex & expandedItem);
	void doubleClicked(const QModelIndex & selectedItem);
protected:
	virtual void showEvent(QShowEvent * event);
	virtual MPDSongList selectedSongs() const;
private:
	ShoutcastModel *m_model;
	QAction *m_enqueueAction, *m_informationAction, *m_playAction;
};
#endif
