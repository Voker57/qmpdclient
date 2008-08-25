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

#include "aafilter.h"
#include "mpdcache.h"
#include "mpdsonglist.h"
#include "stringlistmodel.h"
#include "stringlistview.h"
#include <QMenu>

StringListView::StringListView(QWidget *parent) : AbstractList(parent) {
	Q_ASSERT(m_menu);
	setModel(m_model = new StringListModel(this));

	m_enqueueAction = addMenuAction("enqueue", this, SLOT(enqueue()));
	m_playAction = addMenuAction("play", this, SLOT(play()));
	m_menu->addSeparator();
	m_informationAction = addMenuAction("information", this, SLOT(information()));
}

QStringList StringListView::selectedStrings() const {
	Q_ASSERT(m_model);
	return m_model->stringList(selectedIndexes());
}

MPDSongList StringListView::selectedSongs() const {
	return MPDCache::instance()->songsByAA(aaFilter());
}

void StringListView::filter(const QString &needle) {
	Q_ASSERT(m_model);
	m_model->setStringList(m_strings.filter(QRegExp(needle, Qt::CaseInsensitive)));
}

void StringListView::setStrings(const QStringList &strings) {
	Q_ASSERT(m_model);
	m_model->setStringList(m_strings = strings);
	setCurrentIndex(m_model->index(0));
}

void StringListView::updateTranslation() {
	Q_ASSERT(m_enqueueAction);
	Q_ASSERT(m_informationAction);
	Q_ASSERT(m_playAction);
	m_enqueueAction->setText(tr("&Enqueue"));
	m_informationAction->setText(tr("&Information..."));
	m_playAction->setText(tr("&Play"));
}
