/****************************************************************************
** Meta object code from reading C++ file 'playlistsview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "playlistsview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistsview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlaylistsView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      35,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      64,   14,   14,   14, 0x0a,
      81,   14,   14,   14, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_PlaylistsView[] = {
    "PlaylistsView\0\0toggleActions(bool)\0"
    "playlistChanged(MPDSongList)\0"
    "deletePlaylist()\0updateTranslation()\0"
};

void PlaylistsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlaylistsView *_t = static_cast<PlaylistsView *>(_o);
        switch (_id) {
        case 0: _t->toggleActions((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->playlistChanged((*reinterpret_cast< const MPDSongList(*)>(_a[1]))); break;
        case 2: _t->deletePlaylist(); break;
        case 3: _t->updateTranslation(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlaylistsView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlaylistsView::staticMetaObject = {
    { &MPDSongView::staticMetaObject, qt_meta_stringdata_PlaylistsView,
      qt_meta_data_PlaylistsView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlaylistsView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlaylistsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlaylistsView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlaylistsView))
        return static_cast<void*>(const_cast< PlaylistsView*>(this));
    return MPDSongView::qt_metacast(_clname);
}

int PlaylistsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = MPDSongView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void PlaylistsView::toggleActions(bool _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlaylistsView::playlistChanged(const MPDSongList & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
