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

#ifndef MPDSTATS_H
#define MPDSTATS_H

#include <QSharedData>

struct MPDStatsPrivate;
struct _mpd_Stats;

class MPDStats {
public:
	MPDStats();
	MPDStats(_mpd_Stats *);
	MPDStats(const MPDStats &);
	~MPDStats();
	int numberOfArtists() const;
	int numberOfAlbums() const;
	int numberOfSongs() const;
	unsigned long uptime() const;
	unsigned long dbUpdateTime() const;
	unsigned long playTime() const;
	unsigned long dbPlayTime() const;
	MPDStats &operator=(const MPDStats &);

private:
	QSharedDataPointer<MPDStatsPrivate> d;
};
#endif
