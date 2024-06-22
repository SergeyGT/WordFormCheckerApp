/****************************************************************************
** Meta object code from reading C++ file 'test_word_comparewords.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../test_word_comparewords.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_word_comparewords.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_test_word_compareWords_t {
    QByteArrayData data[10];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_word_compareWords_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_word_compareWords_t qt_meta_stringdata_test_word_compareWords = {
    {
QT_MOC_LITERAL(0, 0, 22), // "test_word_compareWords"
QT_MOC_LITERAL(1, 23, 28), // "testFunctionSelectionForNoun"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 28), // "testFunctionSelectionForVerb"
QT_MOC_LITERAL(4, 82, 33), // "testFunctionSelectionForAdjec..."
QT_MOC_LITERAL(5, 116, 31), // "testFunctionSelectionForNumeral"
QT_MOC_LITERAL(6, 148, 25), // "bothWordsNotCorrectPosTag"
QT_MOC_LITERAL(7, 174, 29), // "incorrectWordNotCorrectPosTag"
QT_MOC_LITERAL(8, 204, 27), // "correctWordNotCorrectPosTag"
QT_MOC_LITERAL(9, 232, 12) // "testNoErrors"

    },
    "test_word_compareWords\0"
    "testFunctionSelectionForNoun\0\0"
    "testFunctionSelectionForVerb\0"
    "testFunctionSelectionForAdjective\0"
    "testFunctionSelectionForNumeral\0"
    "bothWordsNotCorrectPosTag\0"
    "incorrectWordNotCorrectPosTag\0"
    "correctWordNotCorrectPosTag\0testNoErrors"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test_word_compareWords[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void test_word_compareWords::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test_word_compareWords *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testFunctionSelectionForNoun(); break;
        case 1: _t->testFunctionSelectionForVerb(); break;
        case 2: _t->testFunctionSelectionForAdjective(); break;
        case 3: _t->testFunctionSelectionForNumeral(); break;
        case 4: _t->bothWordsNotCorrectPosTag(); break;
        case 5: _t->incorrectWordNotCorrectPosTag(); break;
        case 6: _t->correctWordNotCorrectPosTag(); break;
        case 7: _t->testNoErrors(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject test_word_compareWords::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_test_word_compareWords.data,
    qt_meta_data_test_word_compareWords,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *test_word_compareWords::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_word_compareWords::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_test_word_compareWords.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int test_word_compareWords::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
