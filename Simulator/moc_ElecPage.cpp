/****************************************************************************
** Meta object code from reading C++ file 'ElecPage.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "Pages/ElecPages/ElecPage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ElecPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ElecPage_t {
    uint offsetsAndSizes[8];
    char stringdata0[9];
    char stringdata1[27];
    char stringdata2[1];
    char stringdata3[28];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ElecPage_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ElecPage_t qt_meta_stringdata_ElecPage = {
    {
        QT_MOC_LITERAL(0, 8),  // "ElecPage"
        QT_MOC_LITERAL(9, 26),  // "on_new_project_btn_clicked"
        QT_MOC_LITERAL(36, 0),  // ""
        QT_MOC_LITERAL(37, 27)   // "on_open_project_btn_clicked"
    },
    "ElecPage",
    "on_new_project_btn_clicked",
    "",
    "on_open_project_btn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElecPage[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   26,    2, 0x08,    1 /* Private */,
       3,    0,   27,    2, 0x08,    2 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ElecPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ElecPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_new_project_btn_clicked(); break;
        case 1: _t->on_open_project_btn_clicked(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject ElecPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ElecPage.offsetsAndSizes,
    qt_meta_data_ElecPage,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ElecPage_t
, QtPrivate::TypeAndForceComplete<ElecPage, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *ElecPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElecPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElecPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ElecPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 2;
    }
    return _id;
}
struct qt_meta_stringdata_ElecPageGener_t {
    uint offsetsAndSizes[2];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_ElecPageGener_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_ElecPageGener_t qt_meta_stringdata_ElecPageGener = {
    {
        QT_MOC_LITERAL(0, 13)   // "ElecPageGener"
    },
    "ElecPageGener"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ElecPageGener[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ElecPageGener::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

const QMetaObject ElecPageGener::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ElecPageGener.offsetsAndSizes,
    qt_meta_data_ElecPageGener,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_ElecPageGener_t
, QtPrivate::TypeAndForceComplete<ElecPageGener, std::true_type>



>,
    nullptr
} };


const QMetaObject *ElecPageGener::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ElecPageGener::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ElecPageGener.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "TabPageGenerator"))
        return static_cast< TabPageGenerator*>(this);
    return QObject::qt_metacast(_clname);
}

int ElecPageGener::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
