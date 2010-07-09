/*
 * QMPDClient - An MPDCache client written in Qt 4.
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

#include "mpdcache.h"
#include "aafilter.h"
#include "config.h"
#include "debug.h"
#include "libmpdclient.h"
#include "mpdconnection.h"
#include "mpddirectory.h"
#include "mpdentities.h"
#include "mpdoutput.h"
#include "mpdstats.h"
#include "serverinfo.h"
#include <QDir>
#include <QFileInfo>
#include <QMap>
#include <QSet>
#include <QTime>
#include "mpdcache_p.h"

MPDCache *MPDCache::m_instance = 0;

// Constructors and such
MPDCache::MPDCache() : d(new MPDCachePrivate) {
	qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
	setObjectName("MPDCache");
	connect(Config::instance(), SIGNAL(showAllChanged(bool)), this, SLOT(setShowAll(bool)));
	connect(MPDConnection::instance(), SIGNAL(disconnected(const QString &)), this, SLOT(disconnected()));

	QDir path(d->cachePath = Config::instance()->cachePath());
	if (!path.exists()) {
		if (!path.mkpath(path.absolutePath())) {
			d->cachePath = QString();
			qWarning("Path for cache '%s' did not exist, and could not be created.", qPrintable(path.absolutePath()));
		}
	}
	DEBUG1("Cache path is: %s", qPrintable(d->cachePath));
}

MPDCache::~MPDCache() {
	delete d;
}

MPDCache* MPDCache::instance() {
	if (!m_instance)
		m_instance = new MPDCache();
	return m_instance;
}

void MPDCache::disconnected() {
	d->disconnected();
}

void MPDCache::setShowAll(bool a) {
	if (a)
		d->updateLibrary(false);
}

// Updaters
void MPDCache::rescan(const QList<MPDDirectory> &dirs) const {
	if (!d->isConnected())
		return;

	mpd_beginList();
	foreach(MPDDirectory dir, dirs) {
		mpd_call(MPDCache::rescan(const QList<MPDDirectory> &), Update, dir.absolutePath().toUtf8().data());
	}
	mpd_endList();

	mpd_cleanup();
}

void MPDCache::rescan() const {
	if (!d->isConnected())
		return;
	mpd_call(MPDCache::rescan, Update, "");
	mpd_cleanup();
}

void MPDCache::reReadLibrary(const MPDStats &stats) {
	d->stats = stats;

	if (!d->isConnected())
		return;

	if (d->loadCache)
		d->load();

	d->updateLibrary(!d->loadCache);
	d->updatePlaylists(!d->loadCache);

	d->loadCache = false;
}

// Get stuff
QStringList MPDCache::albumsByArtists(const QStringList &artists) {
	if (!d->isConnected())
		return QStringList();

	foreach(QString artist, artists) {
		// Check for 'All'
		if (artist.isNull()) {
			// Requested all albums
			Q_ASSERT(d->allCached);
			Q_ASSERT(Config::instance()->showAll());
			QSet<QString> ret;
			foreach(QSet<QString> albums, d->artistAlbumMap.values()) {
				ret.unite(albums);
			}
			QStringList retList = ret.toList();
			retList.sort();
			return retList;
		}
	}

	// Find what to cache...
	QStringList toCache;
	foreach(QString artist, artists) {
		Q_ASSERT(!artist.isNull()); // Handled above
		if (!d->artistAlbumMap.contains(artist))
			toCache << artist;
	}

	if (!toCache.isEmpty())
		d->cacheArtistSongs(toCache);

	// Albums should by now have been added to cache by cacheArtistSongs, need just to read'em
	QSet<QString> albums;
	START(tr("Reading albums"), artists.size());
	foreach(QString artist, artists) {
		Q_ASSERT(!artist.isNull()); // Handled above
		Q_ASSERT(d->artistAlbumMap.contains(artist)); // Should be cached
		albums.unite(d->artistAlbumMap.value(artist));
		STEP;
	}
	STOP;

	QStringList ret = albums.toList();
	ret.sort();
	return ret;
}

// Get songslists
MPDSongList MPDCache::songsByDirectories(const QList<MPDDirectory> &dirs, bool forceRecurse) {
	if (!d->isConnected())
		return MPDSongList();

	const bool recurse = forceRecurse || Config::instance()->recurse();

	if (!d->allCached) {
		// Make sure all directories are cached
		QList<MPDDirectory> children = dirs;
		if (recurse) {
			// Add all subdirectories to the child list.
			foreach(MPDDirectory dir, dirs) {
				children << dir.children(true);
			}
		}

		QList<MPDDirectory> toCache;
		foreach(MPDDirectory dir, children) {
			Q_ASSERT(!dir.isNull());
			if (!dir.isCached())
				toCache << dir;
		}
		if (!toCache.isEmpty())
			d->cacheDirectorySongs(toCache);
	}

	MPDSongList ret;
	START(tr("Reading songs"), dirs.size());
	foreach(MPDDirectory dir, dirs) {
		Q_ASSERT(!dir.isNull());
		ret << dir.songs(recurse);
		STEP;
	}
	STOP;

	return ret;
}

MPDSongList MPDCache::songsByAA(const AAFilter &aa) {
	if (!d->isConnected())
		return MPDSongList();

	if (Config::instance()->filterByAlbumOnly()) {
		MPDSongList ret = d->songsByAlbums(aa.albums());
		if (aa.notTaggedAlbum()) {// Add 'not tagged' songs, by artist(!)
			foreach(MPDSong song, d->songsByArtists(aa.artists())) {
				if (song.album().isEmpty())
					ret << song;
			}
		}
		return ret;
	}

	// Find by both artist and album.
	MPDSongList ret = d->songsByArtists(aa.artists());
	if (aa.allAlbums())
		return ret;

	// Apply album filter
	START(tr("Filtering songs"), ret.size());
	for (QMutableListIterator<MPDSong> it(ret); it.hasNext();) {
		MPDSong song = it.next();
		if (!(aa.notTaggedAlbum() && song.album().isEmpty()) && !aa.hasAlbum(song.album()))
			it.remove();
		STEP;
	}
	STOP;

	return ret;
}

MPDSongList MPDCache::songsByPlaylists(const MPDSongList &pls) {
	MPDSongList ret;
	if (!d->isConnected() || MPDConnection::instance()->version() < 12)
		return ret;

	MPDSongList toCache;
	START(tr("Reading songs"), pls.size());
	foreach(MPDSong s, pls) {
		if (d->playlistMap.value(s).isEmpty())
			toCache << s;
		else
			ret << d->playlistMap.value(s);
		STEP;
	}
	STOP;

	if (!toCache.isEmpty())
		ret << d->cachePlaylistSongs(toCache);

	return ret;
}

// Misc methods
void MPDCache::deletePlaylists(const MPDSongList &songs) {
	if (!d->isConnected() || songs.isEmpty())
		return;

	mpd_beginList();
	foreach(MPDSong song, songs) {
		mpd_call(MPDCache::deletePlaylists, Rm, song.url().toUtf8());
	}
	mpd_endList();
	mpd_cleanup();
	d->updatePlaylists(true);
}

void MPDCache::deletePlaylist(const QString &playlistName) {
	if (!d->isConnected()) return;

	mpd_beginList();
	foreach(MPDSong s, d->playlistMap.keys()) {
		mpd_call(MPDCache::deletePlaylists, Rm, playlistName.toAscii());
	}

	mpd_endList();
	mpd_cleanup();
	d->updatePlaylists(true);
}

bool MPDCache::playlistExists(const QString &name) const {
	if (!d->isConnected())
		return false;

	foreach(MPDSong s, d->playlistMap.keys()) {
		if (s.url() == name)
			return true;
	}

	return false;
}

void MPDCache::savePlaylist(const QString &name) {
	if (!d->isConnected())
		return;

	mpd_call(MPDCache::savePlaylist, Save, name.toUtf8());
	mpd_cleanup();
	d->updatePlaylists(true);
}

MPDSongList MPDCache::randomSongs(int n) {
	if (!d->isConnected() || n < 1)
		return MPDSongList();

	MPDSongList songs;
	if (d->files.isEmpty())
		return songs;

	for (int i = 0; i < n; i++)
		songs << MPDSong::createTest(d->files.at(qrand() % d->files.size()));
	return songs;
}

MPDSongList MPDCache::songsByAlbums(const QStringList &ss)
{
	return d->songsByAlbums(ss);
}
