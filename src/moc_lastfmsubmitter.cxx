/****************************************************************************
** Meta object code from reading C++ file 'lastfmsubmitter.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lastfmsubmitter.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lastfmsubmitter.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_LastFmSubmitter[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      17,   16,   16,   16, 0x05,

 // slots: signature, parameters, type, tag, flags
      34,   16,   16,   16, 0x09,
      62,   16,   16,   16, 0x09,
      80,   16,   16,   16, 0x09,
      97,   16,   16,   16, 0x09,
     114,   16,   16,   16, 0x09,
     128,   16,   16,   16, 0x09,

       0        // eod
};

static const char qt_meta_stringdata_LastFmSubmitter[] = {
    "LastFmSubmitter\0\0infoMsg(QString)\0"
    "gotNetReply(QNetworkReply*)\0"
    "scrobbleCurrent()\0scrobbleQueued()\0"
    "sendNowPlaying()\0doHandshake()\0"
    "mpdStateUpdated(bool)\0"
};

void LastFmSubmitter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        LastFmSubmitter *_t = static_cast<LastFmSubmitter *>(_o);
        switch (_id) {
        case 0: _t->infoMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->gotNetReply((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 2: _t->scrobbleCurrent(); break;
        case 3: _t->scrobbleQueued(); break;
        case 4: _t->sendNowPlaying(); break;
        case 5: _t->doHandshake(); break;
        case 6: _t->mpdStateUpdated((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData LastFmSubmitter::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject LastFmSubmitter::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LastFmSubmitter,
      qt_meta_data_LastFmSubmitter, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &LastFmSubmitter::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *LastFmSubmitter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *LastFmSubmitter::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_LastFmSubmitter))
        return static_cast<void*>(const_cast< LastFmSubmitter*>(this));
    return QObject::qt_metacast(_clname);
}

int LastFmSubmitter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void LastFmSubmitter::infoMsg(QString _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
