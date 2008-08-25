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

#include "idealsplitter.h"

IdealSplitter::IdealSplitter(QWidget *parent) : QSplitter(parent), prevComplete(QList<int>() << 100 << 100) {
	setObjectName("idealsplitter");
	connect(this, SIGNAL(splitterMoved(int, int)), this, SLOT(manuallyResized()));
}

void IdealSplitter::restore(const QByteArray &ba) {
	prevSizes = QList<int>() << 0 << 0;
	QSplitter::restoreState(ba);
	manuallyResized();
}

void IdealSplitter::setCollapsed(int index) {
	QList<int> siz = sizes();
	siz[index] = 0;
	setSizes(siz);
	emit sectionCollapsed(index);
}

void IdealSplitter::setExpanded(int index) {
	QList<int> siz = sizes();
	if (siz.at(!index) != 0) {
		// Other is open, restore last complete state
		siz = prevComplete;
	} else
		siz[index] = 100;
	setSizes(siz);
	emit sectionExpanded(index);
}

bool IdealSplitter::isCollapsed(int index) const {
	return sizes().at(index) == 0;
}

void IdealSplitter::manuallyResized() {
	QList<int> siz = sizes();
	for (int i = 0; i < siz.size() && i < prevSizes.size(); i++) {
		if (siz.at(i) != 0 && prevSizes.at(i) == 0)
			emit sectionExpanded(i);
		if (siz.at(i) == 0 && prevSizes.at(i) != 0)
			emit sectionCollapsed(i);
	}
}

void IdealSplitter::paintEvent(QPaintEvent *e) {
	QSplitter::paintEvent(e);
	QList<int> siz = prevSizes = sizes();
	foreach(int s, siz) {
		if (s == 0)
			return;
	}
	prevComplete = siz;
}
