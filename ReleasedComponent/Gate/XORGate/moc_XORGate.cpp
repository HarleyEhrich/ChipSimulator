/****************************************************************************
** Meta object code from reading C++ file 'XORGate.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "XORGate.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'XORGate.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_XORGate_t {
    uint offsetsAndSizes[6];
    char stringdata0[8];
    char stringdata1[4];
    char stringdata2[1];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_XORGate_t::offsetsAndSizes) + ofs), len 
static const qt_meta_stringdata_XORGate_t qt_meta_stringdata_XORGate = {
    {
        QT_MOC_LITERAL(0, 7),  // "XORGate"
        QT_MOC_LITERAL(8, 3),  // "run"
        QT_MOC_LITERAL(12, 0)   // ""
    },
    "XORGate",
    "run",
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_XORGate[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   20,    2, 0x0a,    1 /* Public */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void XORGate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<XORGate *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->run(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject XORGate::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractConInterface::staticMetaObject>(),
    qt_meta_stringdata_XORGate.offsetsAndSizes,
    qt_meta_data_XORGate,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_XORGate_t
, QtPrivate::TypeAndForceComplete<XORGate, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *XORGate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *XORGate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_XORGate.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "com.amtl.plugin.abstractconinterface"))
        return static_cast< AbstractConInterface*>(this);
    return AbstractConInterface::qt_metacast(_clname);
}

int XORGate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractConInterface::qt_metacall(_c, _id, _a);
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

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_XORGate[] = {
    0xbf, 
    // "IID"
    0x02,  0x78,  0x24,  'c',  'o',  'm',  '.',  'a', 
    'm',  't',  'l',  '.',  'p',  'l',  'u',  'g', 
    'i',  'n',  '.',  'a',  'b',  's',  't',  'r', 
    'a',  'c',  't',  'c',  'o',  'n',  'i',  'n', 
    't',  'e',  'r',  'f',  'a',  'c',  'e', 
    // "className"
    0x03,  0x67,  'X',  'O',  'R',  'G',  'a',  't', 
    'e', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(XORGate, XORGate, qt_pluginMetaDataV2_XORGate)
#else
QT_PLUGIN_METADATA_SECTION
static constexpr unsigned char qt_pluginMetaData_XORGate[] = {
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
    0x03,  0x67,  'X',  'O',  'R',  'G',  'a',  't', 
    'e', 
    // "MetaData"
    0x04,  0xa1,  0x64,  'K',  'e',  'y',  's',  0x80, 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(XORGate, XORGate)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
QT_END_MOC_NAMESPACE
