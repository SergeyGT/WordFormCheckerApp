#include "test_word_comparewords.h"
#include <iostream>

test_word_compareWords::test_word_compareWords(QObject *parent) :
    QObject(parent)
{

}

// №1 Выбор функции для существительного
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

// №2 Выбор функции для глагола
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

// №3 Выбор функции для прилагательного
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

// №4 Выбор функции для числительного
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

// №5 Ошибок в словах не найдено
void test_word_compareWords::testNoErrors()
{
    Word word1;
    word1.wordText = "second";
    word1.postag = Num;
    word1.id = 1;

    Word word2;
    word2.wordText = "second";
    word2.postag = Num;
    word2.id = 1;

    ErrorInfo error = word1.compareWords(word2);
    QCOMPARE(error.error, zeroMistakes);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №6 Неправильное слово не относится к (Noun, Adj, Num, Verb)
void test_word_compareWords::bothWordsNotCorrectPosTag() {
    Word word1;
    word1.wordText = "but";
    word1.postag = Conjunction;
    word1.id = 5;

    Word word2;
    word2.wordText = "however";
    word2.postag = Conjunction;
    word2.id = 5;

    try {
        ErrorInfo error = word1.compareWords(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}

// №7 Неправильное слово не относится к (Noun, Adj, Num, Verb)
void test_word_compareWords::incorrectWordNotCorrectPosTag() {
    Word word1;
    word1.wordText = "but";
    word1.postag = Conjunction;
    word1.id = 5;

    Word word2;
    word2.wordText = "first";
    word2.postag = Num;
    word2.id = 5;

    try {
        ErrorInfo error = word1.compareWords(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}

// №8 Неправильное слово не относится к (Noun, Adj, Num, Verb)
void test_word_compareWords::correctWordNotCorrectPosTag() {
    Word word1;
    word1.wordText = "oneth";
    word1.postag = Num;
    word1.id = 5;

    Word word2;
    word2.wordText = "however";
    word2.postag = Conjunction;
    word2.id = 5;

    try {
        ErrorInfo error = word1.compareWords(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}
