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

LyricsDialog::LyricsDialog(QWidget *parent) : QDialog(parent) {
	setupUi(this);
	m_lyricsManager = new QNetworkAccessManager(this);
	m_lyricsReply = 0;
}

void LyricsDialog::show() {
	updateLyrics();
	QDialog::show();
}

void LyricsDialog::updateLyrics() {
	if(m_lyricsReply)
	{
		m_lyricsReply->abort();
		m_lyricsReply = 0;
	}
	setWindowTitle(QString("Lyrics: %1 by %2").arg(m_title, m_artist));
	artistEdit->setText(m_artist);
	titleEdit->setText(m_title);
	lyricsBrowser->setHtml(tr("Getting lyrics from server..."));
	QByteArray ba_artist = QUrl::toPercentEncoding(m_artist.replace(" ", "_"));
	QByteArray ba_title = QUrl::toPercentEncoding(m_title.replace(" ", "_"));
	QUrl url(QString("http://lyrics.wikia.com/" + QString(ba_artist) + ":" + QString(ba_title)));
	m_lyricsReply = m_lyricsManager->get(QNetworkRequest(url));
	connect(m_lyricsReply, SIGNAL(finished()), this, SLOT(updateLyricsText()));
	connect(m_lyricsReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(errorLyricsText(QNetworkReply::NetworkError)));

}

void LyricsDialog::updateLyricsText() {
	QString html = QString(((QNetworkReply *)sender())->readAll());
	QRegExp wittyRegexp("<div class='lyricbox'><script.*</script>(.*)<!--");
	wittyRegexp.setMinimal(true);
	if(wittyRegexp.indexIn(html) > -1)
	{
		lyricsBrowser->setText(wittyRegexp.cap(1));
	} else
	{
		lyricsBrowser->setText(QString("No text found"));
	}
	m_lyricsReply = 0;
}

void LyricsDialog::errorLyricsText(QNetworkReply::NetworkError code) {
	lyricsBrowser->setText(QString("Error retrieving lyrics (%1)").arg(code));
	m_lyricsReply = 0;
}

void LyricsDialog::setSong(const MPDSong &s) {
	m_artist=s.artist();
	m_title=s.title();
	if(!isHidden()) updateLyrics();
}


void LyricsDialog::setUserSong() {
	m_artist = artistEdit->text();
	m_title = titleEdit->text();
	updateLyrics();
}
