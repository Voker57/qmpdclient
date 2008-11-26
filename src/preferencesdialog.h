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

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include "ui_preferencesdialog.h"
#include <QDialog>

struct PreferencesDialogPrivate;

struct PreferencesDialog : QDialog, private Ui::PreferencesDialog {
	PreferencesDialog(QWidget *);
	~PreferencesDialog();
	Q_OBJECT

public slots:
	void updateIconSet();
	void updateTranslation();

private slots:
	void on_addButton_clicked();
	void on_closeButton_clicked();
	void on_categoryList_currentItemChanged(QTreeWidgetItem *, QTreeWidgetItem *);
	void on_deleteButton_clicked();
	void on_downButton_clicked();
	void on_fontButton_clicked();
	void on_patternLine_textChanged(const QString &);
	void on_testLine_textChanged(const QString &);
	void on_upButton_clicked();
	void crossfadeChanged();
	void iconsetChanged(QListWidgetItem *);
	void localeChanged(QListWidgetItem *);
	void notifierChanged(int);
	void outputChanged(QTreeWidgetItem *, int);
	void serverSelectionChanged();
	void styleChanged(QListWidgetItem *);

private:
	void initCategoryList();
	void initServerPage();
	void initConnectionPage();
	void initCoverArtPage();
	void initLookAndFeelPage();
	void initIconSetPage();
	void initLibraryPage();
	void initDirectoriesPage();
	void initPlaylistPage();
	void initStylePage();
	void initShortcutPage();
	void initLanguagePage();
	void initDynamicPlaylistPage();
	void initNotificationsPage();
	void initTagGuesserPage();
	void initTrayIconPage();
	void setFontString(const QFont &);

	PreferencesDialogPrivate *d;
};
#endif
