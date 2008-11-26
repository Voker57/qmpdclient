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

#include "playlistspanel.h"
#include "config.h"

PlaylistsPanel::PlaylistsPanel() {
	setupUi(this);
	playlistsView->setContentView(playlistsContentView);
	playlistsSplit->restoreState(Config::instance()->playlistsSplitterSizes());
	
	connect(deleteButton, SIGNAL(clicked()), playlistsView, SLOT(deletePlaylist()));
	connect(playlistFilter, SIGNAL(textChanged(const QString &)), playlistsView, SLOT(setFilter(const QString &)));
	connect(playlistsView, SIGNAL(toggleActions(bool)), deleteButton, SLOT(setEnabled(bool)));
	connect(playlistContentFilter, SIGNAL(textChanged(const QString &)), playlistsContentView, SLOT(setFilter(const QString &)));
}

void PlaylistsPanel::updateTranslation() {
	retranslateUi(this);
}

void PlaylistsPanel::on_playlistsSplit_splitterMoved(int, int) {
	Config::instance()->setPlaylistsSplitterSizes(playlistsSplit->saveState());
}
