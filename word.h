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
    Noun,
    Verb,
    Adj,
    Adverb,
    Num,
    Pronoun,
    Preposition,
    Conjunction,
    Interjection,
    Article,
    Determiner
};

/**
 * @brief Перечисление для типов ошибок.
 *
 * Это перечисление содержит различные типы ошибок, которые могут возникнуть.
*/
enum errorType {
    doubleConsonantEd, /**< Двойная согласная в глаголе*/
    doubleConsonantIng,
    doubleConsonantAdjEr, /**< Двойная согласная в прилагательном */
    doubleConsonantAdjEst,
    UnnecessarErAdj,
    UnnecessarEstAdj,
    delVerbE, /**< Удаление 'e' в глаголе */
    verbEndS, /**< Окончание глагола на 's' */
    verbEndEs,
    verbIng,
    saveVerbE,
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
    mistakesInFormatPossessiveMultipleFormNoun,
    irregularNumForm,
    incorrectNumForm,
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
//    Word() {
//        wordText = "";
//        postag = Noun;
//        id = 0;
//    }

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

    ErrorInfo findMistakeNum(Word other);

    QString getWordText() const { return wordText; }
    PosTag getPosTag() const { return postag; }
    int getWordID() const { return id; }


    static std::vector<QString> OnlyPluralNouns;
    static std::vector<QString> IrregularNouns;
    static std::vector<QString> IrregularVerbs;
    static std::vector<QString> IrregularAdj;


};

/**
 * @brief Класс для представления ошибки слова.
 *
 * Класс ErrorInfo содержит информацию о слове в котором ошибка и тип ошибки.
*/
class ErrorInfo
{
public:
    int idxErroneousWord;
    errorType error;

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
