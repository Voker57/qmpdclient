/****************************************************************************
** Meta object code from reading C++ file 'mpdconnection.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mpdconnection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mpdconnection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MPDConnection[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      43,   37,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      65,   14,   14,   14, 0x0a,
      90,   14,   14,   14, 0x0a,
     117,   14,   14,   14, 0x2a,

       0        // eod
};

static const char qt_meta_stringdata_MPDConnection[] = {
    "MPDConnection\0\0connected(ServerInfo)\0"
    "error\0disconnected(QString)\0"
    "connectToMPD(ServerInfo)\0"
    "disconnectFromMPD(QString)\0"
    "disconnectFromMPD()\0"
};

void MPDConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        MPDConnection *_t = static_cast<MPDConnection *>(_o);
        switch (_id) {
        case 0: _t->connected((*reinterpret_cast< const ServerInfo(*)>(_a[1]))); break;
        case 1: _t->disconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->connectToMPD((*reinterpret_cast< const ServerInfo(*)>(_a[1]))); break;
        case 3: _t->disconnectFromMPD((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->disconnectFromMPD(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData MPDConnection::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject MPDConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MPDConnection,
      qt_meta_data_MPDConnection, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MPDConnection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MPDConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MPDConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MPDConnection))
        return static_cast<void*>(const_cast< MPDConnection*>(this));
    return QObject::qt_metacast(_clname);
}

int MPDConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void MPDConnection::connected(const ServerInfo & _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< MPDConnection *>(this), &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MPDConnection::disconnected(const QString & _t1)const
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(const_cast< MPDConnection *>(this), &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
