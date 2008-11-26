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

#include "albumview.h"
#include "aafilter.h"
#include "artistview.h"
#include "config.h"
#include "mpdcache.h"
#include "mpdsonglist.h"
#include "songview.h"
#include "stringlistmodel.h"

AlbumView::AlbumView(QWidget *parent) : StringListView(parent), m_artistView(0), m_songView(0) {
	Q_ASSERT(m_model);
	setObjectName("albumview");
	m_model->setShowAll(true);
	connect(Config::instance(), SIGNAL(filterByAlbumOnlyChanged(bool)), this, SLOT(filterByAlbumOnlyChanged()));
}

void AlbumView::setArtistView(ArtistView *a) {
	m_artistView = a;
}

void AlbumView::setSongView(SongView *s) {
	m_songView = s;
}

void AlbumView::filterByAlbumOnlyChanged() {
	selectionChanged();
}

void AlbumView::selectionChanged(const QItemSelection &s, const QItemSelection &u) {
	Q_ASSERT(m_songView);
	StringListView::selectionChanged(s, u);
	m_songView->setSongs(MPDCache::instance()->songsByAA(aaFilter()));
}

AAFilter AlbumView::aaFilter() const {
	Q_ASSERT(m_artistView);
	QStringList albums = selectedStrings();
	
	bool all = false;
	if (albums.isEmpty()) // Nothing selected, lets assume this means 'All'
		all = true;
	foreach (QString s, albums) {
		if (s.isNull())  { // One artist is NULL, so all artists are needed
			all = true;
			break;
		}
	}
	if (all)
		albums = m_strings;

	return AAFilter(m_artistView->aaFilter().artists(), albums, all);
}
