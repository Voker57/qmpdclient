/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      23,   11,   11,   11, 0x0a,
      43,   11,   11,   11, 0x0a,
      66,   11,   11,   11, 0x0a,
      84,   11,   11,   11, 0x08,
     107,  105,   11,   11, 0x08,
     142,   11,   11,   11, 0x08,
     173,   11,   11,   11, 0x08,
     198,   11,   11,   11, 0x08,
     213,   11,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,
     255,   11,   11,   11, 0x08,
     282,   11,   11,   11, 0x08,
     299,   11,   11,   11, 0x08,
     318,   11,   11,   11, 0x08,
     355,   11,   11,   11, 0x08,
     377,  105,   11,   11, 0x08,
     402,   11,   11,   11, 0x08,
     422,   11,   11,   11, 0x08,
     435,   11,   11,   11, 0x08,
     465,   11,   11,   11, 0x08,
     485,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0showHide()\0updateTranslation()\0"
    "shortAnnounce(QString)\0announce(QString)\0"
    "on_about_triggered()\0,\0"
    "on_splitter_splitterMoved(int,int)\0"
    "on_preferencesMenu_triggered()\0"
    "closeEvent(QCloseEvent*)\0connectToMPD()\0"
    "connectionChanged()\0disconnected(QString)\0"
    "resizeEvent(QResizeEvent*)\0setSong(MPDSong)\0"
    "setStats(MPDStats)\0"
    "serverListChanged(QList<ServerInfo>)\0"
    "trayIconChanged(bool)\0updateStart(int,QString)\0"
    "updateProgress(int)\0updateDone()\0"
    "rightStackCurrentChanged(int)\0"
    "locateCurrentSong()\0playlistUpdated(MPDSongList)\0"
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->showHide(); break;
        case 1: _t->updateTranslation(); break;
        case 2: _t->shortAnnounce((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->announce((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->on_about_triggered(); break;
        case 5: _t->on_splitter_splitterMoved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 6: _t->on_preferencesMenu_triggered(); break;
        case 7: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 8: _t->connectToMPD(); break;
        case 9: _t->connectionChanged(); break;
        case 10: _t->disconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->resizeEvent((*reinterpret_cast< QResizeEvent*(*)>(_a[1]))); break;
        case 12: _t->setSong((*reinterpret_cast< const MPDSong(*)>(_a[1]))); break;
        case 13: _t->setStats((*reinterpret_cast< const MPDStats(*)>(_a[1]))); break;
        case 14: _t->serverListChanged((*reinterpret_cast< const QList<ServerInfo>(*)>(_a[1]))); break;
        case 15: _t->trayIconChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 16: _t->updateStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 17: _t->updateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: _t->updateDone(); break;
        case 19: _t->rightStackCurrentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->locateCurrentSong(); break;
        case 21: _t->playlistUpdated((*reinterpret_cast< const MPDSongList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MainWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
