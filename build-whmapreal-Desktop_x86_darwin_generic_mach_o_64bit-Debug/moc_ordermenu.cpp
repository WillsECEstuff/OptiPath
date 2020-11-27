/****************************************************************************
** Meta object code from reading C++ file 'ordermenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../WarehouseApp/ordermenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ordermenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ordermenu_t {
    QByteArrayData data[9];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ordermenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ordermenu_t qt_meta_stringdata_ordermenu = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ordermenu"
QT_MOC_LITERAL(1, 10, 13), // "onOtherSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 21), // "onOrderCompleteSignal"
QT_MOC_LITERAL(4, 47, 16), // "onSettingsSignal"
QT_MOC_LITERAL(5, 64, 17), // "handleRouteButton"
QT_MOC_LITERAL(6, 82, 23), // "handleCreateOrderButton"
QT_MOC_LITERAL(7, 106, 18), // "handleSingleButton"
QT_MOC_LITERAL(8, 125, 20) // "handleSettingsButton"

    },
    "ordermenu\0onOtherSignal\0\0onOrderCompleteSignal\0"
    "onSettingsSignal\0handleRouteButton\0"
    "handleCreateOrderButton\0handleSingleButton\0"
    "handleSettingsButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ordermenu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ordermenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ordermenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onOtherSignal(); break;
        case 1: _t->onOrderCompleteSignal(); break;
        case 2: _t->onSettingsSignal(); break;
        case 3: _t->handleRouteButton(); break;
        case 4: _t->handleCreateOrderButton(); break;
        case 5: _t->handleSingleButton(); break;
        case 6: _t->handleSettingsButton(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ordermenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ordermenu.data,
    qt_meta_data_ordermenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ordermenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ordermenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ordermenu.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ordermenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
