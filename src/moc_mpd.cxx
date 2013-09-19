/****************************************************************************
** Meta object code from reading C++ file 'mpd.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mpd.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mpd.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MPD[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x05,
      33,    4,    4,    4, 0x05,
      62,    4,    4,    4, 0x05,
      82,    4,    4,    4, 0x05,
     102,    4,    4,    4, 0x05,
     121,    4,    4,    4, 0x05,
     146,  144,    4,    4, 0x05,
     167,    4,    4,    4, 0x05,

 // slots: signature, parameters, type, tag, flags
     186,    4,    4,    4, 0x0a,
     202,    4,    4,    4, 0x0a,
     209,    4,    4,    4, 0x0a,
     222,    4,    4,    4, 0x0a,
     230,    4,    4,    4, 0x0a,
     237,    4,    4,    4, 0x0a,
     244,    4,    4,    4, 0x0a,
     261,  251,    4,    4, 0x0a,
     271,    4,    4,    4, 0x0a,
     286,    4,    4,    4, 0x0a,
     308,  300,    4,    4, 0x0a,
     326,    4,    4,    4, 0x0a,
     342,    4,    4,    4, 0x0a,
     358,    4,    4,    4, 0x0a,
     373,    4,    4,    4, 0x0a,
     391,    4,    4,    4, 0x0a,
     405,    4,    4,    4, 0x2a,
     416,    4,    4,    4, 0x0a,
     432,    4,    4,    4, 0x2a,
     445,    4,    4,    4, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MPD[] = {
    "MPD\0\0playingSongUpdated(MPDSong)\0"
    "playlistUpdated(MPDSongList)\0"
    "randomUpdated(bool)\0repeatUpdated(bool)\0"
    "stateUpdated(bool)\0statsUpdated(MPDStats)\0"
    ",\0timeUpdated(int,int)\0volumeUpdated(int)\0"
    "clearPlaylist()\0play()\0togglePlay()\0"
    "pause()\0stop()\0next()\0prev()\0toSeconds\0"
    "seek(int)\0seekBackward()\0seekForward()\0"
    "seconds\0setCrossfade(int)\0setRandom(bool)\0"
    "setRepeat(bool)\0setVolume(int)\0"
    "shufflePlaylist()\0volumeUp(int)\0"
    "volumeUp()\0volumeDown(int)\0volumeDown()\0"
    "poll()\0"
};

void MPD::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MPD *_t = static_cast<MPD *>(_o);
        switch (_id) {
        case 0: _t->playingSongUpdated((*reinterpret_cast< const MPDSong(*)>(_a[1]))); break;
        case 1: _t->playlistUpdated((*reinterpret_cast< const MPDSongList(*)>(_a[1]))); break;
        case 2: _t->randomUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->repeatUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->stateUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->statsUpdated((*reinterpret_cast< const MPDStats(*)>(_a[1]))); break;
        case 6: _t->timeUpdated((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->volumeUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->clearPlaylist(); break;
        case 9: _t->play(); break;
        case 10: _t->togglePlay(); break;
        case 11: _t->pause(); break;
        case 12: _t->stop(); break;
        case 13: _t->next(); break;
        case 14: _t->prev(); break;
        case 15: _t->seek((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->seekBackward(); break;
        case 17: _t->seekForward(); break;
        case 18: _t->setCrossfade((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: _t->setRandom((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 20: _t->setRepeat((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 21: _t->setVolume((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: _t->shufflePlaylist(); break;
        case 23: _t->volumeUp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: _t->volumeUp(); break;
        case 25: _t->volumeDown((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->volumeDown(); break;
        case 27: _t->poll(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MPD::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MPD::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MPD,
      qt_meta_data_MPD, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MPD::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MPD::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MPD::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MPD))
        return static_cast<void*>(const_cast< MPD*>(this));
    return QObject::qt_metacast(_clname);
}

int MPD::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void MPD::playingSongUpdated(const MPDSong & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MPD::playlistUpdated(const MPDSongList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MPD::randomUpdated(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MPD::repeatUpdated(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MPD::stateUpdated(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MPD::statsUpdated(const MPDStats & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void MPD::timeUpdated(int _t1, int _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void MPD::volumeUpdated(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_END_MOC_NAMESPACE
