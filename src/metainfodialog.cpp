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

#include "metainfodialog.h"
#include "iconmanager.h"
#include "mpdsonglist.h"

MetaInfoDialog::MetaInfoDialog(QWidget *parent, const MPDSongList &songs) : QDialog(parent), m_pos(0) {
	setAttribute(Qt::WA_DeleteOnClose, true);
	m_songs = songs;
	if (m_songs.isEmpty()) {
		close();
		return;
	}
	setupUi(this);
	metaInfoDialogLabel->setPixmap(IconManager::pixmap("metainfodialog", 32));
	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
	nextButton->setEnabled(songs.size() > 1);
	setSong();
	resize(minimumSizeHint());
	show();
}

void MetaInfoDialog::setFieldsVisible(bool e) {
	artistEdit->setVisible(e);
	albumEdit->setVisible(e);
	trackEdit->setVisible(e);
	genreEdit->setVisible(e);
	dateEdit->setVisible(e);
	composerEdit->setVisible(e);
	lengthEdit->setVisible(e);
	discEdit->setVisible(e);
	commentEdit->setVisible(e);
	performerEdit->setVisible(e);
	artistLabel->setVisible(e);
	albumLabel->setVisible(e);
	trackLabel->setVisible(e);
	genreLabel->setVisible(e);
	dateLabel->setVisible(e);
	composerLabel->setVisible(e);
	lengthLabel->setVisible(e);
	discLabel->setVisible(e);
	commentLabel->setVisible(e);
	performerLabel->setVisible(e);
}

void MetaInfoDialog::setSong() {
	progressLabel->setText(QString(tr("(%1 of %2)", "This is used in the context 'File number (%1 of %2)'.")).arg(m_pos + 1).arg(m_songs.size()));
	MPDSong song = m_songs.at(m_pos);
	setFieldsVisible(song.type() != MPDSong::STREAM);
	trackEdit->setText(song.track());
	titleEdit->setText(song.title());
	artistEdit->setText(song.artist());
	albumEdit->setText(song.album());
	urlEdit->setText(song.url());
	lengthEdit->setText(song.time());
	genreEdit->setText(song.genre());
	dateEdit->setText(song.date());
	composerEdit->setText(song.composer());
	commentEdit->setText(song.comment());
	discEdit->setText(song.disc());
	performerEdit->setText(song.performer());
}

void MetaInfoDialog::on_nextButton_clicked() {
	m_pos++;
	nextButton->setEnabled(m_pos < m_songs.size() - 1);
	prevButton->setEnabled(true);
	setSong();
}

void MetaInfoDialog::on_prevButton_clicked() {
	m_pos--;
	prevButton->setEnabled(m_pos > 0);
	nextButton->setEnabled(true);
	setSong();
}
