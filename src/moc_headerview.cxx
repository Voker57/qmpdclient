/****************************************************************************
** Meta object code from reading C++ file 'headerview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "headerview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'headerview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HeaderView[] = {

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
      12,   11,   11,   11, 0x08,
      36,   11,   11,   11, 0x08,
      54,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HeaderView[] = {
    "HeaderView\0\0autoResizeChanged(bool)\0"
    "actionTriggered()\0save()\0"
};

void HeaderView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        HeaderView *_t = static_cast<HeaderView *>(_o);
        switch (_id) {
        case 0: _t->autoResizeChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->actionTriggered(); break;
        case 2: _t->save(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData HeaderView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HeaderView::staticMetaObject = {
    { &QHeaderView::staticMetaObject, qt_meta_stringdata_HeaderView,
      qt_meta_data_HeaderView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HeaderView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HeaderView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HeaderView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeaderView))
        return static_cast<void*>(const_cast< HeaderView*>(this));
    return QHeaderView::qt_metacast(_clname);
}

int HeaderView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QHeaderView::qt_metacall(_c, _id, _a);
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
