#include "test_word_findmistakeadj.h"

test_word_findMistakeAdj::test_word_findMistakeAdj(QObject *parent) :
    QObject(parent)
{

}


void test_word_findMistakeAdj::testDoubleConsonantBeforeErAdjective()
{
    Word word1;
    word1.wordText = "biger";
    word1.postag = Adj;
    word1.id = 1;

    Word word2;
    word2.wordText = "bigger";
    word2.postag = Adj;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, doubleConsonantAdjEr);
    QCOMPARE(error.idxErroneousWord, 1);
}

void test_word_findMistakeAdj::testDoubleConsonantBeforeEstAdjective()
{
    Word word1;
    word1.wordText = "bigest";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "biggest";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, doubleConsonantAdjEst);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_findMistakeAdj::testUnnecessarErAdj()
{
    Word word1;
    word1.wordText = "carefuler";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "careful";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, UnnecessarErAdj);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_findMistakeAdj::testUnnecessarEstAdj()
{
    Word word1;
    word1.wordText = "beautifulest";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "beautiful";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, UnnecessarEstAdj);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_findMistakeAdj::testAdjectiveException()
{
    Word word1;
    word1.wordText = "gooder";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "better";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, incorrectDegreesComparisonAdj);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_findMistakeAdj::testYBeforeEr()
{
    Word word1;
    word1.wordText = "carryer";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "carried";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, incorrectFormCompAdj);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_findMistakeAdj::testYBeforeEst()
{
    Word word1;
    word1.wordText = "carryest";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "carriest";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, incorrectFormSuperlatAdj);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_findMistakeAdj::testNoErrorsFound()
{
    Word word1;
    word1.wordText = "bigger";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "bigger";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeAdj(word2);
    QCOMPARE(error.error, zeroMistakes);
    QCOMPARE(error.idxErroneousWord, 2);
}
