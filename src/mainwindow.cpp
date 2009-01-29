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
#include "directorypanel.h"
#include "iconmanager.h"
#include "librarypanel.h"
#include "mainwindow.h"
#include "mpd.h"
#include "mpdcache.h"
#include "mpdconnection.h"
#include "mpdsonglist.h"
#include "mpdstats.h"
#include "playlistpanel.h"
#include "playlistspanel.h"
#include "preferencesdialog.h"
#include "radiopanel.h"
#include "richtext.h"
#include "serverinfo.h"
#include "shortcuts.h"
#include "trayicon.h"
#include <QCloseEvent>
#include <QDesktopWidget>
#include <QProgressBar>
#include <QShortcut>
#include <QDebug> 		// XXX

MainWindow::MainWindow() : QMainWindow(0) {
	setupUi(this);

	// Status bar
	m_statsLabel = new QLabel;
	m_playlistStatsLabel = new QLabel;
	m_progressBar = new QProgressBar;
	m_progressBar->hide();
	m_progressBar->setMaximumWidth(100);
	m_progressBar->setMaximumHeight(m_statsLabel->minimumSizeHint().height());
	statusBar()->addPermanentWidget(m_progressBar);
	statusBar()->addPermanentWidget(m_playlistStatsLabel);
	statusBar()->addPermanentWidget(m_statsLabel);

	// Show program name and version
	statusBar()->showMessage(NAMEVER);
	setStats(MPDStats());

	// Ideal style vertical tabbars
	leftBar->link(leftStack, splitter);
	rightBar->link(rightStack, splitter);
	m_playlistTab = leftBar->addPanel(new PlaylistPanel, true);
	m_libraryTab = rightBar->addPanel(m_libraryPanel = new LibraryPanel);
	m_directoriesTab = rightBar->addPanel(new DirectoryPanel);
	m_radioTab = rightBar->addPanel(new RadioPanel);
	m_playlistsTab = rightBar->addPanel(new PlaylistsPanel);

	// For icon changes
	m_radioTab->setObjectName("radioTab");
	m_libraryTab->setObjectName("libraryTab");
	m_playlistTab->setObjectName("playlistTab");
	m_playlistsTab->setObjectName("playlistsTab");
	m_directoriesTab->setObjectName("directoriesTab");

	// Signals and slots
	connect(MPDConnection::instance(), SIGNAL(connected(const ServerInfo &)), this, SLOT(connectionChanged()));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(connectionChanged()));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(disconnected(const QString &)));

	connect(MPD::instance(), SIGNAL(statsUpdated(const MPDStats &)), this, SLOT(setStats(const MPDStats &)));
	connect(MPD::instance(), SIGNAL(playingSongUpdated(const MPDSong &)), this, SLOT(setSong(const MPDSong &)));
	connect(MPD::instance(), SIGNAL(playlistUpdated(const MPDSongList &)), SLOT(playlistUpdated(const MPDSongList &)));
	connect(MPDCache::instance(), SIGNAL(updateStart(int, const QString &)), this, SLOT(updateStart(int, const QString &)));
	connect(MPDCache::instance(), SIGNAL(updateProgress(int)), this, SLOT(updateProgress(int)));
	connect(MPDCache::instance(), SIGNAL(updateDone()), this, SLOT(updateDone()));

	// Menu action signals
	connect(disconnectMenu, SIGNAL(triggered()), MPDConnection::instance(), SLOT(disconnectFromMPD()));
	connect(rescanMenu, SIGNAL(triggered()), MPDCache::instance(), SLOT(rescan()));
	connect(jumpToSong, SIGNAL(triggered()), this, SLOT(jumpToCurrentSong()));
	connect(aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
	connect(quitMenu, SIGNAL(triggered()), qApp, SLOT(quit()));
	connect(rightStack, SIGNAL(currentChanged(int)), this, SLOT(rightStackCurrentChanged(int)));

	// Config signals
	connect(Config::instance(), SIGNAL(serverListChanged(const QList<ServerInfo> &)), this, SLOT(serverListChanged(const QList<ServerInfo> &)));
	connect(Config::instance(), SIGNAL(trayIconChanged(bool)), this, SLOT(trayIconChanged(bool)));

	// Shortcut keys
	m_hideKey = new QShortcut(Qt::Key_Escape, this, SLOT(showHide())); // Escape minimizes to tray
	m_hideKey->setObjectName("minimizeToTrayKey");

	// Tray icon
	m_trayIcon = new TrayIcon(this);
	if (Config::instance()->trayIconEnabled())
		m_trayIcon->show();
	connect(m_trayIcon, SIGNAL(clicked()), this, SLOT(showHide()));

	// Restore state
	serverListChanged(Config::instance()->servers());
	splitter->restore(Config::instance()->mainSplitterSizes());
	resize(Config::instance()->windowSize());
	if (!m_trayIcon->isVisible() || !Config::instance()->trayIconEnabled() || !Config::instance()->startHidden())
		show();
	rightStack->setCurrentIndex(Config::instance()->rightBarTab());
}

void MainWindow::updateTranslation() {
	retranslateUi(this);
	setSong(m_song); // Sets window title
	Q_ASSERT(m_playlistTab);
	Q_ASSERT(m_libraryTab);
	Q_ASSERT(m_directoriesTab);
	Q_ASSERT(m_radioTab);
	Q_ASSERT(m_playlistsTab);
	Q_ASSERT(m_hideKey);
	m_playlistTab->setText(tr("&Playlist"));
	m_libraryTab->setText(tr("&Library"));
	m_directoriesTab->setText(tr("&Directories"));
	m_radioTab->setText(tr("&Internet Radio"));
	m_playlistsTab->setText(tr("Pla&ylists"));
	m_hideKey->setWhatsThis(tr("Minimize to tray"));
	setStats(m_stats);
}

void MainWindow::connectionChanged() {
	const bool con = MPDConnection::instance()->isConnected();
	foreach(QWidget *w, findChildren<QWidget*>(QRegExp("Panel$"))) {
		w->setEnabled(con);
	}
}

// Auto connected slots
void MainWindow::on_about_triggered() {
	new AboutDialog(this);
}

void MainWindow::on_splitter_splitterMoved(int, int) {
	Config::instance()->setMainSplitterSizes(splitter->saveState());
}

void MainWindow::on_preferencesMenu_triggered() {
	new PreferencesDialog(this);
}

// User defined slots
void MainWindow::closeEvent(QCloseEvent *e) {
	Q_ASSERT(m_trayIcon);
	if (m_trayIcon->isVisible() && Config::instance()->trayIconEnabled() && Config::instance()->minimizeToTray()) {
		e->ignore();
		showHide();
		return;
	}
	e->accept();
	qApp->quit();
}

void MainWindow::connectToMPD() {
	QObject *origin = sender();
	if (!origin)
		return;
	QAction *action = qobject_cast<QAction*>(origin);
	MPDConnection::instance()->connectToMPD(Config::instance()->server(action->text()));
}

void MainWindow::disconnected(const QString &error) {
	Q_ASSERT(m_progressBar);
	if (!error.isEmpty()) {
		statusBar()->showMessage(QString(" %1: %2 ").arg(tr("Error")).arg(error));
		Q_ASSERT(m_trayIcon);
		m_trayIcon->showMessage(tr("Error"), error, QSystemTrayIcon::Critical, 5000);
	}
	m_progressBar->reset();
}

void MainWindow::resizeEvent(QResizeEvent *e) {
	Config::instance()->setWindowSize(e->size());
}

void MainWindow::serverListChanged(const QList<ServerInfo> &sil) {
	while (!m_actions.isEmpty())
		delete m_actions.takeLast();
	foreach(ServerInfo si, sil) {
		QAction *a = connectMenu->addAction(IconManager::icon("server"), si.name(), this, SLOT(connectToMPD()));
		if (m_actions.isEmpty()) {
			a->setParent(this);
			a->setObjectName("connectMenu");
			a->setWhatsThis(tr("Connect to first server"));
			a->setShortcut(tr("Ctrl+C"));
			// Force shortcut service to reload action list
			Shortcuts *s = Shortcuts::instance();
			if (s)
				s->updateTranslation();
		} else
			a->setObjectName("connectOthers");
		m_actions << a;
	}
}

void MainWindow::setSong(const MPDSong &s) {
	m_song = s;
	QString windowTitle = NAMEVER;
	if (!s.isNull()) {
		int desktopWidth = QApplication::desktop()->width();
		QString title = elideRichText("", s.title(), "", desktopWidth / 2);
		QString artist = elideRichText("", s.artist(), "", desktopWidth / 4);
		windowTitle = qApp->applicationName();
		if (!artist.isEmpty())
			windowTitle += " - " + artist;
		windowTitle += " - " + title;
	}
	setWindowTitle(windowTitle);
	setWindowIconText(windowTitle);
}

void MainWindow::setStats(const MPDStats &stats) {
	Q_ASSERT(m_statsLabel);
	unsigned long secs = stats.dbPlayTime();
	const int day = secs / (60 * 60 * 24);
	secs -= day * 60 * 60 * 24;
	const int hour = secs / (60 * 60);
	secs -= hour * 60 * 60;
	const int min = secs / 60;
	m_statsLabel->setText(tr("Library:  %1 %2, %3 %4, %5 %6. (%7 %8 %9 %10 %11 %12) ")
	                      .arg(stats.numberOfArtists())
	                      .arg(tr("artists"))
	                      .arg(stats.numberOfAlbums())
	                      .arg(tr("albums"))
	                      .arg(stats.numberOfSongs())
	                      .arg(tr("songs"))
	                      .arg(day)
	                      .arg(tr("days"))
	                      .arg(hour)
	                      .arg(tr("hours"))
	                      .arg(min)
	                      .arg(tr("minutes")));
	m_stats = stats;
}

void MainWindow::showHide() {
	Q_ASSERT(m_trayIcon);
	if (Config::instance()->trayIconEnabled() && Config::instance()->minimizeToTray() && m_trayIcon->isVisible())
		isVisible() ? hide() : showNormal();
}

void MainWindow::trayIconChanged(bool e) {
	Q_ASSERT(m_trayIcon);
	m_trayIcon->setVisible(e);
}

void MainWindow::updateStart(int max, const QString &msg) {
	Q_ASSERT(m_progressBar);
	m_progressBar->setRange(0, max);
	m_progressBar->setValue(0);
	m_progressBar->show();
	statusBar()->showMessage(msg);
}

void MainWindow::updateProgress(int at) {
	Q_ASSERT(m_progressBar);
	m_progressBar->setValue(at);
}

void MainWindow::updateDone() {
	Q_ASSERT(m_progressBar);
	m_progressBar->setValue(m_progressBar->maximum());
	m_progressBar->hide();
	if (MPDConnection::instance()->isConnected())
		statusBar()->showMessage(tr("Done"), 2000);
	else
		statusBar()->clearMessage();
}

void MainWindow::rightStackCurrentChanged(int index)
{
	Config::instance()->setRightBarTab(index);
}

	// Select library tab
	// this may be not the perfect solution
	rightStack->setCurrentIndex(0);
}

void MainWindow::playlistUpdated(const MPDSongList &list)
{
	unsigned long tsecs = 0;
	for(MPDSongList::const_iterator it = list.constBegin(); it != list.constEnd(); ++it)
	{
		tsecs+=(*it).secs();

/**
 * Jump to the currently playing song (select in artist/album/song list)
 * If no song is being played, do not jump.
 */
void MainWindow::jumpToCurrentSong() {
	MPD * inst = MPD::instance();
	if (!(inst->isPlaying() || inst->isPaused())) {
		return;
	}

	// XXX set the focus to the libary tab

	// Get current song name, album, artist and go update stuff
	
	// XXX figure out a way to clear without having to reload all songs
	m_libraryPanel->artistView->clearSelection();
	m_libraryPanel->artistView->selectString(m_song.artist());
	m_libraryPanel->albumView->clearSelection();
	m_libraryPanel->albumView->selectString(m_song.album());
	}
	const int day = tsecs / (60 * 60 * 24);
	tsecs -= day * 60 * 60 * 24;
	const int hour = tsecs / (60 * 60);
	tsecs -= hour * 60 * 60;
	const int min = tsecs / 60;
	tsecs -= min*60;
	QString txt = tr("Playlist: ");
	if(day) txt += tr("%1 days, ").arg(day);
	if(hour) txt += tr("%1 hours, ").arg(hour);
	if(min) txt += tr("%1 minutes, ").arg(min);
	txt += tr("%1 seconds.").arg(tsecs);
	m_playlistStatsLabel->setText(txt);