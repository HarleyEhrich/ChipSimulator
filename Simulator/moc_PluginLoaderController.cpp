/****************************************************************************
** Meta object code from reading C++ file 'PluginLoaderController.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "ControlObj/PluginLoaderController.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PluginLoaderController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PluginLoaderController_t {
    uint offsetsAndSizes[8];
    char stringdata0[23];
    char stringdata1[15];
    char stringdata2[1];
    char stringdata3[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_PluginLoaderController_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_PluginLoaderController_t qt_meta_stringdata_PluginLoaderController = {
    {
        QT_MOC_LITERAL(0, 22),  // "PluginLoaderController"
        QT_MOC_LITERAL(23, 14),  // "pluginLoadDone"
        QT_MOC_LITERAL(38, 0),  // ""
        QT_MOC_LITERAL(39, 17)   // "componentNameList"
    },
    "PluginLoaderController",
    "pluginLoadDone",
    "",
    "componentNameList"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PluginLoaderController[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   20,    2, 0x06,    1 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QStringList,    3,

       0        // eod
};

void PluginLoaderController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginLoaderController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pluginLoadDone((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PluginLoaderController::*)(const QStringList & );
            if (_t _q_method = &PluginLoaderController::pluginLoadDone; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PluginLoaderController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_PluginLoaderController.offsetsAndSizes,
    qt_meta_data_PluginLoaderController,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PluginLoaderController_t
, QtPrivate::TypeAndForceComplete<PluginLoaderController, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>



>,
    nullptr
} };


const QMetaObject *PluginLoaderController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginLoaderController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PluginLoaderController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PluginLoaderController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void PluginLoaderController::pluginLoadDone(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE