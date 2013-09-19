/****************************************************************************
** Meta object code from reading C++ file 'abstractview.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "abstractview.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_AbstractTree[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      26,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x08,
      51,   13,   13,   13, 0x08,
      65,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AbstractTree[] = {
    "AbstractTree\0\0connected()\0disconnected()\0"
    "enqueue()\0information()\0play()\0"
};

void AbstractTree::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AbstractTree *_t = static_cast<AbstractTree *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->enqueue(); break;
        case 3: _t->information(); break;
        case 4: _t->play(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AbstractTree::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AbstractTree::staticMetaObject = {
    { &QTreeView::staticMetaObject, qt_meta_stringdata_AbstractTree,
      qt_meta_data_AbstractTree, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AbstractTree::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AbstractTree::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AbstractTree::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractTree))
        return static_cast<void*>(const_cast< AbstractTree*>(this));
    return QTreeView::qt_metacast(_clname);
}

int AbstractTree::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
static const uint qt_meta_data_AbstractList[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      26,   13,   13,   13, 0x0a,
      41,   13,   13,   13, 0x08,
      51,   13,   13,   13, 0x08,
      65,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_AbstractList[] = {
    "AbstractList\0\0connected()\0disconnected()\0"
    "enqueue()\0information()\0play()\0"
};

void AbstractList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        AbstractList *_t = static_cast<AbstractList *>(_o);
        switch (_id) {
        case 0: _t->connected(); break;
        case 1: _t->disconnected(); break;
        case 2: _t->enqueue(); break;
        case 3: _t->information(); break;
        case 4: _t->play(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObjectExtraData AbstractList::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject AbstractList::staticMetaObject = {
    { &QListView::staticMetaObject, qt_meta_stringdata_AbstractList,
      qt_meta_data_AbstractList, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &AbstractList::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *AbstractList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *AbstractList::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractList))
        return static_cast<void*>(const_cast< AbstractList*>(this));
    return QListView::qt_metacast(_clname);
}

int AbstractList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
