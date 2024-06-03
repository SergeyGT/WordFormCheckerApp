#include "test_word_findmistakeverb.h"

Test_word_findMistakeVerb::Test_word_findMistakeVerb(QObject *parent) :
    QObject(parent)
{

}


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

void Test_word_findMistakeVerb::testIrregularVerbForm()
{
    Word word1;
    word1.wordText = "be";
    word1.postag = Verb;
    word1.id = 2;

    Word word2;
    word2.wordText = "was";
    word2.postag = Verb;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, wrongFormIrregularVerb);
    QCOMPARE(error.idxErroneousWord, 2);
}

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
    QCOMPARE(error.error, verbendES);
    QCOMPARE(error.idxErroneousWord, 1);
}

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

void Test_word_findMistakeVerb::testIrregularVerbIngForm()
{
    Word word1;
    word1.wordText = "swing";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "swinging";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);
    QCOMPARE(error.error, verbIng);
    QCOMPARE(error.idxErroneousWord, 1);
}

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
