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

#ifndef IDEALBAR_H
#define IDEALBAR_H

#include <QMap>
#include <QWidget>

class IdealBar;
class IdealSplitter;
class VerticalButton;
class QPushButton;
class QStackedWidget;
class QVBoxLayout;

class IdealBar : public QWidget {
	Q_OBJECT
public:
	IdealBar(QWidget *);
	QPushButton *addPanel(QWidget *panel, bool = false);
	void link(QStackedWidget *, IdealSplitter *);

private slots:
	void buttonPressed();

private:
	void paintEvent(QPaintEvent *);

	QMap<VerticalButton *, QWidget *> m_relation;
	QStackedWidget *m_stack;
	QVBoxLayout *m_layout;
	IdealSplitter *m_splitter;
	int m_index;
};
#endif
