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

#include "lineedit.h"
#include "config.h"
#include "iconmanager.h"
#include <QMouseEvent>
#include <QPainter>
#include <QBitmap>

LineEdit::LineEdit(QWidget *parent) : QLineEdit(parent), m_hover(false), m_forceNoHover(false) {
	updateIconSet();
	connect(Config::instance(), SIGNAL(iconSetChanged()), this, SLOT(updateIconSet()));
}

void LineEdit::updateIconSet() {
	m_pixmap = m_hoverPixmap = IconManager::pixmap("clearline");
	if (m_pixmap.isNull())
		return;

	// Make whiteish hover pixmap
	const QBitmap mask = m_hoverPixmap.mask(); // Remember mask
	QPainter p(&m_hoverPixmap);
	QColor c = Qt::white;
	c.setAlpha(128);
	p.fillRect(m_hoverPixmap.rect(), c); // Fill pixmap with halftransparent white
	p.end();
	m_hoverPixmap.setMask(mask); // Set mask again, to remove the white on previously transparent areas
	update();
}

void LineEdit::updateTranslation() {
	setToolTip(tr("Clear the filter"));
}

void LineEdit::paintEvent(QPaintEvent *e) {
	QLineEdit::paintEvent(e);
	QPainter p(this);
	p.drawPixmap(m_pixmapRect.topLeft(), m_hover && !m_forceNoHover ? m_hoverPixmap : m_pixmap);
}

void LineEdit::resizeEvent(QResizeEvent *e) {
	QLineEdit::resizeEvent(e);
	const int leftover = (height() - m_pixmap.height())/2;
	m_pixmapRect = QRect(width() - m_pixmap.width() - leftover, leftover, m_pixmap.width(), m_pixmap.height());
	setStyleSheet(QString(":enabled { padding-right: %1; }").arg(m_pixmapRect.width()+leftover));
}

void LineEdit::leaveEvent(QEvent *e) {
	QLineEdit::leaveEvent(e);
	setCursor(Qt::IBeamCursor);
	m_hover = false;
	m_forceNoHover = false;
	update();
}

void LineEdit::mousePressEvent(QMouseEvent *e) {
	if (e->pos().x() >= m_pixmapRect.left()) {
		m_forceNoHover = true;
		e->accept();
		clear();
		update();
		return;
	}
	QLineEdit::mousePressEvent(e);
}

void LineEdit::mouseMoveEvent(QMouseEvent *e) {
	m_hover = m_pixmapRect.contains(e->pos());
	setCursor(m_hover ? Qt::ArrowCursor : Qt::IBeamCursor);
	QLineEdit::mouseMoveEvent(e);
	update();
}

void LineEdit::mouseReleaseEvent(QMouseEvent *e) {
	QLineEdit::mouseReleaseEvent(e);
	if (e->pos().x() >= m_pixmapRect.left()) {
		m_forceNoHover = false;
		update();
	}
}

bool LineEdit::event(QEvent *e) {
	if (e->type() == QEvent::ToolTip) {
		QHelpEvent *he = static_cast<QHelpEvent *>(e);
		if (m_pixmapRect.contains(he->pos()))
			return QLineEdit::event(e);

		// Not over icon, ignore tooltip request
		e->ignore();
		return true;
	}
	return QLineEdit::event(e);
}
