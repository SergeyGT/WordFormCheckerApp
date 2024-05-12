#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <fstream>

class ErrorInfo;
/**
 * @brief Перечисление для pos-тегов.
 *
 * Это перечисление содержит различные типы частей речи слов.
*/
enum PosTag
{
    Noun,
    Verb,
    Adjective,
    Adverb,
    Pronoun,
    Preposition,
    Conjunction,
    Interjection,
    Determiner
};

/**
 * @brief Перечисление для типов ошибок.
 *
 * Это перечисление содержит различные типы ошибок, которые могут возникнуть.
*/
enum errorType {
    doubleConsonant, /**< Двойная согласная в глаголе*/
    doubleConsonantAdj, /**< Двойная согласная в прилагательном */
    delVerbE, /**< Удаление 'e' в глаголе */
    verbendS, /**< Окончание глагола на 's' */
    verbendES, /**< Окончание глагола на 'es' */
    nounEndS, /**< Окончание существительного на 's' */
    nounEndES, /**< Окончание существительного на 'es' */
    wrongFormIrregularVerb, /**< Неправильная форма неправильного глагола */
    nounsIrregularPluralForm, /**< Неправильная форма множественного числа неправильных существительных */
    nounsOnlyPluralForm, /**< Только форма множественного числа существительных */
    incorrectUseQuantOrdinalNumbers, /**< Неправильное использование порядковых числительных */
    incorrectDegreesComparisonAdj, /**< Неправильное сравнение степеней прилагательных */
    incorrectFormCompAdj, /**< Неправильная форма сравнительной степени прилагательного */
    incorrectFormSuperlatAdj, /**< Неправильная форма превосходной степени прилагательного */
    mistakesInFormatPossessiveFormNouns, /**< Ошибки в формате притяжательной формы существительных */
    unknownError, /**< Неизвестная ошибка */
    zeroMistakes /**< Нет ошибок */
};



/**
 * @brief Класс для представления слова.
 *
 * Класс Word содержит информацию о тексте слова, его POS-теге и ID номере в предложении.
*/
class Word
{
private:
    QString wordText; /**< Текст слова */
    int id; /**< уникальный идентификатор(номер) слова */
    PosTag postag; /**< Часть речи слова */
public:
    /**
     * @brief Конструктор класса Word.
     * @param text Текст слова.
     * @param tag POS-тег слова.
     * @param wordId ID номер слова в предложении.
     */
    Word(QString text, PosTag tag, int wordId);

    /**
     * @brief Сравнение слов.
     *
     * Сравнивает данное слово с другим и возвращает информацию об ошибке.
     * @param other Другое слово для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo compareWords(Word other) const;

    /**
     * @brief Определение типа ошибки в существительных.
     *
     * Определяет тип ошибки в данном существительном.
     * @param other Другое существительное для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeNoun(Word other) const;

    /**
     * @brief Определение типа ошибки в глаголах.
     *
     * Определяет тип ошибки в данном глаголе.
     * @param other Другой глагол для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeVerb(Word other) const;

    /**
     * @brief Определение типа ошибки в прилагательных.
     *
     * Определяет тип ошибки в данном прилагательном.
     * @param other Другое прилагательное для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeAdj(Word other) const;
};

/**
 * @brief Класс для представления ошибки слова.
 *
 * Класс ErrorInfo содержит информацию о слове в котором ошибка и тип ошибки.
*/
class ErrorInfo
{
    Word erroneousWord;
    errorType error;
};

/**
 * @brief Класс для представления предложения.
 *
 * Класс Sentence содержит информацию о тексте предлжения и списке всех слов предложения.
*/
class Sentence
{
private:
    QString sentenceText; /**< Текст предложения */
    QList<Word> words; /**< Список всех слов */
public:
    /**
     * @brief Конструктор класса Sentence.
     * @param text Текст предложения.
     * @param wordList Список слов в предложении.
     */
    Sentence(QString text, QList<Word> wordList);

    /**
     * @brief Сравнение предложений.
     *
     * Сравнивает данное предложение с другим и возвращает список ошибок.
     * @param other Другое предложение для сравнения.
     * @return Список ошибок, возникших при сравнении.
     */
    QList<ErrorInfo> compare(Sentence other) const;
};


/**
 * @brief Функция считывания предложений из файлов.
 *
 * Данная функция считывает неправильное предложение из первого файла, а затем считывает
 * корректное предложение и POS-теги из второго файла.
 *
 * @param filename1 Имя первого файла, содержащего слова с возможной ошибкой.
 * @param filename2 Имя второго файла, содержащего корректные предложения и POS-теги.
 * @param wrongSentence Пустая строка, в которую будет записано неправильное предложение.
 * @param correctSentence Пустая строка, в которую будет записано корректное предложение.
 * @param posTags Пустая строка, в которую будет записаны POS-теги.
*/
void readFiles(const std::string& filename1, const std::string& filename2, std::string& wrongSentence, std::string& correctSentence, std::string& posTags) {
    // Открыть первый файл
    std::ifstream file1(filename1);
    if (!file1.is_open()) {
        std::cerr << "Error: Unable to open file " << filename1 << std::endl;
        return;
    }

    // Прочитать неправильное предложение
    std::getline(file1, wrongSentence);
    if (wrongSentence.empty()) {
        std::cerr << "Error: Incorrect sentence is empty" << std::endl;
        file1.close();
        return;
    }

    // Закрыть первый файл
    file1.close();

    // Открыть второй файл
    std::ifstream file2(filename2);
    if (!file2.is_open()) {
        std::cerr << "Error: Unable to open file " << filename2 << std::endl;
        return;
    }

    // Прочитать корректное предложение
    std::getline(file2, correctSentence);
    if (correctSentence.empty()) {
        std::cerr << "Error: Correct sentence is empty" << std::endl;
        file2.close();
        return;
    }

    // Прочитать pos-теги
    std::getline(file2, posTags);
    if (posTags.empty()) {
        std::cerr << "Error: POS tags are empty" << std::endl;
        file2.close();
        return;
    }

    // Закрыть второй файл
    file2.close();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char *bf;

    if (wninit()) {
      fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
      exit(-1);
    }

    bf = morphstr("fat", ADJ);
// Если слово уже в начальной форме то будет ФЕЙЛ
    printf("%s\n", bf ? bf : "FAIL");

    return a.exec();
}
