#ifndef TEST_SENTENCE_COMPARE_H
#define TEST_SENTENCE_COMPARE_H
#include <QtTest/QtTest>
#include <word.h>
#include <QTest>

class test_sentence_compare: public QObject
{
    Q_OBJECT

public:
    explicit test_sentence_compare(QObject *parent = 0);

private slots:
    void testNoErrors();
    void testSingleErrorInSentence();
    void testMultipleErrorsInSentence();
    void testErrorInEachPartOfSpeech();
    void testErrorInEveryWord();
    void testErrorInNoun();
    void testErrorInAdjective();
    void testErrorInNumeral();
    void testComplexErrorNounVerb();
    void testComplexErrorAdjectiveNumeral();
};

#endif // TEST_SENTENCE_COMPARE_H
