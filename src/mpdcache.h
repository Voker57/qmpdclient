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

#ifndef MPDCACHE_H
#define MPDCACHE_H

#include <QObject>

class AAFilter;
class MPDDirectory;
class MPDSongList;
class MPDStats;
struct MPDCachePrivate;

class MPDCache : public QObject {
	Q_OBJECT
public:
	static MPDCache *instance();
	~MPDCache();
	QStringList albumsByArtists(const QStringList &);
	MPDSongList songsByAlbums(const QStringList &);
	MPDSongList songsByDirectories(const QList<MPDDirectory> &, bool = false);
	MPDSongList songsByAA(const AAFilter &);
	MPDSongList songsByPlaylists(const MPDSongList &);

	void deletePlaylists(const MPDSongList &playlists);
	void deletePlaylist(const QString &playlistName);
	bool playlistExists(const QString &playlistName) const;
	void savePlaylist(const QString &playlistName);

	MPDSongList randomSongs(int);

public slots:
	void rescan(const QList<MPDDirectory> &) const;
	void rescan() const;
	void reReadLibrary(const MPDStats &);

signals:
	void artistsUpdated(const QStringList &);
	void directoriesUpdated(const MPDDirectory &);
	void playlistsUpdated(const MPDSongList &);

	void updateDone();
	void updateProgress(int);
	void updateStart(int, const QString &);

private slots:
	void disconnected();
	void setShowAll(bool);

private:
	MPDCache();

	friend struct MPDCachePrivate;
	MPDCachePrivate *d;
	static MPDCache *m_instance;
};

#endif
