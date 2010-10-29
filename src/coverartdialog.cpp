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

#include <QDir>
#include "coverartdialog.h"
#include "config.h"
#include "mpdsong.h"
#include <QDir>

CoverArtDialog::CoverArtDialog(QWidget *parent) : QDialog(parent) {
	setWindowFlags(Qt::Tool);
	setupUi(this);
}

QPixmap CoverArtDialog::coverArt() const {
	return m_pixmap;
}

bool CoverArtDialog::hasCoverArt() const {
	return !m_pixmap.isNull();
}

void CoverArtDialog::setSong(const MPDSong &s) {
	QDir imageDir((QFileInfo(Config::instance()->coverArtDir(), s.directory())).absoluteFilePath());
	imageDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot | QDir::Readable);
	imageDir.setSorting(QDir::Name);
	QStringList formatList = Config::instance()->coverArtFilenameFormat().split(',', QString::SkipEmptyParts);
	QStringList::iterator it;
	for (it = formatList.begin(); it != formatList.end(); ++it) {
		*it = (*it).trimmed();
	}
	imageDir.setNameFilters(formatList);
	if (imageDir.entryInfoList().count() == 0) {
		imageDir.setNameFilters(QStringList() << "*.jpg" << "*.jpeg" << "*.gif" << "*.png");
	}
	
	const QString imageFile = imageDir.entryInfoList().value(0).absoluteFilePath();

	setWindowTitle(QString("file:/").append(imageFile));
	m_pixmap = QPixmap(imageFile);

	if (m_pixmap.isNull()) {
		coverArtImageLabel->setText(QObject::tr("No cover art found."));
	}
	else {
		int mh = Config::instance()->coverArtMaxHeight().toInt();
		int mw = Config::instance()->coverArtMaxWidth().toInt();
		if (mh == 0) mh = 1024;
		if (mw == 0) mw = 768;
		// resize image
		if (m_pixmap.height() > mh) m_pixmap = m_pixmap.scaledToHeight(mh, Qt::SmoothTransformation);
		if (m_pixmap.width() > mw) m_pixmap = m_pixmap.scaledToWidth(mw, Qt::SmoothTransformation);
		coverArtImageLabel->setPixmap(m_pixmap); // set image
	}

	setFixedSize(minimumSizeHint());
}
