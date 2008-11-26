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

#include "fileview.h"
#include "mpdsongmodel.h"

FileView::FileView(QWidget *parent) : MPDSongView(parent) {
	setObjectName("fileview");
	setHeaderView(new FilelistHeader(this));
}

MPDSongList FileView::selectedSongs() const {
	Q_ASSERT(m_model);
	return m_model->songs(selectedIndexes());
}

FilelistHeader::FilelistHeader(QWidget *p) : MPDSongViewHeader(p) {
	setObjectName("filelistheader");
}

void FilelistHeader::setDefaults() {
	int i = 0;
	foreach (Column col, m_columns) {
		if (col == FILENAME)
			setSortIndicator(i, Qt::AscendingOrder);
		else
			setSectionHidden(i, true);
		++i;
	}
}
