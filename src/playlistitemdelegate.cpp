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

#include "playlistitemdelegate.h"

#include <QApplication>
#include <QPainter>
#include <QTextLayout>

PlaylistDelegate::PlaylistDelegate(QObject *p) : QItemDelegate(p) {}

QString PlaylistDelegate::replaceNewLine(QString text) const {
	const QChar nl = QLatin1Char('\n');
	for (int i = 0; i < text.count(); ++i)
		if (text.at(i) == nl)
			text[i] = QChar::LineSeparator;
	return text;
}

QSizeF PlaylistDelegate::doTextLayout(int lineWidth, QTextLayout *textLayout) const {
	Q_ASSERT(textLayout);
	QFontMetrics fontMetrics(textLayout->font());
	const int leading = fontMetrics.leading();
	qreal height = 0;
	qreal widthUsed = 0;
	textLayout->beginLayout();
	while (true) {
		QTextLine line = textLayout->createLine();
		if (!line.isValid())
			break;
		line.setLineWidth(lineWidth);
		height += leading;
		line.setPosition(QPointF(0, height));
		height += line.height();
		widthUsed = qMax(widthUsed, line.naturalTextWidth());
	}
	textLayout->endLayout();
	return QSizeF(widthUsed, height);
}

void PlaylistDelegate::drawDisplay(QPainter *p, const QStyleOptionViewItem &option, const QRect &rect, const QString &text) const {
	Q_ASSERT(p);
	if (text.isEmpty())
		return;

	QPalette::ColorGroup cg = option.state & QStyle::State_Enabled ? QPalette::Normal : QPalette::Disabled;
	if (cg == QPalette::Normal && !(option.state & QStyle::State_Active))
		cg = QPalette::Inactive;
	if (option.state & QStyle::State_Selected) {
		p->fillRect(rect, option.palette.brush(cg, QPalette::Highlight));
		p->setPen(option.palette.color(cg, QPalette::HighlightedText));
	} else {
		p->setPen(option.palette.color(cg, QPalette::Text));
	}

	if (option.state & QStyle::State_Editing) {
		p->save();
		p->setPen(option.palette.color(cg, QPalette::Text));
		p->drawRect(rect.adjusted(0, 0, -1, -1));
		p->restore();
	}

	const int textMargin = QApplication::style()->pixelMetric(QStyle::PM_FocusFrameHMargin) + 1;
	const QString myText = text.section('|', 0, -2);
	const QString myTime = text.section('|', -1, -1);
	const int timeWidth = p->fontMetrics().width(myTime);
	const int timeMargin = 5;

	QRect textRect = rect.adjusted(textMargin, 0, -textMargin, 0); // remove width padding
	textRect.setRight(p->viewport().right() - (timeWidth + timeMargin));

	QTextOption textOption;
	textOption.setWrapMode(QTextOption::NoWrap);
	textOption.setTextDirection(option.direction);
	textOption.setAlignment(QStyle::visualAlignment(option.direction, option.displayAlignment));
	QTextLayout textLayout;
	textLayout.setTextOption(textOption);
	textLayout.setFont(option.font);
	textLayout.setText(replaceNewLine(myText));

	QSizeF textLayoutSize = doTextLayout(textRect.width(), &textLayout);
	if (textRect.width() < textLayoutSize.width()
	        || textRect.height() < textLayoutSize.height()) {
		const QString elided = option.fontMetrics.elidedText(myText,
		                       option.textElideMode,
		                       textRect.width());
		textLayout.setText(elided);
		textLayoutSize = doTextLayout(textRect.width(), &textLayout);
	}

	textRect.setTop(textRect.top() + (textRect.height()/2) - (textLayoutSize.toSize().height()/2));
	// Draw main text
	textLayout.draw(p, textRect.topLeft(), QVector<QTextLayout::FormatRange>(), textRect);
	// Draw time text on the right
	p->drawText(QRect(textRect.right()+timeMargin, textRect.y(), timeWidth, textRect.height()), myTime);
}
