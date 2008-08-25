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

#ifndef ALBUMVIEW_H
#define ALBUMVIEW_H

#include "stringlistview.h"

class ArtistView;
class SongView;

class AlbumView : public StringListView {
	Q_OBJECT
public:
	AlbumView(QWidget *);
	AAFilter aaFilter() const;
	void setArtistView(ArtistView *);
	void setSongView(SongView *);

private slots:
	void filterByAlbumOnlyChanged();

private:
	void selectionChanged(const QItemSelection & = QItemSelection(), const QItemSelection & = QItemSelection());

	ArtistView *m_artistView;
	SongView *m_songView;
};
#endif
