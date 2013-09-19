/****************************************************************************
** Meta object code from reading C++ file 'qmpdclient.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "qmpdclient.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qmpdclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_QMPDClient[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x0a,
      31,   11,   11,   11, 0x08,
      56,   11,   11,   11, 0x08,
      75,   11,   11,   11, 0x08,
      92,   11,   11,   11, 0x08,
     115,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_QMPDClient[] = {
    "QMPDClient\0\0toggleMainWindow()\0"
    "alternatingChanged(bool)\0fontChanged(QFont)\0"
    "iconSetChanged()\0localeChanged(QString)\0"
    "opaqueResizeChanged(bool)\0"
};

void QMPDClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        QMPDClient *_t = static_cast<QMPDClient *>(_o);
        switch (_id) {
        case 0: _t->toggleMainWindow(); break;
        case 1: _t->alternatingChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->fontChanged((*reinterpret_cast< const QFont(*)>(_a[1]))); break;
        case 3: _t->iconSetChanged(); break;
        case 4: _t->localeChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->opaqueResizeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData QMPDClient::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject QMPDClient::staticMetaObject = {
    { &QApplication::staticMetaObject, qt_meta_stringdata_QMPDClient,
      qt_meta_data_QMPDClient, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &QMPDClient::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *QMPDClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *QMPDClient::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_QMPDClient))
        return static_cast<void*>(const_cast< QMPDClient*>(this));
    return QApplication::qt_metacast(_clname);
}

int QMPDClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QApplication::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
