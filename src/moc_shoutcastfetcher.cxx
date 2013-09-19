/****************************************************************************
** Meta object code from reading C++ file 'shoutcastfetcher.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "shoutcastfetcher.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shoutcastfetcher.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ShoutcastFetcher[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x05,
      44,   36,   17,   17, 0x05,
      82,   74,   17,   17, 0x05,
     136,  118,   17,   17, 0x05,

 // slots: signature, parameters, type, tag, flags
     203,  187,   17,   17, 0x08,
     260,  231,   17,   17, 0x08,
     315,  309,   17,   17, 0x08,
     350,  345,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_ShoutcastFetcher[] = {
    "ShoutcastFetcher\0\0genresAvailable()\0"
    "keyWord\0newStationsAvailable(QString)\0"
    "station\0playlistAvailable(ShoutcastStation)\0"
    "error,errorString\0"
    "errorFetching(QNetworkReply::NetworkError,QString)\0"
    "openInputDevice\0genresAvailable(QIODevice*)\0"
    "host,openInputDevice,keyword\0"
    "newStationsAvailable(QString,QIODevice*,QString)\0"
    "reply\0replyFinished(QNetworkReply*)\0"
    "file\0playlistDownloaded(PlsFile*)\0"
};

void ShoutcastFetcher::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        ShoutcastFetcher *_t = static_cast<ShoutcastFetcher *>(_o);
        switch (_id) {
        case 0: _t->genresAvailable(); break;
        case 1: _t->newStationsAvailable((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->playlistAvailable((*reinterpret_cast< const ShoutcastStation(*)>(_a[1]))); break;
        case 3: _t->errorFetching((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->genresAvailable((*reinterpret_cast< QIODevice*(*)>(_a[1]))); break;
        case 5: _t->newStationsAvailable((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< QIODevice*(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 6: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->playlistDownloaded((*reinterpret_cast< PlsFile*(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData ShoutcastFetcher::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject ShoutcastFetcher::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShoutcastFetcher,
      qt_meta_data_ShoutcastFetcher, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ShoutcastFetcher::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ShoutcastFetcher::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ShoutcastFetcher::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ShoutcastFetcher))
        return static_cast<void*>(const_cast< ShoutcastFetcher*>(this));
    return QObject::qt_metacast(_clname);
}

int ShoutcastFetcher::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ShoutcastFetcher::genresAvailable()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void ShoutcastFetcher::newStationsAvailable(const QString & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ShoutcastFetcher::playlistAvailable(const ShoutcastStation & _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ShoutcastFetcher::errorFetching(QNetworkReply::NetworkError _t1, const QString & _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
