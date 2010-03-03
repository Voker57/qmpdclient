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

#ifndef MPDDIRECTORY_H
#define MPDDIRECTORY_H

#include <QList>
#include <QSharedData>

class MPDDirectoryPointer;
class MPDSong;
class MPDSongList;
struct MPDDirectoryPrivate;

class MPDDirectory {
public:
	MPDDirectory(const QString &, const MPDDirectory & = MPDDirectory());
	MPDDirectory();
	MPDDirectory(const MPDDirectory &);
	~MPDDirectory();
	MPDDirectory parent() const;
	MPDDirectoryPointer *pointer() const;
	bool isNull() const;

	void addChild(const MPDDirectory &) const;
	int childCount(bool = false) const;
	int indexOfChild(const MPDDirectory &) const;
	MPDDirectory child(int) const;
	QList<MPDDirectory> children(bool = false) const;

	QString absolutePath() const;
	QString directoryName() const;

	bool isCached() const;
	void addSong(const MPDSong &) const;
	void setSongs(const MPDSongList &) const;
	MPDSongList songs(bool = false) const;
	bool operator==(const MPDDirectory &) const;
	MPDDirectory &operator=(const MPDDirectory &);

private:
	QExplicitlySharedDataPointer<MPDDirectoryPrivate> d;
};

class MPDDirectoryPointer {
public:
	MPDDirectoryPointer(const MPDDirectory &);
	MPDDirectory directory() const;

private:
	MPDDirectory m_directory;
};
#endif
