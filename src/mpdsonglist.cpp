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

#include "headerview.h"
#include "mpdsonglist.h"

#define STD_COMP(M) \
res = compareCols(l.M(), r.M()); \
if (!res) res = compareCols(l.album(), r.album()); \
if (!res) res = compareCols(l.artist(), r.artist()); \
if (!res) res = compareTrack(l, r); \
if (!res) res = compareCols(l.title(), r.title());

class MPDSongListLessThan {
private:
	int m_sortColumn;
	Qt::SortOrder m_sortOrder;
public:
	inline MPDSongListLessThan(int c, Qt::SortOrder o) : m_sortColumn(c), m_sortOrder(o) {}
	inline bool operator()(const MPDSong &l, const MPDSong &r) const {
		return compareRows(l, r) < 0;
	}

	QString normalizeQString(const QString l) const {
		if (l.startsWith("The ")) {
			return l.mid(4).trimmed();
		}

		return l.trimmed();
	}

	int normalizedCompareCols(const QString l, const QString r) const {
		QString nl = normalizeQString(l);
		QString nr = normalizeQString(r);

		return compareCols(nl, nr);
	}

	int compareCols(const QString l, const QString r) const {
		return QString::localeAwareCompare(l, r);
	}

	int compareCols(int l, int r) const {
		return (l == r) ? 0 : (l < r ? -1 : 1);
	}

	int compareTrack(MPDSong l, MPDSong r) const {
		bool ok1, ok2;
		int ltrack = l.track().toInt(&ok1);
		// Try to handle "8/18" style formated fields
		if (!ok1) ltrack = l.track().section('/', 0, 0).toInt(&ok1);
		int rtrack = r.track().toInt(&ok2);
		if (!ok2) rtrack = r.track().section('/', 0, 0).toInt(&ok2);
		if (ok1 && ok2) {
			return compareCols(ltrack, rtrack);
		} else if (ok1) {
			return -1;
		} else if (ok2) {
			return 1;
		}
		return compareCols(l.track(), r.track());
	}

	int compareRows(MPDSong l, MPDSong r) const {
		int res = 0;

		switch (m_sortColumn) {
			case HeaderView::TRACK:
				res = compareTrack(l, r);
				if (!res) res = compareCols(l.artist(), r.artist());
				if (!res) res = compareCols(l.album(), r.album());
				if (!res) res = compareCols(l.title(), r.title());
				break;

			case HeaderView::LENGTH:
				res = compareCols(l.secs(), r.secs());
				// Fall through
			case HeaderView::ARTIST:
				if (!res) res = compareCols(l.artist(), r.artist());
				if (!res) res = compareCols(l.album(), r.album());
				if (!res) res = compareTrack(l, r);
				if (!res) res = compareCols(l.title(), r.title());
				break;

			case HeaderView::COMPOSER:
				res = compareCols(l.composer(), r.composer());
				if (!res) res = compareCols(l.album(), r.album());
				if (!res) res = compareTrack(l, r);
				if (!res) res = compareCols(l.title(), r.title());
				break;

			case HeaderView::TITLE:
				res = normalizedCompareCols(l.title(), r.title());
				if (!res) res = compareCols(l.artist(), r.artist());
				if (!res) res = compareCols(l.album(), r.album());
				if (!res) res = compareTrack(l, r);
				break;

			case HeaderView::URL:
				res = compareCols(l.url(), r.url());
				break;

			// Similar ones..
			case HeaderView::FILENAME:
				STD_COMP(filename);
				break;

			case HeaderView::GENRE:
				STD_COMP(genre);
				break;

			case HeaderView::DATE:
				STD_COMP(date);
				res = compareCols(l.date(), r.date());
				break;

			case HeaderView::COMMENT:
				STD_COMP(comment);
				break;

			case HeaderView::DISC:
				STD_COMP(disc);
				break;

			case HeaderView::PERFORMER:
				STD_COMP(performer);
				break;

			default: // ALBUM
				res = normalizedCompareCols(l.album(), r.album());
				if (!res) res = compareCols(l.artist(), r.artist());
				if (!res) res = compareTrack(l, r);
				if (!res) res = compareCols(l.title(), r.title());
		}
		if (m_sortOrder != Qt::AscendingOrder)
			res = res * -1;
		return res;
	}
};

MPDSongList::MPDSongList() {}

MPDSongList::MPDSongList(const QList<MPDSong> &songs) {
	MPDSongList me = *this;
	me << songs;
}

void MPDSongList::sort(int column, Qt::SortOrder order) {
	if (isEmpty())
		return;
	MPDSongListLessThan lt(column, order);
	qSort(begin(), end(), lt);
}
