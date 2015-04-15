/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../startovaciokno/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[17];
    char stringdata[260];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 27), // "on_tlacitkoPripojit_clicked"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 26), // "on_tlacitkoOdpojit_clicked"
QT_MOC_LITERAL(4, 67, 33), // "on_tlacitkoHledejZarizeni_cli..."
QT_MOC_LITERAL(5, 101, 19), // "on_listView_clicked"
QT_MOC_LITERAL(6, 121, 5), // "index"
QT_MOC_LITERAL(7, 127, 26), // "on_tlacitkoOdeslat_clicked"
QT_MOC_LITERAL(8, 154, 16), // "on_SeznamChanged"
QT_MOC_LITERAL(9, 171, 12), // "QStringList*"
QT_MOC_LITERAL(10, 184, 4), // "list"
QT_MOC_LITERAL(11, 189, 13), // "on_ZmenaStavu"
QT_MOC_LITERAL(12, 203, 4), // "stav"
QT_MOC_LITERAL(13, 208, 20), // "on_ZmenaStavuSpojeni"
QT_MOC_LITERAL(14, 229, 11), // "stavSpojeni"
QT_MOC_LITERAL(15, 241, 13), // "on_PrijmiData"
QT_MOC_LITERAL(16, 255, 4) // "data"

    },
    "MainWindow\0on_tlacitkoPripojit_clicked\0"
    "\0on_tlacitkoOdpojit_clicked\0"
    "on_tlacitkoHledejZarizeni_clicked\0"
    "on_listView_clicked\0index\0"
    "on_tlacitkoOdeslat_clicked\0on_SeznamChanged\0"
    "QStringList*\0list\0on_ZmenaStavu\0stav\0"
    "on_ZmenaStavuSpojeni\0stavSpojeni\0"
    "on_PrijmiData\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08 /* Private */,
       3,    0,   60,    2, 0x08 /* Private */,
       4,    0,   61,    2, 0x08 /* Private */,
       5,    1,   62,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    1,   66,    2, 0x0a /* Public */,
      11,    1,   69,    2, 0x0a /* Public */,
      13,    1,   72,    2, 0x0a /* Public */,
      15,    1,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QModelIndex,    6,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void, QMetaType::QString,   16,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        switch (_id) {
        case 0: _t->on_tlacitkoPripojit_clicked(); break;
        case 1: _t->on_tlacitkoOdpojit_clicked(); break;
        case 2: _t->on_tlacitkoHledejZarizeni_clicked(); break;
        case 3: _t->on_listView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: _t->on_tlacitkoOdeslat_clicked(); break;
        case 5: _t->on_SeznamChanged((*reinterpret_cast< QStringList*(*)>(_a[1]))); break;
        case 6: _t->on_ZmenaStavu((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->on_ZmenaStavuSpojeni((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->on_PrijmiData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
