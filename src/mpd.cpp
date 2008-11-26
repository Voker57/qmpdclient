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

#include "libmpdclient.h"
#include "mpd.h"
#include "mpd_p.h"
#include <QTimer>

MPD *MPD::m_instance = 0;

// Constructors and such
MPD::MPD() : d(new MPDPrivate) {
	setObjectName("MPD");
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(poll()));
	timer->start(500);
}

MPD::~MPD() {
	Q_ASSERT(d);
	delete d;
}

/**
 * Returns the one and only instance of MPD.
 * @return MPD.
 */
MPD *MPD::instance() {
	if (!m_instance)
		m_instance = new MPD;
	return m_instance;
}

void MPD::poll() {
	Q_ASSERT(d);
	d->poll();
}

void MPD::addSongs(const MPDSongList &songs, bool enqueue, int toPos) const {
	Q_ASSERT(d);
	if (!d->isConnected() || songs.isEmpty())
		return;
	
	mpd_beginList();
	if (!enqueue)
		mpd_call(MPD::addSongs, Clear);
	foreach(MPDSong song, songs) {
		if (song.type() == MPDSong::PLAYLIST)
			mpd_call(MPD::addSongs, Load, song.url().toUtf8());
		else
			mpd_call(MPD::addSongs, Add, song.url().toUtf8());
	}
	if (!enqueue)
		mpd_call(MPD::addSongs, Play, 0);
	mpd_endList();

	if (!mpd_cleanup())
		return;

	// Finish this command, so that playlist is updated.
	d->reverseMoveAddedSongs(toPos);
}

void MPD::moveSongs(const MPDSongList &songs, int toPos) const {
	Q_ASSERT(d);
	if (!d->isConnected() || songs.isEmpty() || toPos < 0)
		return;

	mpd_beginList();
	if (toPos < songs.first().pos()) {
		// Moving upwards, go reverse
		for (int i = songs.size() - 1; i > -1; i--) {
			mpd_call(MPD::moveSongs, MoveId, songs[i].id(), toPos);
		}
	} else {
		foreach(MPDSong song, songs) {
			mpd_call(MPD::moveSongs, MoveId, song.id(), toPos);
		}
	}
	mpd_endList();
	mpd_cleanup();
}

void MPD::togglePlay() const {
	Q_ASSERT(d);
	if (d->isPlaying() || d->isPaused())
		pause();
	else
		play();
}

void MPD::volumeUp(int up) const {
	Q_ASSERT(d);
	setVolume(d->status.volume() + qAbs(up));
}

void MPD::volumeDown(int down) const {
	Q_ASSERT(d);
	setVolume(d->status.volume() - qAbs(down));
}


void MPD::seekBackward() {
	Q_ASSERT(d);
	if (d->status.elapsedTime() > 10) {
		d->status.setElapsedTime(d->status.elapsedTime() - 10);
		seek(d->status.elapsedTime());
	} else
		seek(0);
}

void MPD::seekForward() {
	Q_ASSERT(d);
	d->status.setElapsedTime(d->status.elapsedTime() + 10);
	seek(d->status.elapsedTime());
}

int MPD::crossfade() const {
	Q_ASSERT(d);
	return d->isConnected() ? d->status.crossfade() : 0;
}

void MPD::toggleOutputDevice(int id, bool enable) const {
	Q_ASSERT(d);
	if (!d->isConnected())
		return;

	if (enable) {
		mpd_call(MPD::toggleOutputDevice, EnableOutput, id);
	} else {
		mpd_call(MPD::toggleOutputDevice, DisableOutput, id);
	}
	mpd_cleanup();
}

void MPD::removeSongs(const MPDSongList &songs) const {
	Q_ASSERT(d);
	if (songs.isEmpty() || !d->isConnected())
		return;

	mpd_beginList();
	foreach(MPDSong song, songs) {
		mpd_call(MPD::removeSongs, DeleteId, song.id());
	}
	mpd_endList();
	mpd_cleanup();
}

// Macro for simplifying all these similar small methods.
#define MPD_METHOD(NAME, ARG, CMD, ...) \
	void MPD::NAME(ARG) const { \
		Q_ASSERT(d); \
		if (!d->isConnected()) \
			return; \
 		MPDConnection::instance()->setCaller(QString("MPD::%1").arg(#NAME), QString("mpd_send%1Command").arg(#CMD)); \
 		mpd_send ## CMD ## Command(MPDConnection::instance()->connection(), ##__VA_ARGS__); \
		MPDConnection::instance()->finishCommand(); \
	}
// Macro for methods which take no arguments
#define MPD_METH(NAME, CMD, ...) MPD_METHOD(NAME, , CMD, ##__VA_ARGS__)

// No arguments
MPD_METH(stop, Stop);
MPD_METH(next, Next);
MPD_METH(prev, Prev);
MPD_METH(play, PlayId, -1)
MPD_METH(pause, Pause, !d->isPaused())
MPD_METH(clearPlaylist, Clear);
MPD_METH(shufflePlaylist, Shuffle);
// One primitive argument
MPD_METHOD(setCrossfade, int c, Crossfade, c)
MPD_METHOD(setRepeat, bool r, Repeat, r)
MPD_METHOD(setRandom, bool r, Random, r)
MPD_METHOD(setVolume, int v, Setvol, v)
// Pass objects, and call methods on them
MPD_METHOD(jumpPlaylistSong, const MPDSong &s, PlayId, s.id())
MPD_METHOD(seek, int pos, SeekId, d->status.songid(), pos)
