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

#ifndef HEADERVIEW_H
#define HEADERVIEW_H

#include <QHeaderView>

class HeaderView : public QHeaderView {
	Q_OBJECT
public:
	enum Column { TRACK = 0,
	              TITLE = 1,
	              ARTIST = 2,
	              ALBUM = 3,
	              GENRE = 4,
	              COMPOSER = 5,
	              DATE = 6,
	              LENGTH = 7,
	              URL = 8,
	              FILENAME = 9,
	              DISC = 10,
	              COMMENT = 11,
	              PERFORMER = 12 };
	HeaderView(QWidget *);
	void restore();
	QList<Column> columns() const;
	virtual QString columnName(Column) const;

protected:
	void contextMenuEvent(QContextMenuEvent *);
	void mouseReleaseEvent(QMouseEvent *);
	virtual void setDefaults() = 0;

	QList<Column> m_columns;
	QMenu *m_menu;

private slots:
	void autoResizeChanged(bool);
	void actionTriggered();
	void save();
};
#endif
