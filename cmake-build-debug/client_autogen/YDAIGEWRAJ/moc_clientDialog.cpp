/****************************************************************************
** Meta object code from reading C++ file 'clientDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client/include/clientDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'clientDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientDialog_t {
    QByteArrayData data[12];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientDialog_t qt_meta_stringdata_ClientDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ClientDialog"
QT_MOC_LITERAL(1, 13, 14), // "connectClicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 14), // "updateProgress"
QT_MOC_LITERAL(4, 44, 23), // "onConnectionEstablished"
QT_MOC_LITERAL(5, 68, 17), // "onConnectionError"
QT_MOC_LITERAL(6, 86, 31), // "onShowMessageClientNotAvailable"
QT_MOC_LITERAL(7, 118, 15), // "validateAddress"
QT_MOC_LITERAL(8, 134, 9), // "ipAddress"
QT_MOC_LITERAL(9, 144, 12), // "validatePort"
QT_MOC_LITERAL(10, 157, 4), // "port"
QT_MOC_LITERAL(11, 162, 18) // "onShutClientDialog"

    },
    "ClientDialog\0connectClicked\0\0"
    "updateProgress\0onConnectionEstablished\0"
    "onConnectionError\0onShowMessageClientNotAvailable\0"
    "validateAddress\0ipAddress\0validatePort\0"
    "port\0onShutClientDialog"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    1,   59,    2, 0x08 /* Private */,
       9,    1,   62,    2, 0x08 /* Private */,
      11,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,

       0        // eod
};

void ClientDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ClientDialog *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->connectClicked(); break;
        case 1: _t->updateProgress(); break;
        case 2: _t->onConnectionEstablished(); break;
        case 3: _t->onConnectionError(); break;
        case 4: _t->onShowMessageClientNotAvailable(); break;
        case 5: _t->validateAddress((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->validatePort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->onShutClientDialog(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ClientDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ClientDialog.data,
    qt_meta_data_ClientDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ClientDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ClientDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
