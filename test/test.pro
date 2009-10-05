TEMPLATE = app
INCLUDEPATH += ../src
DEPENDPATH += ../src
CONFIG += qt
QT += network xml xmlpatterns testlib
RESOURCES += test.qrc
HEADERS +=	shoutcastview.h \
			shoutcastmodel.h \
			shoutcastfetcher.h \
			shoutcaststation.h \
			plsfile.h
			
SOURCES +=  shoutcastview.cpp \
			shoutcastmodel.cpp \
			shoutcasttest.cpp \
			shoutcastfetcher.cpp \
			shoutcaststation.cpp \
			plsfile.cpp
			
			