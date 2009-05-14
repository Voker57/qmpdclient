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

#include "aafilter.h"
#include "mpdcache.h"
#include "mpdsonglist.h"
#include "stringlistmodel.h"
#include "stringlistview.h"
#include "mpd.h"
#include "config.h"
#include <QMap>
#include <QMenu>
#include <QItemSelectionModel>

StringListView::StringListView(QWidget *parent) : AbstractList(parent) {
	Q_ASSERT(m_menu);
	setModel(m_model = new StringListModel(this));

	m_enqueueAction = addMenuAction("enqueue", this, SLOT(enqueue()));
	m_playAction = addMenuAction("play", this, SLOT(play()));
	m_menu->addSeparator();
	m_informationAction = addMenuAction("information", this, SLOT(information()));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(doubleClicked(const QModelIndex &)));
}

void StringListView::doubleClicked(const QModelIndex &) {
	MPD::instance()->addSongs(selectedSongs(), Config::instance()->enqueue());
}

QStringList StringListView::selectedStrings() const {
	Q_ASSERT(m_model);
	return m_model->stringList(selectedIndexes());
}

MPDSongList StringListView::selectedSongs() const {
	return MPDCache::instance()->songsByAA(aaFilter());
}

/**
 * Given a string, select it
 * Do nothing if string can not be found
 */
void StringListView::selectString(const QString &str) {

	// search the list to see if we can find the entry
	int index = m_strings.indexOf(str);
	if (index < 0)
		return;

	if (m_model->showAll())
		index++;

	selectionModel()->setCurrentIndex(m_model->index(index), 
			QItemSelectionModel::ClearAndSelect);
}


/**
 * Return a string with "The " lopped off, if it exists
 */
QString StringListView::normalizeString(const QString l) {
	if (l.length() > 4 && l.startsWith("The ", Qt::CaseInsensitive)) {
		return l.mid(4).trimmed();
	}

	return l.trimmed();
}

/**
 * Return a sorted string list, sorted alphabetically case insensitive
 * @param QStringList list of strings
 * @param bool to normalize or not to normalize
 */
QStringList StringListView::sort(const QStringList &strings, bool normalize) {
	// Recommended way to have arbitrary sorting from QT docs
	QMap<QString, QString> map;
	foreach (QString str, strings) {
		if (normalize)
			map.insert(StringListView::normalizeString(str.toLower()), str);
		else
			map.insert(str.toLower(), str);
	}

	QStringList sorted;
	QMapIterator<QString, QString> ii(map);
	while (ii.hasNext()) {
		sorted += ii.next().value();
	}
	return sorted;
}

void StringListView::filter(const QString &needle) {
	Q_ASSERT(m_model);
	m_model->setStringList(m_strings.filter(QRegExp(needle, Qt::CaseInsensitive)));
}

void StringListView::setStrings(const QStringList &strings) {
	Q_ASSERT(m_model);

	m_strings = StringListView::sort(strings, Config::instance()->disregardLeadingThe());

	m_model->setStringList(m_strings);
	setCurrentIndex(m_model->index(0));
}

void StringListView::updateTranslation() {
	Q_ASSERT(m_enqueueAction);
	Q_ASSERT(m_informationAction);
	Q_ASSERT(m_playAction);
	m_enqueueAction->setText(tr("&Enqueue"));
	m_informationAction->setText(tr("&Information..."));
	m_playAction->setText(tr("&Play"));
}
