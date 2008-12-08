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
#include "dynamicplaylist.h"
#include "mpd.h"
#include "mpdcache.h"

DynamicPlaylist::DynamicPlaylist(QObject *parent) : QObject(parent) {
	setObjectName("dynamicplaylist");
	connect(MPD::instance(), SIGNAL(playingSongUpdated(const MPDSong &)), this, SLOT(autoAdd(const MPDSong &)));
	connect(MPD::instance(), SIGNAL(playingSongUpdated(const MPDSong &)), this, SLOT(autoRemove(const MPDSong &)));
	connect(MPD::instance(), SIGNAL(playlistUpdated(const MPDSongList &)), this, SLOT(playlistUpdated(const MPDSongList &)));
}

void DynamicPlaylist::playlistUpdated(const MPDSongList &fs) {
	m_playlist = fs;
}

void DynamicPlaylist::autoAdd(const MPDSong &song) {
	if (song.isNull() || !Config::instance()->autoAddSongs())
		return;

	if (m_playlist.indexOf(song) >= m_playlist.size() - (1 + Config::instance()->autoAddPos())) {
		MPDSongList add = MPDCache::instance()->randomSongs(1 + Config::instance()->autoAddPos() - (m_playlist.size() - m_playlist.indexOf(song)));
		MPD::instance()->addSongs(add);
	}
}

void DynamicPlaylist::autoRemove(const MPDSong &song) {
	if (song.isNull() || song == m_lastPlaying || !Config::instance()->autoRemoveSongs()) {
		m_lastPlaying = song;
		return;
	}

	// Find song's new ID.
	foreach(MPDSong s, m_playlist) {
		if (!m_lastPlaying.isNull() && s.url() == m_lastPlaying.url()) {
			MPDSongList list;
			list << s;
			MPD::instance()->removeSongs(list);
			break;
		}
	}
	m_lastPlaying = song;
}
