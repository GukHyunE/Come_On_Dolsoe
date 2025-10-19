/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[19];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 15), // "connectToServer"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "onConnected"
QT_MOC_LITERAL(4, 40, 11), // "onReadyRead"
QT_MOC_LITERAL(5, 52, 14), // "onDisconnected"
QT_MOC_LITERAL(6, 67, 17), // "onPasswordEntered"
QT_MOC_LITERAL(7, 85, 8), // "password"
QT_MOC_LITERAL(8, 94, 11), // "updateTexts"
QT_MOC_LITERAL(9, 106, 18), // "updateImageDisplay"
QT_MOC_LITERAL(10, 125, 17), // "publishMp3Command"
QT_MOC_LITERAL(11, 143, 5), // "track"
QT_MOC_LITERAL(12, 149, 19), // "on_langKrPB_clicked"
QT_MOC_LITERAL(13, 169, 19), // "on_langEnPB_clicked"
QT_MOC_LITERAL(14, 189, 18), // "on_carryPB_clicked"
QT_MOC_LITERAL(15, 208, 19), // "on_naviCB_activated"
QT_MOC_LITERAL(16, 228, 5), // "index"
QT_MOC_LITERAL(17, 234, 17), // "on_tempPB_clicked"
QT_MOC_LITERAL(18, 252, 16) // "on_endCB_clicked"

    },
    "MainWindow\0connectToServer\0\0onConnected\0"
    "onReadyRead\0onDisconnected\0onPasswordEntered\0"
    "password\0updateTexts\0updateImageDisplay\0"
    "publishMp3Command\0track\0on_langKrPB_clicked\0"
    "on_langEnPB_clicked\0on_carryPB_clicked\0"
    "on_naviCB_activated\0index\0on_tempPB_clicked\0"
    "on_endCB_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       3,    0,   85,    2, 0x08 /* Private */,
       4,    0,   86,    2, 0x08 /* Private */,
       5,    0,   87,    2, 0x08 /* Private */,
       6,    1,   88,    2, 0x08 /* Private */,
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      12,    0,   96,    2, 0x08 /* Private */,
      13,    0,   97,    2, 0x08 /* Private */,
      14,    0,   98,    2, 0x08 /* Private */,
      15,    1,   99,    2, 0x08 /* Private */,
      17,    0,  102,    2, 0x08 /* Private */,
      18,    0,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connectToServer(); break;
        case 1: _t->onConnected(); break;
        case 2: _t->onReadyRead(); break;
        case 3: _t->onDisconnected(); break;
        case 4: _t->onPasswordEntered((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->updateTexts(); break;
        case 6: _t->updateImageDisplay(); break;
        case 7: _t->publishMp3Command((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_langKrPB_clicked(); break;
        case 9: _t->on_langEnPB_clicked(); break;
        case 10: _t->on_carryPB_clicked(); break;
        case 11: _t->on_naviCB_activated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->on_tempPB_clicked(); break;
        case 13: _t->on_endCB_clicked(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
