/*
 * QMPDClient - An MPD client written in Qt 4.
 * Copyright (C) 2005-2008 Hvard Tautra Knutsen <havtknut@tihlde.org>
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

#include "aboutdialog.h"
#include "config.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) {
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);

	titleLabel->setText(NAMEVER);
	pixmapLabel->setPixmap(QPixmap(":/icons/qmpdclient22.png"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

	const QStringList paths = QStringList() << ":/";
	aboutText->setSearchPaths(paths);
	aboutText->setPlainText(aboutText->loadResource(QTextDocument::HtmlResource, QUrl("README")).toString());
	authorText->setSearchPaths(paths);
	authorText->setPlainText(authorText->loadResource(QTextDocument::HtmlResource, QUrl("AUTHORS")).toString());
	thanksText->setSearchPaths(paths);
	thanksText->setPlainText(thanksText->loadResource(QTextDocument::HtmlResource, QUrl("THANKSTO")).toString());
	licenseText->setSearchPaths(paths);
	licenseText->setPlainText(licenseText->loadResource(QTextDocument::HtmlResource, QUrl("COPYING")).toString());
	show();
}
