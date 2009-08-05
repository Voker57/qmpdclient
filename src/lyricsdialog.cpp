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

#include "lyricsdialog.h"
#include "config.h"
#include "mpdsong.h"

#include <QHttp>
#include <QHttpRequestHeader>

LyricsDialog::LyricsDialog(QWidget *parent) : QDialog(parent) {
	setupUi(this);
	lyricsBrowser->setOpenLinks(false);
	m_http = new QHttp("lyricwiki.org", 80, this);
	connect(m_http, SIGNAL(requestFinished(int,bool)), this, SLOT(gotResponse(int,bool)));
}

void LyricsDialog::show() {
	updateLyrics();
	QDialog::show();
}

void LyricsDialog::updateLyrics() {
	setWindowTitle(QString("Lyrics: %1 by %2").arg(m_title, m_artist));
	artistEdit->setText(m_artist);
	titleEdit->setText(m_title);
	lyricsBrowser->setPlainText(tr("Getting lyrics from server..."));
	QUrl req("http://lyricwiki.org/api.php");
	req.addQueryItem("func", "getSong");
	req.addQueryItem("artist", m_artist);
	req.addQueryItem("song", m_title);
	req.addQueryItem("fmt","html");
	m_http->get(req.toEncoded());
}


void LyricsDialog::setSong(const MPDSong &s) {
	m_artist=s.artist();
	m_title=s.title();
	if(!isHidden()) updateLyrics();
}

void LyricsDialog::gotResponse(int id, bool error) {
	Q_UNUSED(id);
	if(error) lyricsBrowser->setPlainText(m_http->errorString());
	else
	{
		QByteArray txt = m_http->readAll();
		lyricsBrowser->setHtml(QString::fromUtf8(txt.data()));
	}
}

void LyricsDialog::setUserSong() {
	m_artist = artistEdit->text();
	m_title = titleEdit->text();
	updateLyrics();
}
