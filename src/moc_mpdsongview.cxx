/****************************************************************************
** Meta object code from reading C++ file 'mpdsongview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mpdsongview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mpdsongview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MPDSongView[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      32,   12,   12,   12, 0x0a,
      54,   12,   12,   12, 0x0a,
      74,   12,   12,   12, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_MPDSongView[] = {
    "MPDSongView\0\0setFilter(QString)\0"
    "setSongs(MPDSongList)\0updateTranslation()\0"
    "doubleClicked(QModelIndex)\0"
};

void MPDSongView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MPDSongView *_t = static_cast<MPDSongView *>(_o);
        switch (_id) {
        case 0: _t->setFilter((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->setSongs((*reinterpret_cast< const MPDSongList(*)>(_a[1]))); break;
        case 2: _t->updateTranslation(); break;
        case 3: _t->doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MPDSongView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MPDSongView::staticMetaObject = {
    { &AbstractTree::staticMetaObject, qt_meta_stringdata_MPDSongView,
      qt_meta_data_MPDSongView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MPDSongView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MPDSongView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MPDSongView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MPDSongView))
        return static_cast<void*>(const_cast< MPDSongView*>(this));
    return AbstractTree::qt_metacast(_clname);
}

int MPDSongView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTree::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
