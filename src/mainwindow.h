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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"
#include "mpdsong.h"
#include "mpdstats.h"

class ServerInfo;
class TrayIcon;
class QProgressBar;
class QShortcut;
class LibraryPanel;

class MainWindow : public QMainWindow, private Ui::MainWindow {
	Q_OBJECT

public:
	MainWindow();
	void findArtist(QString &artist);
	void findAlbum(QString &artist, QString &album);
	void findTrack(QString &artist, QString &album, QString &track);

public slots:
	void showHide();
	void updateTranslation();
	void shortAnnounce(QString);
	void announce(QString);

private slots:
	// Auto connected
	void on_about_triggered();
	void on_splitter_splitterMoved(int, int);
	void on_preferencesMenu_triggered();
	// Mine
	void closeEvent(QCloseEvent *);
	void connectToMPD();
	void connectionChanged();
	void disconnected(const QString &);
	void resizeEvent(QResizeEvent *);
	void setSong(const MPDSong &);
	void setStats(const MPDStats &);
	void serverListChanged(const QList<ServerInfo> &);
	void trayIconChanged(bool);
	void updateStart(int, const QString &);
	void updateProgress(int);
	void updateDone();
	void useLibraryUrl(QString);
	void rightStackCurrentChanged(int);
	void jumpToCurrentSong();

private:
	void retranslate();

	MPDSong m_song;
	MPDStats m_stats;
	QLabel *m_statsLabel;
	QList<QAction*> m_actions;
	QProgressBar *m_progressBar;
	QPushButton *m_playlistTab, *m_libraryTab, *m_directoriesTab, *m_radioTab, *m_playlistsTab;
	QShortcut *m_hideKey;
	TrayIcon *m_trayIcon;
	LibraryPanel *m_libraryPanel;
};
#endif
