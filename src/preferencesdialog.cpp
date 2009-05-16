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

#include "config.h"
#include "iconmanager.h"
#include "mpd.h"
#include "mpdconnection.h"
#include "mpdoutput.h"
#include "mpdsong.h"
#include "notifications.h"
#include "passivepopup.h"
#include "preferencesdialog.h"
#include "serverinfo.h"
#include "servermodel.h"
#include "shortcutmodel.h"
#include "tagguesser.h"
#include <QDir>
#include <QFontDialog>
#include <QHeaderView>
#include <QKeyEvent>
#include <QLocale>

struct PreferencesDialogPrivate {
	PreferencesDialogPrivate() : serverItem(0) {}

	ServerModel *serverModel;
	QItemSelectionModel *serverSel;
	QButtonGroup *positionGroup;

	QTreeWidgetItem *connectionItem, *serverItem, *looknfeelItem;
	QTreeWidgetItem *directoriesItem, *libraryItem, *playlistItem;
	QTreeWidgetItem *iconsItem, *localeItem, *dynamicPlaylistItem;
	QTreeWidgetItem *shortcutsItem, *stylesItem, *notificationsItem;
	QTreeWidgetItem *tagguesserItem, *trayIconItem, *coverArtItem;
};

PreferencesDialog::PreferencesDialog(QWidget *parent) : QDialog(parent), d(new PreferencesDialogPrivate) {
	Q_ASSERT(d);
	setupUi(this);
	setAttribute(Qt::WA_DeleteOnClose, true);

	splitter->setOpaqueResize(Config::instance()->opaqueResize());
	splitter->setStretchFactor(0, 1);
	splitter->setStretchFactor(1, 10);
	categoryList->header()->hide();

	initCategoryList();
	initConnectionPage();
	initServerPage();
	initLookAndFeelPage();
	initIconSetPage();
	initLibraryPage();
	initDirectoriesPage();
	initPlaylistPage();
	initStylePage();
	initCoverArtPage();
	initDynamicPlaylistPage();
	initLanguagePage();
	initNotificationsPage();
	initShortcutPage();
	initTagGuesserPage();
	initTrayIconPage();

	updateTranslation();
	show();
	categoryList->setCurrentItem(d->connectionItem);

	for (int i = 0; i < d->serverModel->columnCount(); i++)
		serverList->resizeColumnToContents(i);

	// set alternating
	QList<QAbstractItemView*> children = findChildren<QAbstractItemView*>(QString());
	foreach(QObject *child, children) {
		if (!child->setProperty("alternatingRowColors", Config::instance()->alternatingRowColors()))
			qWarning("Couldn't set alternatingRowColors for object: %s", qPrintable(child->objectName()));
	}
}

void PreferencesDialog::initCategoryList() {
	d->connectionItem = new QTreeWidgetItem(categoryList);
	if (MPDConnection::instance()->isConnected())
		d->serverItem = new QTreeWidgetItem(d->connectionItem);
	d->looknfeelItem = new QTreeWidgetItem(categoryList);
	d->looknfeelItem->setExpanded(true);
	d->libraryItem = new QTreeWidgetItem(d->looknfeelItem);
	d->directoriesItem = new QTreeWidgetItem(d->looknfeelItem);
	d->playlistItem = new QTreeWidgetItem(d->looknfeelItem);
	d->iconsItem = new QTreeWidgetItem(d->looknfeelItem);
	d->stylesItem = new QTreeWidgetItem(d->looknfeelItem);
	d->coverArtItem = new QTreeWidgetItem(categoryList);
	d->dynamicPlaylistItem = new QTreeWidgetItem(categoryList);
	d->localeItem = new QTreeWidgetItem(categoryList);
	d->notificationsItem = new QTreeWidgetItem(categoryList);
	d->shortcutsItem = new QTreeWidgetItem(categoryList);
	d->tagguesserItem = new QTreeWidgetItem(categoryList);
	d->trayIconItem = new QTreeWidgetItem(categoryList);
	d->trayIconItem->setIcon(0, QIcon(":/icons/qmpdclient16.png"));

	// Make item-index relations
	for (int i = 0, index = 0; i < categoryList->topLevelItemCount(); i++, index++) {
		QTreeWidgetItem *item = categoryList->topLevelItem(i);
		item->setExpanded(true);
		item->setData(0, Qt::UserRole, index);
		for (int j = 0; j < item->childCount(); j++)
			item->child(j)->setData(0, Qt::UserRole, ++index);
	}
}

void PreferencesDialog::initConnectionPage() {
	serverList->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	serverList->verticalHeader()->setDefaultSectionSize(fontMetrics().height());
	serverList->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	serverList->verticalHeader()->hide();

	serverList->setModel(d->serverModel = new ServerModel(this));
	d->serverSel = serverList->selectionModel();
	connect(d->serverSel, SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)), this, SLOT(serverSelectionChanged()));

	deleteButton->setEnabled(false);
	upButton->setEnabled(false);
	downButton->setEnabled(false);
	autoConnectCheck->setChecked(Config::instance()->autoconnect());
	timeoutSpin->setValue(Config::instance()->timeoutTime());
	reconnectCheck->setChecked(Config::instance()->reconnect());
	reconnectSpin->setValue(Config::instance()->reconnectTime());

	connect(autoConnectCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setAutoconnect(bool)));
	connect(timeoutSpin, SIGNAL(valueChanged(int)), Config::instance(), SLOT(setTimeoutTime(int)));
	connect(reconnectCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setReconnect(bool)));
	connect(reconnectSpin, SIGNAL(valueChanged(int)), Config::instance(), SLOT(setReconnectTime(int)));
}

void PreferencesDialog::initServerPage() {
	if (!MPDConnection::instance()->isConnected()) {
		widgetStack->removeWidget(serverPage);
		return;
	}
	Q_ASSERT(d->serverItem);
	d->serverItem->setText(0, MPDConnection::instance()->server().name());
	crossfadeCheck->setChecked(MPD::instance()->crossfade() > 0);
	crossfadeSpin->setValue(MPD::instance()->crossfade());

	foreach(MPDOutput o, MPDConnection::instance()->outputs()) {
		QTreeWidgetItem *i = new QTreeWidgetItem(outputList, o.id());
		i->setText(1, o.name());
		i->setCheckState(0, o.enabled() ? Qt::Checked : Qt::Unchecked);
	}

	connect(crossfadeCheck, SIGNAL(toggled(bool)), this, SLOT(crossfadeChanged()));
	connect(crossfadeSpin, SIGNAL(valueChanged(int)), this, SLOT(crossfadeChanged()));
	connect(outputList, SIGNAL(itemChanged(QTreeWidgetItem *, int)), this, SLOT(outputChanged(QTreeWidgetItem *, int)));
}

void PreferencesDialog::initLookAndFeelPage() {
	setFontString(font());
	if (Config::instance()->enqueue())
		enqueueItemRadio->setChecked(true);
	else
		playItemRadio->setChecked(true);
	autoResizeCheck->setChecked(Config::instance()->autoResizeColumns());
	opaqueCheck->setChecked(Config::instance()->opaqueResize());
	alternatingCheck->setChecked(Config::instance()->alternatingRowColors());
	disregardTheCheck->setChecked(Config::instance()->disregardLeadingThe());

	connect(enqueueItemRadio, SIGNAL(toggled(bool)), Config::instance(), SLOT(setEnqueue(bool)));
	connect(alternatingCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setAlternatingRowColors(bool)));
	connect(autoResizeCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setAutoResizeColumns(bool)));
	connect(opaqueCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setOpaqueResize(bool)));
	connect(disregardTheCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setDisregardLeadingThe(bool)));
}

void PreferencesDialog::initIconSetPage() {
	updateIconSet();

	QDir resourceDir(":/icons");
	QDir systemDir(Config::instance()->systemPath() + "iconsets");
	QDir localDir(Config::instance()->userPath() + "iconsets");
	QFileInfoList icons;
	if (resourceDir.exists())
		icons << resourceDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
	if (systemDir.exists())
		icons << systemDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);
	if (localDir.exists())
		icons << localDir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);

	QString iconSetPath = Config::instance()->iconSetPath();
	QListWidgetItem *selected = 0;

	foreach(QFileInfo fi, icons) {
		QString confFileName = fi.absoluteFilePath() + "/iconset.conf";
		if (!QFile::exists(confFileName))
			continue;

		QSettings conf(confFileName, QSettings::IniFormat);
		QString title = conf.value("/Iconset/Name").toString();
		if (title.isEmpty())
			title = fi.baseName();

		QListWidgetItem *item = new QListWidgetItem(title, iconList);
		item->setData(Qt::UserRole, fi.absoluteFilePath());
		if (fi.absoluteFilePath() == iconSetPath)
			selected = item;
	}
	if (selected) {
		iconList->setCurrentItem(selected);
		iconLabel->setText(IconManager::description());
	}

	connect(iconList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(iconsetChanged(QListWidgetItem *)));
}

void PreferencesDialog::initLibraryPage() {
	if (Config::instance()->filterByAlbumOnly())
		filterByAlbumRadio->setChecked(true);
	else
		filterByBothRadio->setChecked(true);

	showAllCheck->setChecked(Config::instance()->showAll());

	connect(filterByAlbumRadio, SIGNAL(toggled(bool)), Config::instance(), SLOT(setFilterByAlbumOnly(bool)));
	connect(showAllCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setShowAll(bool)));
}

void PreferencesDialog::initDirectoriesPage() {
	recursiveViewCheck->setChecked(Config::instance()->recurse());

	connect(recursiveViewCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setRecurse(bool)));
}

void PreferencesDialog::initPlaylistPage() {
	titleFormatLine->setText(Config::instance()->playlistPattern());
	centerPlayingCheck->setChecked(Config::instance()->scrollToPlaying());

	connect(centerPlayingCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setScrollToPlaying(bool)));
	connect(titleFormatLine, SIGNAL(textChanged(const QString &)), Config::instance(), SLOT(setPlaylistPattern(const QString &)));
}

void PreferencesDialog::initStylePage() {
	QDir systemDir(Config::instance()->systemPath() + "styles", "*.css");
	QDir localDir(Config::instance()->userPath() + "styles", "*.css");
	QFileInfoList styles;
	if (systemDir.exists())
		styles << systemDir.entryInfoList(QDir::Files | QDir::Readable);
	if (localDir.exists())
		styles << localDir.entryInfoList(QDir::Files | QDir::Readable);

	QString styleFile = Config::instance()->styleFile();
	QListWidgetItem *selected = 0;

	QListWidgetItem *defaultStyle = new QListWidgetItem(tr("Default style"), styleList);
	if (styleFile.isEmpty())
		selected = defaultStyle;
	foreach(QFileInfo fi, styles) {
		QListWidgetItem *item = new QListWidgetItem(fi.baseName(), styleList);
		item->setData(Qt::UserRole, fi.absoluteFilePath());
		if (fi.absoluteFilePath() == styleFile)
			selected = item;
	}
	if (selected)
		styleList->setCurrentItem(selected);

	connect(styleList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(styleChanged(QListWidgetItem *)));
}

void PreferencesDialog::initCoverArtPage() {
	showCoverCheck->setChecked(Config::instance()->showCoverArt());
	coverDirEdit->setText(Config::instance()->coverArtDir());
	coverMaxHeight->setText(Config::instance()->coverArtMaxHeight());
	coverMaxWidth->setText(Config::instance()->coverArtMaxWidth());

	connect(showCoverCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setShowCoverArt(bool)));
	connect(coverDirEdit, SIGNAL(textChanged(const QString &)), Config::instance(), SLOT(setCoverArtDir(const QString &)));
	connect(coverMaxHeight, SIGNAL(textChanged(const QString &)), Config::instance(), SLOT(setCoverMaxHeight(const QString &)));
	connect(coverMaxWidth, SIGNAL(textChanged(const QString &)), Config::instance(), SLOT(setCoverMaxWidth(const QString &)));
}

void PreferencesDialog::initLanguagePage() {
	translationCheck->setChecked(Config::instance()->translate());

	QString localeFile = Config::instance()->locale();
	QListWidgetItem *selected = 0;

	QListWidgetItem *systemLocale = new QListWidgetItem(tr("Use system locale"), localeList);
	if (localeFile.isEmpty())
		selected = systemLocale;

	// Find all translations
	QFileInfoList translations;
	QDir localDir(Config::instance()->userPath() + "translations", "??_??.qm");
	if (localDir.exists())
		translations << localDir.entryInfoList(QDir::Files | QDir::Readable);
	QDir systemDir(Config::instance()->systemPath() + "translations", "??_??.qm");
	if (systemDir.exists())
		translations << systemDir.entryInfoList(QDir::Files | QDir::Readable);

	foreach(QFileInfo fi, translations) {
		QListWidgetItem *item = new QListWidgetItem(QLocale::languageToString(QLocale(fi.baseName()).language()), localeList);
		item->setData(Qt::UserRole, fi.absoluteFilePath());
		if (fi.absoluteFilePath() == localeFile)
			selected = item;
	}

	if (selected) {
		localeList->setCurrentItem(selected);
		iconLabel->setText(IconManager::description());
	}

	connect(translationCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setTranslate(bool)));
	connect(localeList, SIGNAL(currentItemChanged(QListWidgetItem *, QListWidgetItem *)), this, SLOT(localeChanged(QListWidgetItem *)));
}

void PreferencesDialog::initDynamicPlaylistPage() {
	autoAddCheck->setChecked(Config::instance()->autoAddSongs());
	autoAddPosSpin->setValue(Config::instance()->autoAddPos());
	autoRemoveCheck->setChecked(Config::instance()->autoRemoveSongs());

	connect(autoAddCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setAutoAddSongs(bool)));
	connect(autoAddPosSpin, SIGNAL(valueChanged(int)), Config::instance(), SLOT(setAutoAddPos(int)));
	connect(autoRemoveCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setAutoRemoveSongs(bool)));
}

void PreferencesDialog::initNotificationsPage() {
	PassivePopup::Position pos = static_cast<PassivePopup::Position>(Config::instance()->notificationsPosition());
	d->positionGroup = new QButtonGroup(this);
	d->positionGroup->addButton(topLeft, PassivePopup::TopLeft);
	d->positionGroup->addButton(top, PassivePopup::Top);
	d->positionGroup->addButton(topRight, PassivePopup::TopRight);
	d->positionGroup->addButton(right, PassivePopup::Right);
	d->positionGroup->addButton(bottomRight, PassivePopup::BottomRight);
	d->positionGroup->addButton(bottom, PassivePopup::Bottom);
	d->positionGroup->addButton(bottomLeft, PassivePopup::BottomLeft);
	d->positionGroup->addButton(left, PassivePopup::Left);

	topLeft->setChecked(pos == PassivePopup::TopLeft);
	top->setChecked(pos == PassivePopup::Top);
	topRight->setChecked(pos == PassivePopup::TopRight);
	right->setChecked(pos == PassivePopup::Right);
	bottom->setChecked(pos == PassivePopup::Bottom);
	bottomLeft->setChecked(pos == PassivePopup::BottomLeft);
	left->setChecked(pos == PassivePopup::Left);
	bottomRight->setChecked(pos == PassivePopup::BottomRight);

	notificationsTimeoutSpinner->setValue(Config::instance()->notificationsTimeout());
	notificationsCheck->setChecked(Config::instance()->notificationsEnabled());

	// Needs to be done here, when buttonGroup  is ready
	int i = 0, idx = 0;
	foreach(Notifications::Type t, Notifications::notifiers()) {
		notificationCombo->addItem(Notifications::name(t), t);
		if (Config::instance()->notifier() == t)
			idx = i;
		i++;
	}
	connect(notificationCombo, SIGNAL(currentIndexChanged(int)), this, SLOT(notifierChanged(int)));
	notificationCombo->setCurrentIndex(idx);

	connect(d->positionGroup, SIGNAL(buttonClicked(int)), Config::instance(), SLOT(setNotificationsPosition(int)));
	connect(notificationsCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setNotificationsEnabled(bool)));
	connect(notificationsTimeoutSpinner, SIGNAL(valueChanged(int)), Config::instance(), SLOT(setNotificationsTimeout(int)));
}

void PreferencesDialog::initShortcutPage() {
	shortcutList->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
	shortcutList->verticalHeader()->setDefaultSectionSize(fontMetrics().height());
	shortcutList->verticalHeader()->setResizeMode(QHeaderView::Fixed);
	shortcutList->verticalHeader()->hide();

	ShortcutModel *model = new ShortcutModel(this);
	shortcutList->setModel(model);
}

void PreferencesDialog::initTagGuesserPage() {
	tagGuesserCheck->setChecked(Config::instance()->tagGuesserEnabled());
	testLine->setText(Config::instance()->testFilename());
	patternLine->setText(Config::instance()->guessPattern());

	connect(tagGuesserCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setTagGuesserEnabled(bool)));
}

void PreferencesDialog::initTrayIconPage() {
	trayIconCheck->setChecked(Config::instance()->trayIconEnabled());
	startHiddenCheck->setChecked(Config::instance()->startHidden());
	minToTrayCheck->setChecked(Config::instance()->minimizeToTray());
	songInfoCheck->setChecked(Config::instance()->extendedSongInfoEnabled());

	connect(trayIconCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setTrayIconEnabled(bool)));
	connect(minToTrayCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setMinimizeToTray(bool)));
	connect(startHiddenCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setStartHidden(bool)));
	connect(songInfoCheck, SIGNAL(toggled(bool)), Config::instance(), SLOT(setExtendedSongInfoEnabled(bool)));
}

PreferencesDialog::~PreferencesDialog() {
	delete d;
}

void PreferencesDialog::crossfadeChanged() {
	Q_ASSERT(widgetStack->indexOf(serverPage) > -1);
	if (crossfadeSpin->value() > 0 && crossfadeCheck->isChecked())
		MPD::instance()->setCrossfade(crossfadeSpin->value());
	else
		MPD::instance()->setCrossfade(0);
}

void PreferencesDialog::updateTranslation() {
	// Save previously selected
	QTreeWidgetItem *selected = categoryList->currentItem();

	retranslateUi(this);
	Q_ASSERT(d->connectionItem);
	Q_ASSERT(d->coverArtItem);
	Q_ASSERT(d->looknfeelItem);
	Q_ASSERT(d->libraryItem);
	Q_ASSERT(d->directoriesItem);
	Q_ASSERT(d->playlistItem);
	Q_ASSERT(d->iconsItem);
	Q_ASSERT(d->localeItem);
	Q_ASSERT(d->dynamicPlaylistItem);
	Q_ASSERT(d->notificationsItem);
	Q_ASSERT(d->shortcutsItem);
	Q_ASSERT(d->tagguesserItem);
	Q_ASSERT(d->trayIconItem);
	d->connectionItem->setText(0, tr("Connection"));
	d->looknfeelItem->setText(0, tr("Look and feel"));
	d->libraryItem->setText(0, tr("Library"));
	d->directoriesItem->setText(0, tr("Directories"));
	d->playlistItem->setText(0, tr("Playlist"));
	d->iconsItem->setText(0, tr("Icons"));
	d->coverArtItem->setText(0, tr("Cover art"));
	d->localeItem->setText(0, tr("Language"));
	d->dynamicPlaylistItem->setText(0, tr("Dynamic playlist"));
	d->notificationsItem->setText(0, tr("Notifications"));
	d->shortcutsItem->setText(0, tr("Shortcuts"));
	d->tagguesserItem->setText(0, tr("Tag guesser"));
	d->trayIconItem->setText(0, tr("Tray icon"));

	categoryList->setCurrentItem(selected);

	QString help = "<table width='100%'>";
	help += QString("<tr><td>%t: %1</td><td>%d: %2</td></tr>").arg(tr("Title")).arg(tr("Date"));
	help += QString("<tr><td>%b: %1</td><td>%c: %2</td></tr>").arg(tr("Artist")).arg(tr("Composer"));
	help += QString("<tr><td>%a: %1</td><td>%f: %2</td></tr>").arg(tr("Album")).arg(tr("Filename"));
	help += QString("<tr><td>%n: %1</td><td>%u: %2</td></tr>").arg(tr("Track")).arg(tr("URL"));
	help += QString("<tr><td>%g: %1</td><td><br></td></tr>").arg(tr("Genre"));
	help += "</table>";
	titleFormatLabel->setText(help);
	on_testLine_textChanged(testLine->text());

	Q_ASSERT(d->stylesItem);
	d->stylesItem->setText(0, tr("Styles"));
	Q_ASSERT(styleList->count() > 0);
	styleList->item(0)->setText(tr("Default style"));
	Q_ASSERT(localeList->count() > 0);
	localeList->item(0)->setText(tr("Use system locale"));
}

void PreferencesDialog::on_closeButton_clicked() {
	accept();
	close();
}

void PreferencesDialog::on_fontButton_clicked() {
	bool ok;
	QFont newfont = QFontDialog::getFont(&ok, fontButton->font(), this);
	if (ok) {
		Config::instance()->setFont(newfont);
		setFontString(newfont);
	}
}

void PreferencesDialog::setFontString(const QFont &newfont) {
	QString font = newfont.family();
	if (newfont.bold())
		font += QString(", %1").arg(tr("bold"));
	if (newfont.italic())
		font += QString(", %1").arg(tr("italic"));
	font += QString(", %1").arg(newfont.pointSize());
	fontLine->setText(font);
	fontLine->setFont(newfont);
}

void PreferencesDialog::on_testLine_textChanged(const QString &url) {
	Config::instance()->setTestFilename(url);
	if (url.isEmpty())
		return;
	// Create song to guess on.
	MPDSong song = MPDSong::createTest(url);
	TagGuesser::guessTags(song);
	bandLabel->setText(QString("%1: %2").arg(tr("Artist")).arg(song.artist()));
	albumLabel->setText(QString("%1: %2").arg(tr("Album")).arg(song.album()));
	trackLabel->setText(QString("%1: %2").arg(tr("Track")).arg(song.track()));
	titleLabel->setText(QString("%1: %2").arg(tr("Title")).arg(song.title()));
}

void PreferencesDialog::on_patternLine_textChanged(const QString &pattern) {
	Config::instance()->setGuessPattern(pattern);
	if (pattern.isEmpty())
		return;
	on_testLine_textChanged(testLine->text());
}

void PreferencesDialog::on_categoryList_currentItemChanged(QTreeWidgetItem *c, QTreeWidgetItem *) {
	if (!c)
		return;
	widgetStack->setCurrentIndex(c->data(0, Qt::UserRole).toInt());
	currentLabel->setText("<h3>" + c->text(0) + "</h3>");
}

void PreferencesDialog::on_addButton_clicked() {
	Q_ASSERT(d->serverModel);
	d->serverModel->addServer();
}

void PreferencesDialog::on_deleteButton_clicked() {
	Q_ASSERT(d->serverModel);
	Q_ASSERT(d->serverSel);
	foreach(QModelIndex sel, d->serverSel->selectedIndexes()) {
		d->serverModel->deleteServer(sel);
		break;
	}
	deleteButton->setEnabled(d->serverModel->size() > 1 && !d->serverSel->selectedIndexes().isEmpty());
}

void PreferencesDialog::serverSelectionChanged() {
	Q_ASSERT(d->serverModel);
	Q_ASSERT(d->serverSel);
	deleteButton->setEnabled(d->serverModel->size() > 1 && !d->serverSel->selectedIndexes().isEmpty());
	foreach(QModelIndex sel, d->serverSel->selectedIndexes()) {
		upButton->setEnabled(sel.row() > 0);
		downButton->setEnabled(sel.row() < d->serverModel->size() - 1);
		return;
	}
	upButton->setEnabled(false);
	downButton->setEnabled(false);
}

void PreferencesDialog::on_downButton_clicked() {
	Q_ASSERT(d->serverModel);
	Q_ASSERT(d->serverSel);
	foreach(QModelIndex sel, d->serverSel->selectedIndexes()) {
		if (d->serverModel->moveDown(sel)) {
			d->serverSel->setCurrentIndex(d->serverModel->index(sel.row() + 1, 0),
			                              QItemSelectionModel::Clear);
			d->serverSel->setCurrentIndex(d->serverModel->index(sel.row() + 1, 0),
			                              QItemSelectionModel::Select | QItemSelectionModel::Rows);
		}
		return;
	}
}

void PreferencesDialog::on_upButton_clicked() {
	Q_ASSERT(d->serverModel);
	Q_ASSERT(d->serverSel);
	foreach(QModelIndex sel, d->serverSel->selectedIndexes()) {
		if (d->serverModel->moveUp(sel)) {
			d->serverSel->setCurrentIndex(d->serverModel->index(sel.row() - 1, 0),
			                              QItemSelectionModel::Clear);
			d->serverSel->setCurrentIndex(d->serverModel->index(sel.row() - 1, 0),
			                              QItemSelectionModel::Select | QItemSelectionModel::Rows);
		}
		return;
	}
}

void PreferencesDialog::updateIconSet() {
	d->connectionItem->setIcon(0, IconManager::icon("connect"));
	if (d->serverItem)
		d->serverItem->setIcon(0, IconManager::icon("server"));
	d->looknfeelItem->setIcon(0, IconManager::icon("lookandfeel"));
	d->libraryItem->setIcon(0, IconManager::icon("library"));
	d->directoriesItem->setIcon(0, IconManager::icon("directories"));
	d->playlistItem->setIcon(0, IconManager::icon("playlist"));
	d->coverArtItem->setIcon(0, IconManager::icon("coverart"));
	d->iconsItem->setIcon(0, IconManager::icon("icons"));
	d->stylesItem->setIcon(0, IconManager::icon("styles"));
	d->localeItem->setIcon(0, IconManager::icon("language"));
	d->dynamicPlaylistItem->setIcon(0, IconManager::icon("dynamicplaylist"));
	d->notificationsItem->setIcon(0, IconManager::icon("notifications"));
	d->shortcutsItem->setIcon(0, IconManager::icon("shortcuts"));
	d->tagguesserItem->setIcon(0, IconManager::icon("tagguesser"));
}

void PreferencesDialog::iconsetChanged(QListWidgetItem *i) {
	if (!i)
		return;
	Config::instance()->setIconSet(i->data(Qt::UserRole).toString());
	updateIconSet();
	iconLabel->setText(IconManager::description());
}

void PreferencesDialog::localeChanged(QListWidgetItem *i) {
	if (i)
		Config::instance()->setLocale(i->data(Qt::UserRole).toString());
}

void PreferencesDialog::notifierChanged(int index) {
	int type = notificationCombo->itemData(index).toInt();
	Config::instance()->setNotifier(type);
	const bool enable = type == Notifications::CUSTOM;
	desktopLabel->setEnabled(enable);
	posLabel->setEnabled(enable);
	foreach(QAbstractButton *b, d->positionGroup->buttons()) {
		b->setEnabled(enable);
	}
}

void PreferencesDialog::outputChanged(QTreeWidgetItem *i, int col) {
	if (i && col == 0)
		MPD::instance()->toggleOutputDevice(i->type(), i->checkState(0) == Qt::Checked);
}

void PreferencesDialog::styleChanged(QListWidgetItem *i) {
	if (i)
		Config::instance()->setStyleFile(i->data(Qt::UserRole).toString());
}
