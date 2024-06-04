#ifndef TEST_WORD_FINDMISTAKEADJ_H
#define TEST_WORD_FINDMISTAKEADJ_H
#include <QtTest/QtTest>
#include <word.h>

class test_word_findMistakeAdj : public QObject {
    Q_OBJECT

public:
    explicit test_word_findMistakeAdj(QObject *parent = 0);

private slots:
    void testDoubleConsonantBeforeErAdjective();
    void testDoubleConsonantBeforeEstAdjective();
    void testUnnecessarErAdj();
    void testUnnecessarEstAdj();
    void testYBeforeEr();
    void testYBeforeEst();
    void testAdjectiveException();
    void bothWordsNotAdj();
    void incorrectWordNotAdj();
    void correctWordNotAdj();
    void testNoErrorsFound();
};

#endif // TEST_WORD_FINDMISTAKEADJ_H
