/****************************************************************************
** Meta object code from reading C++ file 'shoutcastmodel.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "shoutcastmodel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shoutcastmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShoutcastModel[] = {

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
      16,   15,   15,   15, 0x08,
      42,   34,   15,   15, 0x08,
      80,   72,   15,   15, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ShoutcastModel[] = {
    "ShoutcastModel\0\0genresAvailable()\0"
    "keyWord\0newStationsAvailable(QString)\0"
    "station\0playlistAvailable(ShoutcastStation)\0"
};

void ShoutcastModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShoutcastModel *_t = static_cast<ShoutcastModel *>(_o);
        switch (_id) {
        case 0: _t->genresAvailable(); break;
        case 1: _t->newStationsAvailable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->playlistAvailable((*reinterpret_cast< const ShoutcastStation(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShoutcastModel::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShoutcastModel::staticMetaObject = {
    { &QStandardItemModel::staticMetaObject, qt_meta_stringdata_ShoutcastModel,
      qt_meta_data_ShoutcastModel, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShoutcastModel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShoutcastModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShoutcastModel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShoutcastModel))
        return static_cast<void*>(const_cast< ShoutcastModel*>(this));
    if (!strcmp(_clname, "AbstractModel"))
        return static_cast< AbstractModel*>(const_cast< ShoutcastModel*>(this));
    return QStandardItemModel::qt_metacast(_clname);
}

int ShoutcastModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QStandardItemModel::qt_metacall(_c, _id, _a);
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
