/****************************************************************************
** Meta object code from reading C++ file 'ArduinoMiner.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../startovaciokno/ArduinoMiner.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ArduinoMiner.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ArduinoMiner_t {
    QByteArrayData data[7];
    char stringdata[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ArduinoMiner_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ArduinoMiner_t qt_meta_stringdata_ArduinoMiner = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ArduinoMiner"
QT_MOC_LITERAL(1, 13, 11), // "ListChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 12), // "QStringList*"
QT_MOC_LITERAL(4, 39, 12), // "changeStatus"
QT_MOC_LITERAL(5, 52, 17), // "ConnectionChanged"
QT_MOC_LITERAL(6, 70, 11) // "ReceiveData"

    },
    "ArduinoMiner\0ListChanged\0\0QStringList*\0"
    "changeStatus\0ConnectionChanged\0"
    "ReceiveData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ArduinoMiner[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,
       5,    1,   40,    2, 0x06 /* Public */,
       6,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

       0        // eod
};

void ArduinoMiner::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ArduinoMiner *_t = static_cast<ArduinoMiner *>(_o);
        switch (_id) {
        case 0: _t->ListChanged((*reinterpret_cast< QStringList*(*)>(_a[1]))); break;
        case 1: _t->changeStatus((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ConnectionChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ReceiveData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ArduinoMiner::*_t)(QStringList * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ArduinoMiner::ListChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (ArduinoMiner::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ArduinoMiner::changeStatus)) {
                *result = 1;
            }
        }
        {
            typedef void (ArduinoMiner::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ArduinoMiner::ConnectionChanged)) {
                *result = 2;
            }
        }
        {
            typedef void (ArduinoMiner::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ArduinoMiner::ReceiveData)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject ArduinoMiner::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_ArduinoMiner.data,
      qt_meta_data_ArduinoMiner,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ArduinoMiner::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ArduinoMiner::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ArduinoMiner.stringdata))
        return static_cast<void*>(const_cast< ArduinoMiner*>(this));
    return QThread::qt_metacast(_clname);
}

int ArduinoMiner::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ArduinoMiner::ListChanged(QStringList * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ArduinoMiner::changeStatus(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ArduinoMiner::ConnectionChanged(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ArduinoMiner::ReceiveData(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
