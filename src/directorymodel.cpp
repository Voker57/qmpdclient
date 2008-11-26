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

#include "directorymodel.h"
#include "mpddirectory.h"
#include "mpdsong.h"
#include <QMimeData>
#include <QStringList>

DirectoryModel::DirectoryModel(QObject *parent) : QAbstractItemModel(parent) {
	setObjectName("directorymodel");
}

int DirectoryModel::columnCount(const QModelIndex &) const {
	return 1;
}

QVariant DirectoryModel::data(const QModelIndex &index, int role) const {
	MPDDirectory i = directory(index);
	if (!i.isNull() && role == Qt::DisplayRole && index.column() == 0)
		return i.directoryName();
	return QVariant();
}

Qt::ItemFlags DirectoryModel::flags(const QModelIndex &index) const {
	if (!index.isValid())
		return QAbstractItemModel::flags(index);
	return Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled;
}

bool DirectoryModel::hasChildren(const QModelIndex &parent) const {
	// Top level
	if (!parent.isValid()) {
		return !m_root.isNull();
	}

	// Children
	MPDDirectory i = directory(parent);
	if (!i.isNull()) {
		return i.childCount() > 0;
	}
	return false;
}

QVariant DirectoryModel::headerData(int section, Qt::Orientation orientation, int role) const {
	if (role != Qt::DisplayRole || orientation != Qt::Horizontal || section != 0)
		return QVariant();
	return QObject::tr("Directory", "This is used as the header of directory-tree in directory view");
}

QModelIndex DirectoryModel::index(int row, int column, const QModelIndex &parent) const {
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
	MPDDirectory parentDirectory = directory(parent);
	if (!parentDirectory.isNull() && row < parentDirectory.childCount()) {
		MPDDirectory directory = parentDirectory.child(row);
		if (!directory.isNull())
			return createIndex(row, column, directory);
	}
	return QModelIndex();
}

QModelIndex DirectoryModel::parent(const QModelIndex &index) const {
	MPDDirectory indexDirectory = directory(index);
	if (indexDirectory.isNull())
		return QModelIndex();

	MPDDirectory parentDirectory = indexDirectory.parent();
	if (parentDirectory.isNull()) // Toplevel directory
		return QModelIndex();

	MPDDirectory parentsparent = parentDirectory.parent();
	if (!parentsparent.isNull()) // Find index of parent in parent's parent if any
		return createIndex(parentsparent.indexOfChild(parentDirectory), 0, parentDirectory);

	// Parent has no parent, parentDirectory is toplevel
	return createIndex(0, 0, parentDirectory);
}

int DirectoryModel::rowCount(const QModelIndex &parent) const {
	if (parent.isValid()) {
		const MPDDirectory parentDir = directory(parent);
		if (!parentDir.isNull()) {
			return parentDir.childCount();
		}
		Q_ASSERT(false);
	}
	// Parent is not valid, requesting rowcount for toplevel dir. Always 1 or 0.
	return m_root.isNull() ? 0 : 1;
}

QList<MPDDirectory> DirectoryModel::directories(const QModelIndexList &indexes) const {
	QList<MPDDirectory> ret;
	foreach(QModelIndex index, indexes) {
		ret << directory(index);
	}
	return ret;
}

MPDDirectory DirectoryModel::directory(const QModelIndex &index) const {
	if (!index.isValid())
		return MPDDirectory();
	if (!index.internalPointer())
		return MPDDirectory();
	MPDDirectoryPointer *pointer = static_cast<MPDDirectoryPointer*>(index.internalPointer());
	if (!pointer)
		return MPDDirectory();
	return pointer->directory();
}

QModelIndex DirectoryModel::createIndex(int row, int col, const MPDDirectory &dir) const {
	return QAbstractItemModel::createIndex(row, col, dir.pointer());
}

void DirectoryModel::setRoot(const MPDDirectory &root) {
	m_root = root;
	reset();
}

QStringList DirectoryModel::mimeTypes() const {
	return QStringList() << "qmpdclient/song";
}

QMimeData *DirectoryModel::mimeData(const QModelIndexList &indexes) const {
	QByteArray encodedData;
	QDataStream stream(&encodedData, QIODevice::WriteOnly);
	foreach(MPDDirectory dir, directories(indexes)) {
		stream << MPDSong::createTest(dir.absolutePath());
	}
	QMimeData *mimeData = new QMimeData;
	mimeData->setData("qmpdclient/song", encodedData);
	return mimeData;
}
