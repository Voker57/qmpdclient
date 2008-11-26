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
#include "mpdcache.h"
#include "mpdconnection.h"
#include "mpdentities.h"
#include "mpdstats.h"
#include "mpdstatus.h"

#define ASSERT Q_ASSERT(d); Q_ASSERT(d->cache); Q_ASSERT(d->connection);

struct MPDPrivate {
	bool isConnected() const;
	bool isPaused() const;
	bool isPlaying() const;
	MPDSong currentSong() const;
	MPDSongList playlist() const;
	void reverseMoveAddedSongs(int toPos) const;
	void poll();

	MPDStats stats, prevStats;
	MPDStatus status, prevStatus;
};

bool MPDPrivate::isConnected() const {
	return MPDConnection::instance()->isConnected();
}

bool MPDPrivate::isPaused() const {
	return isConnected() && status.state() == MPD_STATUS_STATE_PAUSE;
}

bool MPDPrivate::isPlaying() const {
	return isConnected() && status.state() == MPD_STATUS_STATE_PLAY;
}

MPDSong MPDPrivate::currentSong() const {
	MPDSong ret;
	if (isConnected()) {
		mpd_call(currentSong, CurrentSong);
		MPDSongList songs = MPDConnection::instance()->entities().songs();
		if (!songs.isEmpty())
			ret = songs.first();
		if (!mpd_cleanup())
			return MPDSong();
	}
	return ret;
}

MPDSongList MPDPrivate::playlist() const {
	MPDSongList playlist;
	if (isConnected()) {
		mpd_call(playlist, PlaylistInfo, -1);
		playlist = MPDConnection::instance()->entities().songs();
		if (!mpd_cleanup())
			return MPDSongList();
	}
	return playlist;
}

void MPDPrivate::reverseMoveAddedSongs(int toPos) const {
	if (!isConnected() || toPos < 0)
		return;

	// Find new ids in playlist
	mpd_call(reverseMoveAddedSongs, PlChanges, status.playlist());
	MPDSongList songsToMove = MPDConnection::instance()->entities().songs();
	if (!mpd_cleanup())
		return;

	// Move the new ids, reverse order.
	mpd_beginList();
	for (int i = songsToMove.size() - 1; i > -1; i--) {
		mpd_call(reverseMoveAddedSongs, MoveId, songsToMove.at(i).id(), toPos);
	}
	mpd_endList();
	mpd_cleanup();
}

void MPDPrivate::poll() {
	prevStats = stats;
	prevStatus = status;
	stats = MPDConnection::instance()->stats();
	status = MPDConnection::instance()->status();

	// Simple statuses
	if (status.volume() != prevStatus.volume())
		emit MPD::instance()->volumeUpdated(status.volume());

	if (status.repeat() != prevStatus.repeat())
		emit MPD::instance()->repeatUpdated(status.repeat());

	if (status.random() != prevStatus.random())
		emit MPD::instance()->randomUpdated(status.random());

	if (status.state() != prevStatus.state())
		emit MPD::instance()->stateUpdated(isPlaying());

	if (status.totalTime() != prevStatus.totalTime() || status.elapsedTime() != prevStatus.elapsedTime())
		emit MPD::instance()->timeUpdated(status.elapsedTime(), status.totalTime());

	// Stats
	if (stats.dbUpdateTime() != prevStats.dbUpdateTime()) {
		emit MPD::instance()->statsUpdated(stats);
		MPDCache::instance()->reReadLibrary(stats);
	}

	bool possibleSongChange = false;
	if (status.playlist() != prevStatus.playlist()) {
		emit MPD::instance()->playlistUpdated(playlist());

		// If songid has not changed, but playlist has, it might be a stream which has
		// switched song, since that is the way they notify song change. Update to check.
		if (status.songid() == prevStatus.songid())
			possibleSongChange = true;
	}

	if (possibleSongChange) {
		emit MPD::instance()->playingSongUpdated(currentSong());
	}
	// Good olde song change
	else if (status.songid() != prevStatus.songid()) {
		emit MPD::instance()->playingSongUpdated(currentSong());
	}
	// State change
	else if ((prevStatus.state() == MPDStatus::STOP && status.state() == MPDStatus::PLAY) ||
	         (prevStatus.state() == MPDStatus::UNKNOWN && status.state() == MPDStatus::PLAY)) {
		emit MPD::instance()->playingSongUpdated(currentSong());
	}
}
