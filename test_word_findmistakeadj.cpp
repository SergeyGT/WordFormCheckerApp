#include "test_word_findmistakeadj.h"

test_word_findMistakeAdj::test_word_findMistakeAdj(QObject *parent) :
    QObject(parent)
{

}

// №1 Ошибка в удвоении согласной перед окончанием "er" в прилагательном
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

// №2 Ошибка в удвоении согласной перед окончанием "est" в прилагательном
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

// №3 Прилагательное относится к исключениям
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

// №4 Ошибка в употреблении суффикса –er с гласной y в окончании
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

// №5 Ошибка в употреблении суффикса –er с гласной y в окончании
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

// №6 Использование неверной формы сранвительной степени прилагательного
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

// №7 Использование неверной формы превосходной степени прилагательного
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

// №8 Ни одной ошибки не было найдено
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

// №9 Оба слова не прилагательные
void test_word_findMistakeAdj::bothWordsNotAdj() {
    Word word1;
    word1.wordText = "run";
    word1.postag = Verb;
    word1.id = 5;

    Word word2;
    word2.wordText = "runs";
    word2.postag = Verb;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeAdj(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {

    }

}

// №10 Неправильное слово не прилагательное
void test_word_findMistakeAdj::incorrectWordNotAdj() {
    Word word1;
    word1.wordText = "run";
    word1.postag = Verb;
    word1.id = 5;

    Word word2;
    word2.wordText = "smaller";
    word2.postag = Adj;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeAdj(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {

    }

}

// №11 Правильное слово не прилагательное
void test_word_findMistakeAdj::correctWordNotAdj() {
    Word word1;
    word1.wordText = "smalles";
    word1.postag = Adj;
    word1.id = 5;

    Word word2;
    word2.wordText = "runs";
    word2.postag = Verb;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeAdj(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {

    }

}

