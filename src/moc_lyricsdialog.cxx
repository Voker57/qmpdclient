/****************************************************************************
** Meta object code from reading C++ file 'lyricsdialog.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lyricsdialog.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lyricsdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LyricsDialog[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      14,   13,   13,   13, 0x0a,
      21,   13,   13,   13, 0x0a,
      40,   13,   13,   13, 0x0a,
      85,   13,   13,   13, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_LyricsDialog[] = {
    "LyricsDialog\0\0show()\0updateLyricsText()\0"
    "errorLyricsText(QNetworkReply::NetworkError)\0"
    "setUserSong()\0"
};

void LyricsDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LyricsDialog *_t = static_cast<LyricsDialog *>(_o);
        switch (_id) {
        case 0: _t->show(); break;
        case 1: _t->updateLyricsText(); break;
        case 2: _t->errorLyricsText((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 3: _t->setUserSong(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LyricsDialog::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LyricsDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_LyricsDialog,
      qt_meta_data_LyricsDialog, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LyricsDialog::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LyricsDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LyricsDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LyricsDialog))
        return static_cast<void*>(const_cast< LyricsDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int LyricsDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
