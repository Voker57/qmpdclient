/****************************************************************************
** Meta object code from reading C++ file 'plsfile.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "plsfile.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'plsfile.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PlsFile[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      14,    9,    8,    8, 0x05,

 // slots: signature, parameters, type, tag, flags
      36,   30,    8,    8, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PlsFile[] = {
    "PlsFile\0\0file\0ready(PlsFile*)\0reply\0"
    "newDataAvailable(QNetworkReply*)\0"
};

void PlsFile::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PlsFile *_t = static_cast<PlsFile *>(_o);
        switch (_id) {
        case 0: _t->ready((*reinterpret_cast< PlsFile*(*)>(_a[1]))); break;
        case 1: _t->newDataAvailable((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PlsFile::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PlsFile::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PlsFile,
      qt_meta_data_PlsFile, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PlsFile::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PlsFile::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PlsFile::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PlsFile))
        return static_cast<void*>(const_cast< PlsFile*>(this));
    return QObject::qt_metacast(_clname);
}

int PlsFile::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void PlsFile::ready(PlsFile * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
