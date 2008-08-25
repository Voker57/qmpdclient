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

#ifndef DIRECTORYVIEW_H
#define DIRECTORYVIEW_H

#include "abstractview.h"

class DirectoryModel;
class FileView;
class MPDDirectory;

class DirectoryView : public AbstractTree {
	Q_OBJECT
public:
	DirectoryView(QWidget *);
	void setFileView(FileView *);
	MPDSongList selectedSongs() const;

public slots:
	void updateTranslation();

private slots:
	void rescan();
	void setRoot(const MPDDirectory &);

private:
	void selectionChanged(const QItemSelection & = QItemSelection(), const QItemSelection & = QItemSelection());

	DirectoryModel *m_model;
	FileView *m_fileView;
	QAction *m_enqueueAction, *m_informationAction, *m_rescanAction, *m_playAction;
};
#endif
