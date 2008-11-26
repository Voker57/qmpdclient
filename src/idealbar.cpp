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

#include "idealbar.h"
#include "idealsplitter.h"
#include "verticalbutton.h"
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>

IdealBar::IdealBar(QWidget *parent) : QWidget(parent),
		m_stack(0),
		m_layout(new QVBoxLayout(this)),
		m_splitter(0) {
	Q_ASSERT(m_layout);
	setObjectName("idealbar");
	setMinimumWidth(22);
	m_layout->setMargin(0);
	m_layout->setSpacing(3);
	m_layout->addItem(new QSpacerItem(16, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

QPushButton *IdealBar::addPanel(QWidget *panel, bool left) {
	Q_ASSERT(m_layout);
	Q_ASSERT(m_stack);
	QFrame *frame = new QFrame(m_stack);
	frame->setFrameStyle(QFrame::StyledPanel);
	QVBoxLayout *vb = new QVBoxLayout(frame);
	vb->addWidget(panel);
	m_stack->addWidget(frame);
	VerticalButton *pb = new VerticalButton("", this, left);

	connect(pb, SIGNAL(pressed()), this, SLOT(buttonPressed()));
	m_layout->insertWidget(m_layout->count() - 1, pb);
	m_relation.insert(pb, frame);
	return pb;
}

void IdealBar::paintEvent(QPaintEvent *e) {
	foreach (VerticalButton *b, m_relation.keys()) {
		Q_ASSERT(m_stack);
		Q_ASSERT(m_splitter);
		if (m_splitter->isCollapsed(m_index))
			b->setActive(false);
		else
			b->setActive(m_relation.value(b) == m_stack->currentWidget());
	}
	QWidget::paintEvent(e);
}

void IdealBar::buttonPressed() {
	Q_ASSERT(m_splitter);
	Q_ASSERT(m_stack);
	VerticalButton *button = qobject_cast<VerticalButton*>(sender());
	QWidget *panel = m_relation.value(button);

	if (m_splitter->isCollapsed(m_index)) // Open a closed tab
		m_splitter->setExpanded(m_index);
	else if (button->isActive()) {// Close current tab
		m_splitter->setCollapsed(m_index);
		if (m_splitter->isCollapsed(m_index ? 0 : 1))
			m_splitter->setExpanded(m_index ? 0 : 1);
	}

	m_stack->setCurrentWidget(panel);
	update();
}

void IdealBar::link(QStackedWidget *s, IdealSplitter *sp) {
	if (!m_stack)
		m_stack = s;
	if (!m_splitter) {
		m_splitter = sp;
		Q_ASSERT(m_stack);
		Q_ASSERT(m_splitter);
		m_index = m_splitter->indexOf(m_stack);
		connect(m_splitter, SIGNAL(sectionCollapsed(int)), this, SLOT(update()));
		connect(m_splitter, SIGNAL(sectionExpanded(int)), this, SLOT(update()));
	}
}
