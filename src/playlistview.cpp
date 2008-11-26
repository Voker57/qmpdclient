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

#include "config.h"
#include "jumptosongdialog.h"
#include "mpd.h"
#include "mpdcache.h"
#include "mpdconnection.h"
#include "playlistitemdelegate.h"
#include "playlistmodel.h"
#include "playlistview.h"
#include <QDragMoveEvent>
#include <QInputDialog>
#include <QMenu>
#include <QPainter>
#include <QShortcut>

PlaylistView::PlaylistView(QWidget *parent) : AbstractList(parent) {
	Q_ASSERT(m_menu);
	setItemDelegate(new PlaylistDelegate(this));
	setModel(m_model = new PlaylistModel(this));
	m_model->setPattern(Config::instance()->playlistPattern());

	// playlist menu
	m_jumpToAction = addMenuAction("jumpTo", this, SLOT(jumpToSong()), false);
	addAction(m_jumpToAction); // Needed for shortcut key to work
	m_menu->addSeparator();
	m_queueAction = addMenuAction("queue", this, SLOT(queueSelectedSong()));
	m_deQueueAction = addMenuAction("deQueue", this, SLOT(deQueueSelectedSong()));

	m_menu->addSeparator();
	m_removeAction = addMenuAction("remove", this, SLOT(removeItems()));
	m_removeAction->setShortcut(Qt::Key_Delete);
	m_removeAction->setShortcutContext(Qt::WidgetShortcut);
	addAction(m_removeAction); // Needed for shortcut key to work
	m_cropAction = addMenuAction("crop", this, SLOT(cropItems()));
	m_clearAction = addMenuAction("clear", MPD::instance(), SLOT(clearPlaylist()), false);

	m_menu->addSeparator();
	m_randomAction = addMenuAction("random", false);
	m_repeatAction = addMenuAction("repeat", false);
	m_shuffleAction = addMenuAction("shuffle", MPD::instance(), SLOT(shufflePlaylist()), false);

	m_menu->addSeparator();
	m_saveAction = addMenuAction("saveAs", this, SLOT(savePlaylist()), false);
	m_informationAction = addMenuAction("information", this, SLOT(information()));
	m_randomAction->setCheckable(true);
	m_repeatAction->setCheckable(true);

	// signals and slots connections
	connect(Config::instance(), SIGNAL(playlistPatternChanged(const QString &)), this, SLOT(playlistPatternChanged(const QString &)));
	connect(MPD::instance(), SIGNAL(playingSongUpdated(const MPDSong &)), this, SLOT(setSong(const MPDSong &)));
	connect(MPD::instance(), SIGNAL(playlistUpdated(const MPDSongList &)), this, SLOT(setPlaylist(const MPDSongList &)));
	connect(MPD::instance(), SIGNAL(randomUpdated(bool)), m_randomAction, SLOT(setChecked(bool)));
	connect(MPD::instance(), SIGNAL(repeatUpdated(bool)), m_repeatAction, SLOT(setChecked(bool)));
	connect(m_randomAction, SIGNAL(toggled(bool)), MPD::instance(), SLOT(setRandom(bool)));
	connect(m_repeatAction, SIGNAL(toggled(bool)), MPD::instance(), SLOT(setRepeat(bool)));
	// Disconnect the default action in AbstractList
	disconnect(this, SIGNAL(activated(const QModelIndex &)), this, SLOT(activated(const QModelIndex &)));
	connect(this, SIGNAL(activated(const QModelIndex &)), this, SLOT(indexActivated(const QModelIndex &)));

	m_focusKey = new QShortcut(Qt::ALT | Qt::SHIFT | Qt::Key_P, this, SLOT(setFocus()));
	m_focusKey->setObjectName("focusPlaylistKey");
}

void PlaylistView::updateTranslation() {
	Q_ASSERT(m_cropAction);
	Q_ASSERT(m_informationAction);
	Q_ASSERT(m_jumpToAction);
	Q_ASSERT(m_randomAction);
	Q_ASSERT(m_removeAction);
	Q_ASSERT(m_clearAction);
	Q_ASSERT(m_repeatAction);
	Q_ASSERT(m_saveAction);
	Q_ASSERT(m_shuffleAction);
	Q_ASSERT(m_queueAction);
	Q_ASSERT(m_deQueueAction);
	Q_ASSERT(m_focusKey);
	m_cropAction->setText(tr("&Crop playlist"));
	m_informationAction->setText(tr("&Information..."));
	m_jumpToAction->setText(tr("J&ump to song..."));
	m_jumpToAction->setShortcut(tr("Ctrl+U", "This is the shortcut for 'Jump to song in playlist'"));
	m_randomAction->setText(tr("Ra&ndom play"));
	m_removeAction->setText(tr("&Remove"));
	m_clearAction->setText(tr("Remove &all"));
	m_repeatAction->setText(tr("Re&peat play"));
	m_saveAction->setText(tr("&Save playlist..."));
	m_shuffleAction->setText(tr("S&huffle playlist"));
	m_queueAction->setText(tr("Add to queue"));
	m_deQueueAction->setText(tr("Remove from queue"));
	m_focusKey->setWhatsThis(tr("Focus playlist"));
}

void PlaylistView::selectionChanged(const QItemSelection &s, const QItemSelection &u) {
	AbstractList::selectionChanged(s, u);
	emit toggleActions(!selectedIndexes().isEmpty());
}

void PlaylistView::playlistPatternChanged(const QString &p) {
	Q_ASSERT(m_model);
	m_model->setPattern(p);
}

void PlaylistView::indexActivated(const QModelIndex &index) {
	Q_ASSERT(m_model);
	foreach(MPDSong s, m_model->songs(index)) {
		MPD::instance()->jumpPlaylistSong(s);
		break;
	}
}

void PlaylistView::cropItems() {
	Q_ASSERT(m_model);
	MPD::instance()->removeSongs(m_model->unSelectedSongs(selectedIndexes()));
}

void PlaylistView::removeItems() {
	QModelIndexList selected = selectedIndexes();
	if (selected.isEmpty())
		return;
	Q_ASSERT(m_model);
	MPD::instance()->removeSongs(m_model->songs(selected));
}

void PlaylistView::setPlaylist(const MPDSongList &songs) {
	Q_ASSERT(m_model);
	QModelIndexList selected = selectedIndexes();
	QModelIndex last = selected.isEmpty() ? QModelIndex() : selected.last();
	m_model->setSongs(songs);
	setCurrentIndex(last);
}


void PlaylistView::setSong(const MPDSong &s) {
	Q_ASSERT(m_model);
	MPDSong playing = s;
	if (m_model->queue().isEmpty()) {
		m_model->setPlaying(s);
	} else {
		playing = m_model->playingSong();
		if (s != playing) {
			m_model->advanceQueue();
			playing = m_model->playingSong();
			if (s != playing) {
				indexActivated(m_model->indexOfSong(playing));
			}
		}
	}
	if (!playing.isNull() && Config::instance()->scrollToPlaying()) {
		scrollTo(m_model->indexOfSong(playing), QAbstractItemView::PositionAtCenter);
		m_hidden = true;
	}
}

void PlaylistView::hideEvent(QHideEvent *e) {
	AbstractList::hideEvent(e);
	m_hidden = true;
}

void PlaylistView::paintEvent(QPaintEvent *e) {
	Q_ASSERT(m_model);
	AbstractList::paintEvent(e);
	if (MPDConnection::instance()->isConnected() && isEnabled()) {
		if (!m_dropLine.isNull()) {
			QPainter painter(viewport());
			painter.drawLine(m_dropLine);
		}
		if (m_hidden && Config::instance()->scrollToPlaying()) {
			scrollTo(m_model->indexOfSong(m_model->playingSong()), QAbstractItemView::PositionAtCenter);
			m_hidden = false;
		}
		return;
	}
}

void PlaylistView::savePlaylist() {
	bool ok;
	QString plName = QInputDialog::getText(this, tr("Save playlist as..."),
	                                       tr("Playlist name:"), QLineEdit::Normal, "", &ok);
	while (ok && !plName.isEmpty()) {
		if (!MPDCache::instance()->playlistExists(plName)) {
			MPDCache::instance()->savePlaylist(plName);
			break;
		}
		QString msg = tr("A playlist with that name already exists.\nPlease use another name:");
		plName = QInputDialog::getText(this, tr("Save playlist as..."),
		                               msg, QLineEdit::Normal, "", &ok);
	}
}

void PlaylistView::jumpToSong() {
	JumpToSongDialog *search = new JumpToSongDialog(this, m_model->songs(), m_model->playingSong());
	if (search->exec() == QDialog::Accepted) {
		MPD::instance()->jumpPlaylistSong(search->jumpSong());
		if (Config::instance()->scrollToPlaying())
			scrollTo(m_model->indexOfSong(search->jumpSong()), QAbstractItemView::PositionAtCenter);
	}
	delete search;
}

MPDSongList PlaylistView::selectedSongs() const {
	Q_ASSERT(m_model);
	return m_model->songs(selectedIndexes());
}

// Set up custom drop indicator, since the default one does not behave as I wish.
void PlaylistView::dragMoveEvent(QDragMoveEvent *e) {
	Q_ASSERT(m_model);
	AbstractList::dragMoveEvent(e);
	if (m_model->rowCount() < 1) // The list is empty, draw nothing
		return;

	startAutoScroll();

	QModelIndex mouseIndex = indexAt(e->pos());
	if (!mouseIndex.isValid())
		mouseIndex = m_model->index(m_model->rowCount() - 1, 0);

	QRect itemRect = visualRect(mouseIndex);

	int y = itemRect.bottom();
	const int halfy = itemRect.y() + itemRect.height() / 2;

	if (mouseIndex.row() == 0 && e->pos().y() < halfy) {
		// We are at first song, and halfway above item, draw line on top
		y = itemRect.top();
		m_model->setTopDrop(true);
	} else
		m_model->setTopDrop(false);

	m_dropLine = QLine(0, y, viewport()->width(), y);
	setDirtyRegion(visibleRegion());
	repaint();
}

// Remove drop indicator
void PlaylistView::dropEvent(QDropEvent *e) {
	AbstractList::dropEvent(e);
	m_dropLine = QLine();
	setDirtyRegion(visibleRegion());
	repaint();
}

// Remove drop indicator
void PlaylistView::dragLeaveEvent(QDragLeaveEvent *e) {
	AbstractList::dragLeaveEvent(e);
	m_dropLine = QLine();
	setDirtyRegion(visibleRegion());
	repaint();
}

// Queue
void PlaylistView::queueSelectedSong() {
	m_model->addToQueue(selectedIndexes());
}

void PlaylistView::deQueueSelectedSong() {
	m_model->removeFromQueue(selectedIndexes());
}
