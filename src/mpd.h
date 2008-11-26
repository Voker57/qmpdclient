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

#ifndef MPD_H
#define MPD_H

#include <QObject>

class MPDSong;
class MPDSongList;
class MPDStats;
struct MPDPrivate;

class MPD : public QObject {
	Q_OBJECT
public:
	static MPD *instance();
	~MPD();

	// Playlist management
	void addSongs(const MPDSongList &songs, bool enqueue = true, int atPos = -1) const;
	void moveSongs(const MPDSongList &songs, int toPos) const;
	void removeSongs(const MPDSongList &songs) const;
	void jumpPlaylistSong(const MPDSong &song) const;

	// Server
	int crossfade() const;
	void toggleOutputDevice(int id, bool enabled) const;

public slots:
	// Playlist control
	void clearPlaylist() const;
	void play() const;
	void togglePlay() const;
	void pause() const;
	void stop() const;
	void next() const;
	void prev() const;
	void seek(int toSeconds) const;
	void seekBackward();
	void seekForward();
	void setCrossfade(int seconds) const;
	void setRandom(bool) const;
	void setRepeat(bool) const;
	void setVolume(int) const;
	void shufflePlaylist() const;
	void volumeUp(int = 5) const;
	void volumeDown(int = 5) const;

signals:
	void playingSongUpdated(const MPDSong &);
	void playlistUpdated(const MPDSongList &);
	void randomUpdated(bool);
	void repeatUpdated(bool);
	void stateUpdated(bool);
	void statsUpdated(const MPDStats &);
	void timeUpdated(int, int);
	void volumeUpdated(int);

private slots:
	void poll();

private:
	MPD();

	friend struct MPDPrivate;
	MPDPrivate *d;
	static MPD *m_instance;
};

#endif
