#include "word.h"
#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <fstream>

/**< Определения статических членов класса */
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

/**
 @brief Реализация вспомогательной функции для приведения слова в начальную форму
 @param word - слово, которое необходимо привести в начальную форму
 @param pos - часть речи слова
 */
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
    return word; /**< Если базовая форма не найдена, возвращаем исходное слово */
}


/**< Реализация методов класса Word */

ErrorInfo Word::compareWords(Word other) {

    ErrorInfo errorInfo;

    /**< Если оба слова не существительные, глаголы, прилагательные или числительные*/
    if ((this->postag != Noun && this->postag != Adj && this->postag != Num && this->postag != Verb) &&
        (other.postag != Noun && other.postag != Adj && other.postag != Num && other.postag != Verb)) {
        throw std::runtime_error("Both words are not a Noun, Adjective, Numeral, or Verb");
    }
    /**< Если возможное некорректное слово не существительное, глагол, прилагательное или числительное*/
    if (this->postag != Noun && this->postag != Adj && this->postag != Num && this->postag != Verb) {
        throw std::runtime_error("Incorrect word is not a Noun, Adjective, Numeral, or Verb");
    }
    /**< Если корректное слово не существительное, глагол, прилагательное или числительное*/
    if (other.postag != Noun && other.postag != Adj && other.postag != Num && other.postag != Verb) {
        throw std::runtime_error("Correct word is not a Noun, Adjective, Numeral, or Verb");
    }

    /**< 1. Если слово существительное*/
    if (postag == PosTag::Noun) {
        errorInfo = findMistakeNoun(other);
    }
    /**< 2. Если слово глагол*/
    else if (postag == PosTag::Verb) {
        errorInfo = findMistakeVerb(other);
    }
    /**< 3. Если слово прилагательное*/
    else if (postag == PosTag::Adj) {
        errorInfo = findMistakeAdj(other);
    }
    /**< 4. Если слово числительное*/
    else if (postag == PosTag::Num) {
        errorInfo = findMistakeNum(other);
    }

    /**< Вернуть ошибку*/
    return errorInfo;
}

/**
 * @brief Функция удаления обрезания апострофов в существительном
 *
 * @param word слово, которое необходимо обрезать
*/
QString trimApostrophe(const QString& word) {
    int apostropheIndex = word.indexOf('`');
    if (apostropheIndex != -1) {
        return word.left(apostropheIndex);
    }
    return word;
}

ErrorInfo Word::findMistakeNoun(Word other) {

    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    /**< Исключения для существительных */
    /// Если оба слова не существительные
    if (this->postag != Noun && other.postag != Noun) {
            throw std::runtime_error("Both words are not nouns");
        }

    /**< Если возможное некорректное слово не существительное */
    if (this->postag != Noun && other.postag == Noun) {
            throw std::runtime_error("The incorrect word is not a noun");
        }

    /**< Если корректное слово не существительное */
    if (this->postag == Noun && other.postag != Noun) {
            throw std::runtime_error("The correct word is not a noun");
        }

    /**< Если слова одинаковые*/
    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    /**< 1. Проверка притяжательного существительного  в ед.ч.*/
    if (other.wordText.endsWith("`s") && !this->wordText.endsWith("`s")) {
        errorInfo.error = errorType::mistakesInFormatPossessiveFormNouns;
        return errorInfo;
    }

    /**< Проверка окончания в корне у притяжательного*/
    if((other.wordText.endsWith("`") && this->wordText.endsWith("`")) || (other.wordText.endsWith("`s") && this->wordText.endsWith("`s")))
    {
        /**< Образуем слово без апострофа*/
        QString wordWithoutApos = trimApostrophe(other.wordText);
        /**< Приводим слоово в начальную форму*/
        QString baseForm = base_form(wordWithoutApos, NOUN);

        /**< Проверка на окончание -s*/
        QString nounSApos = baseForm + "s";
        if (wordWithoutApos.toLower() == nounSApos.toLower()) {
            errorInfo.error = errorType::nounEndS;
            return errorInfo;
        }

        /**< Проверка на окончание -es*/
        QString nounESApos = baseForm + "es";
        if (other.wordText.toLower() == nounESApos.toLower()) {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }
    }

    /**< 2. Проверка притяжательного существительного во мн.ч.*/
    if (other.wordText.endsWith("`")) {
        if (!this->wordText.endsWith("`")) {
            errorInfo.error = errorType::mistakesInFormatPossessiveMultipleFormNoun;
            return errorInfo;
        }
    } else {
        // 3. Приведение правильного слова в начальную форму
         QString baseForm = base_form(other.wordText, NOUN);

        /**< 3.2. Проверка наличия существительного в контейнере OnlyPluralNouns - только во множественном числе.*/
        if (std::find(OnlyPluralNouns.begin(), OnlyPluralNouns.end(), baseForm) != OnlyPluralNouns.end()) {
            errorInfo.error = errorType::nounsOnlyPluralForm;
            return errorInfo;
        }

        /**< 3.3. Проверка наличия существительного в контейнере IrregularNouns - неправильных существительных*/
        if (std::find(IrregularNouns.begin(), IrregularNouns.end(), baseForm) != IrregularNouns.end()) {
            errorInfo.error = errorType::nounsIrregularPluralForm;
            return errorInfo;
        }

        /**< Если в начальной форме существительное имеет окончание y, а во мн.ч. -ies*/
        if(baseForm.endsWith("y") && other.wordText.endsWith("ies"))
        {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }

        /**< 3.4. Создание строки nounS для проверки окончания -es*/
        QString nounS = baseForm + "s";
        if (other.wordText.toLower() == nounS.toLower()) {
            errorInfo.error = errorType::nounEndS;
            return errorInfo;
        }

        /**< 3.6. Создание строки nounES для проверки окончания -es*/
        QString nounES = baseForm + "es";
        if (other.wordText.toLower() == nounES.toLower()) {
            errorInfo.error = errorType::nounEndES;
            return errorInfo;
        }
    }
}

ErrorInfo Word::findMistakeVerb(Word other) {

    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    /**< Исключения для глаголов*/
    /// Если Обе части речи не глаголы
    if (this->postag != Verb && other.postag != Verb) {
            throw std::runtime_error("Both words are not verbs");
        }

    /**< Если вохможное некорректное слово не глагол*/
    if (this->postag != Verb && other.postag == Verb) {
            throw std::runtime_error("The incorrect word is not a verb");
        }

    /**< Если корректное слово не глагол*/
    if (this->postag == Verb && other.postag != Verb) {
            throw std::runtime_error("The correct word is not a verb");
        }

    /**< Если оба слова одинаковые - ошибок нет*/
    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    /**< Приводим глагол в начальную форму*/
    QString baseFormStr = base_form(other.wordText, VERB);

    /**< Проверка наличия слова в IrregularVerbs*/
    bool foundIrregular = std::find(IrregularVerbs.begin(), IrregularVerbs.end(), baseFormStr) != IrregularVerbs.end();

    /**< Если глагол неправильный и в прошедшем времени*/
    if (foundIrregular && !other.wordText.endsWith("ing") && !other.wordText.endsWith("s") && !other.wordText.endsWith("es")) {
        errorInfo.error = errorType::wrongFormIrregularVerb;
        return errorInfo;
    }

    /**< Проверка на совпадение с удвоенной согласной в глаголе с окончанием -ed*/
    if (other.wordText.endsWith("ed")) {
            if (this->wordText.compare(baseFormStr + "ed") == 0) {
            errorInfo.error = errorType::doubleConsonantEd;
            return errorInfo;
        }
    }

    /**< Если глагол заканчивается на -ing*/
    if (other.wordText.endsWith("ing")) {
        /**< Проверка на окончание -e и замену на -ing*/
        if (baseFormStr.endsWith("e")) {
            errorInfo.error = errorType::delVerbE;
            return errorInfo;
        }
        /**< Проверка на удвоение согласной при использовании окончания -ing*/
        else if (this->wordText.toLower().compare(baseFormStr + "ing") == 0) {
            errorInfo.error = errorType::doubleConsonantIng;
            return errorInfo;
        }
        /**< Проверка на отсутствующий -ing в окончании глагола*/
        else if(other.wordText.toLower().compare(baseFormStr + "ing") == 0)
        {
            errorInfo.error = errorType::verbIng;
            return errorInfo;
        }
    }

    /**< Проверка на сохранение окончания e в начальной форме глгогола и добавления окончания -s*/
    if(baseFormStr.endsWith("e")){
        if(other.wordText.toLower().compare(baseFormStr+"s") == 0) {
            errorInfo.error = errorType::saveVerbE;
            return errorInfo;
        }
    }

    /**< Проверка на наличие окончания -s*/
    QString verbS = baseFormStr + "s";
    if (other.wordText.toLower() == verbS.toLower()) {
        errorInfo.error = errorType::verbEndS;
        return errorInfo;
    }

    /**< Проверка на наличие окончания -es*/
    QString verbES = baseFormStr + "es";
    if (other.wordText.toLower() == verbES.toLower()) {
        errorInfo.error = errorType::verbEndEs;
        return errorInfo;
    }
}

ErrorInfo Word::findMistakeAdj(Word other) {

    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    /**< Исключения для прилагательных*/
    /// Если Обе части речи не прилагательные
    if (this->postag != Adj && other.postag != Adj) {
            throw std::runtime_error("Both words are not adjectives");
        }
    /**< Если возможное некорректное слово не прилагательное*/
    if (this->postag != Adj && other.postag == Adj) {
            throw std::runtime_error("The incorrect word is not an adjective");
        }
    /**< Если корректное слово не прилагательное*/
    if (this->postag == Adj && other.postag != Adj) {
            throw std::runtime_error("The correct word is not an adjective");
        }

    /**< Если слова одинаковые*/
    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    /**< Получение начальной формы текущего слова*/
    QString baseForm = base_form(other.wordText, ADJ);

    /**< 2. Проверка наличия слова в списке IrregularAdj*/
    if (std::find(IrregularAdj.begin(), IrregularAdj.end(), baseForm) != IrregularAdj.end()) {
        errorInfo.error = errorType::incorrectDegreesComparisonAdj;
        return errorInfo;
    }

    /**< 3. Проверка на замену гласной буквы -y в начальной форме на er/est*/
    if (baseForm.endsWith("y")) {
        if (other.wordText.endsWith("er")) {
            errorInfo.error = errorType::incorrectFormCompAdj;
        } else if (other.wordText.endsWith("est")) {
            errorInfo.error = errorType::incorrectFormSuperlatAdj;
        }
        return errorInfo;
    }

    /**< 4. Подсчет гласных букв в начальной форме прилагательного*/
    QString vowels = "aeiouAEIOU";
    int vowelCount = 0;
    for (QChar ch : baseForm) {
        if (vowels.contains(ch)) {
            vowelCount++;
        }
    }

    /**< Проверка прилагательного на наличие удвоенной согласной, при том условии, что в начальной форме у него 1 гласная буква*/
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

    /**< Употребление суффикосв er/est с прилагательными, где употреблять его так невозможно*/
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

    /**< 5. Проверка окончания на "er"*/
    if (other.wordText.endsWith("er")) {
        errorInfo.error = errorType::incorrectFormCompAdj;
        return errorInfo;
    }
    /**< 6. Проверка окончания на "est"*/
    else if (other.wordText.endsWith("est")) {
        errorInfo.error = errorType::incorrectFormSuperlatAdj;
        return errorInfo;
    }
}

ErrorInfo Word::findMistakeNum(Word other) {
    ErrorInfo errorInfo;
    errorInfo.idxErroneousWord = this->id;

    /**< Исключения для числительных*/
    /// Если Обе части речи не числительные
    if (this->postag != Num && other.postag != Num) {
            throw std::runtime_error("Both words are not numerals");
        }
    /**< Если возможное некорректное слово не числительное*/
    if (this->postag != Num && other.postag == Num) {
            throw std::runtime_error("The incorrect word is not a numeral");
        }
    /**< Если корректное слово не числительное*/
    if (this->postag == Num && other.postag != Num) {
            throw std::runtime_error("The correct word is not a numeral");
        }

    /**< Если слова одинаковые*/
    if(this->wordText == other.wordText)
    {
        errorInfo.error = zeroMistakes;
        return errorInfo;
    }

    /**< 1. Проверка на особые числительные: first, second, third*/
    if (other.wordText.toLower() == "first" || other.wordText.toLower() == "second" || other.wordText.toLower() == "third") {
        errorInfo.error = errorType::irregularNumForm;
        return errorInfo;
    }

    /**< 2. Проверка окончания на -th*/
    if (other.wordText.endsWith("th")) {
        errorInfo.error = errorType::incorrectNumForm;
        return errorInfo;
    }
}

QList<ErrorInfo> Sentence::compare(Sentence other) {
    QList<ErrorInfo> errors;
    /**< Проход по словам предложений*/
    for (int i = 0; i < words.size(); ++i) {
        Word correctWord = words[i];
        Word incorrectWord = other.words[i];

        /**< 1.1. Сравнение текущего слова*/
        if (correctWord.wordText != incorrectWord.wordText) {
            /**< 1.2. Вызов функции compareWords, если слова не совпадают*/
            ErrorInfo error = incorrectWord.compareWords(correctWord);
            errors.append(error);
        } else {
            /**< 1.3. Присвоение типа ошибки - zeroMistakes, если слова совпадают*/
            ErrorInfo error;
            error.idxErroneousWord = incorrectWord.id;
            error.error = errorType::zeroMistakes;
            errors.append(error);
        }
    }

    /**< Вернуть все найденные ошибки*/
    return errors;
}
