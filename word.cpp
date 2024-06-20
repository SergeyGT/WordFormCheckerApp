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

    if ((this->postag != Noun && this->postag != Adj && this->postag != Num && this->postag != Verb) &&
        (other.postag != Noun && other.postag != Adj && other.postag != Num && other.postag != Verb)) {
        throw std::runtime_error("Both words are not a Noun, Adjective, Numeral, or Verb");
    }
    if (this->postag != Noun && this->postag != Adj && this->postag != Num && this->postag != Verb) {
        throw std::runtime_error("Incorrect word is not a Noun, Adjective, Numeral, or Verb");
    }

    if (other.postag != Noun && other.postag != Adj && other.postag != Num && other.postag != Verb) {
        throw std::runtime_error("Correct word is not a Noun, Adjective, Numeral, or Verb");
    }

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

QString trimApostrophe(const QString& word) {
    int apostropheIndex = word.indexOf('`');
    if (apostropheIndex != -1) {
        return word.left(apostropheIndex);
    }
    return word;
}

ErrorInfo Word::findMistakeNoun(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // Исключения для существительных
    if (this->postag != Noun && other.postag != Noun) {
            throw std::runtime_error("Both words are not nouns");
        }

    if (this->postag != Noun && other.postag == Noun) {
            throw std::runtime_error("The incorrect word is not a noun");
        }

    if (this->postag == Noun && other.postag != Noun) {
            throw std::runtime_error("The correct word is not a noun");
        }

    // 1. Проверка окончания на 's
    if (other.wordText.endsWith("`s") && !this->wordText.endsWith("`s")) {
        errorInfo.error = errorType::mistakesInFormatPossessiveFormNouns;
        return errorInfo;
    }


    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    // Проверка окончания в корне у притяжательного
    if((other.wordText.endsWith("`") && this->wordText.endsWith("`")) || (other.wordText.endsWith("`s") && this->wordText.endsWith("`s")))
    {
        QString wordWithoutApos = trimApostrophe(other.wordText);
        QString baseForm = base_form(wordWithoutApos, NOUN);

        QString nounSApos = baseForm + "s";
        if (wordWithoutApos.toLower() == nounSApos.toLower()) {
            errorInfo.error = errorType::nounEndS;
            return errorInfo;
        }

        QString nounESApos = baseForm + "es";
        if (other.wordText.toLower() == nounESApos.toLower()) {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }
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

        if(baseForm.endsWith("y") && other.wordText.endsWith("ies"))
        {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }

        // 3.4. Создание строки nounS
        QString nounS = baseForm + "s";
        if (other.wordText.toLower() == nounS.toLower()) {
            errorInfo.error = errorType::nounEndS;
            return errorInfo;
        }

        // 3.6. Создание строки nounES
        QString nounES = baseForm + "es";
        if (other.wordText.toLower() == nounES.toLower()) {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }
    }
}

ErrorInfo Word::findMistakeVerb(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // Исключения для Глаголов
    if (this->postag != Verb && other.postag != Verb) {
            throw std::runtime_error("Both words are not verbs");
        }

    if (this->postag != Verb && other.postag == Verb) {
            throw std::runtime_error("The incorrect word is not a verb");
        }

    if (this->postag == Verb && other.postag != Verb) {
            throw std::runtime_error("The correct word is not a verb");
        }

    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    QString baseFormStr = base_form(other.wordText, VERB);

    // Проверка наличия слова в IrregularVerbs
    bool foundIrregular = std::find(IrregularVerbs.begin(), IrregularVerbs.end(), baseFormStr) != IrregularVerbs.end();

    if (foundIrregular && !other.wordText.endsWith("ing") && !other.wordText.endsWith("s") && !other.wordText.endsWith("es")) {
        errorInfo.error = errorType::wrongFormIrregularVerb;
        return errorInfo;
    }

    if (other.wordText.endsWith("ed")) {
        // Проверка на совпадение с удвоенной согласной
        if (this->wordText.compare(baseFormStr + "ed") == 0) {
            errorInfo.error = errorType::doubleConsonantEd;
            return errorInfo;
        }
        // Иначе продолжить проверку
    }

    if (other.wordText.endsWith("ing")) {
        // Проверка на окончание -e и замену на -ing
        if (baseFormStr.endsWith("e")) {
            errorInfo.error = errorType::delVerbE;
            return errorInfo;
        }
        // Проверка на совпадение с удвоенной согласной
        else if (this->wordText.toLower().compare(baseFormStr + "ing") == 0) {
            errorInfo.error = errorType::doubleConsonantIng;
            return errorInfo;
        }
        else if(other.wordText.toLower().compare(baseFormStr + "ing") == 0)
        {
            errorInfo.error = errorType::verbIng;
            return errorInfo;
        }
        // Завершить проверку
    }

    // save e

    if(baseFormStr.endsWith("e")){
        if(other.wordText.toLower().compare(baseFormStr+"s") == 0) {
            errorInfo.error = errorType::saveVerbE;
            return errorInfo;
        }
    }




    QString verbS = baseFormStr + "s";
    if (other.wordText.toLower() == verbS.toLower()) {
        errorInfo.error = errorType::verbEndS;
        return errorInfo;
    }

    QString verbES = baseFormStr + "es";
    if (other.wordText.toLower() == verbES.toLower()) {
        errorInfo.error = errorType::verbEndEs;
        return errorInfo;
    }
        // Завершить проверку

}

ErrorInfo Word::findMistakeAdj(Word other) {
    // Реализация метода
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // Исключения для прилагательных
    if (this->postag != Adj && other.postag != Adj) {
            throw std::runtime_error("Both words are not adjectives");
        }

    if (this->postag != Adj && other.postag == Adj) {
            throw std::runtime_error("The incorrect word is not an adjective");
        }

    if (this->postag == Adj && other.postag != Adj) {
            throw std::runtime_error("The correct word is not an adjective");
        }

    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

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

   // Употребление суффикосв er/est с прилагательными, где употреблять его так невозможно

    if(!other.wordText.endsWith("er") && this->wordText.endsWith("er"))
    {
        errorInfo.error = errorType::UnnecessarErAdj;
        return errorInfo;
    }

    else if(!other.wordText.endsWith("est") && this->wordText.endsWith("est"))
    {
        errorInfo.error = errorType::UnnecessarEstAdj;
        return errorInfo;
    }

    // 5. Проверка окончания на "er"
    if (other.wordText.endsWith("er")) {
        errorInfo.error = errorType::incorrectFormCompAdj;
        return errorInfo;
    }
    // 6. Проверка окончания на "est"
    else if (other.wordText.endsWith("est")) {
        errorInfo.error = errorType::incorrectFormSuperlatAdj;
        return errorInfo;
    }
}

ErrorInfo Word::findMistakeNum(Word other) {
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    // Исключения для числительных
    if (this->postag != Num && other.postag != Num) {
            throw std::runtime_error("Both words are not numerals");
        }

    if (this->postag != Num && other.postag == Num) {
            throw std::runtime_error("The incorrect word is not a numeral");
        }

    if (this->postag == Num && other.postag != Num) {
            throw std::runtime_error("The correct word is not a numeral");
        }

    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    // 1. Проверка на особые числительные: first, second, third
    if (other.wordText.toLower() == "first" || other.wordText.toLower() == "second" || other.wordText.toLower() == "third") {
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
