/****************************************************************************
** Meta object code from reading C++ file 'preferencesdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "preferencesdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'preferencesdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_PreferencesDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
      23,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x0a,
      35,   18,   18,   18, 0x0a,
      55,   18,   18,   18, 0x08,
      78,   18,   18,   18, 0x08,
     105,  103,   18,   18, 0x08,
     175,   18,   18,   18, 0x08,
     201,   18,   18,   18, 0x08,
     225,   18,   18,   18, 0x08,
     249,   18,   18,   18, 0x08,
     285,   18,   18,   18, 0x08,
     318,   18,   18,   18, 0x08,
     340,   18,   18,   18, 0x08,
     359,   18,   18,   18, 0x08,
     392,   18,   18,   18, 0x08,
     424,   18,   18,   18, 0x08,
     445,  103,   18,   18, 0x08,
     481,   18,   18,   18, 0x08,
     506,   18,   18,   18, 0x08,
     537,   18,   18,   18, 0x08,
     558,   18,   18,   18, 0x08,
     579,   18,   18,   18, 0x08,
     600,   18,   18,   18, 0x08,
     618,   18,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_PreferencesDialog[] = {
    "PreferencesDialog\0\0updateIconSet()\0"
    "updateTranslation()\0on_addButton_clicked()\0"
    "on_closeButton_clicked()\0,\0"
    "on_categoryList_currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)\0"
    "on_deleteButton_clicked()\0"
    "on_downButton_clicked()\0on_fontButton_clicked()\0"
    "on_patternLine_textChanged(QString)\0"
    "on_testLine_textChanged(QString)\0"
    "on_upButton_clicked()\0crossfadeChanged()\0"
    "iconsetChanged(QListWidgetItem*)\0"
    "localeChanged(QListWidgetItem*)\0"
    "notifierChanged(int)\0"
    "outputChanged(QTreeWidgetItem*,int)\0"
    "serverSelectionChanged()\0"
    "styleChanged(QListWidgetItem*)\0"
    "hashLastFmPassword()\0setLastFmSlider(int)\0"
    "setLastFmSpiner(int)\0setLastFmServer()\0"
    "setLibreFmServer()\0"
};

void PreferencesDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        PreferencesDialog *_t = static_cast<PreferencesDialog *>(_o);
        switch (_id) {
        case 0: _t->updateIconSet(); break;
        case 1: _t->updateTranslation(); break;
        case 2: _t->on_addButton_clicked(); break;
        case 3: _t->on_closeButton_clicked(); break;
        case 4: _t->on_categoryList_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< QTreeWidgetItem*(*)>(_a[2]))); break;
        case 5: _t->on_deleteButton_clicked(); break;
        case 6: _t->on_downButton_clicked(); break;
        case 7: _t->on_fontButton_clicked(); break;
        case 8: _t->on_patternLine_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->on_testLine_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->on_upButton_clicked(); break;
        case 11: _t->crossfadeChanged(); break;
        case 12: _t->iconsetChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->localeChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: _t->notifierChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->outputChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 16: _t->serverSelectionChanged(); break;
        case 17: _t->styleChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 18: _t->hashLastFmPassword(); break;
        case 19: _t->setLastFmSlider((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->setLastFmSpiner((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->setLastFmServer(); break;
        case 22: _t->setLibreFmServer(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData PreferencesDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject PreferencesDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_PreferencesDialog,
      qt_meta_data_PreferencesDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &PreferencesDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *PreferencesDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *PreferencesDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_PreferencesDialog))
        return static_cast<void*>(const_cast< PreferencesDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int PreferencesDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 23)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 23;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
