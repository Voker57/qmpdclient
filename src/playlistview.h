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

#ifndef PLAYLISTVIEW_H
#define PLAYLISTVIEW_H

#include "abstractview.h"
#include <QLine>

class MPDSong;
class PlaylistModel;
class QShortcut;

class PlaylistView : public AbstractList {
	Q_OBJECT
public:
	PlaylistView(QWidget *);
	MPDSongList selectedSongs() const;
	void setFilter(const QString &);

public slots:
	void updateTranslation();

signals:
	void toggleActions(bool);

private slots:
	void cropItems();
	void indexActivated(const QModelIndex &);
	void playlistPatternChanged(const QString &);
	void removeItems();
	void savePlaylist();
	void setPlaylist(const MPDSongList &);
	void setSong(const MPDSong &);
	void queueSelectedSong();

private:
	void dragLeaveEvent(QDragLeaveEvent *);
	void dragMoveEvent(QDragMoveEvent *);
	void dropEvent(QDropEvent *);
	bool hasDroppableFormat(const QMimeData *);
	void hideEvent(QHideEvent *);
	void paintEvent(QPaintEvent *);
	void selectionChanged(const QItemSelection & = QItemSelection(), const QItemSelection & = QItemSelection());

	bool m_hidden;
	PlaylistModel *m_model;
	QAction *m_clearAction, *m_cropAction, *m_informationAction,  *m_randomAction;
	QAction *m_removeAction, *m_repeatAction, *m_saveAction, *m_shuffleAction;
	QAction *m_queueAction;
	QLine m_dropLine;
	QShortcut *m_focusKey;
};
#endif
