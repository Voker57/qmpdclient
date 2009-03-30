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

// Implementation of AbstractList / AbstractView, TYPE and PARENT need to be defined on include

TYPE::TYPE(QWidget *parent) : PARENT(parent),
		m_abstractModel(0),
		m_menu(new QMenu(this)) {
	connect(MPDConnection::instance(), SIGNAL(connected(const ServerInfo &)), this, SLOT(connected()));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(disconnected()));
	connect(this, SIGNAL(doubleClicked(const QModelIndex &)), this, SLOT(activated(const QModelIndex &)));
}

QAction *TYPE::addMenuAction(const QString &objectName, QObject *receiver, const char *method, bool conditional) {
	Q_ASSERT(m_menu);
	QAction *a = m_menu->addAction("", receiver, method);
	a->setObjectName(objectName);
	if (conditional) {
		a->setEnabled(false); //All conditional actions start disabled
		m_actions << a;
	}
	return a;
}

QAction *TYPE::addMenuAction(const QString &objectName, bool conditional) {
	Q_ASSERT(m_menu);
	QAction *a = m_menu->addAction("");
	a->setObjectName(objectName);
	if (conditional)
		m_actions << a;
	return a;
}

void TYPE::contextMenuEvent(QContextMenuEvent *e) {
	const QModelIndex clicked = indexAt(e->pos());
	const QModelIndexList indexes = selectedIndexes();
	if (indexes.isEmpty() || !indexes.contains(clicked))
		setCurrentIndex(indexAt(e->pos()));
	Q_ASSERT(m_menu);
	m_menu->popup(e->globalPos());
}

void TYPE::selectionChanged(const QItemSelection &s, const QItemSelection &u) {
	PARENT::selectionChanged(s, u);
	foreach(QAction *a, m_actions) {
		Q_ASSERT(a);
		a->setEnabled(!s.indexes().isEmpty());
	}
}

void TYPE::activated(const QModelIndex &) {
	MPD::instance()->addSongs(selectedSongs(), Config::instance()->enqueue());
}

void TYPE::enqueue() {
	MPD::instance()->addSongs(selectedSongs());
}

void TYPE::information() {
	new MetaInfoDialog(this, selectedSongs());
}

void TYPE::play() {
	MPD::instance()->addSongs(selectedSongs(), false);
}

void TYPE::connected() {
	setEnabled(true);
}

void TYPE::disconnected() {
	setEnabled(false);
}

void TYPE::paintEvent(QPaintEvent *e) {
	if (isEnabled()) {
		PARENT::paintEvent(e);
		return;
	}
	const QString text = qApp->translate("AbstractView", "Not connected");
	const int x = width() / 2 - fontMetrics().width(text) / 2;
	const int y = height() / 2 - fontMetrics().height() / 2;
	QPainter p(viewport());
	p.drawText(x, y, text);
}

void TYPE::setModel(QAbstractItemModel *model) {
	Q_ASSERT(model);
	PARENT::setModel(model);
	m_abstractModel = dynamic_cast<AbstractModel*>(model);
	Q_ASSERT(m_abstractModel);
}

void TYPE::mouseMoveEvent(QMouseEvent *e) {
	QMouseEvent *e2 = e;
	Q_ASSERT(m_abstractModel);
	if (m_abstractModel->isDragDisabled())
		e2 = new QMouseEvent(e->type(), e->pos(), Qt::LeftButton, e->buttons() | Qt::LeftButton, e->modifiers());
	PARENT::mouseMoveEvent(e2);
}

void TYPE::mousePressEvent(QMouseEvent *e) {
	QMouseEvent *e2 = e;
	if (e->button() == Qt::MidButton) {
		Q_ASSERT(m_abstractModel);
		m_abstractModel->setDragDisabled(true);
		e2 = new QMouseEvent(e->type(), e->pos(), Qt::LeftButton, e->buttons(), e->modifiers());
	}
	PARENT::mousePressEvent(e2);
}

void TYPE::mouseReleaseEvent(QMouseEvent *e) {
	if (e->button() == Qt::MidButton) {
		Q_ASSERT(m_abstractModel);
		m_abstractModel->setDragDisabled(false);
	}
	PARENT::mouseReleaseEvent(e);
}
