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
#include "directorypanel.h"

DirectoryPanel::DirectoryPanel() {
	setupUi(this);
	directoryView->setFileView(fileView);
	directorySplit->restoreState(Config::instance()->directorySplitterSizes());

	connect(fileFilter, SIGNAL(textChanged(const QString &)), fileView, SLOT(setFilter(const QString &)));
}

void DirectoryPanel::updateTranslation() {
	retranslateUi(this);
}

void DirectoryPanel::on_directorySplit_splitterMoved(int, int) {
	Config::instance()->setDirectorySplitterSizes(directorySplit->saveState());
}
