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

#ifndef MPDSTATUS_H
#define MPDSTATUS_H

#include <QSharedData>

struct MPDStatusPrivate;
struct mpd_Status;

class MPDStatus {
public:
	enum State { STOP, PLAY, PAUSE, UNKNOWN };
	MPDStatus();
	MPDStatus(mpd_Status *);
	MPDStatus(const MPDStatus &);
	MPDStatus &operator=(const MPDStatus &);
	~MPDStatus();
	int volume() const;
	int repeat() const;
	int random() const;
	int playlistLength() const;
	int state() const;
	int crossfade() const;
	int song() const;
	int songid() const;
	int elapsedTime() const;
	void setElapsedTime(int time);
	int totalTime() const;
	int bitRate() const;
	int bits() const;
	int channels() const;
	int updatingDb() const;
	long long playlist() const;
	unsigned int sampleRate() const;
	QString error() const;

private:
	QSharedDataPointer<MPDStatusPrivate> d;
};
#endif
