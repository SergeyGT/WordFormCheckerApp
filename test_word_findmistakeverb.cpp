#include "test_word_findmistakeverb.h"
#include <iostream>

Test_word_findMistakeVerb::Test_word_findMistakeVerb(QObject *parent) :
    QObject(parent)
{

}

// №1 Ошибка в удвоении согласной перед окончанием "ed" в глаголе
void Test_word_findMistakeVerb::testDoubleConsonantBeforeEdVerb()
{
    Word word1;
    word1.wordText = "planed";
    word1.postag = Verb;
    word1.id = 2;

    Word word2;
    word2.wordText = "planned";
    word2.postag = Verb;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, doubleConsonantEd);
    QCOMPARE(error.idxErroneousWord, 2);
}

// №2 Ошибка в удвоении согласной перед окончанием "ed" в глаголе
void Test_word_findMistakeVerb::testDoubleConsonantBeforeIngVerb()
{
    Word word1;
    word1.wordText = "runing";
    word1.postag = Verb;
    word1.id = 4;

    Word word2;
    word2.wordText = "running";
    word2.postag = Verb;
    word2.id = 4;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, doubleConsonantIng);
    QCOMPARE(error.idxErroneousWord, 4);
}

// №3 Ошибка в неправильной форме неправильного глагола
void Test_word_findMistakeVerb::testIrregularVerbForm()
{
    Word word1;
    word1.wordText = "winned";
    word1.postag = Verb;
    word1.id = 2;

    Word word2;
    word2.wordText = "won";
    word2.postag = Verb;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, wrongFormIrregularVerb);
    QCOMPARE(error.idxErroneousWord, 2);
}

// Ошибка в неправильной форме неправильного глагола
void Test_word_findMistakeVerb::testIrregularVerbForm1()
{
    Word word1;
    word1.wordText = "becomed";
    word1.postag = Verb;
    word1.id = 2;

    Word word2;
    word2.wordText = "became";
    word2.postag = Verb;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, wrongFormIrregularVerb);
    QCOMPARE(error.idxErroneousWord, 2);
}

// №4 Ошибка в окончании –es глагола
void Test_word_findMistakeVerb::testVerbEndsWithEs()
{
    Word word1;
    word1.wordText = "go";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "goes";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, verbEndEs);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №5 Ошибка в окончании –s глагола
void Test_word_findMistakeVerb::testVerbEndsWithS()
{
    Word word1;
    word1.wordText = "runes";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "runs";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, verbEndS);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №6 Ошибка в удалении "e" у глагола
void Test_word_findMistakeVerb::testVerbDropE()
{
    Word word1;
    word1.wordText = "writeing";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "writing";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, delVerbE);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №7 Ошибка в образовании глагола с окончанием –ing у неправильного глагола
void Test_word_findMistakeVerb::testIrregularVerbIngForm()
{
    Word word1;
    word1.wordText = "ring";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "ringing";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, verbIng);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №8 Сохранение окончания – e у глагола в 3-м л.
void Test_word_findMistakeVerb::testSaveEBeforeS()
{
    Word word1;
    word1.wordText = "livs";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "lives";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, saveVerbE);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №9 Ошибок нет
void Test_word_findMistakeVerb::testNoErrorsFound()
{
    Word word1;
    word1.wordText = "runs";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "runs";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, zeroMistakes);
    QCOMPARE(error.idxErroneousWord, 1);
}

// №10 Оба слова не глаголы
void Test_word_findMistakeVerb::bothWordsNotVerb() {
    Word word1;
    word1.wordText = "box";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "boxes";
    word2.postag = Noun;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeVerb(word2);
        // Ожидаем, что эта часть не выполнится из-за исключения
        QVERIFY(false);
    } catch (const std::exception& e) {
        // Проверяем, что сообщение сообщение соответствует ожидаемому значению
        QCOMPARE(std::string(e.what()), std::string("Both words are not verbs"));
    }

}

// №11 Неправильное слово не глагол
void Test_word_findMistakeVerb::incorrectWordNotVerb() {
    Word word1;
    word1.wordText = "box";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "goes";
    word2.postag = Verb;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeVerb(word2);
        // Ожидаем, что эта часть не выполнится из-за исключения
        QVERIFY(false);
    } catch (const std::exception& e) {
        // Проверяем, что сообщение сообщение соответствует ожидаемому значению
        QCOMPARE(std::string(e.what()), std::string("The incorrect word is not a verb"));
    }

}

// №12 Правильное слово не глагол
void Test_word_findMistakeVerb::correctWordNotVerb() {
    Word word1;
    word1.wordText = "go";
    word1.postag = Verb;
    word1.id = 5;

    Word word2;
    word2.wordText = "boxes";
    word2.postag = Noun;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeVerb(word2);
        // Ожидаем, что эта часть не выполнится из-за исключения
        QVERIFY(false);
    } catch (const std::exception& e) {
        // Проверяем, что сообщение сообщение соответствует ожидаемому значению
        QCOMPARE(std::string(e.what()), std::string("The correct word is not a verb"));
    }

}
