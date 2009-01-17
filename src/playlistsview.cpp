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

#include <QMenu>
#include "mpdcache.h"
#include "mpdsongmodel.h"
#include "playlistsview.h"
#include "plconview.h"

PlaylistsView::PlaylistsView(QWidget *parent)
	: MPDSongView(parent)
{
	Q_ASSERT(m_menu);
	setObjectName("playlistsview");
	setHeaderView(new PlaylistsHeader(this));

	m_menu->addSeparator();
	m_deleteAction = addMenuAction("delete", this, SLOT(deletePlaylist()));
	m_deleteAction->setShortcut(Qt::Key_Delete);
	m_deleteAction->setShortcutContext(Qt::WidgetShortcut);
	addAction(m_deleteAction); // Needed for shortcut key to work
	
	connect(MPDCache::instance(), SIGNAL(playlistsUpdated(const MPDSongList &)), this, SLOT(setSongs(const MPDSongList &)));
}

void PlaylistsView::updateTranslation() {
	Q_ASSERT(m_deleteAction);
	MPDSongView::updateTranslation();
	m_deleteAction->setText(tr("&Delete"));
}

void PlaylistsView::selectionChanged(const QItemSelection &s, const QItemSelection &u) {
	Q_ASSERT(m_contentView);
	MPDSongView::selectionChanged(s, u);
	emit toggleActions(!s.indexes().isEmpty());
	m_contentView->setSongs(MPDCache::instance()->songsByPlaylists(m_model->songs(s.indexes())));
}


void PlaylistsView::setContentView(PlaylistsContentView *cv) {
	m_contentView = cv;
}

void PlaylistsView::deletePlaylist() {
	Q_ASSERT(m_model);
	MPDCache::instance()->deletePlaylists(m_model->songs(selectedIndexes()));
	selectionChanged();
}

MPDSongList PlaylistsView::selectedSongs() const {
	return MPDCache::instance()->songsByPlaylists(m_model->songs(selectedIndexes()));
}

PlaylistsHeader::PlaylistsHeader(QWidget *p) : HeaderView(p) {
	setObjectName("playlistsheader");
	m_columns << TITLE;
}

void PlaylistsHeader::setDefaults() {
	setSortIndicator(0, Qt::AscendingOrder);
}

QString PlaylistsHeader::columnName(Column col) const {
	if (col == TITLE)
		return QObject::tr("Playlist");
	return HeaderView::columnName(col);
}
