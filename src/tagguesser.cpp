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

#include "tagguesser.h"
#include "config.h"
#include "debug.h"
#include "mpdsong.h"
#include <QStringList>

QHash<QString, QString> TagGuesser::patterns() {
	QHash<QString, QString> patterns;
	patterns["/%b/%a/%n - %t."] = "/music/Artist/Album/42 - Title of Song.ogg";
	patterns["/%b/%a (%i)/%n - %t."] = "/music/Artist/Album (1992)/42 - Title of Song.ogg";
	patterns["/%b/%n - %a - %t."] = "/music/Artist/42 - Album - Title of Song.ogg";
	patterns["/%n - %b - %a - %t."] = "/music/42 - Artist - Album - Title of Song.ogg";
	return patterns;
}

void TagGuesser::guessTags(MPDSong &song) {
	QString pattern = Config::instance()->guessPattern();

	// Check that we have a pattern at all
	if (pattern.isEmpty())
		return;

	// Cant guess from URL's
	if (song.url().contains("://"))
		return;

	// Return if we already have everything we can guess
	if (!(song.title().isEmpty() || song.album().isEmpty() || song.artist().isEmpty() || song.track().isEmpty()))
		return;

	DEBUG4("Guessing..");
	// Tokens to expand. %a=album, %b=band, %n=tracknr, %t=title, %i=ignore
	QStringList matchers = pattern.split(QRegExp("%[abnti]"), QString::SkipEmptyParts);
	QStringList markers = pattern.split('%', QString::SkipEmptyParts);

	// Check that we actually have any matchers, if not, return filename as title, the rest empty.

	DEBUG4("Matchers size: %d %d", matchers.size(), markers.size());
	if (matchers.isEmpty() || markers.isEmpty()) {

		DEBUG4("No matchers or no markers");
		if (song.title().isEmpty())
			song.setTitle(song.url());
		return;
	}

	// Remove bogus markers

	DEBUG4("Removing bogus markers");
	markers = markers.filter(QRegExp("^[abnti]"));
	// Remove trailing garbage on markers

	DEBUG4("Removing trailing garbage on markers");
	markers = markers.replaceInStrings(QRegExp("^([abnti]).*"), "%\\1");


	DEBUG4("Adding greedy front matcher");
	// If pattern does not have leading characters, add a greedy matcher at front so we get the whole start
	if (pattern.contains(QRegExp("^%[abnti]")))
		matchers.push_front("^");

	// If pattern contains trailing characters, add a dummy marker at the end.
	DEBUG4("Finding last matcher");
	QString lastMarker = markers.last();

	DEBUG4("Finding end of last marker");
	int endOfLastMatcher = pattern.lastIndexOf(lastMarker) + lastMarker.size();

	DEBUG4("Adding dummy end marker");
	if (endOfLastMatcher < pattern.size())
		markers += "trailingcharacters";

	foreach (QString p, markers) {
		DEBUG4("marker : %s", qPrintable(p));
	}
	foreach (QString p, matchers) {
		DEBUG4("matcher: %s", qPrintable(p));
	}

	DEBUG4("checkpoint");
	// Match pattern, starting last
	QString left = song.url();

	DEBUG4("Matching pattern, starting last");
	while (!matchers.empty()) {
		QString p = matchers.takeLast();
		QString m = markers.takeLast();
		int pos = left.lastIndexOf(p);
		QString result = left.mid(pos + p.size());
		DEBUG4("%s, %s matches: %s at pos %d", qPrintable(left), qPrintable(m), qPrintable(result), pos);
		left = left.mid(0, pos);
		// Save what we found
		if (m == "%a" && song.album().isEmpty())
			song.setAlbum(result);
		if (m == "%b" && song.artist().isEmpty())
			song.setArtist(result);
		if (m == "%n" && song.track().isEmpty())
			song.setTrack(result);
		if (m == "%t" && song.title().isEmpty())
			song.setTitle(result);
	}
}
