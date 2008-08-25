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
#include "mpdstats.h"
#include <QString>

struct MPDStatsPrivate : public QSharedData {
	int numberOfArtists, numberOfAlbums, numberOfSongs;
	unsigned long uptime, dbUpdateTime, playTime, dbPlayTime;
	MPDStatsPrivate() :
			numberOfArtists(0),
			numberOfAlbums(0),
			numberOfSongs(0),
			uptime(0),
			dbUpdateTime(0),
			playTime(0),
			dbPlayTime(0) {}
};

MPDStats::MPDStats(mpd_Stats *s) : d(new MPDStatsPrivate) {
	d->numberOfArtists = s->numberOfArtists;
	d->numberOfAlbums = s->numberOfAlbums;
	d->numberOfSongs = s->numberOfSongs;
	d->uptime = s->uptime;
	d->dbUpdateTime = s->dbUpdateTime;
	d->playTime = s->playTime;
	d->dbPlayTime = s->dbPlayTime;
}

MPDStats::MPDStats() : d(new MPDStatsPrivate) {}
MPDStats::MPDStats(const MPDStats &other) : d(other.d) {}
MPDStats::~MPDStats() {}

int MPDStats::numberOfArtists() const {
	Q_ASSERT(d);
	return d->numberOfArtists;
}

int MPDStats::numberOfAlbums() const {
	Q_ASSERT(d);
	return d->numberOfAlbums;
}

int MPDStats::numberOfSongs() const {
	Q_ASSERT(d);
	return d->numberOfSongs;
}

unsigned long MPDStats::uptime() const {
	Q_ASSERT(d);
	return d->uptime;
}

unsigned long MPDStats::dbUpdateTime() const {
	Q_ASSERT(d);
	return d->dbUpdateTime;
}

unsigned long MPDStats::playTime() const {
	Q_ASSERT(d);
	return d->playTime;
}

unsigned long MPDStats::dbPlayTime() const {
	Q_ASSERT(d);
	return d->dbPlayTime;
}

MPDStats &MPDStats::operator=(const MPDStats &other) {
	d = other.d;
	return *this;
}
