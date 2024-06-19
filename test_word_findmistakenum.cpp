#include "test_word_findmistakenum.h"
#include <iostream>

test_word_findMistakeNum::test_word_findMistakeNum(QObject *parent) :
    QObject(parent)
{

}

//  №1 Числительное относится к исключениям
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

// №2 Ошибка в употреблении числительного с окончанием -th
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

// №3 Ошибка в употреблении числительного с окончанием -fth
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

// №4 Ошибка в употреблении числительного с окончанием -ieth
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

// №5 Ни одной ошибки не было найдено
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


// №6 Оба слова не числительные
void test_word_findMistakeNum::bothWordsNotNum() {
    Word word1;
    word1.wordText = "betterer";
    word1.postag = Adj;
    word1.id = 5;

    Word word2;
    word2.wordText = "best";
    word2.postag = Adj;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeNum(word2);
        // Ожидаем, что эта часть не выполнится из-за исключения
        QVERIFY(false);
    } catch (const std::exception& e) {
        // Проверяем, что сообщение сообщение соответствует ожидаемому значению
        QCOMPARE(std::string(e.what()), std::string("Both words are not numerals"));
    }

}

// №7 Неправильное слово не числительные
void test_word_findMistakeNum::incorrectWordNotNum() {
    Word word1;
    word1.wordText = "best";
    word1.postag = Adj;
    word1.id = 5;

    Word word2;
    word2.wordText = "second";
    word2.postag = Num;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeNum(word2);
        // Ожидаем, что эта часть не выполнится из-за исключения
        QVERIFY(false);
    } catch (const std::exception& e) {
        // Проверяем, что сообщение сообщение соответствует ожидаемому значению
        QCOMPARE(std::string(e.what()), std::string("The incorrect word is not a numeral"));
    }

}

// №8 Правильное слово не числительное
void test_word_findMistakeNum::correctWordNotNum() {
    Word word1;
    word1.wordText = "second";
    word1.postag = Num;
    word1.id = 5;

    Word word2;
    word2.wordText = "best";
    word2.postag = Adj;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeNum(word2);
        // Ожидаем, что эта часть не выполнится из-за исключения
        QVERIFY(false);
    } catch (const std::exception& e) {
        // Проверяем, что сообщение сообщение соответствует ожидаемому значению
        QCOMPARE(std::string(e.what()), std::string("The correct word is not a numeral"));
    }

}
