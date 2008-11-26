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

#include "verticalbutton.h"
#include <QStyle>
#include <QStyleOptionButton>
#include <QStylePainter>

VerticalButton::VerticalButton(const QString &text, QWidget *parent, bool left) : QPushButton(text, parent),
		m_active(false),
		m_left(left) {
	setLayoutDirection(Qt::LeftToRight);
}

void VerticalButton::setActive(bool a) {
	m_active = a;
}

bool VerticalButton::isActive() const {
	return m_active;
}

QSize VerticalButton::sizeHint() const {
	QSize size = QPushButton::sizeHint();
	size.transpose();
	return size;
}

QStyleOptionButton VerticalButton::styleOption() const {
	QStyleOptionButton opt;
	opt.initFrom(this);
	// Rotate button
	QSize size = opt.rect.size();
	size.transpose();
	if (m_active)
		opt.state |= QStyle::State_On;
	opt.rect = QRect(QPoint(opt.rect.x(), opt.rect.y()), size);
	opt.text = text();
	opt.icon = icon();
	opt.iconSize = iconSize();
	return opt;
}

void VerticalButton::paintEvent(QPaintEvent *) {
	QStylePainter sp(this);
	const QStyleOptionButton option = styleOption();
	if (m_left) {
		sp.rotate(-90);
		sp.translate(-option.rect.width(), 0);
	}
	else {
		sp.rotate(90);
		sp.translate(0, -option.rect.height());
	}
	sp.drawControl(QStyle::CE_PushButton, option);
}
