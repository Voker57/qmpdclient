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

#ifndef RICHTEXT_H
#define RICHTEXT_H

#include <QLabel>

/**
 * Very ugly workaround to find max size of a html-formatted text string.
 * Need this since QFontMetrics does not support rich text.
 */
static QString elideRichText(const QString &preTag, const QString &text, const QString &postTag, int maxwidth) {
	QLabel dummy;
	dummy.setText(preTag + text + postTag);
	int n = text.size();
	for (; dummy.minimumSizeHint().width() > maxwidth; n--) {
		dummy.setText(preTag + text.left(n) + postTag);
	}
	if (n < text.size())
		return preTag + text.left(n-3) + "..." + postTag;
	return preTag + text + postTag;
}
#endif
