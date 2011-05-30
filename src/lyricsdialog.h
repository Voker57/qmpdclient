/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Håvard Tautra Knutsen <havtknut@tihlde.org>
 * Copyright (C) 2008 Voker57 <voker57@gmail.com>
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

#ifndef LYRICS_DIALOG_H
#define LYRICS_DIALOG_H

#include "ui_lyricsdialog.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>

class MPDSong;

class LyricsDialog : public QDialog, private Ui::LyricsDialog {
	Q_OBJECT
public:
	LyricsDialog(QWidget *);
	void setSong(const MPDSong &);
	void updateLyrics();
private:
	QString m_artist, m_title;
	QNetworkReply *m_lyricsReply;
	QNetworkAccessManager *m_lyricsManager;
public slots:
	void show();
	void updateLyricsText();
	void errorLyricsText(QNetworkReply::NetworkError);
private slots:
	void setUserSong();
};
#endif
