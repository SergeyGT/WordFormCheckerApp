#pragma once
#include <QString>
#include <vector>
#include <QList>
#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <fstream>

class ErrorInfo;

class Word;
/**
 * @brief Перечисление для pos-тегов.
 *
 * Это перечисление содержит различные типы частей речи слов.
*/
enum PosTag
{
    Noun, ///< Существительное.
    Verb, ///< Глагол.
    Adj, ///< Прилагательное.
    Adverb, ///< Наречие.
    Num, ///< Числительное.
    Pronoun, ///< Местоимение.
    Preposition, ///< Предлог.
    Conjunction, ///< Союз.
    Interjection, ///< Междометие.
    Article, ///< Артикль.
    Determiner ///< Разделитель.
};

/**
 * @brief Перечисление для типов ошибок.
 *
 * Это перечисление содержит различные типы ошибок, которые могут возникнуть.
*/
enum errorType {
    doubleConsonantEd, /**< Двойная согласная в глаголе с окончанием ed*/
    doubleConsonantIng, /**< Двойная согласная в глаголе с окончанием ing*/
    doubleConsonantAdjEr, /**< Двойная согласная в прилагательном -er */
    doubleConsonantAdjEst, /**< Двойная согласная в прилагательном -est */
    UnnecessarErAdj, /**< Прилагательного с суффиксом -er не существует*/
    UnnecessarEstAdj, /**< Прилагательного с суффиксом -est не существует*/
    delVerbE, /**< Удаление 'e' в глаголе */
    verbEndS, /**< Окончание глагола на 's' */
    verbEndEs, /**< Окончание глагола на 'es' */
    verbIng, /**< Окончание глагола на 'ing' */
    saveVerbE, /**< Сохранение окончания -e глагола*/
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
    mistakesInFormatPossessiveMultipleFormNoun, /**< Ошибки во мн.ч. притяжательной формы существительных */
    irregularNumForm, /**< Использование числительного-исключения */
    incorrectNumForm, /**< Использование числительного с образованием неверной формы*/
    unknownError, /**< Неизвестная ошибка */
    zeroMistakes /**< Нет ошибок */
};


// Объявление вспомогательной функции для приведения слова в начальную форму
QString base_form(const QString& word, int pos);


/**
 * @brief Класс для представления слова.
 *
 * Класс Word содержит информацию о тексте слова, его POS-теге и ID номере в предложении.
*/
class Word
{
public:
    QString wordText; /**< Текст слова */
    int id; /**< уникальный идентификатор(номер) слова */
    PosTag postag; /**< Часть речи слова */
public:

    Word() = default;
    Word(const QString &text, int idx, PosTag tag)
        : wordText(text), id(idx), postag(tag) {}
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
    ErrorInfo compareWords(Word other);

    /**
     * @brief Определение типа ошибки в существительных.
     *
     * Определяет тип ошибки в данном существительном.
     * @param other Другое существительное для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeNoun(Word other);

    /**
     * @brief Определение типа ошибки в глаголах.
     *
     * Определяет тип ошибки в данном глаголе.
     * @param other Другой глагол для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeVerb(Word other);

    /**
     * @brief Определение типа ошибки в прилагательных.
     *
     * Определяет тип ошибки в данном прилагательном.
     * @param other Другое прилагательное для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeAdj(Word other);

    /**
     * @brief Определение типа ошибки в числительных.
     *
     * Определяет тип ошибки в данном числительном.
     * @param other Другое числительное для сравнения.
     * @return Информация об ошибке.
     */
    ErrorInfo findMistakeNum(Word other);


    static std::vector<QString> OnlyPluralNouns; ///< Статический вектор для хранения существительных только во мн.ч..
    static std::vector<QString> IrregularNouns; ///< Статический вектор для хранения неправильных существительных.
    static std::vector<QString> IrregularVerbs; ///< Статический вектор для хранения неправильных глаголов.
    static std::vector<QString> IrregularAdj; ///< Статический вектор для хранения неправильных прилагательных.

    QString getWordText() const { return wordText; }
    PosTag getPosTag() const { return postag; }
    int getWordID() const { return id; }


};

/**
 * @brief Класс для представления ошибки слова.
 *
 * Класс ErrorInfo содержит информацию о слове в котором ошибка и тип ошибки.
*/
class ErrorInfo
{
public:
    int idxErroneousWord; /**< Индекс слова */
    errorType error; /**< Тип ошибки слова */

    ErrorInfo()
    {
        idxErroneousWord = 0;
        error = zeroMistakes;
    }

    errorType getErrorType() const { return error; }
    int getWordIndex() const { return idxErroneousWord; }
};

/**
 * @brief Класс для представления предложения.
 *
 * Класс Sentence содержит информацию о тексте предлжения и списке всех слов предложения.
*/
class Sentence
{
public:
    QString sentenceText; /**< Текст предложения */
    QList<Word> words; /**< Список всех слов */
public:
    Sentence()
    {

    }

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
    QList<ErrorInfo> compare(Sentence other);

};
