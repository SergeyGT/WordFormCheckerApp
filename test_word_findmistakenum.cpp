#include "test_word_findmistakenum.h"

test_word_findMistakeNum::test_word_findMistakeNum(QObject *parent) :
    QObject(parent)
{

}

void test_word_findMistakeNum::testNumeralException()
{
    Word word1;
    word1.wordText = "oneth";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "first";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeNum(word2);
    QCOMPARE(error.error, irregularNumForm);
    QCOMPARE(error.idxErroneousWord, 1);
}

void test_word_findMistakeNum::testIncorrectNumeralFormTh()
{
    Word word1;
    word1.wordText = "sixfth";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "sixth";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeNum(word2);
    QCOMPARE(error.error, incorrectNumForm);
    QCOMPARE(error.idxErroneousWord, 1);
}

void test_word_findMistakeNum::testIncorrectNumeralFormFth()
{
    Word word1;
    word1.wordText = "twelth";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "twelfth";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeNum(word2);
    QCOMPARE(error.error, incorrectNumForm);
    QCOMPARE(error.idxErroneousWord, 1);
}

void test_word_findMistakeNum::testIncorrectNumeralFormIeth()
{
    Word word1;
    word1.wordText = "seventith";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "seventieth";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeNum(word2);
    QCOMPARE(error.error, incorrectNumForm);
    QCOMPARE(error.idxErroneousWord, 1);
}


void test_word_findMistakeNum::testNoMistakesInNumeral()
{
    Word word1;
    word1.wordText = "second";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "second";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeNum(word2);
    QCOMPARE(error.error, zeroMistakes);
    QCOMPARE(error.idxErroneousWord, 1);
}
