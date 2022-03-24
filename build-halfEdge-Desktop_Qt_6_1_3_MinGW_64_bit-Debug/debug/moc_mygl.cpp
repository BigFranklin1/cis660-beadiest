/****************************************************************************
** Meta object code from reading C++ file 'mygl.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.1.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../assignment_package/src/mygl.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mygl.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.1.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MyGL_t {
    const uint offsetsAndSize[100];
    char stringdata0[618];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MyGL_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MyGL_t qt_meta_stringdata_MyGL = {
    {
QT_MOC_LITERAL(0, 4), // "MyGL"
QT_MOC_LITERAL(5, 18), // "sig_sendVertexData"
QT_MOC_LITERAL(24, 0), // ""
QT_MOC_LITERAL(25, 5), // "Mesh*"
QT_MOC_LITERAL(31, 4), // "mesh"
QT_MOC_LITERAL(36, 16), // "sig_sendFaceData"
QT_MOC_LITERAL(53, 20), // "sig_sendHalfEdgeData"
QT_MOC_LITERAL(74, 17), // "sig_sendJointData"
QT_MOC_LITERAL(92, 9), // "Skeleton*"
QT_MOC_LITERAL(102, 8), // "skeleton"
QT_MOC_LITERAL(111, 28), // "slot_highlightSelectedVertex"
QT_MOC_LITERAL(140, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(157, 1), // "v"
QT_MOC_LITERAL(159, 26), // "slot_highlightSelectedFace"
QT_MOC_LITERAL(186, 1), // "f"
QT_MOC_LITERAL(188, 30), // "slot_highlightSelectedHalfEdge"
QT_MOC_LITERAL(219, 2), // "he"
QT_MOC_LITERAL(222, 27), // "slot_highlightSelectedJoint"
QT_MOC_LITERAL(250, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(267, 5), // "joint"
QT_MOC_LITERAL(273, 10), // "slot_vertX"
QT_MOC_LITERAL(284, 1), // "x"
QT_MOC_LITERAL(286, 10), // "slot_vertY"
QT_MOC_LITERAL(297, 1), // "y"
QT_MOC_LITERAL(299, 10), // "slot_vertZ"
QT_MOC_LITERAL(310, 1), // "z"
QT_MOC_LITERAL(312, 10), // "slot_faceR"
QT_MOC_LITERAL(323, 1), // "r"
QT_MOC_LITERAL(325, 10), // "slot_faceG"
QT_MOC_LITERAL(336, 1), // "g"
QT_MOC_LITERAL(338, 10), // "slot_faceB"
QT_MOC_LITERAL(349, 1), // "b"
QT_MOC_LITERAL(351, 14), // "slot_splitEdge"
QT_MOC_LITERAL(366, 16), // "slot_triangulate"
QT_MOC_LITERAL(383, 16), // "slot_subdivision"
QT_MOC_LITERAL(400, 12), // "slot_loadOBJ"
QT_MOC_LITERAL(413, 13), // "slot_loadJSON"
QT_MOC_LITERAL(427, 14), // "loadJSONHelper"
QT_MOC_LITERAL(442, 6), // "Joint*"
QT_MOC_LITERAL(449, 6), // "parent"
QT_MOC_LITERAL(456, 17), // "slot_meshSkinning"
QT_MOC_LITERAL(474, 14), // "slot_jointRotX"
QT_MOC_LITERAL(489, 14), // "slot_jointRotY"
QT_MOC_LITERAL(504, 14), // "slot_jointRotZ"
QT_MOC_LITERAL(519, 17), // "slot_jointRotNegX"
QT_MOC_LITERAL(537, 17), // "slot_jointRotNegY"
QT_MOC_LITERAL(555, 17), // "slot_jointRotNegZ"
QT_MOC_LITERAL(573, 14), // "slot_jointPosX"
QT_MOC_LITERAL(588, 14), // "slot_jointPosY"
QT_MOC_LITERAL(603, 14) // "slot_jointPosZ"

    },
    "MyGL\0sig_sendVertexData\0\0Mesh*\0mesh\0"
    "sig_sendFaceData\0sig_sendHalfEdgeData\0"
    "sig_sendJointData\0Skeleton*\0skeleton\0"
    "slot_highlightSelectedVertex\0"
    "QListWidgetItem*\0v\0slot_highlightSelectedFace\0"
    "f\0slot_highlightSelectedHalfEdge\0he\0"
    "slot_highlightSelectedJoint\0"
    "QTreeWidgetItem*\0joint\0slot_vertX\0x\0"
    "slot_vertY\0y\0slot_vertZ\0z\0slot_faceR\0"
    "r\0slot_faceG\0g\0slot_faceB\0b\0slot_splitEdge\0"
    "slot_triangulate\0slot_subdivision\0"
    "slot_loadOBJ\0slot_loadJSON\0loadJSONHelper\0"
    "Joint*\0parent\0slot_meshSkinning\0"
    "slot_jointRotX\0slot_jointRotY\0"
    "slot_jointRotZ\0slot_jointRotNegX\0"
    "slot_jointRotNegY\0slot_jointRotNegZ\0"
    "slot_jointPosX\0slot_jointPosY\0"
    "slot_jointPosZ"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyGL[] = {

 // content:
       9,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,  194,    2, 0x06,    0 /* Public */,
       5,    1,  197,    2, 0x06,    2 /* Public */,
       6,    1,  200,    2, 0x06,    4 /* Public */,
       7,    1,  203,    2, 0x06,    6 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    1,  206,    2, 0x0a,    8 /* Public */,
      13,    1,  209,    2, 0x0a,   10 /* Public */,
      15,    1,  212,    2, 0x0a,   12 /* Public */,
      17,    1,  215,    2, 0x0a,   14 /* Public */,
      20,    1,  218,    2, 0x0a,   16 /* Public */,
      22,    1,  221,    2, 0x0a,   18 /* Public */,
      24,    1,  224,    2, 0x0a,   20 /* Public */,
      26,    1,  227,    2, 0x0a,   22 /* Public */,
      28,    1,  230,    2, 0x0a,   24 /* Public */,
      30,    1,  233,    2, 0x0a,   26 /* Public */,
      32,    0,  236,    2, 0x0a,   28 /* Public */,
      33,    0,  237,    2, 0x0a,   29 /* Public */,
      34,    0,  238,    2, 0x0a,   30 /* Public */,
      35,    0,  239,    2, 0x0a,   31 /* Public */,
      36,    0,  240,    2, 0x0a,   32 /* Public */,
      37,    1,  241,    2, 0x0a,   33 /* Public */,
      40,    0,  244,    2, 0x0a,   35 /* Public */,
      41,    0,  245,    2, 0x0a,   36 /* Public */,
      42,    0,  246,    2, 0x0a,   37 /* Public */,
      43,    0,  247,    2, 0x0a,   38 /* Public */,
      44,    0,  248,    2, 0x0a,   39 /* Public */,
      45,    0,  249,    2, 0x0a,   40 /* Public */,
      46,    0,  250,    2, 0x0a,   41 /* Public */,
      47,    1,  251,    2, 0x0a,   42 /* Public */,
      48,    1,  254,    2, 0x0a,   44 /* Public */,
      49,    1,  257,    2, 0x0a,   46 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 11,   14,
    QMetaType::Void, 0x80000000 | 11,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, QMetaType::Double,   21,
    QMetaType::Void, QMetaType::Double,   23,
    QMetaType::Void, QMetaType::Double,   25,
    QMetaType::Void, QMetaType::Double,   27,
    QMetaType::Void, QMetaType::Double,   29,
    QMetaType::Void, QMetaType::Double,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 38, QMetaType::QJsonObject,   39,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void, QMetaType::Double,   12,
    QMetaType::Void, QMetaType::Double,   12,

       0        // eod
};

void MyGL::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyGL *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->sig_sendVertexData((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 1: _t->sig_sendFaceData((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 2: _t->sig_sendHalfEdgeData((*reinterpret_cast< Mesh*(*)>(_a[1]))); break;
        case 3: _t->sig_sendJointData((*reinterpret_cast< Skeleton*(*)>(_a[1]))); break;
        case 4: _t->slot_highlightSelectedVertex((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->slot_highlightSelectedFace((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->slot_highlightSelectedHalfEdge((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->slot_highlightSelectedJoint((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->slot_vertX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 9: _t->slot_vertY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 10: _t->slot_vertZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 11: _t->slot_faceR((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 12: _t->slot_faceG((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 13: _t->slot_faceB((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 14: _t->slot_splitEdge(); break;
        case 15: _t->slot_triangulate(); break;
        case 16: _t->slot_subdivision(); break;
        case 17: _t->slot_loadOBJ(); break;
        case 18: _t->slot_loadJSON(); break;
        case 19: { Joint* _r = _t->loadJSONHelper((*reinterpret_cast< QJsonObject(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< Joint**>(_a[0]) = std::move(_r); }  break;
        case 20: _t->slot_meshSkinning(); break;
        case 21: _t->slot_jointRotX(); break;
        case 22: _t->slot_jointRotY(); break;
        case 23: _t->slot_jointRotZ(); break;
        case 24: _t->slot_jointRotNegX(); break;
        case 25: _t->slot_jointRotNegY(); break;
        case 26: _t->slot_jointRotNegZ(); break;
        case 27: _t->slot_jointPosX((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 28: _t->slot_jointPosY((*reinterpret_cast< double(*)>(_a[1]))); break;
        case 29: _t->slot_jointPosZ((*reinterpret_cast< double(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendVertexData)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendFaceData)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyGL::*)(Mesh * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendHalfEdgeData)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyGL::*)(Skeleton * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyGL::sig_sendJointData)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject MyGL::staticMetaObject = { {
    QMetaObject::SuperData::link<OpenGLContext::staticMetaObject>(),
    qt_meta_stringdata_MyGL.offsetsAndSize,
    qt_meta_data_MyGL,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MyGL_t
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Mesh *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Mesh *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Mesh *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Skeleton *, std::false_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QListWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QTreeWidgetItem *, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<Joint *, std::false_type>, QtPrivate::TypeAndForceComplete<QJsonObject, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<double, std::false_type>


>,
    nullptr
} };


const QMetaObject *MyGL::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyGL::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyGL.stringdata0))
        return static_cast<void*>(this);
    return OpenGLContext::qt_metacast(_clname);
}

int MyGL::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = OpenGLContext::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void MyGL::sig_sendVertexData(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MyGL::sig_sendFaceData(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MyGL::sig_sendHalfEdgeData(Mesh * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyGL::sig_sendJointData(Skeleton * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
