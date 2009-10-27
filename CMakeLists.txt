cmake_minimum_required(VERSION 2.6)

find_package(Qt4 4.4.0 COMPONENTS QtCore QtGui QtNetwork REQUIRED QtDBus)
include(${QT_USE_FILE})

if(NOT DEFINED VERSION)
	find_program (GIT_CMD git)
	execute_process (COMMAND "${GIT_CMD}" describe
		OUTPUT_VARIABLE VERSION
		OUTPUT_STRIP_TRAILING_WHITESPACE
		)
	if(NOT VERSION)
		set(VERSION 1.1.2)
	endif()
	message (STATUS "Current version: ${VERSION}")
endif()

set(NAMEVER "QMPDClient ${VERSION}")

set(QMPDClient_srcs
	src/aafilter.cpp
	src/aboutdialog.cpp
	src/abstractmodel.cpp
	src/abstractview.cpp
	src/albumview.cpp
	src/artistview.cpp
	src/clickablelabel.cpp
	src/config.cpp
	src/controlpanel.cpp
	src/coverartdialog.cpp
	src/directorymodel.cpp
	src/directorypanel.cpp
	src/directoryview.cpp
	src/dynamicplaylist.cpp
	src/fileview.cpp
	src/headerview.cpp
	src/iconmanager.cpp
	src/idealbar.cpp
	src/idealsplitter.cpp
	src/jumptosongdialog.cpp
	src/lastfmsubmitter.cpp
	src/libmpdclient.c
	src/librarypanel.cpp
	src/lineedit.cpp
	src/lyricsdialog.cpp
	src/mainwindow.cpp
	src/metainfodialog.cpp
	src/mpdcache.cpp
	src/mpdconnection.cpp
	src/mpd.cpp
	src/mpddirectory.cpp
	src/mpdentities.cpp
	src/mpdoutput.cpp
	src/mpdsong.cpp
	src/mpdsonglist.cpp
	src/mpdsongmodel.cpp
	src/mpdsongview.cpp
	src/mpdstats.cpp
	src/mpdstatus.cpp
	src/notifications.cpp
	src/passivepopup.cpp
	src/pausabletimer.cpp
	src/playlistitemdelegate.cpp
	src/playlistmodel.cpp
	src/playlistpanel.cpp
	src/playlistspanel.cpp
	src/playlistsview.cpp
	src/playlistview.cpp
	src/plconview.cpp
	src/preferencesdialog.cpp
	src/qmpdclient.cpp
	src/radiopanel.cpp
	src/radioview.cpp
	src/reconnect.cpp
	src/serverinfo.cpp
	src/servermodel.cpp
	src/shortcutmodel.cpp
	src/shortcuts.cpp
	src/songview.cpp
	src/stringlistmodel.cpp
	src/stringlistview.cpp
	src/tagguesser.cpp
	src/tagmodel.cpp
	src/timelabel.cpp
	src/timeslider.cpp
	src/trayicon.cpp
	src/traysonginfo.cpp
	src/verticalbutton.cpp)

# 	src/qmpdclient_mac.cpp
# 	src/qmpdclient_win.cpp
# 	src/qmpdclient_x11.cpp
# 	src/notifications_dbus.cpp
# 	src/notifications_nodbus.cpp

set(QMPDClient_hdrs
	src/aafilter.h
	src/aboutdialog.h
	src/abstractmodel.h
	src/abstractview_defn.h
	src/abstractview.h
	src/abstractview_impl.h
	src/albumview.h
	src/artistview.h
	src/clickablelabel.h
	src/config.h
	src/controlpanel.h
	src/coverartdialog.h
	src/debug.h
	src/directorymodel.h
	src/directorypanel.h
	src/directoryview.h
	src/dynamicplaylist.h
	src/fileview.h
	src/headerview.h
	src/iconmanager.h
	src/idealbar.h
	src/idealsplitter.h
	src/jumptosongdialog.h
	src/lastfmsubmitter.h
	src/libmpdclient.h
	src/librarypanel.h
	src/lineedit.h
	src/lyricsdialog.h
	src/macroexpander.h
	src/mainwindow.h
	src/metainfodialog.h
	src/mpdcache.h
	src/mpdcache_p.h
	src/mpdconnection.h
	src/mpddirectory.h
	src/mpdentities.h
	src/mpd.h
	src/mpdoutput.h
	src/mpd_p.h
	src/mpdsong.h
	src/mpdsonglist.h
	src/mpdsongmodel.h
	src/mpdsongview.h
	src/mpdstats.h
	src/mpdstatus.h
	src/notifications.h
	src/passivepopup.h
	src/pausabletimer.h
	src/playlistitemdelegate.h
	src/playlistmodel.h
	src/playlistpanel.h
	src/playlistspanel.h
	src/playlistsview.h
	src/playlistview.h
	src/plconview.h
	src/preferencesdialog.h
	src/qmpdclient.h
	src/radiopanel.h
	src/radioview.h
	src/reconnect.h
	src/richtext.h
	src/serverinfo.h
	src/servermodel.h
	src/shortcutmodel.h
	src/shortcuts.h
	src/songview.h
	src/stringlistmodel.h
	src/stringlistview.h
	src/tagguesser.h
	src/tagmodel.h
	src/timelabel.h
	src/timeslider.h
	src/trayicon.h
	src/traysonginfo.h
	src/verticalbutton.h)

SET(QMPDClient_uis
	ui/aboutdialog.ui
	ui/addradiodialog.ui
	ui/controlpanel.ui
	ui/coverartdialog.ui
	ui/directorypanel.ui
	ui/jumptosongdialog.ui
	ui/librarypanel.ui
	ui/lyricsdialog.ui
	ui/mainwindow.ui
	ui/metainfodialog.ui
	ui/playlistpanel.ui
	ui/playlistspanel.ui
	ui/preferencesdialog.ui
	ui/radiopanel.ui)

if(UNIX)
	if(NOT MAC)
		if(QT_QTDBUS_FOUND)
			message(STATUS "QtDBus found")
			list(APPEND QMPDClient_srcs src/notifications_dbus.cpp)
		else()
			message(STATUS "QtDBus not found")
			list(APPEND QMPDClient_srcs src/notifications_nodbus.cpp)
		endif()
		list(APPEND QMPDClient_srcs src/qmpdclient_x11.cpp)
	else()
		list(APPEND QMPDClient_srcs src/notifications_nodbus.cpp
			src/qmpdclient_mac.cpp)
	endif()
endif()

if(WIN32)
	list(APPEND QMPDClient_srcs src/notifications_nodbus.cpp
			src/qmpdclient_win.cpp)
endif()

qt4_wrap_cpp(QMPDClient_ppd_hdrs ${QMPDClient_hdrs})
qt4_add_resources(QMPDClient_ppd_res qmpdclient.qrc)
qt4_wrap_ui(QMPDClient_ppd_uis ${QMPDClient_uis})
include_directories (${CMAKE_CURRENT_BINARY_DIR}
	src)

SET (TRANSLATIONS
	lang/cs_CZ.ts
	lang/de_DE.ts
	lang/fr_FR.ts
	lang/it_IT.ts
	lang/nl_NL.ts
	lang/nn_NO.ts
	lang/no_NO.ts
	lang/pt_BR.ts
	lang/ru_RU.ts
	lang/sv_SE.ts
	lang/tr_TR.ts
	lang/uk_UA.ts
	lang/zh_CN.ts
	lang/zh_TW.ts)

SET (COMPILED_TRANSLATIONS
	lang/cs_CZ.qm
	lang/de_DE.qm
	lang/fr_FR.qm
	lang/it_IT.qm
	lang/nl_NL.qm
	lang/nn_NO.qm
	lang/no_NO.qm
	lang/pt_BR.qm
	lang/ru_RU.qm
	lang/sv_SE.qm
	lang/tr_TR.qm
	lang/uk_UA.qm
	lang/zh_CN.qm
	lang/zh_TW.qm)


ADD_CUSTOM_COMMAND (OUTPUT
	${COMPILED_TRANSLATIONS}
	COMMAND "${QT_LRELEASE_EXECUTABLE}" ${TRANSLATIONS}
	DEPENDS ${TRANSLATIONS}
	WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	)

add_definitions(-DNAMEVER="${NAMEVER}" -DPREFIX="${CMAKE_INSTALL_PREFIX}" -DVERSION="${VERSION}")

add_executable(qmpdclient ${QMPDClient_srcs} ${QMPDClient_ppd_hdrs} ${QMPDClient_ppd_uis} ${QMPDClient_ppd_res} ${COMPILED_TRANSLATIONS})

target_link_libraries(qmpdclient ${QT_LIBRARIES})

install(FILES ${COMPILED_TRANSLATIONS} DESTINATION share/QMPDClient/translations)
install(TARGETS qmpdclient DESTINATION bin)
if(UNIX)
	install(FILES qmpdclient.desktop DESTINATION share/applications)
	install(FILES icons/qmpdclient64.png DESTINATION share/icons)
endif()