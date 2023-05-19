/****************************************************************************
** Meta object code from reading C++ file 'LedComponent.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "LedComponent.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LedComponent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LedComponent_t {
    uint offsetsAndSizes[10];
    char stringdata0[13];
    char stringdata1[28];
    char stringdata2[1];
    char stringdata3[9];
    char stringdata4[4];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_LedComponent_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_LedComponent_t qt_meta_stringdata_LedComponent = {
    {
        QT_MOC_LITERAL(0, 12),  // "LedComponent"
        QT_MOC_LITERAL(13, 27),  // "tellLedLightBallCountChange"
        QT_MOC_LITERAL(41, 0),  // ""
        QT_MOC_LITERAL(42, 8),  // "newCount"
        QT_MOC_LITERAL(51, 3)   // "run"
    },
    "LedComponent",
    "tellLedLightBallCountChange",
    "",
    "newCount",
    "run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LedComponent[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   26,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    0,   29,    2, 0x0a,    3 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void LedComponent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LedComponent *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->tellLedLightBallCountChange((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LedComponent::*)(int );
            if (_t _q_method = &LedComponent::tellLedLightBallCountChange; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LedComponent::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractConInterface::staticMetaObject>(),
    qt_meta_stringdata_LedComponent.offsetsAndSizes,
    qt_meta_data_LedComponent,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_LedComponent_t
, QtPrivate::TypeAndForceComplete<LedComponent, std::true_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *LedComponent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LedComponent::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LedComponent.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.amtl.plugin.abstractconinterface"))
        return static_cast< AbstractConInterface*>(this);
    return AbstractConInterface::qt_metacast(_clname);
}

int LedComponent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractConInterface::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void LedComponent::tellLedLightBallCountChange(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_LedComponent[] = {
    0xbf, 
    // "IID"
    0x02,  0x78,  0x24,  'c',  'o',  'm',  '.',  'a', 
    'm',  't',  'l',  '.',  'p',  'l',  'u',  'g', 
    'i',  'n',  '.',  'a',  'b',  's',  't',  'r', 
    'a',  'c',  't',  'c',  'o',  'n',  'i',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x6c,  'L',  'e',  'd',  'C',  'o',  'm', 
    'p',  'o',  'n',  'e',  'n',  't', 
    // "MetaData"
    0x04,  0xa3,  0x68,  'C',  'a',  't',  'e',  'g', 
    'o',  'r',  'y',  0x67,  'D',  'i',  's',  'p', 
    'l',  'a',  'y',  0x64,  'K',  'e',  'y',  's', 
    0x80,  0x63,  'T',  'a',  'g',  0x82,  0x67,  'D', 
    'i',  's',  'p',  'l',  'a',  'y',  0x63,  'L', 
    'e',  'd', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(LedComponent, LedComponent, qt_pluginMetaDataV2_LedComponent)
#else
QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_LedComponent[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x78,  0x24,  'c',  'o',  'm',  '.',  'a', 
    'm',  't',  'l',  '.',  'p',  'l',  'u',  'g', 
    'i',  'n',  '.',  'a',  'b',  's',  't',  'r', 
    'a',  'c',  't',  'c',  'o',  'n',  'i',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x6c,  'L',  'e',  'd',  'C',  'o',  'm', 
    'p',  'o',  'n',  'e',  'n',  't', 
    // "MetaData"
    0x04,  0xa3,  0x68,  'C',  'a',  't',  'e',  'g', 
    'o',  'r',  'y',  0x67,  'D',  'i',  's',  'p', 
    'l',  'a',  'y',  0x64,  'K',  'e',  'y',  's', 
    0x80,  0x63,  'T',  'a',  'g',  0x82,  0x67,  'D', 
    'i',  's',  'p',  'l',  'a',  'y',  0x63,  'L', 
    'e',  'd', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(LedComponent, LedComponent)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
QT_END_MOC_NAMESPACE
