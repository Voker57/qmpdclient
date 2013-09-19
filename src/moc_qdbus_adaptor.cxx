/****************************************************************************
** Meta object code from reading C++ file 'qdbus_adaptor.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qdbus_adaptor.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qdbus_adaptor.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainApplicationAdaptor[] = {

 // content:
       6,       // revision
       0,       // classname
       1,   14, // classinfo
       3,   16, // methods
       2,   31, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // classinfo: key, value
      48,   23,

 // signals: signature, parameters, type, tag, flags
      65,   64,   64,   64, 0x05,

 // slots: signature, parameters, type, tag, flags
      79,   64,   64,   64, 0x0a,
      86,   64,   64,   64, 0x0a,

 // properties: name, type, flags
     113,  105, 0x0a095001,
     130,  105, 0x0a095001,

       0        // eod
};

static const char qt_meta_stringdata_MainApplicationAdaptor[] = {
    "MainApplicationAdaptor\0net.bitcheese.QMPDClient\0"
    "D-Bus Interface\0\0aboutToQuit()\0quit()\0"
    "toggleMainWindow()\0QString\0organizationName\0"
    "organizationDomain\0"
};

void MainApplicationAdaptor::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MainApplicationAdaptor *_t = static_cast<MainApplicationAdaptor *>(_o);
        switch (_id) {
        case 0: _t->aboutToQuit(); break;
        case 1: _t->quit(); break;
        case 2: _t->toggleMainWindow(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData MainApplicationAdaptor::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MainApplicationAdaptor::staticMetaObject = {
    { &QDBusAbstractAdaptor::staticMetaObject, qt_meta_stringdata_MainApplicationAdaptor,
      qt_meta_data_MainApplicationAdaptor, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainApplicationAdaptor::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainApplicationAdaptor::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainApplicationAdaptor::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainApplicationAdaptor))
        return static_cast<void*>(const_cast< MainApplicationAdaptor*>(this));
    return QDBusAbstractAdaptor::qt_metacast(_clname);
}

int MainApplicationAdaptor::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDBusAbstractAdaptor::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
#ifndef QT_NO_PROPERTIES
      else if (_c == QMetaObject::ReadProperty) {
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = organizationName(); break;
        case 1: *reinterpret_cast< QString*>(_v) = organizationDomain(); break;
        }
        _id -= 2;
    } else if (_c == QMetaObject::WriteProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::ResetProperty) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void MainApplicationAdaptor::aboutToQuit()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
