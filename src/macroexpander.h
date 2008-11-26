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

#ifndef MACROEXPANDER_H
#define MACROEXPANDER_H

#include "mpdsong.h"

static QString expandMacros(const MPDSong &song, const QString &pattern) {
	QString rester = pattern;
	rester.replace(QRegExp("%[batngdcfu]"), "");
	QStringList parts = pattern.split('%');
	for (int i = 0; i < parts.size(); i++) {
		QString part = parts[i];
		if (part.startsWith('b'))
			parts[i] = part.replace(0, 1, song.artist());
		else if (part.startsWith('a'))
			parts[i] = part.replace(0, 1, song.album());
		else if (part.startsWith('t'))
			parts[i] = part.replace(0, 1, song.title());
		else if (part.startsWith('n'))
			parts[i] = part.replace(0, 1, song.track());
		else if (part.startsWith('g'))
			parts[i] = part.replace(0, 1, song.genre());
		else if (part.startsWith('d'))
			parts[i] = part.replace(0, 1, song.date());
		else if (part.startsWith('c'))
			parts[i] = part.replace(0, 1, song.composer());
		else if (part.startsWith('f'))
			parts[i] = part.replace(0, 1, song.filename());
		else if (part.startsWith('u'))
			parts[i] = part.replace(0, 1, song.url());
	}
	QString resultat = parts.join("");
	if (resultat == rester)
		return song.filename();
	return resultat;
}
#endif
