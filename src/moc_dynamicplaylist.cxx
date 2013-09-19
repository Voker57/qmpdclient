/****************************************************************************
** Meta object code from reading C++ file 'dynamicplaylist.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "dynamicplaylist.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dynamicplaylist.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_DynamicPlaylist[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x08,
      34,   16,   16,   16, 0x08,
      54,   16,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_DynamicPlaylist[] = {
    "DynamicPlaylist\0\0autoAdd(MPDSong)\0"
    "autoRemove(MPDSong)\0playlistUpdated(MPDSongList)\0"
};

void DynamicPlaylist::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        DynamicPlaylist *_t = static_cast<DynamicPlaylist *>(_o);
        switch (_id) {
        case 0: _t->autoAdd((*reinterpret_cast< const MPDSong(*)>(_a[1]))); break;
        case 1: _t->autoRemove((*reinterpret_cast< const MPDSong(*)>(_a[1]))); break;
        case 2: _t->playlistUpdated((*reinterpret_cast< const MPDSongList(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData DynamicPlaylist::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject DynamicPlaylist::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DynamicPlaylist,
      qt_meta_data_DynamicPlaylist, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &DynamicPlaylist::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *DynamicPlaylist::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *DynamicPlaylist::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_DynamicPlaylist))
        return static_cast<void*>(const_cast< DynamicPlaylist*>(this));
    return QObject::qt_metacast(_clname);
}

int DynamicPlaylist::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
