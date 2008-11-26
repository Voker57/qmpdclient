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

#include "jumptosongdialog.h"
#include "playlistitemdelegate.h"
#include "playlistmodel.h"

JumpToSongDialog::JumpToSongDialog(QWidget *parent, const MPDSongList &songs, const MPDSong &playing) : QDialog(parent) {
	setupUi(this);
	searchView->setItemDelegate(new PlaylistDelegate(this));
	searchView->setModel(m_model = new PlaylistModel(this));
	m_model->setSongs(songs);

	searchView->setCurrentIndex(m_model->indexOfSong(playing));

	// signals and slots connections
	connect(searchView, SIGNAL(activated(const QModelIndex &)), this, SLOT(indexActivated(const QModelIndex &)));
	show();
}

void JumpToSongDialog::indexActivated(const QModelIndex &index) {
	Q_ASSERT(m_model);
	if (!index.isValid())
		return;
	foreach(MPDSong s, m_model->songs(index)) {
		m_jumpSong = s;
		accept();
		break;
	}
}

void JumpToSongDialog::on_cancel_clicked() {
	reject();
}

void JumpToSongDialog::on_filter_textChanged(const QString &needle) {
	Q_ASSERT(m_model);
	Q_ASSERT(searchView);
	m_model->setFilter(needle);
	searchView->setCurrentIndex(m_model->index(0, 0));
}

void JumpToSongDialog::on_ok_clicked() {
	Q_ASSERT(m_model);
	Q_ASSERT(searchView);
	QModelIndex i = searchView->currentIndex();
	if (!i.isValid()) {
		reject();
		return;
	}
	foreach(MPDSong s, m_model->songs(i)) {
		m_jumpSong = s;
		accept();
		break;
	}
}

MPDSong JumpToSongDialog::jumpSong() const {
	return m_jumpSong;
}
