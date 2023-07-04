/****************************************************************************
** Meta object code from reading C++ file 'AmtlGraphicsView.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Widgets/Graphics/AmtlGraphicsView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AmtlGraphicsView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AmtlGraphicsView_t {
    uint offsetsAndSizes[16];
    char stringdata0[17];
    char stringdata1[12];
    char stringdata2[1];
    char stringdata3[12];
    char stringdata4[9];
    char stringdata5[12];
    char stringdata6[11];
    char stringdata7[9];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_AmtlGraphicsView_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_AmtlGraphicsView_t qt_meta_stringdata_AmtlGraphicsView = {
    {
        QT_MOC_LITERAL(0, 16),  // "AmtlGraphicsView"
        QT_MOC_LITERAL(17, 11),  // "alignBottom"
        QT_MOC_LITERAL(29, 0),  // ""
        QT_MOC_LITERAL(30, 11),  // "alignCenter"
        QT_MOC_LITERAL(42, 8),  // "alignEnd"
        QT_MOC_LITERAL(51, 11),  // "alignMiddle"
        QT_MOC_LITERAL(63, 10),  // "alignStart"
        QT_MOC_LITERAL(74, 8)   // "alignTop"
    },
    "AmtlGraphicsView",
    "alignBottom",
    "",
    "alignCenter",
    "alignEnd",
    "alignMiddle",
    "alignStart",
    "alignTop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AmtlGraphicsView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   50,    2, 0x0a,    1 /* Public */,
       3,    0,   51,    2, 0x0a,    2 /* Public */,
       4,    0,   52,    2, 0x0a,    3 /* Public */,
       5,    0,   53,    2, 0x0a,    4 /* Public */,
       6,    0,   54,    2, 0x0a,    5 /* Public */,
       7,    0,   55,    2, 0x0a,    6 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AmtlGraphicsView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AmtlGraphicsView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->alignBottom(); break;
        case 1: _t->alignCenter(); break;
        case 2: _t->alignEnd(); break;
        case 3: _t->alignMiddle(); break;
        case 4: _t->alignStart(); break;
        case 5: _t->alignTop(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject AmtlGraphicsView::staticMetaObject = { {
    QMetaObject::SuperData::link<QGraphicsView::staticMetaObject>(),
    qt_meta_stringdata_AmtlGraphicsView.offsetsAndSizes,
    qt_meta_data_AmtlGraphicsView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_AmtlGraphicsView_t
, QtPrivate::TypeAndForceComplete<AmtlGraphicsView, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *AmtlGraphicsView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AmtlGraphicsView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AmtlGraphicsView.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int AmtlGraphicsView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
