#include "word.h"
#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <fstream>

// Определения статических членов класса
std::vector<QString> Word::OnlyPluralNouns = {    "scissors", "trousers", "pants", "shorts", "jeans", "briefs", "glasses", "spectacles", "earphones", "braces",
                                                  "sunglasses", "surroundings", "contents", "fireworks", "assets", "congratulations", "clothes", "stairs",
                                                  "goods", "brains", "forces", "relations", "physics", "linguistics", "economics", "statistics", "acoustics",
                                                  "aeronautics", "electronics", "genetics", "mathematics", "logistics", "mechanics", "politics", "cards", "darts",
                                                  "acrobatics", "athletics", "billiards", "groceries"};

std::vector<QString> Word::IrregularNouns = {      "man", "woman", "child", "tooth", "foot", "person", "mouse", "goose", "ox", "die", "penny", "louse",
                                                   "cactus", "focus", "thesis", "analysis", "phenomenon", "criterion", "bacterium", "medium", "curriculum",
                                                   "datum", "memorandum", "erratum", "alumnus", "radius", "fungus", "syllabus", "nucleus"};

std::vector<QString> Word::IrregularVerbs = {    "beat", "become", "begin", "bend", "bet", "bite", "bleed", "blow", "break", "breed", "bring", "build", "burn", "buy",
                                                 "catch", "choose", "come", "cost", "cut", "do", "dig", "draw", "dream", "drink", "drive", "eat", "fall", "feed", "feel",
                                                 "fight", "find", "fly", "forget", "forgive", "freeze", "get", "give", "go", "grow", "have", "hear", "hide", "hit", "hold",
                                                 "hurt", "keep", "know", "lay", "lead", "lean", "leave", "lend", "let", "lie", "make", "mean", "meet", "pay", "put", "quit",
                                                 "read", "ride", "ring", "rise", "run", "say", "see", "sell", "send", "set", "shake", "shine", "shoe", "shoot", "show",
                                                 "shrink", "shut", "sing", "sink", "sit", "sleep", "speak", "spend", "spill", "spread", "speed", "stand", "steal", "stick",
                                                 "sting", "stink", "swear", "sweep", "swim", "swing", "take", "teach", "tear", "tell", "think", "throw", "understand",
                                                 "wake", "wear", "win", "write"};
std::vector<QString> Word::IrregularAdj = {    "good", "bad", "much", "far", "less", "little", "many"};

// Реализация вспомогательной функции для приведения слова в начальную форму
QString base_form(const QString& word, int pos) {
    char *bf;
    if (wninit()) {
        std::cerr << "morphy: Fatal error - cannot open WordNet database\n";
        exit(-1);
    }

    bf = ::morphstr(word.toLatin1().data(), pos);
    if (bf) {
        return QString(bf);
    }
    return word; // Если базовая форма не найдена, возвращаем исходное слово
}


// Реализация методов класса Word

ErrorInfo Word::compareWords(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;

    // 1. Если слово существительное
    if (postag == PosTag::Noun) {
        errorInfo = findMistakeNoun(other);
    }
    // 2. Если слово глагол
    else if (postag == PosTag::Verb) {
        errorInfo = findMistakeVerb(other);
    }
    // 3. Если слово прилагательное
    else if (postag == PosTag::Adj) {
        errorInfo = findMistakeAdj(other);
    }
    // 4. Если слово числительное
    else if (postag == PosTag::Num) {
        errorInfo = findMistakeNum(other);
    }

    return errorInfo;
}

ErrorInfo Word::findMistakeNoun(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // 1. Проверка окончания на 's
    if (other.wordText.endsWith("`s") && !this->wordText.endsWith("`s")) {
        errorInfo.error = errorType::mistakesInFormatPossessiveFormNouns;
        return errorInfo;
    }

    // 2. Проверка окончания на '
    if (other.wordText.endsWith("`")) {
        if (!this->wordText.endsWith("`")) {
            errorInfo.error = errorType::mistakesInFormatPossessiveMultipleFormNoun;
            return errorInfo;
        }
    } else {
        // 3. Приведение правильного слова в начальную форму
         QString baseForm = base_form(other.wordText, NOUN);

        // 3.2. Проверка в контейнере OnlyPluralNouns
        if (std::find(OnlyPluralNouns.begin(), OnlyPluralNouns.end(), baseForm) != OnlyPluralNouns.end()) {
            errorInfo.error = errorType::nounsOnlyPluralForm;
            return errorInfo;
        }

        // 3.3. Проверка в контейнере IrregularNouns
        if (std::find(IrregularNouns.begin(), IrregularNouns.end(), baseForm) != IrregularNouns.end()) {
            errorInfo.error = errorType::nounsIrregularPluralForm;
            return errorInfo;
        }

        // 3.4. Создание строки nounS
        QString nounS = baseForm + "s";
        if (other.wordText == nounS) {
            errorInfo.error = errorType::nounEndS;
            return errorInfo;
        }

        // 3.6. Создание строки nounES
        QString nounES = baseForm + "es";
        if (other.wordText == nounES) {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }
    }
}

ErrorInfo Word::findMistakeVerb(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    QString baseFormStr = base_form(other.wordText, VERB);

    // Проверка наличия слова в IrregularVerbs
    bool foundIrregular = std::find(IrregularVerbs.begin(), IrregularVerbs.end(), baseFormStr) != IrregularVerbs.end();

    // Шаг 2.1
    if (foundIrregular && !other.wordText.endsWith("ing")) {
        errorInfo.error = errorType::wrongFormIrregularVerb;
        return errorInfo;
    }

    // Шаг 3
    if (other.wordText.endsWith("ed")) {
        // Проверка на совпадение с удвоенной согласной
        if (this->wordText.compare(baseFormStr + "ed") == 0) {
            errorInfo.error = errorType::doubleConsonantEd;
            return errorInfo;
        }
        // Иначе продолжить проверку
    }

    // Шаг 4
    if (other.wordText.endsWith("ing")) {
        // Проверка на совпадение с удвоенной согласной
        if (this->wordText.compare(baseFormStr + "ing") == 0) {
            errorInfo.error = errorType::doubleConsonantIng;
            return errorInfo;
        }
        // Проверка на окончание -e и замену на -ing
        if (baseFormStr.endsWith("e")) {
            errorInfo.error = errorType::delVerbE;
            return errorInfo;
        }
        // Завершить проверку
    }

    // Шаг 5
    QString verbS = baseFormStr + "s";
    if (other.wordText == verbS) {
        errorInfo.error = errorType::verbEndS;
        return errorInfo;
    }

    QString verbES = baseFormStr + "es";
    if (other.wordText == verbES) {
        errorInfo.error = errorType::verbEndEs;
        return errorInfo;
    }
        // Завершить проверку

}

ErrorInfo Word::findMistakeAdj(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // Получение начальной формы текущего слова
    QString baseForm = base_form(other.wordText, ADJ);

    // 2. Проверка наличия слова в списке IrregularAdj
    if (std::find(IrregularAdj.begin(), IrregularAdj.end(), baseForm) != IrregularAdj.end()) {
        errorInfo.error = errorType::incorrectDegreesComparisonAdj;
        return errorInfo;
    }

    // 3. Проверка окончаний
    if (baseForm.endsWith("y")) {
        if (other.wordText.endsWith("er")) {
            errorInfo.error = errorType::incorrectFormCompAdj;
        } else if (other.wordText.endsWith("est")) {
            errorInfo.error = errorType::incorrectFormSuperlatAdj;
        }
        return errorInfo;
    }

    // 4. Проверка наличия одной гласной буквы
    QString vowels = "aeiouAEIOU";
    int vowelCount = 0;
    for (QChar ch : baseForm) {
        if (vowels.contains(ch)) {
            vowelCount++;
        }
    }

    if (vowelCount == 1) {
        if (other.wordText.endsWith("er")) {
            errorInfo.error = errorType::doubleConsonantAdjEr;
            return errorInfo;
        }
        else if(other.wordText.endsWith("est")) {
            errorInfo.error = errorType::doubleConsonantAdjEst;
            return errorInfo;
        }
    }

    // 5. Проверка окончания на "er"
    if (other.wordText.endsWith("er")) {
        errorInfo.error = errorType::incorrectFormCompAdj;
    }
    // 6. Проверка окончания на "est"
    else if (other.wordText.endsWith("est")) {
        errorInfo.error = errorType::incorrectFormSuperlatAdj;
    }
}

ErrorInfo Word::findMistakeNum(Word other) {
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // 1. Проверка на особые числительные: first, second, third
    if (other.wordText == "first" || other.wordText == "second" || other.wordText == "third") {
        errorInfo.error = errorType::irregularNumForm;
        return errorInfo;
    }

    // 2. Проверка окончания на -th
    if (other.wordText.endsWith("th")) {
        errorInfo.error = errorType::incorrectNumForm;
        return errorInfo;
    }
}

QList<ErrorInfo> Sentence::compare(Sentence other) {
    QList<ErrorInfo> errors;
    // Проход по словам предложений
    for (int i = 0; i < words.size(); ++i) {
        Word correctWord = words[i];
        Word incorrectWord = other.words[i];

        // 1.1. Сравнение текущего слова
        if (correctWord.wordText != incorrectWord.wordText) {
            // 1.2. Вызов функции compareWords, если слова не совпадают
            ErrorInfo error = incorrectWord.compareWords(correctWord);
            errors.append(error);
        } else {
            // 1.3. Присвоение типа ошибки - zeroMistakes, если слова совпадают
            ErrorInfo error;
            error.idxErroneousWord = incorrectWord.id;
            error.error = errorType::zeroMistakes;
            errors.append(error);
        }
    }

    return errors;
}
