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
#include "iconmanager.h"
#include "mpdconnection.h"
#include "mpdsongmodel.h"
#include "radioview.h"
#include "ui_addradiodialog.h"
#include <QMenu>

RadioView::RadioView(QWidget *parent) : MPDSongView(parent) {
	Q_ASSERT(m_menu);
	setObjectName("radioview");
	setHeaderView(new RadiolistHeader(this));

	m_menu->addSeparator();
	m_addAction = addMenuAction("newStationAction", this, SLOT(newStation()), false);
	m_deleteAction = addMenuAction("deleteAction", this, SLOT(deleteStation()));
	m_deleteAction->setShortcut(Qt::Key_Delete);
	m_deleteAction->setShortcutContext(Qt::WidgetShortcut);
	addAction(m_deleteAction); // Needed for shortcut key to work

	connect(MPDConnection::instance(), SIGNAL(connected(const ServerInfo &)), this, SLOT(connected()));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(disconnected()));
}

void RadioView::selectionChanged(const QItemSelection &s, const QItemSelection &u) {
	MPDSongView::selectionChanged(s, u);
	emit toggleDeleteAction(!s.indexes().isEmpty());
}

MPDSongList RadioView::selectedSongs() const {
	Q_ASSERT(m_model);
	return m_model->songs(selectedIndexes());
}

void RadioView::updateTranslation() {
	Q_ASSERT(m_addAction);
	Q_ASSERT(m_deleteAction);
	MPDSongView::updateTranslation();
	m_addAction->setText(tr("&New..."));
	m_deleteAction->setText(tr("&Delete"));
}

void RadioView::newStation() {
	QDialog *dia = new QDialog(this);
	Ui_AddRadioDialog *ard = new Ui_AddRadioDialog;
	ard->setupUi(dia);
	ard->addRadioDialogLabel->setPixmap(IconManager::pixmap("addradiodialog", 32));
	dia->resize(300, 100);
	if (dia->exec() == QDialog::Accepted) {
		if (!ard->title->text().isEmpty() && !ard->url->text().isEmpty()) {
			Config::instance()->addRadioStation(ard->title->text(), ard->url->text());
			connected();
		}
	}
	delete dia;
}

void RadioView::connected() {
	Q_ASSERT(m_model);
	m_model->setSongs(Config::instance()->radioStations());
    if (header()->sectionsClickable())
		m_model->sort(header()->sortIndicatorSection(), header()->sortIndicatorOrder());
	emit toggleNewAction(true);
}

void RadioView::disconnected() {
	emit toggleNewAction(false);
}

void RadioView::deleteStation() {
	Config::instance()->removeRadioStations(m_model->songs(selectedIndexes()));
	connected();
}

RadiolistHeader::RadiolistHeader(QWidget *p) : HeaderView(p) {
	setObjectName("radioviewheader");
	m_columns << TITLE << URL;
}

void RadiolistHeader::setDefaults() {
	int i = 0;
	foreach(Column col, m_columns) {
		if (col == TITLE)
			setSortIndicator(i, Qt::AscendingOrder);
		++i;
	}
}

QString RadiolistHeader::columnName(Column col) const {
	if (col == TITLE)
		return QObject::tr("Stream");
	return HeaderView::columnName(col);
}
