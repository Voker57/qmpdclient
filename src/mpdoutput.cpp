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
#include "mpdoutput.h"
#include <QString>

struct MPDOutputPrivate : public QSharedData {
	bool enabled;
	int id;
	QString name;
	MPDOutputPrivate() :
			enabled(false),
			id(-1) {}
};

MPDOutput::MPDOutput(mpd_OutputEntity *e) : d(new MPDOutputPrivate) {
	d->enabled = e->enabled;
	d->name = e->name;
	d->id = e->id;
}

MPDOutput::MPDOutput() : d(new MPDOutputPrivate) {}
MPDOutput::MPDOutput(const MPDOutput &other) : d(other.d) {}
MPDOutput::~MPDOutput() {}

QString MPDOutput::name() const {
	Q_ASSERT(d);
	return d->name;
}

int MPDOutput::id() const {
	Q_ASSERT(d);
	return d->id;
}

bool MPDOutput::enabled() const {
	Q_ASSERT(d);
	return d->enabled;
}

MPDOutput &MPDOutput::operator=(const MPDOutput &other) {
	d = other.d;
	return *this;
}
