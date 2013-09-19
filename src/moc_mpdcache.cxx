/****************************************************************************
** Meta object code from reading C++ file 'mpdcache.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mpdcache.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mpdcache.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MPDCache[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: signature, parameters, type, tag, flags
      10,    9,    9,    9, 0x05,
      38,    9,    9,    9, 0x05,
      71,    9,    9,    9, 0x05,
     101,    9,    9,    9, 0x05,
     114,    9,    9,    9, 0x05,
     136,  134,    9,    9, 0x05,

 // slots: signature, parameters, type, tag, flags
     161,    9,    9,    9, 0x0a,
     189,    9,    9,    9, 0x0a,
     198,    9,    9,    9, 0x0a,
     222,    9,    9,    9, 0x08,
     237,    9,    9,    9, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MPDCache[] = {
    "MPDCache\0\0artistsUpdated(QStringList)\0"
    "directoriesUpdated(MPDDirectory)\0"
    "playlistsUpdated(MPDSongList)\0"
    "updateDone()\0updateProgress(int)\0,\0"
    "updateStart(int,QString)\0"
    "rescan(QList<MPDDirectory>)\0rescan()\0"
    "reReadLibrary(MPDStats)\0disconnected()\0"
    "setShowAll(bool)\0"
};

void MPDCache::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MPDCache *_t = static_cast<MPDCache *>(_o);
        switch (_id) {
        case 0: _t->artistsUpdated((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 1: _t->directoriesUpdated((*reinterpret_cast< const MPDDirectory(*)>(_a[1]))); break;
        case 2: _t->playlistsUpdated((*reinterpret_cast< const MPDSongList(*)>(_a[1]))); break;
        case 3: _t->updateDone(); break;
        case 4: _t->updateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->updateStart((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->rescan((*reinterpret_cast< const QList<MPDDirectory>(*)>(_a[1]))); break;
        case 7: _t->rescan(); break;
        case 8: _t->reReadLibrary((*reinterpret_cast< const MPDStats(*)>(_a[1]))); break;
        case 9: _t->disconnected(); break;
        case 10: _t->setShowAll((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MPDCache::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MPDCache::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MPDCache,
      qt_meta_data_MPDCache, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MPDCache::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MPDCache::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MPDCache::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MPDCache))
        return static_cast<void*>(const_cast< MPDCache*>(this));
    return QObject::qt_metacast(_clname);
}

int MPDCache::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void MPDCache::artistsUpdated(const QStringList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MPDCache::directoriesUpdated(const MPDDirectory & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MPDCache::playlistsUpdated(const MPDSongList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MPDCache::updateDone()
{
    QMetaObject::activate(this, &staticMetaObject, 3, 0);
}

// SIGNAL 4
void MPDCache::updateProgress(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MPDCache::updateStart(int _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
