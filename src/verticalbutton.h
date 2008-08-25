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

#ifndef VERTICALBUTTON_H
#define VERTICALBUTTON_H

#include <QPushButton>

class QStyleOptionButton;

class VerticalButton : public QPushButton {
	Q_OBJECT
public:
	VerticalButton(const QString &text, QWidget *parent, bool left);
	void setActive(bool);
	bool isActive() const;
	QSize sizeHint() const;
	QStyleOptionButton styleOption() const;
	void paintEvent(QPaintEvent *);

private:
	bool m_active, m_left;
};
#endif
