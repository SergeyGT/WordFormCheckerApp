#ifndef TEST_WORD_COMPAREWORDS_H
#define TEST_WORD_COMPAREWORDS_H
#include <QtTest/QtTest>
#include <word.h>

class test_word_compareWords : public QObject
{
    Q_OBJECT

public:
    explicit test_word_compareWords(QObject *parent = 0);

private slots:
    void testFunctionSelectionForNoun();
    void testFunctionSelectionForVerb();
    void testFunctionSelectionForAdjective();
    void testFunctionSelectionForNumeral();
};

#endif // TEST_WORD_COMPAREWORDS_H
