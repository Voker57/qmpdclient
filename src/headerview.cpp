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

#include "config.h"
#include "headerview.h"

#include <QContextMenuEvent>
#include <QMenu>

const int HEADER_FORMAT = 108;

HeaderView::HeaderView(QWidget *p) : QHeaderView(Qt::Horizontal, p),
		m_menu(new QMenu(this)) {
	setMovable(true);
	connect(Config::instance(), SIGNAL(autoResizeChanged(bool)), this, SLOT(autoResizeChanged(bool)));
}

void HeaderView::mouseReleaseEvent(QMouseEvent *e) {
	// sectionClicked(int) signal is emitted too early, and thus saves the previous sortorder.
	// Therefore we save it here.
	QHeaderView::mouseReleaseEvent(e);
	save();
}

void HeaderView::autoResizeChanged(bool a) {
	if (!a) {
		setResizeMode(QHeaderView::Interactive);
		setStretchLastSection(true);
		return;
	}

	setUpdatesEnabled(false);
	setStretchLastSection(false);
	for (int i = 0; i < m_columns.size(); i++) {
		if (visualIndex(i) < 0)
			continue;
		Column col = m_columns.at(i);
		if (col == TRACK || col == LENGTH || col == DATE)
			setResizeMode(i, QHeaderView::ResizeToContents);
		else
			setResizeMode(i, QHeaderView::Stretch);
	}
	setUpdatesEnabled(true);

	if (model())
		update();
}

void HeaderView::restore() {
	Q_ASSERT(m_menu);
	Q_ASSERT(model());
	blockSignals(true);

	// Restore view state
	QByteArray ba2(Config::instance()->headerViewState(objectName()));
	if (!ba2.isEmpty()) {
		QDataStream ds2(&ba2, QIODevice::ReadOnly);
		int version;
		ds2 >> version;
		if (version == HEADER_FORMAT) {
			for (int j = 0;j < model()->columnCount();j++) {
				int size, vi;
				bool hidden;
				ds2 >> size >> vi >> hidden;
				resizeSection(j, size);
				moveSection(visualIndex(j), vi);
				setSectionHidden(j, hidden);
			}
			int sortOrder, sortSection;
			ds2 >> sortOrder >> sortSection;
			setSortIndicator(sortSection, (Qt::SortOrder)sortOrder);
		} else { // Header state was of incorrect version. Use defaults.
			setDefaults();
		}
	} else { // Header state was empty. Use defaults.
		setDefaults();
	}

	for (int i = 0; i < m_columns.size(); i++) {
		QAction *a = m_menu->addAction(columnName(m_columns.at(i)), this, SLOT(actionTriggered()));
		a->setCheckable(true);
		a->setChecked(!isSectionHidden(i));
	}

	autoResizeChanged(Config::instance()->autoResizeColumns());

	blockSignals(false);
}

void HeaderView::save() {
	Q_ASSERT(model());
	// Save headerview state
	QByteArray ba;
	QDataStream ds(&ba, QIODevice::ReadWrite);
	ds << HEADER_FORMAT;
	for (int i = 0;i < model()->columnCount();i++) {
		if (isSectionHidden(i))
			ds << 100;
		else
			ds << sectionSize(i);
		ds << visualIndex(i);
		ds << isSectionHidden(i);
	}
	ds << (int)sortIndicatorOrder();
	ds << sortIndicatorSection();
	Config::instance()->setHeaderViewState(objectName(), ba);
}

void HeaderView::contextMenuEvent(QContextMenuEvent *event) {
	if (m_columns.size() > 1) {
		Q_ASSERT(m_menu);
		m_menu->popup(event->globalPos());
	}
}

void HeaderView::actionTriggered() {
	Q_ASSERT(m_menu);
	blockSignals(true);
	int i = 0;
	foreach(QAction *a, m_menu->actions()) {
		setSectionHidden(i++, !a->isChecked());
	}
	blockSignals(false);
	save();
}

QList<HeaderView::Column> HeaderView::columns() const {
	return m_columns;
}

QString HeaderView::columnName(Column col) const {
	switch (col) {
		case HeaderView::TITLE:
			return QObject::tr("Title");
		case HeaderView::TRACK:
			return QObject::tr("Track");
		case HeaderView::ARTIST:
			return QObject::tr("Artist");
		case HeaderView::ALBUM:
			return QObject::tr("Album");
		case HeaderView::LENGTH:
			return QObject::tr("Length");
		case HeaderView::URL:
			return QObject::tr("URL");
		case HeaderView::FILENAME:
			return QObject::tr("Filename");
		case HeaderView::GENRE:
			return QObject::tr("Genre");
		case HeaderView::DATE:
			return QObject::tr("Date");
		case HeaderView::COMMENT:
			return QObject::tr("Comment");
		case HeaderView::DISC:
			return QObject::tr("Disc");
		case HeaderView::COMPOSER:
			return QObject::tr("Composer");
		case HeaderView::PERFORMER:
			return QObject::tr("Performer");
		default:
			return "?";
	}
}
