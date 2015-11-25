# installation prefix on *nix/osx
PREFIX = /usr/local

# Most people need not muck about below here
# !contains(QT_MAJOR_VERSION, 4):error(QMPDClient requires Qt 4)
CONFIG += qt5 debug

# addition ldflags for release build
QMAKE_LFLAGS_RELEASE += -O2 -g0 -s

# CONFIG -= debug # Needed to avoid console on win32
TEMPLATE = app
RESOURCES = qmpdclient.qrc
VERSION = 1.3
DEFINES += NAMEVER='"\\"QMPDClient \
    $$VERSION\\""'
DEFINES += VERSION='"\\"$$VERSION\\""'
INCLUDEPATH += src
QT += network xml xmlpatterns widgets x11extras

FORMS += \
    ui/addradiodialog.ui \
    ui/controlpanel.ui \
    ui/coverartdialog.ui \
    ui/directorypanel.ui \
    ui/librarypanel.ui \
    ui/mainwindow.ui \
    ui/metainfodialog.ui \
    ui/playlistpanel.ui \
    ui/playlistspanel.ui \
    ui/preferencesdialog.ui \
    ui/radiopanel.ui \
    ui/shoutcastpanel.ui \
    ui/lyricsdialog.ui \
    ui/aboutdialog.ui

HEADERS += src/aafilter.h \
    src/aboutdialog.h \
    src/abstractmodel.h \
    src/abstractview.h \
    src/abstractview_defn.h \
    src/abstractview_impl.h \
    src/albumview.h \
    src/artistview.h \
    src/clickablelabel.h \
    src/config.h \
    src/controlpanel.h \
    src/coverartdialog.h \
    src/lyricsdialog.h \
    src/debug.h \
    src/directorymodel.h \
    src/directorypanel.h \
    src/directoryview.h \
    src/dynamicplaylist.h \
    src/fileview.h \
    src/headerview.h \
    src/iconmanager.h \
    src/idealbar.h \
    src/idealsplitter.h \
    src/libmpdclient.h \
    src/librarypanel.h \
    src/lineedit.h \
    src/macroexpander.h \
    src/mainwindow.h \
    src/metainfodialog.h \
    src/mpd.h \
    src/mpd_p.h \
    src/mpdcache.h \
    src/mpdcache_p.h \
    src/mpdconnection.h \
    src/mpddirectory.h \
    src/mpdentities.h \
    src/mpdoutput.h \
    src/mpdsong.h \
    src/mpdsonglist.h \
    src/mpdsongmodel.h \
    src/mpdsongview.h \
    src/mpdstats.h \
    src/mpdstatus.h \
    src/notifications.h \
    src/passivepopup.h \
    src/pausabletimer.h \
    src/playlistitemdelegate.h \
    src/playlistmodel.h \
    src/playlistspanel.h \
    src/playlistsview.h \
    src/plsfile.h \
    src/preferencesdialog.h \
    src/qmpdclient.h \
    src/playlistpanel.h \
    src/playlistview.h \
    src/plconview.h \
    src/radiopanel.h \
    src/radioview.h \
    src/reconnect.h \
    src/richtext.h \
    src/serverinfo.h \
    src/servermodel.h \
    src/shortcutmodel.h \
    src/shortcuts.h \
    src/shoutcastpanel.h \
    src/shoutcastview.h \
    src/shoutcastmodel.h \
    src/shoutcastfetcher.h \
    src/shoutcaststation.h \
    src/songview.h \
    src/stringlistmodel.h \
    src/stringlistview.h \
    src/tagmodel.h \
    src/tagguesser.h \
    src/timelabel.h \
    src/timeslider.h \
    src/trayicon.h \
	src/traysonginfo.h \
    src/verticalbutton.h \
    src/lastfmsubmitter.h

SOURCES += src/aafilter.cpp \
    src/aboutdialog.cpp \
    src/abstractmodel.cpp \
    src/abstractview.cpp \
    src/albumview.cpp \
    src/artistview.cpp \
    src/clickablelabel.cpp \
    src/config.cpp \
    src/controlpanel.cpp \
    src/coverartdialog.cpp \
    src/lyricsdialog.cpp \
    src/directorymodel.cpp \
    src/directorypanel.cpp \
    src/directoryview.cpp \
    src/dynamicplaylist.cpp \
    src/fileview.cpp \
    src/headerview.cpp \
    src/iconmanager.cpp \
    src/idealbar.cpp \
    src/idealsplitter.cpp \
    src/libmpdclient.c \
    src/librarypanel.cpp \
    src/lineedit.cpp \
    src/mainwindow.cpp \
    src/metainfodialog.cpp \
    src/mpd.cpp \
    src/mpdcache.cpp \
    src/mpdconnection.cpp \
    src/mpddirectory.cpp \
    src/mpdentities.cpp \
    src/mpdoutput.cpp \
    src/mpdsong.cpp \
    src/mpdsonglist.cpp \
    src/mpdsongmodel.cpp \
    src/mpdsongview.cpp \
    src/mpdstats.cpp \
    src/mpdstatus.cpp \
    src/notifications.cpp \
    src/passivepopup.cpp \
    src/pausabletimer.cpp \
    src/playlistitemdelegate.cpp \
    src/playlistmodel.cpp \
    src/playlistpanel.cpp \
    src/playlistview.cpp \
    src/playlistspanel.cpp \
    src/playlistsview.cpp \
    src/plconview.cpp \
    src/plsfile.cpp \
    src/preferencesdialog.cpp \
    src/qmpdclient.cpp \
    src/radiopanel.cpp \
    src/radioview.cpp \
    src/reconnect.cpp \
    src/serverinfo.cpp \
    src/servermodel.cpp \
    src/shortcutmodel.cpp \
    src/shortcuts.cpp \
    src/shoutcastmodel.cpp \
    src/shoutcastpanel.cpp \
    src/shoutcastview.cpp \
    src/shoutcastfetcher.cpp \
    src/shoutcaststation.cpp \
    src/songview.cpp \
    src/stringlistmodel.cpp \
    src/stringlistview.cpp \
    src/tagguesser.cpp \
    src/tagmodel.cpp \
    src/timelabel.cpp \
    src/timeslider.cpp \
    src/trayicon.cpp \
	src/traysonginfo.cpp \
    src/verticalbutton.cpp \
    src/lastfmsubmitter.cpp

# translations
LANG_PATH = $$PWD/lang
TRANSLATIONS = $$LANG_PATH/ru_RU.ts $$LANG_PATH/de_DE.ts  $$LANG_PATH/it_IT.ts  $$LANG_PATH/nn_NO.ts $$LANG_PATH/pt_BR.ts  $$LANG_PATH/sv_SE.ts  $$LANG_PATH/uk_UA.ts  $$LANG_PATH/zh_TW.ts $$LANG_PATH/fr_FR.ts $$LANG_PATH/nl_NL.ts $$LANG_PATH/no_NO.ts   $$LANG_PATH/tr_TR.ts  $$LANG_PATH/zh_CN.ts $$LANG_PATH/cs_CZ.ts $$LANG_PATH/es_ES.ts

MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .res
UI_DIR = .ui

# Platform specific
win32 {
#   debug:CONFIG += console
    LIBS += -lws2_32
    RC_FILE = icons/resource.rc
    SOURCES += src/qmpdclient_win.cpp \
        src/notifications_nodbus.cpp
}

# Installation in done through own installer on win32
unix {
    !mac {
        SOURCES += src/qmpdclient_x11.cpp
        LIBS += -lX11
        # Check for dbus support
        contains(QT_CONFIG, dbus) {
            message(DBus: enabled)
            CONFIG += qdbus
            SOURCES += src/notifications_dbus.cpp \
            	src/qdbus_adaptor.cpp
            HEADERS += src/qdbus_adaptor.h
            DEFINES += WITH_DBUS
        }
        else {
            message(DBus: disabled (Qt is not compiled with dbus support))
            SOURCES += src/notifications_nodbus.cpp
        }
    }
    mac {
        RC_FILE = icons/qmpdclient.icns
        SOURCES += src/qmpdclient_mac.cpp \
            src/notifications_nodbus.cpp
    }
    DEFINES += PREFIX='"\\"$$PREFIX\\""'
    TARGET = qmpdclient
    INSTALLS += target
    target.path = $$PREFIX/bin
}
unix {
	desktop_file.files = qmpdclient.desktop
	desktop_file.path = $$PREFIX/share/applications
	icon64.files = icons/64x64/qmpdclient.png
	icon64.path = $$PREFIX/share/icons/hicolor/64x64/apps/
	icon48.files = icons/48x48/qmpdclient.png
	icon48.path = $$PREFIX/share/icons/hicolor/48x48/apps/
	icon22.files = icons/22x22/qmpdclient.png
	icon22.path = $$PREFIX/share/icons/hicolor/22x22/apps/
	icon16.files = icons/16x16/qmpdclient.png
	icon16.path = $$PREFIX/share/icons/hicolor/16x16/apps/
	iconsvg.files = icons/svg/qmpdclient.svg
	iconsvg.path = $$PREFIX/share/icons/hicolor/scalable/apps/
	INSTALLS += desktop_file icon64 icon48 icon22 icon16 iconsvg
}
translations.commands = lrelease $$TRANSLATIONS
translations.files = lang/cs_CZ.qm lang/de_DE.qm lang/es_ES.qm lang/fr_FR.qm lang/it_IT.qm lang/nl_NL.qm lang/nn_NO.qm lang/no_NO.qm lang/pt_BR.qm lang/ru_RU.qm lang/sv_SE.qm lang/tr_TR.qm lang/uk_UA.qm lang/zh_CN.qm lang/zh_TW.qm
translations.path = $$PREFIX/share/QMPDClient/translations

INSTALLS += translations

# update translations (make translate)
QMAKE_EXTRA_TARGETS += translate
translate.commands = lupdate $$PWD/qmpdclient.pro -ts $$TRANSLATIONS;
