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

#ifndef IDEALSPLITTER_H
#define IDEALSPLITTER_H

#include <QSplitter>

class IdealSplitter : public QSplitter {
	Q_OBJECT
public:
	IdealSplitter(QWidget *parent);
	void setCollapsed(int);
	void setExpanded(int);
	void restore(const QByteArray &);
	bool isCollapsed(int) const;

signals:
	void sectionCollapsed(int);
	void sectionExpanded(int);

protected:
	void paintEvent(QPaintEvent *);

private slots:
	void manuallyResized();

private:
	QList<int> prevComplete, prevSizes;
};
#endif
