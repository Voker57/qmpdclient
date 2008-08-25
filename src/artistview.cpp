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

#include "artistview.h"
#include "aafilter.h"
#include "albumview.h"
#include "config.h"
#include "mpdcache.h"
#include "stringlistmodel.h"

ArtistView::ArtistView(QWidget *parent) : StringListView(parent), m_albumView(0) {
	setObjectName("artistview");
	connect(MPDCache::instance(), SIGNAL(artistsUpdated(const QStringList &)), this, SLOT(setStrings(const QStringList &)));
	connect(Config::instance(), SIGNAL(showAllChanged(bool)), this, SLOT(setShowAll(bool)));
	setShowAll(Config::instance()->showAll());
}

void ArtistView::setShowAll(bool a) {
	Q_ASSERT(m_model);
	m_model->setShowAll(a);
}

void ArtistView::setAlbumView(AlbumView *a) {
	m_albumView = a;
}

void ArtistView::selectionChanged(const QItemSelection &s, const QItemSelection &u) {
	Q_ASSERT(m_albumView);
	StringListView::selectionChanged(s, u);
	m_albumView->setStrings(MPDCache::instance()->albumsByArtists(selectedStrings()));
}

AAFilter ArtistView::aaFilter() const {
	QStringList artists = selectedStrings();
	
	if (artists.isEmpty()) // Nothing selected, lets assume this means 'All'
		artists = m_strings;
	foreach (QString s, artists) {
		if (s.isNull())  { // One artist is NULL, so all artists are needed
			artists = m_strings;
			break;
		}
	}

	return AAFilter(artists, MPDCache::instance()->albumsByArtists(selectedStrings()));
}
