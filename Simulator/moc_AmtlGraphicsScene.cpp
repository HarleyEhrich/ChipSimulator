/****************************************************************************
** Meta object code from reading C++ file 'AmtlGraphicsScene.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Widgets/Graphics/AmtlGraphicsScene.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AmtlGraphicsScene.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AmtlGraphicsScene_t {
    uint offsetsAndSizes[28];
    char stringdata0[18];
    char stringdata1[17];
    char stringdata2[1];
    char stringdata3[10];
    char stringdata4[5];
    char stringdata5[9];
    char stringdata6[24];
    char stringdata7[8];
    char stringdata8[20];
    char stringdata9[9];
    char stringdata10[23];
    char stringdata11[11];
    char stringdata12[22];
    char stringdata13[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AmtlGraphicsScene_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_AmtlGraphicsScene_t qt_meta_stringdata_AmtlGraphicsScene = {
    {
        QT_MOC_LITERAL(0, 17),  // "AmtlGraphicsScene"
        QT_MOC_LITERAL(18, 16),  // "requestToastInfo"
        QT_MOC_LITERAL(35, 0),  // ""
        QT_MOC_LITERAL(36, 9),  // "infoTitle"
        QT_MOC_LITERAL(46, 4),  // "info"
        QT_MOC_LITERAL(51, 8),  // "autoHide"
        QT_MOC_LITERAL(60, 23),  // "AMTL::ToastInfoPosition"
        QT_MOC_LITERAL(84, 7),  // "showPos"
        QT_MOC_LITERAL(92, 19),  // "AMTL::ToastInfoType"
        QT_MOC_LITERAL(112, 8),  // "infoType"
        QT_MOC_LITERAL(121, 22),  // "pairUniConnectionPoint"
        QT_MOC_LITERAL(144, 10),  // "linkStatus"
        QT_MOC_LITERAL(155, 21),  // "UniConnectionPointPtr"
        QT_MOC_LITERAL(177, 6)   // "target"
    },
    "AmtlGraphicsScene",
    "requestToastInfo",
    "",
    "infoTitle",
    "info",
    "autoHide",
    "AMTL::ToastInfoPosition",
    "showPos",
    "AMTL::ToastInfoType",
    "infoType",
    "pairUniConnectionPoint",
    "linkStatus",
    "UniConnectionPointPtr",
    "target"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AmtlGraphicsScene[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    5,   44,    2, 0x06,    1 /* Public */,
       1,    4,   55,    2, 0x26,    7 /* Public | MethodCloned */,
       1,    3,   64,    2, 0x26,   12 /* Public | MethodCloned */,
       1,    2,   71,    2, 0x26,   16 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    2,   76,    2, 0x0a,   19 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, 0x80000000 | 6, 0x80000000 | 8,    3,    4,    5,    7,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool, 0x80000000 | 6,    3,    4,    5,    7,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::Bool,    3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, 0x80000000 | 12,   11,   13,

       0        // eod
};

void AmtlGraphicsScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AmtlGraphicsScene *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->requestToastInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<AMTL::ToastInfoPosition>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<AMTL::ToastInfoType>>(_a[5]))); break;
        case 1: _t->requestToastInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<AMTL::ToastInfoPosition>>(_a[4]))); break;
        case 2: _t->requestToastInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<bool>>(_a[3]))); break;
        case 3: _t->requestToastInfo((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QString>>(_a[2]))); break;
        case 4: _t->pairUniConnectionPoint((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<UniConnectionPointPtr>>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AmtlGraphicsScene::*)(QString , QString , bool , AMTL::ToastInfoPosition , AMTL::ToastInfoType );
            if (_t _q_method = &AmtlGraphicsScene::requestToastInfo; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject AmtlGraphicsScene::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsScene::staticMetaObject>(),
    qt_meta_stringdata_AmtlGraphicsScene.offsetsAndSizes,
    qt_meta_data_AmtlGraphicsScene,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AmtlGraphicsScene_t
, QtPrivate::TypeAndForceComplete<AmtlGraphicsScene, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<AMTL::ToastInfoPosition, std::false_type>, QtPrivate::TypeAndForceComplete<AMTL::ToastInfoType, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<AMTL::ToastInfoPosition, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>, QtPrivate::TypeAndForceComplete<QString, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<bool, std::false_type>, QtPrivate::TypeAndForceComplete<UniConnectionPointPtr, std::false_type>


>,
    nullptr
} };


const QMetaObject *AmtlGraphicsScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AmtlGraphicsScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AmtlGraphicsScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int AmtlGraphicsScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void AmtlGraphicsScene::requestToastInfo(QString _t1, QString _t2, bool _t3, AMTL::ToastInfoPosition _t4, AMTL::ToastInfoType _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
