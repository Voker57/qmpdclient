/****************************************************************************
** Meta object code from reading C++ file 'idealsplitter.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "idealsplitter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'idealsplitter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_IdealSplitter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      15,   14,   14,   14, 0x05,
      37,   14,   14,   14, 0x05,

 // slots: signature, parameters, type, tag, flags
      58,   14,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_IdealSplitter[] = {
    "IdealSplitter\0\0sectionCollapsed(int)\0"
    "sectionExpanded(int)\0manuallyResized()\0"
};

void IdealSplitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        IdealSplitter *_t = static_cast<IdealSplitter *>(_o);
        switch (_id) {
        case 0: _t->sectionCollapsed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sectionExpanded((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->manuallyResized(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData IdealSplitter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject IdealSplitter::staticMetaObject = {
    { &QSplitter::staticMetaObject, qt_meta_stringdata_IdealSplitter,
      qt_meta_data_IdealSplitter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &IdealSplitter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *IdealSplitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *IdealSplitter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_IdealSplitter))
        return static_cast<void*>(const_cast< IdealSplitter*>(this));
    return QSplitter::qt_metacast(_clname);
}

int IdealSplitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSplitter::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void IdealSplitter::sectionCollapsed(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void IdealSplitter::sectionExpanded(int _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
