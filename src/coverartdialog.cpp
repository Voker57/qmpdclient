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

CoverArtDialog::CoverArtDialog(QWidget *parent)
	: QDialog(parent)
{
	setWindowFlags(Qt::Tool);
	setupUi(this);
}

QPixmap CoverArtDialog::coverArt() const
{
	return m_pixmap;
}

bool CoverArtDialog::hasCoverArt() const
{
	return !m_pixmap.isNull();
}

void CoverArtDialog::setSong(const MPDSong &s)
{
	QDir imageDir((QFileInfo(Config::instance()->coverArtDir(), s.directory())).absoluteFilePath());

	imageDir.setFilter(QDir::Files | QDir::Hidden | QDir::NoDotAndDotDot | QDir::Readable);
	imageDir.setSorting(QDir::Name);
	imageDir.setNameFilters(QStringList() << "*.jpg" << "*.jpeg" << "*.gif" << "*.png");

	const QString imageFile = imageDir.entryInfoList().value(0).absoluteFilePath();

	setWindowTitle(QString("file:/").append(imageFile));
	m_pixmap = QPixmap(imageFile);

	if (m_pixmap.isNull()) {
		coverArtImageLabel->setText(QObject::tr("No cover art found."));
	}
	else {
		// resize image
		if (m_pixmap.height() > 1024) m_pixmap = m_pixmap.scaledToHeight(1024, Qt::SmoothTransformation);
		if (m_pixmap.width() > 768) m_pixmap = m_pixmap.scaledToWidth(768, Qt::SmoothTransformation);
		coverArtImageLabel->setPixmap(m_pixmap); // set image
	}

	setFixedSize(minimumSizeHint());
}
