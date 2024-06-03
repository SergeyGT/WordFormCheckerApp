#include <QtTest/QtTest>
#include <word.h>
#include "test_word_findMistakeNoun.h"

TestWordfindMistakeNoun::TestWordfindMistakeNoun(QObject *parent) :
    QObject(parent)
{

}

void TestWordfindMistakeNoun::testPossessiveSingularNoun() {
    Word word1;
    word1.wordText = "Peters";
    word1.postag = Noun;
    word1.id = 4;

    Word word2;
    word2.wordText = "Peter`s";
    word2.postag = Noun;
    word2.id = 4;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, mistakesInFormatPossessiveFormNouns);
    QCOMPARE(error.idxErroneousWord, 4);
}

void TestWordfindMistakeNoun::testPossessivePluralNoun() {
    Word word1;
    word1.wordText = "girls";
    word1.postag = Noun;
    word1.id = 3;

    Word word2;
    word2.wordText = "girls`";
    word2.postag = Noun;
    word2.id = 3;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, mistakesInFormatPossessiveMultipleFormNoun);
    QCOMPARE(error.idxErroneousWord, 3);
}

void TestWordfindMistakeNoun::testPossessivePluralNounAndEndS() {
    Word word1;
    word1.wordText = "girles`";
    word1.postag = Noun;
    word1.id = 3;

    Word word2;
    word2.wordText = "girls`";
    word2.postag = Noun;
    word2.id = 3;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndS);
    QCOMPARE(error.idxErroneousWord, 3);
}

void TestWordfindMistakeNoun::testPossessivePluralNounAndEndES() {
    Word word1;
    word1.wordText = "girles";
    word1.postag = Noun;
    word1.id = 3;

    Word word2;
    word2.wordText = "girls`";
    word2.postag = Noun;
    word2.id = 3;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, mistakesInFormatPossessiveMultipleFormNoun);
    QCOMPARE(error.idxErroneousWord, 3);
}

void TestWordfindMistakeNoun::testPossessivePluralNounEndES() {
    Word word1;
    word1.wordText = "dishs";
    word1.postag = Noun;
    word1.id = 3;

    Word word2;
    word2.wordText = "dishes`";
    word2.postag = Noun;
    word2.id = 3;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, mistakesInFormatPossessiveMultipleFormNoun);
    QCOMPARE(error.idxErroneousWord, 3);
}

void TestWordfindMistakeNoun::testOnlyPluralformNoun() {
    Word word1;
    word1.wordText = "scissor";
    word1.postag = Noun;
    word1.id = 2;

    Word word2;
    word2.wordText = "scissors`";
    word2.postag = Noun;
    word2.id = 2;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounsOnlyPluralForm);
    QCOMPARE(error.idxErroneousWord, 2);
}

void TestWordfindMistakeNoun::testIrregularFormNoun() {
    Word word1;
    word1.wordText = "mans";
    word1.postag = Noun;
    word1.id = 1;

    Word word2;
    word2.wordText = "men`";
    word2.postag = Noun;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounsIrregularPluralForm);
    QCOMPARE(error.idxErroneousWord, 1);
}

void TestWordfindMistakeNoun::testNounEndS() {
    Word word1;
    word1.wordText = "cates";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "cats";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndS);
    QCOMPARE(error.idxErroneousWord, 5);
}

void TestWordfindMistakeNoun::testNounEndS2() {
    Word word1;
    word1.wordText = "girrafs";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "girrafes";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndS);
    QCOMPARE(error.idxErroneousWord, 5);
}

void TestWordfindMistakeNoun::testNounEndS1() {
    Word word1;
    word1.wordText = "boates";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "boats";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndS);
    QCOMPARE(error.idxErroneousWord, 5);
}

void TestWordfindMistakeNoun::testNounEndEs() {
    Word word1;
    word1.wordText = "boxs";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "boxes";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndES);
    QCOMPARE(error.idxErroneousWord, 5);
}


void TestWordfindMistakeNoun::testNounEndEs1() {
    Word word1;
    word1.wordText = "drivs";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "drives";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndES);
    QCOMPARE(error.idxErroneousWord, 5);
}

void TestWordfindMistakeNoun::testNounEndEs2() {
    Word word1;
    word1.wordText = "bodys";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "bodies";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndES);
    QCOMPARE(error.idxErroneousWord, 5);
}

void TestWordfindMistakeNoun::testNounEndEs3() {
    Word word1;
    word1.wordText = "heros";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "heroes";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, nounEndES);
    QCOMPARE(error.idxErroneousWord, 5);
}

void TestWordfindMistakeNoun::testNounZeroMistakes() {
    Word word1;
    word1.wordText = "cats";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "cats";
    word2.postag = Noun;
    word2.id = 5;

    ErrorInfo error = word1.findMistakeNoun(word2);
    QCOMPARE(error.error, zeroMistakes);
    QCOMPARE(error.idxErroneousWord, 5);
}



