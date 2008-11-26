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

#include "timeslider.h"
#include "mpdconnection.h"
#include <QMouseEvent>
#include <QPainter>

TimeSlider::TimeSlider(QWidget *parent) : QSlider(Qt::Horizontal, parent), m_seeking(false) {
	setObjectName("timeslider");
	setTime(0, 0);
	connect(this, SIGNAL(actionTriggered(int)), this, SLOT(onActionTriggered(int)));
}

void TimeSlider::onActionTriggered(int action) {
	if (action == SliderPageStepAdd ||
	        action == SliderPageStepSub ||
	        action == SliderSingleStepAdd ||
	        action == SliderSingleStepSub)
		emit timeChanged(sliderPosition());
}

/**
 * Draw the text "Streaming" over the slider if we are streaming (the slider is disabled)
 */
void TimeSlider::paintEvent(QPaintEvent *e) {
	// Paint slider
	QSlider::paintEvent(e);

	// Draw text just when slider is disabled
	if (isEnabled() || !MPDConnection::instance()->isConnected())
		return;

	const int handleX = (int)(((double)width() / maximum()) * value());
	const int handleLeft = handleX - 10;
	const int handleRight = handleX + 10;

	QFontMetrics fm = fontMetrics();
	QString text = tr("Streaming");
	const int w = fm.width(text);
	const int h = fm.height();
	const int x = (width()/2) - (w/2);
	const int y = (height()/2) - (h/2);

	QRect textRect(x, y, w, h);
	// right edge of handle is inside text box, move text box right of handle
	if (textRect.contains(handleRight, y))
		textRect.moveLeft(handleRight);
	// left edge of handle is inside text box, move text box left of handle
	if (textRect.contains(handleLeft, y))
		textRect.moveLeft(handleLeft - w);

	QPainter p(this);
	// Remove background for better readability
	p.eraseRect(textRect);
	if (!isEnabled()) { // Draw disabled text with shadow disabled
		p.save();
		p.setPen(QColor(255, 255, 255));
		// Draw text shadow
		p.drawText(textRect, text);
		textRect.moveLeft(x-1);
		textRect.moveTop(y-1);
		p.restore();
	}
	// Draw the text
	p.drawText(textRect, text);
}

void TimeSlider::wheelEvent(QWheelEvent *e) {
	QSlider::wheelEvent(e);
	emit timeChanged(value());
}

void TimeSlider::mouseReleaseEvent(QMouseEvent *) {
	m_seeking = false;
	emit timeChanged(value());
}

void TimeSlider::mouseMoveEvent(QMouseEvent *e) {
	// Find handleX position, never larger than width(), never less than 0.
	int x = e->x();
	const int max = width();
	if (x > max)
		x = max;
	else if (x < 0)
		x = 0;
	// Pass value, with ratio of maxTime / width
	setValue(static_cast<int>(x*(static_cast<double>(maximum()) / width())));
}

void TimeSlider::mousePressEvent(QMouseEvent *e) {
	m_seeking = true;
	mouseMoveEvent(e);
}

void TimeSlider::setTime(int elapsed, int max) {
	QSlider::setMaximum(isEnabled() ? max : 0);
	if (!m_seeking)
		setValue(elapsed);
}
