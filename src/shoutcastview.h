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

#ifndef SHOUTCASTVIEW_H
#define SHOUTCASTVIEW_H

#include "abstractview.h"

class ShoutcastModel;
class FileView;
class MPDDirectory;

class ShoutcastView : public AbstractTree {
	Q_OBJECT
public:
	ShoutcastView(QWidget *);
	void setFileView(FileView *);

public slots:
	void updateTranslation();


private:

	ShoutcastModel *m_model;
	FileView *m_fileView;
	QAction *m_enqueueAction, *m_informationAction, *m_rescanAction, *m_playAction;
};
#endif
