/****************************************************************************
** Meta object code from reading C++ file 'ckernel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ckernel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ckernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CKernel_t {
    QByteArrayData data[19];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CKernel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CKernel_t qt_meta_stringdata_CKernel = {
    {
QT_MOC_LITERAL(0, 0, 7), // "CKernel"
QT_MOC_LITERAL(1, 8, 14), // "slot_ReadyData"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "ISendIp"
QT_MOC_LITERAL(4, 32, 5), // "char*"
QT_MOC_LITERAL(5, 38, 3), // "buf"
QT_MOC_LITERAL(6, 42, 4), // "nLen"
QT_MOC_LITERAL(7, 47, 19), // "slot_RegisterCommit"
QT_MOC_LITERAL(8, 67, 4), // "name"
QT_MOC_LITERAL(9, 72, 3), // "tel"
QT_MOC_LITERAL(10, 76, 8), // "password"
QT_MOC_LITERAL(11, 85, 16), // "slot_LoginCommit"
QT_MOC_LITERAL(12, 102, 16), // "slot_sendChatMsg"
QT_MOC_LITERAL(13, 119, 2), // "id"
QT_MOC_LITERAL(14, 122, 7), // "content"
QT_MOC_LITERAL(15, 130, 20), // "slot_userItemClicked"
QT_MOC_LITERAL(16, 151, 14), // "slot_addFriend"
QT_MOC_LITERAL(17, 166, 10), // "slot_close"
QT_MOC_LITERAL(18, 177, 12) // "slot_offline"

    },
    "CKernel\0slot_ReadyData\0\0ISendIp\0char*\0"
    "buf\0nLen\0slot_RegisterCommit\0name\0tel\0"
    "password\0slot_LoginCommit\0slot_sendChatMsg\0"
    "id\0content\0slot_userItemClicked\0"
    "slot_addFriend\0slot_close\0slot_offline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CKernel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    3,   54,    2, 0x0a /* Public */,
       7,    3,   61,    2, 0x0a /* Public */,
      11,    2,   68,    2, 0x0a /* Public */,
      12,    2,   73,    2, 0x0a /* Public */,
      15,    1,   78,    2, 0x0a /* Public */,
      16,    0,   81,    2, 0x0a /* Public */,
      17,    0,   82,    2, 0x0a /* Public */,
      18,    0,   83,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Long, 0x80000000 | 4, QMetaType::Int,    3,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    8,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,   13,   14,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void CKernel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CKernel *_t = static_cast<CKernel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slot_ReadyData((*reinterpret_cast< long(*)>(_a[1])),(*reinterpret_cast< char*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->slot_RegisterCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->slot_LoginCommit((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->slot_sendChatMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->slot_userItemClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->slot_addFriend(); break;
        case 6: _t->slot_close(); break;
        case 7: _t->slot_offline(); break;
        default: ;
        }
    }
}

const QMetaObject CKernel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_CKernel.data,
      qt_meta_data_CKernel,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CKernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CKernel::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CKernel.stringdata0))
        return static_cast<void*>(const_cast< CKernel*>(this));
    return QObject::qt_metacast(_clname);
}

int CKernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
