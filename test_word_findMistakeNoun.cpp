#include <QtTest/QtTest>
#include <word.h>
#include <iostream>
#include "test_word_findMistakeNoun.h"

TestWordfindMistakeNoun::TestWordfindMistakeNoun(QObject *parent) :
    QObject(parent)
{

}

// №1 Ошибка в притяжательном существительном в ед.ч.
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

// №2 Ошибка в притяжательном существительном в ед.ч. – апостроф не в нужном месте
void TestWordfindMistakeNoun::testPossessiveSingularNounApos() {
    Word word1;
    word1.wordText = "Peters`";
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

// №3 Ошибка в притяжательном существительном во мн.ч.
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

// №4 Ошибка в притяжательном существительном во мн.ч. + образование неверной формы окончания -s
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

// №5 Ошибка в притяжательном существительном во мн.ч.- в образовании неверной формы окончания -s
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

// №6 Ошибка в существительном только во множественном числе
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

// №7 Ошибка в существительном только во множественном числе
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

// №8 Ошибка в окончании –s существительного
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


// №9 Ошибка в окончании –es существительного
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


// №10 Ни одной ошибки не было найдено
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

// №11 Оба слова не существительные
void TestWordfindMistakeNoun::bothWordsNotNoun() {
    Word word1;
    word1.wordText = "go";
    word1.postag = Verb;
    word1.id = 5;

    Word word2;
    word2.wordText = "goes";
    word2.postag = Verb;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeNoun(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}

// №12 Неправильное слово не существительные
void TestWordfindMistakeNoun::incorrectWordNotNoun() {
    Word word1;
    word1.wordText = "go";
    word1.postag = Verb;
    word1.id = 5;

    Word word2;
    word2.wordText = "cat";
    word2.postag = Noun;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeNoun(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}

// №13 Неправильное слово не существительные
void TestWordfindMistakeNoun::correctWordNotNoun() {
    Word word1;
    word1.wordText = "cat";
    word1.postag = Noun;
    word1.id = 5;

    Word word2;
    word2.wordText = "goes";
    word2.postag = Verb;
    word2.id = 5;

    try {
        ErrorInfo error = word1.findMistakeNoun(word2);
        QCOMPARE(error.error, zeroMistakes);
        QCOMPARE(error.idxErroneousWord, 5);
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

}

// Ошибка в окончаниии s глагола, заканчивающегося на букву -e
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

// Ошибка в окончании существительного с окончанием -s
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

// Ошибка в окончании –es существительного
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

// Ошибка в окончании –es существительного c окончанием -y в начальной форме
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

// Ошибка в окончании –es существительного c окончанием -о в начальной форме
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



















































//// Ошибка в притяжательном существительном во мн.ч., с окончанием -es
//void TestWordfindMistakeNoun::testPossessivePluralNounEndES() {
//    Word word1;
//    word1.wordText = "dishs";
//    word1.postag = Noun;
//    word1.id = 3;

//    Word word2;
//    word2.wordText = "dishes`";
//    word2.postag = Noun;
//    word2.id = 3;

//    ErrorInfo error = word1.findMistakeNoun(word2);
//    QCOMPARE(error.error, mistakesInFormatPossessiveMultipleFormNoun);
//    QCOMPARE(error.idxErroneousWord, 3);
//}


