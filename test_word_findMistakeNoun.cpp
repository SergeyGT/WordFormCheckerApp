#include <QtTest/QtTest>
#include <word.h>

class TestWordfindMistakeNoun : public QObject {
    Q_OBJECT

private slots:
    void testPossessiveSingularNoun();
    void testPossessivePluralNoun();
    void testPossessivePluralNounAndEndS();
    void testPossessivePluralNounAndEndES();
    void testPossessivePluralNounEndES();
    void testOnlyPluralformNoun();
    void testIrregularFormNoun();
    void testNounEndS();
    void testNounEndS1();
    void testNounEndEs();
    void testNounEndEs2();
    void testNounZeroMistakes();
};

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

////////////// Добавить этот тест в протокол  /////////////////////
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

////////// оканчание на гласную body girrafe hero /////////
