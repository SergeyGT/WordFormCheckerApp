#ifndef TEST_WORD_FINDMISTAKENOUN_H
#define TEST_WORD_FINDMISTAKENOUN_H
#include <QtTest/QtTest>
#include <word.h>

class TestWordfindMistakeNoun : public QObject {
    Q_OBJECT

public:
    explicit TestWordfindMistakeNoun(QObject *parent = 0);

private slots:
    void testPossessiveSingularNoun();
    void testPossessivePluralNoun();
    void testPossessivePluralNounAndEndS();
    void testPossessivePluralNounAndEndES();
    void testPossessivePluralNounEndES();
    void testOnlyPluralformNoun();
    void testIrregularFormNoun();
    void testNounEndS();
    void testNounEndS1();
    void testNounEndS2();
    void testNounEndEs();
    void testNounEndEs1();
    void testNounEndEs2();
    void testNounEndEs3();
    void testNounZeroMistakes();
};

#endif // TEST_WORD_FINDMISTAKENOUN_H
