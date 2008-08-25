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

#ifndef PLAYLISTSVIEW_H
#define PLAYLISTSVIEW_H

#include "headerview.h"
#include "mpdsongview.h"

class PlaylistsContentView;

class PlaylistsView : public MPDSongView {
	Q_OBJECT
public:
	PlaylistsView(QWidget *);
	MPDSongList selectedSongs() const;
	void setContentView(PlaylistsContentView *);

public slots:
	void deletePlaylist();
	void updateTranslation();

signals:
	void toggleActions(bool);
	void playlistChanged(const MPDSongList &);

private:
	void selectionChanged(const QItemSelection & = QItemSelection(), const QItemSelection & = QItemSelection());

	PlaylistsContentView *m_contentView;
	QAction *m_deleteAction;
};

class PlaylistsHeader : public HeaderView {
public:
	PlaylistsHeader(QWidget *);
	QString columnName(Column) const;

private:
	void setDefaults();
};
#endif
