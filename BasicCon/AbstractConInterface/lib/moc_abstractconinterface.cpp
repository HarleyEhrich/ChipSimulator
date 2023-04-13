/****************************************************************************
** Meta object code from reading C++ file 'abstractconinterface.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../AMTL_Simulator/AbstractConInterface/abstractconinterface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractconinterface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AbstractConInterface_t {
    uint offsetsAndSizes[44];
    char stringdata0[21];
    char stringdata1[7];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[4];
    char stringdata5[14];
    char stringdata6[8];
    char stringdata7[16];
    char stringdata8[12];
    char stringdata9[9];
    char stringdata10[7];
    char stringdata11[6];
    char stringdata12[22];
    char stringdata13[8];
    char stringdata14[4];
    char stringdata15[19];
    char stringdata16[5];
    char stringdata17[17];
    char stringdata18[9];
    char stringdata19[17];
    char stringdata20[16];
    char stringdata21[17];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AbstractConInterface_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_AbstractConInterface_t qt_meta_stringdata_AbstractConInterface = {
    {
        QT_MOC_LITERAL(0, 20),  // "AbstractConInterface"
        QT_MOC_LITERAL(21, 6),  // "newLog"
        QT_MOC_LITERAL(28, 0),  // ""
        QT_MOC_LITERAL(29, 9),  // "senderMsg"
        QT_MOC_LITERAL(39, 3),  // "msg"
        QT_MOC_LITERAL(43, 13),  // "amtl::MSGTYPE"
        QT_MOC_LITERAL(57, 7),  // "msgType"
        QT_MOC_LITERAL(65, 15),  // "newPannelWidget"
        QT_MOC_LITERAL(81, 11),  // "pannelTitle"
        QT_MOC_LITERAL(93, 8),  // "QWidget*"
        QT_MOC_LITERAL(102, 6),  // "pannel"
        QT_MOC_LITERAL(109, 5),  // "creat"
        QT_MOC_LITERAL(115, 21),  // "AbstractConInterface*"
        QT_MOC_LITERAL(137, 7),  // "sceneId"
        QT_MOC_LITERAL(145, 3),  // "run"
        QT_MOC_LITERAL(149, 18),  // "loadStatusFormText"
        QT_MOC_LITERAL(168, 4),  // "text"
        QT_MOC_LITERAL(173, 16),  // "saveStatusToText"
        QT_MOC_LITERAL(190, 8),  // "QString&"
        QT_MOC_LITERAL(199, 16),  // "getSetWidgetsVec"
        QT_MOC_LITERAL(216, 15),  // "QList<QWidget*>"
        QT_MOC_LITERAL(232, 16)   // "getSettingPannel"
    },
    "AbstractConInterface",
    "newLog",
    "",
    "senderMsg",
    "msg",
    "amtl::MSGTYPE",
    "msgType",
    "newPannelWidget",
    "pannelTitle",
    "QWidget*",
    "pannel",
    "creat",
    "AbstractConInterface*",
    "sceneId",
    "run",
    "loadStatusFormText",
    "text",
    "saveStatusToText",
    "QString&",
    "getSetWidgetsVec",
    "QList<QWidget*>",
    "getSettingPannel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractConInterface[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    3,   62,    2, 0x06,    1 /* Public */,
       7,    3,   69,    2, 0x06,    5 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      11,    1,   76,    2, 0x0a,    9 /* Public */,
      14,    0,   79,    2, 0x0a,   11 /* Public */,
      15,    1,   80,    2, 0x0a,   12 /* Public */,
      17,    1,   83,    2, 0x0a,   14 /* Public */,
      19,    0,   86,    2, 0x0a,   16 /* Public */,
      21,    0,   87,    2, 0x0a,   17 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 5,    3,    4,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, 0x80000000 | 9,    3,    8,   10,

 // slots: parameters
    0x80000000 | 12, QMetaType::Long,   13,
    QMetaType::Void,
    QMetaType::Bool, QMetaType::QString,   16,
    QMetaType::Bool, 0x80000000 | 18,   16,
    0x80000000 | 20,
    0x80000000 | 9,

       0        // eod
};

void AbstractConInterface::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AbstractConInterface *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->newLog((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<amtl::MSGTYPE>>(_a[3]))); break;
        case 1: _t->newPannelWidget((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<QWidget*>>(_a[3]))); break;
        case 2: { AbstractConInterface* _r = _t->creat((*reinterpret_cast< std::add_pointer_t<long>>(_a[1])));
            if (_a[0]) *reinterpret_cast< AbstractConInterface**>(_a[0]) = std::move(_r); }  break;
        case 3: _t->run(); break;
        case 4: { bool _r = _t->loadStatusFormText((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: { bool _r = _t->saveStatusToText((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 6: { QList<QWidget*> _r = _t->getSetWidgetsVec();
            if (_a[0]) *reinterpret_cast< QList<QWidget*>*>(_a[0]) = std::move(_r); }  break;
        case 7: { QWidget* _r = _t->getSettingPannel();
            if (_a[0]) *reinterpret_cast< QWidget**>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 2:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AbstractConInterface::*)(const QString & , const QString & , amtl::MSGTYPE );
            if (_t _q_method = &AbstractConInterface::newLog; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AbstractConInterface::*)(const QString & , const QString & , QWidget * );
            if (_t _q_method = &AbstractConInterface::newPannelWidget; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AbstractConInterface::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_AbstractConInterface.offsetsAndSizes,
    qt_meta_data_AbstractConInterface,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AbstractConInterface_t
, QtPrivate::TypeAndForceComplete<AbstractConInterface, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<amtl::MSGTYPE, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>
, QtPrivate::TypeAndForceComplete<AbstractConInterface *, std::false_type>, QtPrivate::TypeAndForceComplete<long, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<QString &, std::false_type>, QtPrivate::TypeAndForceComplete<QVector<QWidget*>, std::false_type>, QtPrivate::TypeAndForceComplete<QWidget *, std::false_type>


>,
    nullptr
} };


const QMetaObject *AbstractConInterface::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractConInterface::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractConInterface.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    if (!strcmp(_clname, "org.qt-project.Qt.QGraphicsItem"))
        return static_cast< QGraphicsItem*>(this);
    return QObject::qt_metacast(_clname);
}

int AbstractConInterface::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void AbstractConInterface::newLog(const QString & _t1, const QString & _t2, amtl::MSGTYPE _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AbstractConInterface::newPannelWidget(const QString & _t1, const QString & _t2, QWidget * _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
