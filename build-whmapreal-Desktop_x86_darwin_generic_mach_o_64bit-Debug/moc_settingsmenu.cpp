/****************************************************************************
** Meta object code from reading C++ file 'settingsmenu.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../WarehouseApp/settingsmenu.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingsmenu.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_settingsmenu_t {
    QByteArrayData data[10];
    char stringdata0[158];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_settingsmenu_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_settingsmenu_t qt_meta_stringdata_settingsmenu = {
    {
QT_MOC_LITERAL(0, 0, 12), // "settingsmenu"
QT_MOC_LITERAL(1, 13, 13), // "fromOtherMenu"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 16), // "fromSettingsMenu"
QT_MOC_LITERAL(4, 45, 21), // "handleSLocationButton"
QT_MOC_LITERAL(5, 67, 21), // "handleELocationButton"
QT_MOC_LITERAL(6, 89, 17), // "handleTimerButton"
QT_MOC_LITERAL(7, 107, 18), // "handleReturnButton"
QT_MOC_LITERAL(8, 126, 17), // "handleApplyButton"
QT_MOC_LITERAL(9, 144, 13) // "handleDevMode"

    },
    "settingsmenu\0fromOtherMenu\0\0"
    "fromSettingsMenu\0handleSLocationButton\0"
    "handleELocationButton\0handleTimerButton\0"
    "handleReturnButton\0handleApplyButton\0"
    "handleDevMode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_settingsmenu[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x06 /* Public */,
       3,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void settingsmenu::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<settingsmenu *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->fromOtherMenu(); break;
        case 1: _t->fromSettingsMenu(); break;
        case 2: _t->handleSLocationButton(); break;
        case 3: _t->handleELocationButton(); break;
        case 4: _t->handleTimerButton(); break;
        case 5: _t->handleReturnButton(); break;
        case 6: _t->handleApplyButton(); break;
        case 7: _t->handleDevMode(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (settingsmenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&settingsmenu::fromOtherMenu)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (settingsmenu::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&settingsmenu::fromSettingsMenu)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject settingsmenu::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_settingsmenu.data,
    qt_meta_data_settingsmenu,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *settingsmenu::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *settingsmenu::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_settingsmenu.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int settingsmenu::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void settingsmenu::fromOtherMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void settingsmenu::fromSettingsMenu()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
