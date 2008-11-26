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

#include "mpdentities.h"

struct MPDEntitiesPrivate : public QSharedData {
	QStringList directories;
	MPDSongList playlists, songs;
};

MPDEntities::MPDEntities() : d(new MPDEntitiesPrivate) {}

MPDEntities::MPDEntities(const MPDEntities &o) : d(o.d) {}

MPDEntities &MPDEntities::operator=(const MPDEntities &other) {
	d = other.d;
	return *this;
}

MPDEntities::~MPDEntities() {}

void MPDEntities::appendDirectory(const QString &dir) {
	Q_ASSERT(d);
	d->directories << dir;
}

void MPDEntities::appendPlaylist(const MPDSong &p) {
	Q_ASSERT(d);
	d->playlists << p;
}

void MPDEntities::appendSong(const MPDSong &p) {
	Q_ASSERT(d);
	d->songs << p;
}

QStringList MPDEntities::directories() const {
	Q_ASSERT(d);
	return d->directories;
}

MPDSongList MPDEntities::playlists() const {
	Q_ASSERT(d);
	return d->playlists;
}

MPDSongList MPDEntities::songs() const {
	Q_ASSERT(d);
	return d->songs;
}
