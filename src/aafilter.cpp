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

AAFilter::AAFilter() :
		m_allAlbums(false),
		m_notTaggedAlbum(false) {}

AAFilter::AAFilter(const QStringList &artists, const QStringList &albums, bool allAlbums) :
		m_allAlbums(allAlbums),
		m_notTaggedAlbum(false),
		m_albums(albums),
		m_artists(artists) {
	const int idx = m_albums.indexOf(QString());
	if (idx > -1) {
		m_notTaggedAlbum = true;
		m_albums.removeAt(idx);
	}
}

bool AAFilter::allAlbums() const {
	return m_allAlbums;
}

bool AAFilter::notTaggedAlbum() const {
	return m_notTaggedAlbum;
}

bool AAFilter::hasAlbum(const QString &album) const {
	return m_albums.contains(album);
}

bool AAFilter::hasArtist(const QString &artist) const {
	return m_artists.contains(artist);
}

QStringList AAFilter::albums() const {
	return m_albums;
}

QStringList AAFilter::artists() const {
	return m_artists;
}

QDataStream &operator<<(QDataStream &s, const AAFilter &g) {
	s << g.m_allAlbums;
	s << g.m_notTaggedAlbum;
	s << g.m_albums;
	s << g.m_artists;
	return s;
}

QDataStream &operator>>(QDataStream &s, AAFilter &g) {
	s >> g.m_allAlbums;
	s >> g.m_notTaggedAlbum;
	s >> g.m_albums;
	s >> g.m_artists;
	return s;
}
