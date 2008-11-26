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

#include "timelabel.h"
#include "config.h"
#include <QTime>

TimeLabel::TimeLabel(QWidget *p) : QLabel(p),
		m_remaning(Config::instance()->showRemaining()),
		m_total(-1) {
	m_remaningText = m_elapsedText = "0:00";
}

void TimeLabel::mousePressEvent(QMouseEvent *) {
	m_remaning = !m_remaning;
	Config::instance()->setShowRemaining(m_remaning);
	update();
}

void TimeLabel::paintEvent(QPaintEvent *e) {
	setText(m_remaning ? m_remaningText : m_elapsedText);
	QLabel::paintEvent(e);
}

void TimeLabel::setTime(int elapsed, int total) {
	if (total > -1)
		m_total = total;

	const QTime r = QTime(0, 0).addSecs(m_total - elapsed);
	m_remaningText = r.toString(r.hour() > 0 ? "-h:mm:ss" : "-m:ss");
	const QTime e = QTime(0, 0).addSecs(elapsed);
	m_elapsedText = e.toString(e.hour() > 0 ? "h:mm:ss" : "m:ss");
	update();
}

QSize TimeLabel::minimumSizeHint() const {
	return QSize(fontMetrics().width(m_remaning ? m_remaningText : m_elapsedText), height());
}

TotalTimeLabel::TotalTimeLabel(QWidget *p) : QLabel("0:00", p) {}

void TotalTimeLabel::setTime(int, int total) {
	const QTime t = QTime(0, 0).addSecs(total);
	setText(t.toString(t.hour() > 0 ? "h:mm:ss" : "m:ss"));
}
