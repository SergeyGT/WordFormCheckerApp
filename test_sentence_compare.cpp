#include "test_sentence_compare.h"

test_sentence_compare::test_sentence_compare(QObject *parent) :
    QObject(parent)
{

}

void test_sentence_compare::testNoErrors()
{
    Sentence sentence1;
    sentence1.sentenceText = "The cat is sleeping";
    sentence1.words.append(Word{"The", 0, Article});
    sentence1.words.append(Word{"cat", 1, Noun});
    sentence1.words.append(Word{"is", 2, Verb});
    sentence1.words.append(Word{"sleeping", 3, Verb});

    Sentence sentence2;
    sentence2.sentenceText = "The cat is sleeping";
    sentence2.words.append(Word{"The", 0, Article});
    sentence2.words.append(Word{"cat", 1, Noun});
    sentence2.words.append(Word{"is", 2, Verb});
    sentence2.words.append(Word{"sleeping", 3, Verb});

    QList<ErrorInfo> errors = sentence1.compare(sentence2);
    for (int i = 0; i < sentence1.words.size(); ++i) {
        QCOMPARE(errors[i].error, zeroMistakes);
        QCOMPARE(errors[i].idxErroneousWord, i);
    }
}

void test_sentence_compare::testSingleErrorInSentence() {
    Sentence sentence1;
    sentence1.sentenceText = "The cat is runing";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("cat", 1, Noun));
    sentence1.words.append(Word("is", 2, Verb));
    sentence1.words.append(Word("runing", 3, Verb));

    Sentence sentence2;
    sentence2.sentenceText = "The cat is running";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("cat", 1, Noun));
    sentence2.words.append(Word("is", 2, Verb));
    sentence2.words.append(Word("running", 3, Verb));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, zeroMistakes);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, zeroMistakes);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, doubleConsonantIng);
    QCOMPARE(errors[3].idxErroneousWord, 3);

}

void test_sentence_compare::testMultipleErrorsInSentence() {
    Sentence sentence1;
    sentence1.sentenceText = "The cat runes fast";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("cat", 1, Noun));
    sentence1.words.append(Word("runes", 2, Verb));
    sentence1.words.append(Word("fast", 3, Adj));

    Sentence sentence2;
    sentence2.sentenceText = "The cats runs fast";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("cats", 1, Noun));
    sentence2.words.append(Word("runs", 2, Verb));
    sentence2.words.append(Word("fast", 3, Adj));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, nounEndS);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, verbEndS);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, zeroMistakes);
    QCOMPARE(errors[3].idxErroneousWord, 3);
}

void test_sentence_compare::testErrorInEachPartOfSpeech() {
    Sentence sentence1;
    sentence1.sentenceText = "The oneth cates was biger than a hamster and runed very fast";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("oneth", 1, Num));
    sentence1.words.append(Word("cates", 2, Noun));
    sentence1.words.append(Word("was", 3, Verb));
    sentence1.words.append(Word("biger", 4, Adj));
    sentence1.words.append(Word("than", 5, Preposition));
    sentence1.words.append(Word("a", 6, Article));
    sentence1.words.append(Word("hamster", 7, Noun));
    sentence1.words.append(Word("and", 8, Conjunction));
    sentence1.words.append(Word("runed", 9, Verb));
    sentence1.words.append(Word("very", 10, Adverb));
    sentence1.words.append(Word("fast", 11, Adj));

    Sentence sentence2;
    sentence2.sentenceText = "The first cats was bigger than a hamster and ran very fast";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("first", 1, Num));
    sentence2.words.append(Word("cats", 2, Noun));
    sentence2.words.append(Word("was", 3, Verb));
    sentence2.words.append(Word("bigger", 4, Adj));
    sentence2.words.append(Word("than", 5, Preposition));
    sentence2.words.append(Word("a", 6, Article));
    sentence2.words.append(Word("hamster", 7, Noun));
    sentence2.words.append(Word("and", 8, Conjunction));
    sentence2.words.append(Word("ran", 9, Verb));
    sentence2.words.append(Word("very", 10, Adverb));
    sentence2.words.append(Word("fast", 11, Adj));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, irregularNumForm);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, nounEndS);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, zeroMistakes);
    QCOMPARE(errors[3].idxErroneousWord, 3);
    QCOMPARE(errors[4].error, doubleConsonantAdjEr);
    QCOMPARE(errors[4].idxErroneousWord, 4);
    QCOMPARE(errors[5].error, zeroMistakes);
    QCOMPARE(errors[5].idxErroneousWord, 5);
    QCOMPARE(errors[6].error, zeroMistakes);
    QCOMPARE(errors[6].idxErroneousWord, 6);
    QCOMPARE(errors[7].error, zeroMistakes);
    QCOMPARE(errors[7].idxErroneousWord, 7);
    QCOMPARE(errors[8].error, zeroMistakes);
    QCOMPARE(errors[8].idxErroneousWord, 8);
    QCOMPARE(errors[9].error, wrongFormIrregularVerb);
    QCOMPARE(errors[9].idxErroneousWord, 9);
    QCOMPARE(errors[10].error, zeroMistakes);
    QCOMPARE(errors[10].idxErroneousWord, 10);
}

void test_sentence_compare::testErrorInEveryWord() {
    Sentence sentence1;
    sentence1.sentenceText = "Doges runed";
    sentence1.words.append(Word("Doges", 0, Noun));
    sentence1.words.append(Word("runed", 1, Verb));

    Sentence sentence2;
    sentence2.sentenceText = "Dogs ran";
    sentence2.words.append(Word("Dogs", 0, Noun));
    sentence2.words.append(Word("ran", 1, Verb));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, nounEndS);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, wrongFormIrregularVerb);
    QCOMPARE(errors[1].idxErroneousWord, 1);
}

void test_sentence_compare::testErrorInNoun() {
    Sentence sentence1;
    sentence1.sentenceText = "The mans are here";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("mans", 1, Noun));
    sentence1.words.append(Word("are", 2, Verb));
    sentence1.words.append(Word("here", 3, Adverb));

    Sentence sentence2;
    sentence2.sentenceText = "The men are here";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("men", 1, Noun));
    sentence2.words.append(Word("are", 2, Verb));
    sentence2.words.append(Word("here", 3, Adverb));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, nounsIrregularPluralForm);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, zeroMistakes);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, zeroMistakes);
    QCOMPARE(errors[3].idxErroneousWord, 3);
}

void test_sentence_compare::testErrorInAdjective() {
    Sentence sentence1;
    sentence1.sentenceText = "The big cat is here";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("big", 1, Adj));
    sentence1.words.append(Word("cat", 2, Noun));
    sentence1.words.append(Word("is", 3, Verb));
    sentence1.words.append(Word("here", 4, Adverb));

    Sentence sentence2;
    sentence2.sentenceText = "The bigger cat is here";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("bigger", 1, Adj));
    sentence2.words.append(Word("cat", 2, Noun));
    sentence2.words.append(Word("is", 3, Verb));
    sentence2.words.append(Word("here", 4, Adverb));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, incorrectDegreesComparisonAdj);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, zeroMistakes);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, zeroMistakes);
    QCOMPARE(errors[3].idxErroneousWord, 3);
    QCOMPARE(errors[4].error, zeroMistakes);
    QCOMPARE(errors[4].idxErroneousWord, 4);
}

void test_sentence_compare::testErrorInNumeral() {
    Sentence sentence1;
    sentence1.sentenceText = "The twoth prize is awarded";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("twoth", 1, Num));
    sentence1.words.append(Word("prize", 2, Noun));
    sentence1.words.append(Word("is", 3, Verb));
    sentence1.words.append(Word("awarded", 4, Verb));

    Sentence sentence2;
    sentence2.sentenceText = "The second prize is awarded";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("second", 1, Num));
    sentence2.words.append(Word("prize", 2, Noun));
    sentence2.words.append(Word("is", 3, Verb));
    sentence2.words.append(Word("awarded", 4, Verb));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, irregularNumForm);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, zeroMistakes);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, zeroMistakes);
    QCOMPARE(errors[3].idxErroneousWord, 3);
    QCOMPARE(errors[4].error, zeroMistakes);
    QCOMPARE(errors[4].idxErroneousWord, 4);
}

void test_sentence_compare::testComplexErrorNounVerb() {
    Sentence sentence1;
    sentence1.sentenceText = "The mans are runing";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("mans", 1, Noun));
    sentence1.words.append(Word("are", 2, Verb));
    sentence1.words.append(Word("runing", 3, Verb));

    Sentence sentence2;
    sentence2.sentenceText = "The men are running";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("men", 1, Noun));
    sentence2.words.append(Word("are", 2, Verb));
    sentence2.words.append(Word("running", 3, Verb));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, nounsIrregularPluralForm);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, zeroMistakes);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, doubleConsonantIng);
    QCOMPARE(errors[3].idxErroneousWord, 3);
}

void test_sentence_compare::testComplexErrorAdjectiveNumeral() {
    Sentence sentence1;
    sentence1.sentenceText = "The twoth prize is bigger";
    sentence1.words.append(Word("The", 0, Article));
    sentence1.words.append(Word("twoth", 1, Num));
    sentence1.words.append(Word("prize", 2, Noun));
    sentence1.words.append(Word("is", 3, Verb));
    sentence1.words.append(Word("bigger", 4, Adj));

    Sentence sentence2;
    sentence2.sentenceText = "The second prize is big";
    sentence2.words.append(Word("The", 0, Article));
    sentence2.words.append(Word("second", 1, Num));
    sentence2.words.append(Word("prize", 2, Noun));
    sentence2.words.append(Word("is", 3, Verb));
    sentence2.words.append(Word("big", 4, Adj));

    QList<ErrorInfo> errors = sentence1.compare(sentence2);

    QCOMPARE(errors[0].error, zeroMistakes);
    QCOMPARE(errors[0].idxErroneousWord, 0);
    QCOMPARE(errors[1].error, irregularNumForm);
    QCOMPARE(errors[1].idxErroneousWord, 1);
    QCOMPARE(errors[2].error, zeroMistakes);
    QCOMPARE(errors[2].idxErroneousWord, 2);
    QCOMPARE(errors[3].error, zeroMistakes);
    QCOMPARE(errors[3].idxErroneousWord, 3);
    QCOMPARE(errors[4].error, incorrectDegreesComparisonAdj);
    QCOMPARE(errors[4].idxErroneousWord, 4);
}
