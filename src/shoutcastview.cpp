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
#include "shoutcastmodel.h"
#include "iconmanager.h"
#include "shoutcastview.h"
#include "shoutcaststation.h"
#include "mpdsonglist.h"
#include <QMenu>
//#include <QDebug>

ShoutcastView::ShoutcastView(QWidget *parent) : AbstractTree(parent) {
	setObjectName("shoutcastview");
	setModel(m_model = new ShoutcastModel(this));
	connect(this, SIGNAL(expanded(const QModelIndex &)), this, SLOT(expanded(const QModelIndex &)));
	setColumnWidth(0, 300);
	m_enqueueAction = addMenuAction("enqueue", this, SLOT(enqueue()));
	m_playAction = addMenuAction("play", this, SLOT(play()));
	m_menu->addSeparator();
	m_informationAction = addMenuAction("information", this, SLOT(information()));
}

void ShoutcastView::updateTranslation() {
	m_enqueueAction->setText(tr("&Enqueue"));
	m_informationAction->setText(tr("&Information..."));
	m_playAction->setText(tr("&Play"));
}

MPDSongList ShoutcastView::selectedSongs() const {
	Q_ASSERT(m_model);
	return m_model->songs(selectedIndexes());
}

void ShoutcastView::showEvent(QShowEvent * /*event*/) {
	m_model->downloadGenres();
}

void ShoutcastView::expanded(const QModelIndex & expandedItem)
{
	//qDebug() << expandedItem.data() << " expanded";
	if (!expandedItem.parent().isValid())
		m_model->downloadStationsForGenre(expandedItem.data().toString());
	else
		m_model->downloadPlaylistForStation(
				qvariant_cast<ShoutcastStation>(expandedItem.data(ShoutcastModel::StationRole)));
}
