/****************************************************************************
** Meta object code from reading C++ file 'test_word_findmistakenum.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../test_word_findmistakenum.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'test_word_findmistakenum.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_test_word_findMistakeNum_t {
    QByteArrayData data[10];
    char stringdata0[209];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_test_word_findMistakeNum_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_test_word_findMistakeNum_t qt_meta_stringdata_test_word_findMistakeNum = {
    {
QT_MOC_LITERAL(0, 0, 24), // "test_word_findMistakeNum"
QT_MOC_LITERAL(1, 25, 20), // "testNumeralException"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 26), // "testIncorrectNumeralFormTh"
QT_MOC_LITERAL(4, 74, 27), // "testIncorrectNumeralFormFth"
QT_MOC_LITERAL(5, 102, 28), // "testIncorrectNumeralFormIeth"
QT_MOC_LITERAL(6, 131, 15), // "bothWordsNotNum"
QT_MOC_LITERAL(7, 147, 19), // "incorrectWordNotNum"
QT_MOC_LITERAL(8, 167, 17), // "correctWordNotNum"
QT_MOC_LITERAL(9, 185, 23) // "testNoMistakesInNumeral"

    },
    "test_word_findMistakeNum\0testNumeralException\0"
    "\0testIncorrectNumeralFormTh\0"
    "testIncorrectNumeralFormFth\0"
    "testIncorrectNumeralFormIeth\0"
    "bothWordsNotNum\0incorrectWordNotNum\0"
    "correctWordNotNum\0testNoMistakesInNumeral"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_test_word_findMistakeNum[] = {

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

void test_word_findMistakeNum::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<test_word_findMistakeNum *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->testNumeralException(); break;
        case 1: _t->testIncorrectNumeralFormTh(); break;
        case 2: _t->testIncorrectNumeralFormFth(); break;
        case 3: _t->testIncorrectNumeralFormIeth(); break;
        case 4: _t->bothWordsNotNum(); break;
        case 5: _t->incorrectWordNotNum(); break;
        case 6: _t->correctWordNotNum(); break;
        case 7: _t->testNoMistakesInNumeral(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject test_word_findMistakeNum::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_test_word_findMistakeNum.data,
    qt_meta_data_test_word_findMistakeNum,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *test_word_findMistakeNum::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *test_word_findMistakeNum::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_test_word_findMistakeNum.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int test_word_findMistakeNum::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
