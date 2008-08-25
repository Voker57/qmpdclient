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
/*
#include "tagmodel.h"
#include "mpddirectory.h"
#include "mpdsong.h"
#include <QMimeData>
#include <QStringList>

#include "mpdsonglist.h"
struct TagPrivate : public QSharedData {
	mutable bool cached;
	mutable QList<Tag> children;
	mutable MPDSongList songs;
	QString absolutePath;
	Tag parent;
	TagPointer *pointer;

	TagPrivate(const QString &a, const Tag &p) :
			cached(false),
			absolutePath(a),
			parent(p),
			pointer(0) {}
	~TagPrivate() {
		Q_ASSERT(pointer);
		delete pointer;
	}
};

TagPointer::TagPointer(const Tag &d) : m_directory(d) {}

Tag TagPointer::directory() const {
	return m_directory;
}





Tag::Tag(const QString &absPath, const Tag &parent) : d(new TagPrivate(absPath, parent)) {
	d->pointer = new TagPointer(*this);
}
Tag::Tag() : d(0) {}
Tag::Tag(const Tag &other) : d(other.d) {}
Tag::~Tag() {}

bool Tag::isNull() const {
	return d == NULL;
}

TagPointer *Tag::pointer() const {
	Q_ASSERT(d);
	if (!d)
		return 0;
	return d->pointer;
}

void Tag::addChild(const Tag &newChild) const {
	Q_ASSERT(d);
	d->children << newChild;
}

Tag Tag::child(int childNumber) const {
	Q_ASSERT(d);
	return d->children.at(childNumber);
}

int Tag::childCount() const {
	Q_ASSERT(d);
	if (!d)
		return 0;
	return d->children.size();
}

int Tag::indexOfChild(const Tag &child) const {
	Q_ASSERT(d);
	return d->children.indexOf(child);
}

QList<Tag> Tag::children(bool recurse) const {
	Q_ASSERT(d);
	if (!recurse)
		return d->children;
	QList<Tag> ret = d->children;
	foreach(Tag child, d->children) {
		ret << child.children(true);
	}
	return ret;
}

Tag Tag::parent() const {
	Q_ASSERT(d);
	if (!d)
		return Tag();
	return d->parent;
}

QString Tag::absolutePath() const {
	Q_ASSERT(d);
	if (!d)
		return QString();
	return d->absolutePath;
}

QString Tag::directoryName() const {
	Q_ASSERT(d);
	if (absolutePath().isEmpty())
		return QObject::tr("Root", "This is the name of the root directory in the directory browser");
	return absolutePath().section('/', -1);
}

bool Tag::isCached() const {
	Q_ASSERT(d);
	if (!d)
		return false;
	return d->cached;
}

void Tag::addSong(const MPDSong &song) const {
	Q_ASSERT(d);
	d->songs << song;
	d->cached = true;
}

void Tag::setSongs(const MPDSongList &songs) const {
	Q_ASSERT(d);
	d->songs = songs;
	d->cached = true;
}

MPDSongList Tag::songs(bool recursive) const {
	Q_ASSERT(d);
	if (!recursive)
		return d->songs;
	MPDSongList ret = d->songs;
	foreach(Tag child, d->children) {
		ret << child.songs(true);
	}
	return ret;
}

bool Tag::operator==(const Tag &other) const {
	if (isNull() && other.isNull())
		return true;
	if (other.isNull())
		return false;
	return (absolutePath() == other.absolutePath()
	        && isCached() == other.isCached()
	        && childCount(false) == other.childCount(false));
}

Tag &Tag::operator=(const Tag & other) {
	d = other.d;
	return *this;
}






































TagModel::TagModel(QObject *parent) : QAbstractItemModel(parent) {
	setObjectName("tagmodel");
}

int TagModel::columnCount(const QModelIndex &) const {
	return 1;
}

QVariant TagModel::data(const QModelIndex &index, int role) const {
	Tag i = directory(index);
	if (!i.isNull() && role == Qt::DisplayRole && index.column() == 0)
		return i.title();
	return QVariant();
}

Qt::ItemFlags TagModel::flags(const QModelIndex &index) const {
	if (!index.isValid())
		return QAbstractItemModel::flags(index);
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled;
}

bool TagModel::hasChildren(const QModelIndex &parent) const {
	// Top level
	if (!parent.isValid()) {
		return !m_root.isNull();
	}

	// Children
	Tag i = directory(parent);
	if (!i.isNull()) {
		return i.childCount() > 0;
	}
	return false;
}

QVariant TagModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal || section != 0)
		return QVariant();
	return QObject::tr("Directory", "This is used as the header of directory-tree in directory view");
}

QModelIndex TagModel::index(int row, int column, const QModelIndex &parent) const {
	if (row < 0 || column != 0)
		return QModelIndex();

	// Toplevel items
	if (!parent.isValid()) {
		if (row > 0) // Only one root
			return QModelIndex();

		if (!m_root.isNull()) {
			Q_ASSERT(row == 0 && column == 0 && !m_root.isNull());
			return createIndex(row, column, m_root);
		}
		Q_ASSERT(m_root.isNull());
		return QModelIndex();
	}

	// Non-toplevel items
	Tag parentDirectory = directory(parent);
	if (!parentDirectory.isNull() && row < parentDirectory.childCount()) {
		Tag directory = parentDirectory.child(row);
		if (!directory.isNull())
			return createIndex(row, column, directory);
	}
	return QModelIndex();
}

QModelIndex TagModel::parent(const QModelIndex &index) const {
	Tag indexDirectory = directory(index);
	if (indexDirectory.isNull())
		return QModelIndex();

	Tag parentDirectory = indexDirectory.parent();
	if (parentDirectory.isNull()) // Toplevel directory
		return QModelIndex();

	Tag parentsparent = parentDirectory.parent();
	if (!parentsparent.isNull()) // Find index of parent in parent's parent if any
		return createIndex(parentsparent.indexOfChild(parentDirectory), 0, parentDirectory);

	// Parent has no parent, parentDirectory is toplevel
	return createIndex(0, 0, parentDirectory);
}

int TagModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid()) {
		const Tag parentDir = directory(parent);
		if (!parentDir.isNull()) {
			return parentDir.childCount();
		}
		Q_ASSERT(false);
	}
	// Parent is not valid, requesting rowcount for toplevel dir. Always 1 or 0.
	return m_root.isNull() ? 0 : 1;
}

QList<Tag> TagModel::directories(const QModelIndexList &indexes) const {
	QList<Tag> ret;
	foreach(QModelIndex index, indexes) {
		ret << directory(index);
	}
	return ret;
}

Tag TagModel::directory(const QModelIndex &index) const {
	if (!index.isValid())
		return Tag();
	if (!index.internalPointer())
		return Tag();
	TagPointer *pointer = static_cast<TagPointer*>(index.internalPointer());
	if (!pointer)
		return Tag();
	return pointer->directory();
}

QModelIndex TagModel::createIndex(int row, int col, const Tag &dir) const {
	return QAbstractItemModel::createIndex(row, col, dir.pointer());
}

void TagModel::setRoot(const Tag &root) {
	m_root = root;
	reset();
}

QStringList TagModel::mimeTypes() const {
	return QStringList() << "qmpdclient/song";
}

QMimeData *TagModel::mimeData(const QModelIndexList &indexes) const {
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);
	foreach(Tag dir, directories(indexes)) {
		// TODO
// 		stream << MPDSong::createTest(dir.absolutePath());
	}
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("qmpdclient/song", encodedData);
	return mimeData;
}
*/