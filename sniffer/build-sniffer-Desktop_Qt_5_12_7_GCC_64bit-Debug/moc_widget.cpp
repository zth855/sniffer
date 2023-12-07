/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../sniffer/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PacketCaptureThread_t {
    QByteArrayData data[11];
    char stringdata0[97];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PacketCaptureThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PacketCaptureThread_t qt_meta_stringdata_PacketCaptureThread = {
    {
QT_MOC_LITERAL(0, 0, 19), // "PacketCaptureThread"
QT_MOC_LITERAL(1, 20, 13), // "addPacketInfo"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "number"
QT_MOC_LITERAL(4, 42, 8), // "timeInfo"
QT_MOC_LITERAL(5, 51, 6), // "length"
QT_MOC_LITERAL(6, 58, 12), // "protocolType"
QT_MOC_LITERAL(7, 71, 6), // "srcMac"
QT_MOC_LITERAL(8, 78, 6), // "dstMac"
QT_MOC_LITERAL(9, 85, 5), // "srcIp"
QT_MOC_LITERAL(10, 91, 5) // "dstIp"

    },
    "PacketCaptureThread\0addPacketInfo\0\0"
    "number\0timeInfo\0length\0protocolType\0"
    "srcMac\0dstMac\0srcIp\0dstIp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PacketCaptureThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    8,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Int, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,    6,    7,    8,    9,   10,

       0        // eod
};

void PacketCaptureThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PacketCaptureThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addPacketInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4])),(*reinterpret_cast< const QString(*)>(_a[5])),(*reinterpret_cast< const QString(*)>(_a[6])),(*reinterpret_cast< const QString(*)>(_a[7])),(*reinterpret_cast< const QString(*)>(_a[8]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PacketCaptureThread::*)(int , const QString & , int , const QString & , const QString & , const QString & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PacketCaptureThread::addPacketInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PacketCaptureThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_PacketCaptureThread.data,
    qt_meta_data_PacketCaptureThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PacketCaptureThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PacketCaptureThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PacketCaptureThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int PacketCaptureThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void PacketCaptureThread::addPacketInfo(int _t1, const QString & _t2, int _t3, const QString & _t4, const QString & _t5, const QString & _t6, const QString & _t7, const QString & _t8)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)), const_cast<void*>(reinterpret_cast<const void*>(&_t7)), const_cast<void*>(reinterpret_cast<const void*>(&_t8)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[17];
    char stringdata0[290];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 24), // "on_capture_start_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 23), // "on_capture_stop_clicked"
QT_MOC_LITERAL(4, 57, 22), // "on_result_save_clicked"
QT_MOC_LITERAL(5, 80, 28), // "on_packet_reassemble_clicked"
QT_MOC_LITERAL(6, 109, 14), // "on_tcp_clicked"
QT_MOC_LITERAL(7, 124, 7), // "checked"
QT_MOC_LITERAL(8, 132, 15), // "on_icmp_clicked"
QT_MOC_LITERAL(9, 148, 15), // "on_igmp_clicked"
QT_MOC_LITERAL(10, 164, 15), // "on_ipv6_clicked"
QT_MOC_LITERAL(11, 180, 14), // "on_arp_clicked"
QT_MOC_LITERAL(12, 195, 16), // "on_other_clicked"
QT_MOC_LITERAL(13, 212, 14), // "on_udp_clicked"
QT_MOC_LITERAL(14, 227, 15), // "on_exit_clicked"
QT_MOC_LITERAL(15, 243, 24), // "on_packet_filter_clicked"
QT_MOC_LITERAL(16, 268, 21) // "print_network_traffic"

    },
    "Widget\0on_capture_start_clicked\0\0"
    "on_capture_stop_clicked\0on_result_save_clicked\0"
    "on_packet_reassemble_clicked\0"
    "on_tcp_clicked\0checked\0on_icmp_clicked\0"
    "on_igmp_clicked\0on_ipv6_clicked\0"
    "on_arp_clicked\0on_other_clicked\0"
    "on_udp_clicked\0on_exit_clicked\0"
    "on_packet_filter_clicked\0print_network_traffic"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

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
       8,    1,   91,    2, 0x08 /* Private */,
       9,    1,   94,    2, 0x08 /* Private */,
      10,    1,   97,    2, 0x08 /* Private */,
      11,    1,  100,    2, 0x08 /* Private */,
      12,    1,  103,    2, 0x08 /* Private */,
      13,    1,  106,    2, 0x08 /* Private */,
      14,    0,  109,    2, 0x08 /* Private */,
      15,    0,  110,    2, 0x08 /* Private */,
      16,    0,  111,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_capture_start_clicked(); break;
        case 1: _t->on_capture_stop_clicked(); break;
        case 2: _t->on_result_save_clicked(); break;
        case 3: _t->on_packet_reassemble_clicked(); break;
        case 4: _t->on_tcp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_icmp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_igmp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_ipv6_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_arp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_other_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->on_udp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->on_exit_clicked(); break;
        case 12: _t->on_packet_filter_clicked(); break;
        case 13: _t->print_network_traffic(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
