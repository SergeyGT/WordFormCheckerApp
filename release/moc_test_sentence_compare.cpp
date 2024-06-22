/****************************************************************************
** Meta object code from reading C++ file 'test_sentence_compare.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../test_sentence_compare.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_sentence_compare.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_test_sentence_compare_t {
    QByteArrayData data[12];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_sentence_compare_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_sentence_compare_t qt_meta_stringdata_test_sentence_compare = {
    {
QT_MOC_LITERAL(0, 0, 21), // "test_sentence_compare"
QT_MOC_LITERAL(1, 22, 12), // "testNoErrors"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 25), // "testSingleErrorInSentence"
QT_MOC_LITERAL(4, 62, 28), // "testMultipleErrorsInSentence"
QT_MOC_LITERAL(5, 91, 27), // "testErrorInEachPartOfSpeech"
QT_MOC_LITERAL(6, 119, 20), // "testErrorInEveryWord"
QT_MOC_LITERAL(7, 140, 15), // "testErrorInNoun"
QT_MOC_LITERAL(8, 156, 20), // "testErrorInAdjective"
QT_MOC_LITERAL(9, 177, 18), // "testErrorInNumeral"
QT_MOC_LITERAL(10, 196, 24), // "testComplexErrorNounVerb"
QT_MOC_LITERAL(11, 221, 32) // "testComplexErrorAdjectiveNumeral"

    },
    "test_sentence_compare\0testNoErrors\0\0"
    "testSingleErrorInSentence\0"
    "testMultipleErrorsInSentence\0"
    "testErrorInEachPartOfSpeech\0"
    "testErrorInEveryWord\0testErrorInNoun\0"
    "testErrorInAdjective\0testErrorInNumeral\0"
    "testComplexErrorNounVerb\0"
    "testComplexErrorAdjectiveNumeral"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test_sentence_compare[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    0,   67,    2, 0x08 /* Private */,
       6,    0,   68,    2, 0x08 /* Private */,
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
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

void test_sentence_compare::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test_sentence_compare *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testNoErrors(); break;
        case 1: _t->testSingleErrorInSentence(); break;
        case 2: _t->testMultipleErrorsInSentence(); break;
        case 3: _t->testErrorInEachPartOfSpeech(); break;
        case 4: _t->testErrorInEveryWord(); break;
        case 5: _t->testErrorInNoun(); break;
        case 6: _t->testErrorInAdjective(); break;
        case 7: _t->testErrorInNumeral(); break;
        case 8: _t->testComplexErrorNounVerb(); break;
        case 9: _t->testComplexErrorAdjectiveNumeral(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject test_sentence_compare::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_test_sentence_compare.data,
    qt_meta_data_test_sentence_compare,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *test_sentence_compare::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_sentence_compare::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_test_sentence_compare.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int test_sentence_compare::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
