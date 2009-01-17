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

#include "aboutdialog.h"
#include "config.h"

#include <QTextCodec>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) {
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);

	titleLabel->setText(NAMEVER);
	pixmapLabel->setPixmap(QPixmap(":/icons/qmpdclient22.png"));

	connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));

	const QStringList paths = QStringList() << ":/";
	aboutText->setSearchPaths(paths);
	QTextCodec *codec = QTextCodec::codecForName("UTF-8");
	aboutText->setPlainText(codec->toUnicode(aboutText->loadResource(QTextDocument::HtmlResource, QUrl("README")).toByteArray()));
	authorText->setSearchPaths(paths);
	authorText->setPlainText(codec->toUnicode(authorText->loadResource(QTextDocument::HtmlResource, QUrl("AUTHORS")).toByteArray()));
	thanksText->setSearchPaths(paths);
	thanksText->setPlainText(codec->toUnicode(thanksText->loadResource(QTextDocument::HtmlResource, QUrl("THANKSTO")).toByteArray()));
	licenseText->setSearchPaths(paths);
	licenseText->setPlainText(codec->toUnicode(licenseText->loadResource(QTextDocument::HtmlResource, QUrl("COPYING")).toByteArray()));
	show();
}
