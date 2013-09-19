/****************************************************************************
** Meta object code from reading C++ file 'shoutcastview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "shoutcastview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shoutcastview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShoutcastView[] = {

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
      15,   14,   14,   14, 0x0a,
      48,   35,   14,   14, 0x08,
      83,   70,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ShoutcastView[] = {
    "ShoutcastView\0\0updateTranslation()\0"
    "expandedItem\0expanded(QModelIndex)\0"
    "selectedItem\0doubleClicked(QModelIndex)\0"
};

void ShoutcastView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShoutcastView *_t = static_cast<ShoutcastView *>(_o);
        switch (_id) {
        case 0: _t->updateTranslation(); break;
        case 1: _t->expanded((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 2: _t->doubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShoutcastView::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShoutcastView::staticMetaObject = {
    { &AbstractTree::staticMetaObject, qt_meta_stringdata_ShoutcastView,
      qt_meta_data_ShoutcastView, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShoutcastView::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShoutcastView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShoutcastView::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShoutcastView))
        return static_cast<void*>(const_cast< ShoutcastView*>(this));
    return AbstractTree::qt_metacast(_clname);
}

int ShoutcastView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractTree::qt_metacall(_c, _id, _a);
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
