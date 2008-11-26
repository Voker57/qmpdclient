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

#ifndef STRINGLISTVIEW_H
#define STRINGLISTVIEW_H

#include "abstractview.h"

class AAFilter;
class StringListModel;

class StringListView : public AbstractList {
	Q_OBJECT

public:
	StringListView(QWidget *);
	virtual AAFilter aaFilter() const = 0;
	QStringList selectedStrings() const;
	MPDSongList selectedSongs() const;

public slots:
	void filter(const QString &);
	void setStrings(const QStringList &);
	void updateTranslation();

protected:
	StringListModel *m_model;
	QStringList m_strings;
	QAction *m_enqueueAction, *m_informationAction, *m_playAction;
};
#endif
