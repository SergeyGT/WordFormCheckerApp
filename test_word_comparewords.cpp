#include "test_word_comparewords.h"

test_word_compareWords::test_word_compareWords(QObject *parent) :
    QObject(parent)
{

}

void test_word_compareWords::testFunctionSelectionForNoun()
{
    Word word1;
    word1.wordText = "Peters";
    word1.postag = Noun;
    word1.id = 4;

    Word word2;
    word2.wordText = "Peter`s";
    word2.postag = Noun;
    word2.id = 4;

    ErrorInfo error = word1.compareWords(word2);
    QCOMPARE(error.error, mistakesInFormatPossessiveFormNouns);
    QCOMPARE(error.idxErroneousWord, 4);
}

void test_word_compareWords::testFunctionSelectionForVerb()
{
    Word word1;
    word1.wordText = "runing";
    word1.postag = Verb;
    word1.id = 4;

    Word word2;
    word2.wordText = "running";
    word2.postag = Verb;
    word2.id = 4;

    ErrorInfo error = word1.compareWords(word2);
    QCOMPARE(error.error, doubleConsonantIng);
    QCOMPARE(error.idxErroneousWord, 4);
}

void test_word_compareWords::testFunctionSelectionForAdjective()
{
    Word word1;
    word1.wordText = "carryest";
    word1.postag = Adj;
    word1.id = 2;

    Word word2;
    word2.wordText = "carriest";
    word2.postag = Adj;
    word2.id = 2;

    ErrorInfo error = word1.compareWords(word2);
    QCOMPARE(error.error, incorrectFormSuperlatAdj);
    QCOMPARE(error.idxErroneousWord, 2);
}

void test_word_compareWords::testFunctionSelectionForNumeral()
{
    Word word1;
    word1.wordText = "oneth";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "first";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.compareWords(word2);
    QCOMPARE(error.error, irregularNumForm);
    QCOMPARE(error.idxErroneousWord, 1);
}
