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

#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>

class MPDSongList;
class QFont;
class ServerInfo;

class Config : public QSettings {
	Q_OBJECT

public:
	static Config *instance();

	QString cachePath() const;
	QString systemPath() const;
	QString userPath() const;

	// Server settings
	bool autoconnect() const;
	bool reconnect() const;
	int reconnectTime() const;
	int timeoutTime() const;
	QList<ServerInfo> servers() const;
	ServerInfo server(const QString & = QString()) const;

	// Look and feel
	bool alternatingRowColors() const;
	bool autoResizeColumns() const;
	bool enqueue() const;
	QFont font() const;
	bool opaqueResize() const;
	bool scrollToPlaying() const;
	bool showRemaining() const;

	// Look and feel subpages
	QString iconSetPath() const;
	bool filterByAlbumOnly() const;
	bool disregardLeadingThe() const;
	QString playlistPattern() const;
	bool recurse() const;
	bool showAll() const;
	QString style(const QString & = QString()) const;
	QString styleFile() const;
	bool showCoverArt() const;
	QString coverArtDir() const;
	QString coverArtMaxHeight() const;
	QString coverArtMaxWidth() const;

	// Shortcuts
	QString shortcut(const QString &) const;

	// Language
	QString locale() const;
	QString localeFile() const;
	bool translate() const;

	// Popups
	bool notificationsEnabled() const;
	int notificationsPosition() const;
	int notificationsTimeout() const;
	int notifier() const;

	// Tray icon
	bool minimizeToTray() const;
	bool startHidden() const;
	bool trayIconEnabled() const;

	// Dynamic playlist
	int autoAddCount() const;
	int autoAddPos() const;
	bool autoAddSongs() const;
	bool autoRemoveSongs() const;

	// Last.fm
	bool submitSongsToLastFm() const;
	QString lastFmUsername() const;
	QString lastFmPassword() const;
	bool lastFmHashedPassword() const;

	// Tag guesser
	QString guessPattern() const;
	bool tagGuesserEnabled() const;
	QString testFilename() const;

	// Window and splitter sizes
	void setDirectorySplitterSizes(const QByteArray &);
	void setLibraryHSplitterSizes(const QByteArray &);
	void setLibraryVSplitterSizes(const QByteArray &);
	void setMainSplitterSizes(const QByteArray &);
	void setPlaylistsSplitterSizes(const QByteArray &);
	void setRightBarTab(int);
	int rightBarTab();
	void setWindowSize(const QSize &);
	QByteArray directorySplitterSizes() const;
	QByteArray libraryHSplitterSizes() const;
	QByteArray libraryVSplitterSizes() const;
	QByteArray mainSplitterSizes() const;
	QByteArray playlistsSplitterSizes() const;
	QSize windowSize() const;

	// View's properties
	void setHeaderViewState(const QString &, const QByteArray &);
	QByteArray headerViewState(const QString &) const;

	// Radio stations
	void addRadioStation(const QString &title, const QString &url);
	void removeRadioStations(const MPDSongList &stations);
	MPDSongList radioStations() const;

public slots:
	// Server settings
	void setAutoconnect(bool);
	void setServers(const QList<ServerInfo> &);
	void setReconnect(bool);
	void setReconnectTime(int);
	void setTimeoutTime(int);

	// Look and feel
	void setAlternatingRowColors(bool);
	void setAutoResizeColumns(bool);
	void setEnqueue(bool);
	void setFont(const QFont &);
	void setOpaqueResize(bool);
	void setRecurse(bool);
	void setShowAll(bool);
	void setShowRemaining(bool);

	// Look and feel subpages
	void setFilterByAlbumOnly(bool);
	void setIconSet(const QString &);
	void setPlaylistPattern(const QString &);
	void setDisregardLeadingThe(bool);
	void setScrollToPlaying(bool);
	void setStyleFile(const QString &);
	void setShowCoverArt(bool);
	void setCoverArtDir(const QString &);
	void setCoverMaxHeight(const QString &);
	void setCoverMaxWidth(const QString &);

	// Shortcuts
	void setOriginalShortcut(const QString &action, const QString &shortcut);
	void setShortcut(const QString &action, const QString &shortcut);

	// Language
	void setLocale(const QString &);
	void setTranslate(bool);

	// Notifications
	void setNotificationsEnabled(bool);
	void setNotificationsPosition(int);
	void setNotificationsTimeout(int);
	void setNotifier(int);

	// Tray icon
	void setMinimizeToTray(bool);
	void setStartHidden(bool);
	void setTrayIconEnabled(bool);

	// Dynamic playlist
	void setAutoAddCount(int);
	void setAutoAddPos(int);
	void setAutoAddSongs(bool);
	void setAutoRemoveSongs(bool);

	// Tag guesser
	void setGuessPattern(const QString &);
	void setTagGuesserEnabled(bool);
	void setTestFilename(const QString &);

	// Last.fm
	void setSubmitSongsToLastFm(bool);
	void setLastFmUsername(const QString &);
	void setLastFmPassword(const QString &);
	void setLastFmHashedPassword(bool);

signals:
	void alternatingChanged(bool);
	void autoResizeChanged(bool);
	void filterByAlbumOnlyChanged(bool);
	void fontChanged(const QFont &);
	void iconSetChanged();
	void localeChanged(const QString &);
	void opaqueResizeChanged(bool);
	void playlistPatternChanged(const QString &);
	void serverListChanged(const QList<ServerInfo> &);
	void showAllChanged(bool);
	void showCoverArtChanged(bool);
	void styleChanged(const QString &);
	void trayIconChanged(bool);

private:
	Config();

	static Config *m_instance;
	QString m_cachePath, m_systemPath, m_userPath;
	QMap<QString, QString> m_originalShortcuts;
};
#endif
