#ifndef TEST_WORD_FINDMISTAKENUM_H
#define TEST_WORD_FINDMISTAKENUM_H
#include <QtTest/QtTest>
#include <word.h>

class test_word_findMistakeNum : public QObject {
    Q_OBJECT

public:
    explicit test_word_findMistakeNum(QObject *parent = 0);

private slots:
    void testNumeralException();
    void testIncorrectNumeralFormTh();
    void testIncorrectNumeralFormFth();
    void testIncorrectNumeralFormIeth();
    void testNoMistakesInNumeral();

};

#endif // TEST_WORD_FINDMISTAKENUM_H
