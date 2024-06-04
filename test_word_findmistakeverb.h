#ifndef TEST_WORD_FINDMISTAKEVERB_H
#define TEST_WORD_FINDMISTAKEVERB_H
#include <QtTest/QtTest>
#include <word.h>

class Test_word_findMistakeVerb : public QObject {
    Q_OBJECT

public:
    explicit Test_word_findMistakeVerb(QObject *parent = 0);

private slots:
    void testDoubleConsonantBeforeEdVerb();
    void testDoubleConsonantBeforeIngVerb();
    void testIrregularVerbForm();
    void testIrregularVerbForm1();
    void testVerbEndsWithEs();
    void testVerbEndsWithS();
    void testVerbDropE();
    void testIrregularVerbIngForm();
    void testSaveEBeforeS();
    void bothWordsNotVerb();
    void incorrectWordNotVerb();
    void correctWordNotVerb();
    void testNoErrorsFound();
};

#endif // TEST_WORD_FINDMISTAKEVERB_H
