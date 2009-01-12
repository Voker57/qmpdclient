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

#ifndef CONTROLPANEL_H
#define CONTROLPANEL_H

#include "ui_controlpanel.h"

class CoverArtDialog;
class LyricsDialog;
class MPDSong;
class QShortcut;
class LastFmSubmitter;

class ControlPanel : public QWidget, private Ui::ControlPanel {
	Q_OBJECT
public:
	ControlPanel(QWidget *);

public slots:
	void updateTranslation();

private slots:
	void setSong(const MPDSong &);
	void showCoverArtChanged(bool);

private:
	CoverArtDialog *m_coverArt;
	LyricsDialog *m_lyricsDialog;
	LastFmSubmitter * m_lastFm;
	QShortcut *m_fwdKey, *m_rwdKey, *m_volUpKey, *m_volDnKey;
};
#endif
