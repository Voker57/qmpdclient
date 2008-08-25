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

#include "mpddirectory.h"
#include "mpdsonglist.h"
#include <QObject>

struct MPDDirectoryPrivate : public QSharedData {
	mutable bool cached;
	mutable QList<MPDDirectory> children;
	mutable MPDSongList songs;
	QString absolutePath;
	MPDDirectory parent;
	MPDDirectoryPointer *pointer;

	MPDDirectoryPrivate(const QString &a, const MPDDirectory &p) :
			cached(false),
			absolutePath(a),
			parent(p),
			pointer(0) {}
	~MPDDirectoryPrivate() {
		Q_ASSERT(pointer);
		delete pointer;
	}
};

MPDDirectoryPointer::MPDDirectoryPointer(const MPDDirectory &d) : m_directory(d) {}

MPDDirectory MPDDirectoryPointer::directory() const {
	return m_directory;
}

/**
 * Create a new directory
 * @param abspath Absolute path of directory
 * @param parent Parent directory
 */
MPDDirectory::MPDDirectory(const QString &absPath, const MPDDirectory &parent) : d(new MPDDirectoryPrivate(absPath, parent)) {
	d->pointer = new MPDDirectoryPointer(*this);
}
MPDDirectory::MPDDirectory() : d(0) {}
MPDDirectory::MPDDirectory(const MPDDirectory &other) : d(other.d) {}
MPDDirectory::~MPDDirectory() {}

bool MPDDirectory::isNull() const {
	return d == NULL;
}

MPDDirectoryPointer *MPDDirectory::pointer() const {
	Q_ASSERT(d);
	if (!d)
		return 0;
	return d->pointer;
}

/**
 * Add a new child to this directory, or a sub directory
 * @param newChild directory to add
 */
void MPDDirectory::addChild(const MPDDirectory &newChild) const {
	Q_ASSERT(d);
	d->children << newChild;
}

/**
 * Get child number x
 * @param childNumber Number of child
 * @return Child
 */
MPDDirectory MPDDirectory::child(int childNumber) const {
	Q_ASSERT(d);
	return d->children.at(childNumber);
}

/**
 * Get number of children
 * @return Number of children
 */
int MPDDirectory::childCount(bool recursive) const {
	Q_ASSERT(d);
	if (!d)
		return 0;
	if (!recursive)
		return d->children.size();
	int sum = d->children.size();
	foreach(MPDDirectory child, d->children) {
		sum += child.childCount(true);
	}
	return sum;
}

/**
 * Get index of a child
 * @param child Child to find index of
 * @return Index of child
 */
int MPDDirectory::indexOfChild(const MPDDirectory &child) const {
	Q_ASSERT(d);
	return d->children.indexOf(child);
}

QList<MPDDirectory> MPDDirectory::children(bool recurse) const {
	Q_ASSERT(d);
	if (!recurse)
		return d->children;
	QList<MPDDirectory> ret = d->children;
	foreach(MPDDirectory child, d->children) {
		ret << child.children(true);
	}
	return ret;
}

/**
 * Get parent directory of this directory
 * @return Parent directory
 */
MPDDirectory MPDDirectory::parent() const {
	Q_ASSERT(d);
	if (!d)
		return MPDDirectory();
	return d->parent;
}

/**
 * Absolute path of directory. e.g '/Artist/Album/Disc1'
 * @return Absolute directory path
 */
QString MPDDirectory::absolutePath() const {
	Q_ASSERT(d);
	if (!d)
		return QString();
	return d->absolutePath;
}

/**
 * Get name of directory. e.g. 'Disc1'
 * @return Directory name
 */
QString MPDDirectory::directoryName() const {
	Q_ASSERT(d);
	if (absolutePath().isEmpty())
		return QObject::tr("Root", "This is the name of the root directory in the directory browser");
	return absolutePath().section('/', -1);
}

bool MPDDirectory::isCached() const {
	Q_ASSERT(d);
	if (!d)
		return false;
	return d->cached;
}

void MPDDirectory::addSong(const MPDSong &song) const {
	Q_ASSERT(d);
	d->songs << song;
	d->cached = true;
}

void MPDDirectory::setSongs(const MPDSongList &songs) const {
	Q_ASSERT(d);
	d->songs = songs;
	d->cached = true;
}

MPDSongList MPDDirectory::songs(bool recursive) const {
	Q_ASSERT(d);
	if (!recursive)
		return d->songs;
	MPDSongList ret = d->songs;
	foreach(MPDDirectory child, d->children) {
		ret << child.songs(true);
	}
	return ret;
}

bool MPDDirectory::operator==(const MPDDirectory &other) const {
	if (isNull() && other.isNull())
		return true;
	if (other.isNull())
		return false;
	return (absolutePath() == other.absolutePath()
	        && isCached() == other.isCached()
	        && childCount(false) == other.childCount(false));
}

MPDDirectory &MPDDirectory::operator=(const MPDDirectory &other) {
	d = other.d;
	return *this;
}
