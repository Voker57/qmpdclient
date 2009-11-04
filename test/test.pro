TEMPLATE = app
INCLUDEPATH += ../src
DEPENDPATH += ../src ../ui
CONFIG += qt
QT += network xml xmlpatterns testlib
RESOURCES += test.qrc
HEADERS +=	shoutcastfetcher.h \
			shoutcaststation.h \
			plsfile.h
			
SOURCES +=  shoutcasttest.cpp \
			shoutcastfetcher.cpp \
			shoutcaststation.cpp \
			plsfile.cpp
			
FORMS +=