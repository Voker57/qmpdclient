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
#include "mpdstatus.h"
#include <QString>

struct MPDStatusPrivate : public QSharedData {
	int volume, repeat, random, playlistLength, state,
	crossfade, song, songid, elapsedTime, totalTime,
	bitRate, bits, channels, updatingDb;
	long long playlist;
	unsigned int sampleRate;
	QString error;

	MPDStatusPrivate() :
			volume(0),
			repeat(0),
			random(0),
			playlistLength(0),
			state(0),
			crossfade(0),
			song(-1),
			songid(-1),
			elapsedTime(0),
			totalTime(0),
			bitRate(0),
			bits(0),
			channels(0),
			updatingDb(0),
			playlist(0),
			sampleRate(0) {}
};

MPDStatus::MPDStatus(mpd_Status *s) : d(new MPDStatusPrivate) {
	d->volume = s->volume;
	d->repeat = s->repeat;
	d->random = s->random;
	d->playlistLength = s->playlistLength;
	d->state = s->state;
	d->crossfade = s->crossfade;
	d->song = s->song;
	d->songid = s->songid;
	d->elapsedTime = s->elapsedTime;
	d->totalTime = s->totalTime;
	d->bitRate = s->bitRate;
	d->bits = s->bits;
	d->channels = s->channels;
	d->updatingDb = s->updatingDb;
	d->playlist = s->playlist;
	d->sampleRate = s->sampleRate;
	d->error = QString::fromUtf8(s->error);
}

MPDStatus::MPDStatus() : d(new MPDStatusPrivate) {}
MPDStatus::MPDStatus(const MPDStatus &other) : d(other.d) {}
MPDStatus::~MPDStatus() {}


int MPDStatus::MPDStatus::volume() const {
	Q_ASSERT(d);
	return d->volume;
}

int MPDStatus::repeat() const {
	Q_ASSERT(d);
	return d->repeat;
}

int MPDStatus::random() const {
	Q_ASSERT(d);
	return d->random;
}

int MPDStatus::playlistLength() const {
	Q_ASSERT(d);
	return d->playlistLength;
}

int MPDStatus::state() const {
	Q_ASSERT(d);
	return d->state;
}

int MPDStatus::crossfade() const {
	Q_ASSERT(d);
	return d->crossfade;
}

int MPDStatus::song() const {
	Q_ASSERT(d);
	return d->song;
}

int MPDStatus::songid() const {
	Q_ASSERT(d);
	return d->songid;
}

int MPDStatus::elapsedTime() const {
	Q_ASSERT(d);
	return d->elapsedTime;
}

void MPDStatus::setElapsedTime(int time) {
	Q_ASSERT(d);
	d->elapsedTime = time;
}

int MPDStatus::totalTime() const {
	Q_ASSERT(d);
	return d->totalTime;
}

int MPDStatus::bitRate() const {
	Q_ASSERT(d);
	return d->bitRate;
}

int MPDStatus::bits() const {
	Q_ASSERT(d);
	return d->bits;
}

int MPDStatus::channels() const {
	Q_ASSERT(d);
	return d->channels;
}

int MPDStatus::updatingDb() const {
	Q_ASSERT(d);
	return d->updatingDb;
}

long long MPDStatus::playlist() const {
	Q_ASSERT(d);
	return d->playlist;
}

unsigned int MPDStatus::sampleRate() const {
	Q_ASSERT(d);
	return d->sampleRate;
}

QString MPDStatus::error() const {
	Q_ASSERT(d);
	return d->error;
}

MPDStatus &MPDStatus::operator=(const MPDStatus &other) {
	d = other.d;
	return *this;
}
