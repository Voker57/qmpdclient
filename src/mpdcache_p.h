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

// Stuff for updating progress bar
#define START(MSG, SIZE) int factorX = progressFactor(SIZE); if (factorX > 0) emit MPDCache::instance()->updateStart(SIZE, MSG); int stepX = 0
#define STEP ++stepX; if (factorX > 0 && stepX % factorX == 0) emit MPDCache::instance()->updateProgress(++stepX)
#define STOP if (factorX > 0) emit MPDCache::instance()->updateDone()
#define DEBUGCONTEXT "MPDCachePrivate"

inline int progressFactor(int nr) {
	if (nr > 1000)
		return 50;
	if (nr > 100)
		return 10;
	if (nr > 25)
		return 2;
	return 0;
}

const int CACHE_FORMAT = 109;

struct MPDCachePrivate {
	MPDCachePrivate();
	void disconnected();
	bool isConnected();
	MPDSongList cacheAlbumSongs(const QStringList &);
	MPDSongList cacheArtistSongs(const QStringList &);
	MPDSongList cacheDirectorySongs(const QList<MPDDirectory> &);
	MPDSongList cachePlaylistSongs(const MPDSongList &);
	MPDSongList playlists();
	MPDSongList songsByAlbums(const QStringList &);
	MPDSongList songsByArtists(const QStringList &);
	void load();
	void save();
	void updateLibrary(bool reread);
	void updatePlaylists(bool reread);

	MPDStats stats;
	bool allCached;
	bool loadCache;
	MPDDirectory root;
	QMap<QString, QSet<QString> > artistAlbumMap;
	QMap<QString, MPDSongList> artistSongMap, albumSongMap;
	QMap<QString, MPDDirectory> pathDirectoryMap;
	QMap<MPDSong, MPDSongList> playlistMap;
	QString cachePath;
	QStringList files, artists;

private:
	void cacheArtists();
	void cacheEverything();
	void cacheDirectories();
	void clearArtistCache();
	void clearDirectoryCache();
};

MPDCachePrivate::MPDCachePrivate() :
		allCached(false),
		loadCache(true) {}

inline bool MPDCachePrivate::isConnected() {
	return MPDConnection::instance()->isConnected();
}

void MPDCachePrivate::clearArtistCache() {
	allCached = false;
	artists.clear();
	artistAlbumMap.clear();
	albumSongMap.clear();
	artistSongMap.clear();
}

void MPDCachePrivate::clearDirectoryCache() {
	files.clear();
	pathDirectoryMap.clear();
	root = MPDDirectory();
}

void MPDCachePrivate::disconnected() {
	clearArtistCache();
	clearDirectoryCache();
	playlistMap.clear();
	loadCache = true;
}

/// Cache stuff
void MPDCachePrivate::cacheArtists() {
	if (!isConnected())
		return;

	mpd_call(updateArtists, List, MPD_TABLE_ARTIST, 0);
	artists = MPDConnection::instance()->artists();
	if (!mpd_cleanup()) {
		clearArtistCache();
		return;
	}

	DEBUG1("Cached all artists");
	save();
}

void MPDCachePrivate::cacheEverything() {
	if (!isConnected())
		return;

	const int atime = 500;
	MPDSongList ret;

	emit MPDCache::instance()->updateStart(files.size(), MPDCache::tr("Reading songs"));
	for (int i = 0; i < files.size(); i += atime) {
		mpd_beginList();
		for (int j = i; j < i + atime && j < files.size(); ++j) {
			mpd_call(cacheAllSongs, ListallInfo, files.at(j).toUtf8());
			if (j % 50 == 0)
				emit MPDCache::instance()->updateProgress(i);
		}
		mpd_endList();

		MPDSongList a = MPDConnection::instance()->entities().songs();

		if (!mpd_cleanup()) {
			clearArtistCache();
			emit MPDCache::instance()->updateDone();
			return;
		}

		// Fill caches
		foreach(MPDSong s, a) {
			if (!artists.contains(s.artist()))
				artists << s.artist();
			artistAlbumMap[s.artist()].insert(s.album());
			albumSongMap[s.album()].append(s);
			artistSongMap[s.artist()].append(s);
			Q_ASSERT(pathDirectoryMap.contains(s.directory()));
			pathDirectoryMap[s.directory()].addSong(s);
		}
	}
	emit MPDCache::instance()->updateDone();

	artists.sort();
	allCached = true;
	DEBUG1("Cached all songs and directories");
	save();
}

void MPDCachePrivate::cacheDirectories() {
	if (!isConnected())
		return;

	mpd_call(cacheDirectories, Listall, "/");
	MPDEntities entities = MPDConnection::instance()->entities();
	if (!mpd_cleanup())
		return;

	// Files
	foreach(MPDSong s, entities.songs()) {
		files << s.url();
	}

	// Directory tree skeleton
	pathDirectoryMap[""] = root = MPDDirectory("");
	foreach(QString dir, entities.directories()) {
		MPDDirectory parent;
		if (!dir.contains('/')) {
			parent = root;
		} else {
			QString parentPath = dir.section('/', 0, -2);
			Q_ASSERT(pathDirectoryMap.contains(parentPath));
			parent = pathDirectoryMap[parentPath];
		}

		MPDDirectory child(dir, parent);
		parent.addChild(child);
		pathDirectoryMap[child.absolutePath()] = child;
	}
}

MPDSongList MPDCachePrivate::cacheAlbumSongs(const QStringList &albums) {
	Q_ASSERT(!allCached);
	Q_ASSERT(!Config::instance()->showAll());
	Q_ASSERT(!albums.isEmpty());
	MPDSongList ret;
	if (!isConnected())
		return ret;

	START(MPDCache::tr("Caching songs"), albums.size());
	foreach(QString album, albums) {
		mpd_call(cacheAlbumSongs, Find, MPD_TABLE_ALBUM, album.toUtf8());
		MPDSongList songs = MPDConnection::instance()->entities().songs();
		if (!mpd_cleanup()) {
			ret.clear();
			break;
		}
		albumSongMap[album] = songs;
		ret << songs;
		STEP;
	}
	STOP;
	DEBUG1("Cached songs by albums: %s", qPrintable(albums.join(", ")));
	save();

	return ret;
}

MPDSongList MPDCachePrivate::cacheArtistSongs(const QStringList &artists) {
	Q_ASSERT(!allCached);
	Q_ASSERT(!Config::instance()->showAll());
	Q_ASSERT(!artists.isEmpty());
	MPDSongList ret;
	if (!isConnected())
		return ret;

	START(MPDCache::tr("Caching songs"), artists.size());
	foreach(QString artist, artists) {
		mpd_call(cacheArtistSongs, Find, MPD_TABLE_ARTIST, artist.toUtf8());
		MPDSongList songs = MPDConnection::instance()->entities().songs();
		if (!mpd_cleanup()) {
			ret.clear();
			break;
		}
		artistSongMap[artist] = songs;
		ret << songs;
		STEP;
	}
	STOP;

	// Populate artistAlbumMap
	foreach(MPDSong s, ret) {
		artistAlbumMap[s.artist()].insert(s.album());
	}
	DEBUG1("Cached songs by artists: %s", qPrintable(artists.join(", ")));
	save();

	return ret;
}

MPDSongList MPDCachePrivate::cacheDirectorySongs(const QList<MPDDirectory> &dirs) {
	Q_ASSERT(!allCached);
	Q_ASSERT(!Config::instance()->showAll());
	Q_ASSERT(!dirs.isEmpty());
	MPDSongList ret;
	if (!isConnected())
		return ret;

	START(MPDCache::tr("Caching songs"), dirs.size());
	foreach(MPDDirectory dir, dirs) {
		mpd_call(cacheDirectorySongs, LsInfo, dir.absolutePath().toUtf8());
		MPDSongList songs = MPDConnection::instance()->entities().songs();
		if (!mpd_cleanup()) {
			ret.clear();
			break;
		}
		dir.setSongs(songs);
		ret << songs;
		STEP;
	}
	STOP;
	DEBUG1("Cached songs by directory: %s and others", dirs.isEmpty() ? "" : qPrintable(dirs.first().absolutePath()));
	save();

	return ret;
}

MPDSongList MPDCachePrivate::cachePlaylistSongs(const MPDSongList &playlists) {
	MPDSongList ret;
	if (!isConnected())
		return ret;

	START(MPDCache::tr("Caching songs"), playlists.size());
	foreach(MPDSong playlist, playlists) {
		mpd_call(cachePlaylistSongs, ListPlaylistInfo, playlist.url().toUtf8().data());
		MPDSongList songs = MPDConnection::instance()->entities().songs();
		if (!mpd_cleanup()) {
			ret.clear();
			break;
		}
		playlistMap[playlist] = songs;
		ret << songs;
		STEP;
	}
	STOP;
	DEBUG1("Cached songs by playlist: %s and others", playlists.isEmpty() ? "" : qPrintable(playlists.first().url()));
	save();

	return ret;
}

MPDSongList MPDCachePrivate::playlists() {
	MPDSongList pls;
	foreach(MPDSong s, playlistMap.keys()) {
		pls << s;
	}
	return pls;
}

MPDSongList MPDCachePrivate::songsByAlbums(const QStringList &albums) {
	if (!isConnected())
		return MPDSongList();

	QStringList toCache;
	MPDSongList ret;
	START(MPDCache::tr("Reading songs"), albums.size());
	foreach(QString album, albums) {
		if (!albumSongMap.contains(album))
			toCache << album;
		else
			ret << albumSongMap.value(album);
		STEP;
	}
	STOP;

	if (!toCache.isEmpty())
		ret << cacheAlbumSongs(toCache);

	return ret;
}

MPDSongList MPDCachePrivate::songsByArtists(const QStringList &artists) {
	if (!isConnected())
		return MPDSongList();

	QStringList toCache;
	MPDSongList ret;
	START(MPDCache::tr("Reading songs"), artists.size());
	foreach(QString artist, artists) {
		if (!artistSongMap.contains(artist))
			toCache << artist;
		else
			ret << artistSongMap.value(artist);
		STEP;
	}
	STOP;

	if (!toCache.isEmpty())
		ret << cacheArtistSongs(toCache);

	return ret;
}

void MPDCachePrivate::updateLibrary(bool reread) {
	// Preliminary file structure must be in place before library can be read
	if (reread || root.isNull()) { // Cache is missing, or forced reread
		clearDirectoryCache(); // Clear directory cache

		// Cache files and directory structure
		cacheDirectories();
	}

	if (reread || (Config::instance()->showAll() && !allCached) || (!Config::instance()->showAll() && artists.isEmpty())) {
		clearArtistCache(); // Clear artist/album/songs cache

		if (Config::instance()->showAll())
			cacheEverything(); // Cache all artists, albums, songs and directories. Note: playlists are not cached here.
		else
			cacheArtists(); // Cache artists only, read the rest on demand.
	}

	// All done, tell the gui.
	emit MPDCache::instance()->artistsUpdated(artists);
	emit MPDCache::instance()->directoriesUpdated(root);
}

void MPDCachePrivate::updatePlaylists(bool reread) {
	if (!reread && !playlistMap.isEmpty()) {
		// All was in cache, just emit!
		emit MPDCache::instance()->playlistsUpdated(playlists());
		return;
	}

	playlistMap.clear();
	if (!isConnected())
		return;

	mpd_call(updatePlaylists, LsInfo, "");
	foreach(MPDSong pl, MPDConnection::instance()->entities().playlists()) {
		playlistMap[pl] = MPDSongList();
	}
	if (!mpd_cleanup()) {
		playlistMap.clear();
		return;
	}

	save();
	emit MPDCache::instance()->playlistsUpdated(playlists());
}

void MPDCachePrivate::load() {
	ServerInfo server = MPDConnection::instance()->server();
	if (cachePath.isNull() || server.isNull())
		return;

	QFile in(QString("%1%2_%3.cache").arg(cachePath).arg(server.address()).arg(server.port()));
	if (!in.open(QIODevice::ReadOnly)) {
		DEBUG("Could not open cache for reading: %s", qPrintable(in.fileName()));
		return;
	}

	QDataStream ds(&in);
	int cacheFormat;
	ds >> cacheFormat;
	if (cacheFormat != CACHE_FORMAT) {
		DEBUG("Wrong cache format: %s", qPrintable(in.fileName()));
		return;
	}

	long long cacheVersion;
	ds >> cacheVersion;
	if (static_cast<unsigned long>(cacheVersion) != stats.dbUpdateTime()) {
		DEBUG("Cache not up to date: %s", qPrintable(in.fileName()));
		return;
	}

	// Version number is correct. Read the cache.
	DEBUG2("Reading cache:");
	ds >> allCached;
	DEBUG2("  allCached: %s", BTS(allCached));
	ds >> artists;
	DEBUG2("  artists: %d", artists.size());
	ds >> artistAlbumMap;
	DEBUG2("  artistAlbumMap: %d", artistAlbumMap.size());
	ds >> artistSongMap;
	DEBUG2("  artistSongMap: %d", artistSongMap.size());
	ds >> albumSongMap;
	DEBUG2("  albumSongMap: %d", albumSongMap.size());
	ds >> playlistMap;
	DEBUG2("  playlistMap: %d", playlistMap.size());
	ds >> files;
	DEBUG2("  files: %d", files.size());

	// Read directory crud
	pathDirectoryMap[""] = root = MPDDirectory("");

	int dirCount = 0;
	bool readDir;
	MPDSongList songs;

	ds >> readDir;
	if (readDir) {
		ds >> songs;
		root.setSongs(songs);
		dirCount++;
	}
	while (!ds.atEnd()) {
		QString abspath;
		ds >> abspath;

		MPDDirectory parent;
		if (!abspath.contains('/')) {
			parent = root;
		} else {
			QString parentPath = abspath.section('/', 0, -2);
			Q_ASSERT(pathDirectoryMap.contains(parentPath));
			parent = pathDirectoryMap[parentPath];
		}
		MPDDirectory child(abspath, parent);
		parent.addChild(child);
		pathDirectoryMap[child.absolutePath()] = child;

		ds >> readDir;
		if (readDir) {
			ds >> songs;
			child.setSongs(songs);
			dirCount++;
		}
	}
	DEBUG2("  directories: %d", dirCount);

	in.close();
	DEBUG("Cache was read: %s", qPrintable(in.fileName()));
}

void MPDCachePrivate::save() {
	ServerInfo server = MPDConnection::instance()->server();
	if (cachePath.isNull() || server.isNull())
		return;

	QFile in(QString("%1%2_%3.cache").arg(cachePath).arg(server.address()).arg(server.port()));
	if (!in.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
		DEBUG("Could not open cache for writing: %s", qPrintable(in.fileName()));
		return;
	}

	QDataStream ds(&in);
	ds << CACHE_FORMAT;
	ds << static_cast<long long>(stats.dbUpdateTime());
	DEBUG2("Saving cache:");
	ds << allCached;
	DEBUG2("  allCached: %s", BTS(allCached));
	ds << artists;
	DEBUG2("  artists: %d", artists.size());
	ds << artistAlbumMap;
	DEBUG2("  artistAlbumMap: %d", artistAlbumMap.size());
	ds << artistSongMap;
	DEBUG2("  artistSongMap: %d", artistSongMap.size());
	ds << albumSongMap;
	DEBUG2("  albumSongMap: %d", albumSongMap.size());
	ds << playlistMap;
	DEBUG2("  playlistMap: %d", playlistMap.size());
	ds << files;
	DEBUG2("  files: %d", files.size());
	int dirCount = 0;
	ds << root.isCached();
	if (root.isCached()) {
		ds << root.songs(false);
		dirCount++;
	}
	foreach(MPDDirectory dir, root.children(true)) {
		ds << dir.absolutePath();
		ds << dir.isCached();
		if (dir.isCached()) {
			ds << dir.songs(false);
			dirCount++;
		}
	}
	DEBUG2("  directories: %d", dirCount);

	in.close();
	DEBUG1("Cache was written: %s", qPrintable(in.fileName()));
}
