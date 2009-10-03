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

#include "shoutcastmodel.h"
#include <QList>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QDomDocument>
#include <QXmlQuery>
#include <QDebug>
#include <QBuffer>

namespace
{
	int maxSize = 200000;
}

ShoutcastModel::ShoutcastModel(QObject *parent)
: QStandardItemModel(parent),
  m_networkManager(new QNetworkAccessManager(this)) {
	setObjectName("shoutcastmodel");

	connect(m_networkManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(replyFinished(QNetworkReply*)));
}

void ShoutcastModel::replyFinished(QNetworkReply *reply)
{
	// Using read() putting the content into a QBuffer to workaround
	// some strange hangs occuring if passing IO device directly into
	// QXmlQuery object.
	QByteArray content = reply->read(maxSize);
	QBuffer buf(&content);
	buf.open(QIODevice::ReadOnly);
	QXmlQuery q;
	q.bindVariable("glist", &buf);
	q.setQuery("for $i in doc($glist)/genrelist/genre/@name return string($i)");
	QStringList genres;
	bool res = q.evaluateTo(&genres);
	if (!res)
		return;
	clear();
	QStandardItem * root = new QStandardItem("Genres");

	foreach(QString s, genres)
	{
		QStandardItem * item = new QStandardItem(s);
		root->appendRow(item);
		qDebug() << s;
	}
	appendRow(root);
}

void ShoutcastModel::refresh()
{
	//m_networkManager->get(QNetworkRequest(QUrl("http://yp.shoutcast.com/sbin/newxml.phtml")));
	m_networkManager->get(QNetworkRequest(QUrl("file:///C:/Users/Magne.Pelle/Documents/git/qmpdclient/newxml.phtml.xml")));
}
