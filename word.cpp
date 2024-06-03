#include "word.h"

// Определения статических членов класса
std::vector<QString> Word::OnlyPluralNouns = {"scissors", "pants", "glasses"};
std::vector<QString> Word::IrregularNouns = {"men", "children", "feet"};
std::vector<QString> Word::IrregularVerbs = {"run", "go", "eat"};
std::vector<QString> Word::IrregularAdj = {"better", "worse", "farther"};

// Реализация методов класса Word

ErrorInfo Word::compareWords(Word other) {
    // Реализация метода
}

ErrorInfo Word::findMistakeNoun(Word other) {
    // Реализация метода
}

ErrorInfo Word::findMistakeVerb(Word other) {
    // Реализация метода
}

ErrorInfo Word::findMistakeAdj(Word other) {
    // Реализация метода
}

ErrorInfo Word::findMistakeNum(Word other) {

}

QList<ErrorInfo> Sentence::compare(Sentence other) {

}
