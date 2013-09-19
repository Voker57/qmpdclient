/****************************************************************************
** Meta object code from reading C++ file 'traysonginfo.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "traysonginfo.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'traysonginfo.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TraySongInfo[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      30,   14,   13,   13, 0x08,
      59,   54,   13,   13, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TraySongInfo[] = {
    "TraySongInfo\0\0elapsed,maximum\0"
    "updatePosition(int,int)\0song\0"
    "setSong(MPDSong)\0"
};

void TraySongInfo::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        TraySongInfo *_t = static_cast<TraySongInfo *>(_o);
        switch (_id) {
        case 0: _t->updatePosition((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->setSong((*reinterpret_cast< const MPDSong(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData TraySongInfo::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject TraySongInfo::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TraySongInfo,
      qt_meta_data_TraySongInfo, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TraySongInfo::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TraySongInfo::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TraySongInfo::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TraySongInfo))
        return static_cast<void*>(const_cast< TraySongInfo*>(this));
    return QWidget::qt_metacast(_clname);
}

int TraySongInfo::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
