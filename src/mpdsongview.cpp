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

#include "headerview.h"
#include "mpdsongmodel.h"
#include "mpdsongview.h"
#include "mpd.h"
#include "config.h"
#include <QMenu>

MPDSongView::MPDSongView(QWidget *parent) : AbstractTree(parent), m_model(0) {
	Q_ASSERT(m_menu);
	m_enqueueAction = addMenuAction("enqueue", this, SLOT(enqueue()));
	m_playAction = addMenuAction("play", this, SLOT(play()));
	m_menu->addSeparator();
	m_informationAction = addMenuAction("information", this, SLOT(information()));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClicked(const QModelIndex &)));
}

void MPDSongView::doubleClicked(const QModelIndex &) {
	MPD::instance()->addSongs(selectedSongs(), Config::instance()->enqueue());
}

void MPDSongView::setHeaderView(HeaderView *header) {
	Q_ASSERT(header);
	setModel(m_model = new MPDSongModel(this, header));
	setHeader(header);
	header->restore();
}

void MPDSongView::setSongs(const MPDSongList &songs) {
	Q_ASSERT(m_model);
	m_model->setSongs(songs);
	if (header()->isClickable())
		m_model->sort(header()->sortIndicatorSection(), header()->sortIndicatorOrder());
}

void MPDSongView::setFilter(const QString &needle) {
	Q_ASSERT(m_model);
	m_model->setFilter(needle);
	selectionChanged();
}

void MPDSongView::updateTranslation() {
	Q_ASSERT(m_enqueueAction);
	Q_ASSERT(m_informationAction);
	Q_ASSERT(m_playAction);
	m_enqueueAction->setText(tr("&Enqueue"));
	m_informationAction->setText(tr("&Information..."));
	m_playAction->setText(tr("&Play"));
}

MPDSongViewHeader::MPDSongViewHeader(QWidget *p) : HeaderView(p) {
	setObjectName("mpdsongviewheader");
	m_columns << TRACK << TITLE << ARTIST << ALBUM << GENRE << DATE << COMPOSER << PERFORMER << FILENAME << LENGTH << COMMENT << DISC << URL;
}
