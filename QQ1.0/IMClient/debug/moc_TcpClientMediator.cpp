/****************************************************************************
** Meta object code from reading C++ file 'TcpClientMediator.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mediator/TcpClientMediator.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpClientMediator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpClientMediator_t {
    QByteArrayData data[7];
    char stringdata0[56];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpClientMediator_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpClientMediator_t qt_meta_stringdata_TcpClientMediator = {
    {
QT_MOC_LITERAL(0, 0, 17), // "TcpClientMediator"
QT_MOC_LITERAL(1, 18, 13), // "SIG_ReadyData"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 7), // "ISendIp"
QT_MOC_LITERAL(4, 41, 5), // "char*"
QT_MOC_LITERAL(5, 47, 3), // "buf"
QT_MOC_LITERAL(6, 51, 4) // "nLen"

    },
    "TcpClientMediator\0SIG_ReadyData\0\0"
    "ISendIp\0char*\0buf\0nLen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpClientMediator[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Long, 0x80000000 | 4, QMetaType::Int,    3,    5,    6,

       0        // eod
};

void TcpClientMediator::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpClientMediator *_t = static_cast<TcpClientMediator *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SIG_ReadyData((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpClientMediator::*_t)(long , char * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpClientMediator::SIG_ReadyData)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject TcpClientMediator::staticMetaObject = {
    { &INetMediator::staticMetaObject, qt_meta_stringdata_TcpClientMediator.data,
      qt_meta_data_TcpClientMediator,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpClientMediator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpClientMediator::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpClientMediator.stringdata0))
        return static_cast<void*>(const_cast< TcpClientMediator*>(this));
    return INetMediator::qt_metacast(_clname);
}

int TcpClientMediator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = INetMediator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TcpClientMediator::SIG_ReadyData(long _t1, char * _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
