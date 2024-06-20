#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <fstream>
#include "word.h"
#include "test_sentence_compare.h"
#include "test_word_findmistakenum.h"
#include "test_word_comparewords.h"
#include "test_word_findMistakeNoun.h"
#include "test_word_findmistakeadj.h"
#include "test_word_findmistakeverb.h"

// Перечисление ошибок при обработке предложений
enum class sentencesProcessingCodes {
    sentencesProcessed,
    fewerWordsThanTags,
    fewerTagsThanWords,
    wrongPosTag
};

// Класс для обработки ошибок предложения
class SentenceDataError {
public:
    sentencesProcessingCodes sentenceProcessingResult;
    int countWords = 0;

    void printSentenceDataMessage() {}
};


enum class fileProcessingCodes {
    filesProcessed,
    inputCorrectFileNotExist,
    inputIncorrectFileNotExist,
    cantCreateOutputFile,
    wrongStrCountInCorrectFile,
    wrongStrCountInVerifiedFile,
    correctFileIsEmpty,
    invalidFileIsEmpty,
    posTagsAreEmpty
};

class InvalidInputError {
public:
    fileProcessingCodes fileProcessingResult;
    int countOfWordsInFile = 0;
    int countOfPosTagsInFile = 0;
    void printInputDataMessage() {}
};

// Функция преобразования QString в PosTag
PosTag stringToPosTag(const QString& posTagStr) {
    static const QHash<QString, PosTag> posTagMap = {
        {"NOUN", PosTag::Noun},
        {"VERB", PosTag::Verb},
        {"ADJ", PosTag::Adj},
        {"NUM", PosTag::Num},
        {"ARTICLE", PosTag::Article},
        {"ADVERB", PosTag::Adverb},
        {"PRONOUN", PosTag::Pronoun},
        {"PREPOSITION", PosTag::Preposition},
        {"CONJUCTION", PosTag::Conjunction},
        {"INTERJECTION", PosTag::Interjection},
        {"DETERMINER", PosTag::Determiner},
    };

    return posTagMap.value(posTagStr, PosTag::Noun); // или другой дефолтный PosTag
}

void writeErrorsToFile(const QList<ErrorInfo>& errors, const QString& fileName, const Sentence& incorrect, const Sentence& correct, InvalidInputError& errorsObj) {
    QFile file(fileName);

    // Попытка открыть файл для записи
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        errorsObj.fileProcessingResult = fileProcessingCodes::cantCreateOutputFile;
        errorsObj.printInputDataMessage();
        return;
    }

    QTextStream out(&file);

    // Подсчет количества ошибок, исключая zeroMistakes
    int nonZeroMistakesCount = 0;
    for (const ErrorInfo& error : errors) {
        if (error.getErrorType() != errorType::zeroMistakes) {
            nonZeroMistakesCount++;
        }
    }

    if(nonZeroMistakesCount > 0)
    {
        QString numErrors = QString::number(nonZeroMistakesCount) + " mistake(s) found.\n";
        out <<  numErrors;
    }
    // Запись информации об ошибках
       for (const ErrorInfo& error : errors) {
           if (error.getErrorType() == errorType::zeroMistakes) {
               continue; // Пропускаем ошибки типа zeroMistakes
           }

           int wordIndex = error.getWordIndex();
           QString wrongWord = incorrect.words[wordIndex].getWordText();
           QString correctWord = correct.words[wordIndex].getWordText();
           QString errorType = "";

           switch (error.getErrorType()) {
               case errorType::wrongFormIrregularVerb:
                   errorType = "Wrong form irregular verb.";
                   break;
               case errorType::doubleConsonantEd:
                   errorType = "Double consonant ed.";
                   break;
               case errorType::delVerbE:
                   errorType = "Delete verb -e.";
                   break;
               case errorType::verbEndS:
                   errorType = "Verb end -s.";
                   break;
               case errorType::verbEndEs:
                   errorType = "Verb end -Es.";
                   break;
               case errorType::nounsIrregularPluralForm:
                   errorType = "Irregular plural form";
                   break;
               case errorType::doubleConsonantIng:
                   errorType = "Double consonant -Ing verb.";
                   break;
               case errorType::doubleConsonantAdjEr:
                   errorType = "Double Consonant Adjective suffix -er.";
                   break;
               case errorType::doubleConsonantAdjEst:
                   errorType = "Double Consonant Adjective suffix -est.";
                   break;
               case errorType::incorrectFormCompAdj:
                   errorType = "Incorrect form comparative adjective.";
                   break;
               case errorType::incorrectFormSuperlatAdj:
                   errorType = "Incorrect form superlative adjective.";
                   break;
               case errorType::irregularNumForm:
                   errorType = "Irregular number form.";
                   break;
               case errorType::incorrectNumForm:
                   errorType = "Incorrect number form.";
                   break;
               case errorType::nounEndS:
                   errorType = "Noun end -s.";
                   break;
               case errorType::nounEndES:
                   errorType = "Noun end -es.";
                   break;
               case errorType::nounsOnlyPluralForm:
                   errorType = "Noun in only plural form.";
                   break;
               case errorType::mistakesInFormatPossessiveMultipleFormNoun:
                   errorType = "Format Possessive Multiple Form Noun";
                   break;
               case errorType::mistakesInFormatPossessiveFormNouns:
                   errorType = "Format Possessive Form Nouns.";
                   break;
               case errorType::incorrectDegreesComparisonAdj:
                   errorType = "Incorrect degrees comparison in adjective.";
                   break;
               case errorType::saveVerbE:
                   errorType = "Saving the ending -e verb.";
                   break;
               case errorType::UnnecessarErAdj:
                   errorType = "Unnecessar suffix -er in adjective.";
                   break;
               case errorType::UnnecessarEstAdj:
                   errorType = "Unnecessar suffix -est in adjective.";
                   break;
               case errorType::verbIng:
                   errorType = "Miss -ing verb.";
                   break;
               default:
                   errorType = "unknown error";
                   break;
           }

           // Формируем текст ошибки
           QString errorText = errorType + " Incorrectly used - " + wrongWord + " (word №" + QString::number(wordIndex + 1) + ") Correct form: " + correctWord + "\n";

           // Записываем текст ошибки в файл
           out << errorText;

       }

    // Если никаких ошибок не было найдено - проверить файл на его содержимое
    bool isFileEmpty = false;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
       QTextStream in(&file);
       // Если файл не пуст, то все останется без изменений
       if (!in.readAll().isEmpty()) {
           isFileEmpty = false;
       }
       // Если файл пуст, то поменять флажок на true - т.е. ошибок в предложении нет
       else {isFileEmpty = true;}
           file.close();
    }

    // Печать сообщения об отсутсвии ошибок в предложении
    if (isFileEmpty) {
        out << "Zero mistakes in sentence\n";
        file.close();
        return;
    }

    file.close();
}

// Функция для заполнения объектов класса Sentence
void writeToSentenceObjects(const QString& wrongSentence, const QString& correctSentence, const QString& posTags, Sentence& incorrect, Sentence& correct, SentenceDataError& errors) {
    // Разделение строк на слова и теги
    QStringList wrongWords = wrongSentence.split(" ", QString::SkipEmptyParts);
    QStringList correctWords = correctSentence.split(" ", QString::SkipEmptyParts);
    QStringList posTagList = posTags.split(" ", QString::SkipEmptyParts);

    // Проверка на наличие ошибок в количестве слов и тегов
    if (posTagList.size() != correctWords.size() || posTagList.size() != wrongWords.size()) {
        if (posTagList.size() < wrongWords.size()) {
            errors.sentenceProcessingResult = sentencesProcessingCodes::fewerTagsThanWords;
        } else if (posTagList.size() > wrongWords.size()) {
            errors.sentenceProcessingResult = sentencesProcessingCodes::fewerWordsThanTags;
        } else {
            errors.sentenceProcessingResult = sentencesProcessingCodes::wrongPosTag;
        }
        errors.printSentenceDataMessage();
        return;
    }

    // Заполнение объектов Sentence
    for (int i = 0; i < wrongWords.size(); ++i) {
        Word wrongWord;
        wrongWord.wordText = wrongWords[i];
        wrongWord.postag = stringToPosTag(posTagList[i]);
        wrongWord.id = i;
        incorrect.words.append(wrongWord);
    }

    for (int i = 0; i < correctWords.size(); ++i) {
        Word correctWord;
        correctWord.wordText = correctWords[i];
        correctWord.postag = stringToPosTag(posTagList[i]);
        correctWord.id = i;
        correct.words.append(correctWord);
    }

    // Сохранение текстов предложений
    incorrect.sentenceText = wrongSentence;
    correct.sentenceText = correctSentence;

    // Установка успешного результата обработки
    errors.sentenceProcessingResult = sentencesProcessingCodes::sentencesProcessed;
}


void readFiles(const QString& filename1, const QString& filename2, QString& wrongSentence, QString& correctSentence, QString& posTags, InvalidInputError& errors) {
    // Открыть первый файл по имени, полученному в качестве входного параметра
    QFile file1(filename1);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors.fileProcessingResult = fileProcessingCodes::inputIncorrectFileNotExist;
        errors.printInputDataMessage();
        return;
    }

    // Прочитать первую строку из первого файла
    QTextStream in1(&file1);
    if (in1.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::invalidFileIsEmpty;
        errors.printInputDataMessage();
        file1.close();
        return;
    }
    wrongSentence = in1.readLine();

    // Открыть второй файл по имени, полученному в качестве входного параметра
    QFile file2(filename2);
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors.fileProcessingResult = fileProcessingCodes::inputCorrectFileNotExist;
        errors.printInputDataMessage();
        file1.close();
        return;
    }

    // Прочитать первые две строки из второго файла
    QTextStream in2(&file2);
    if (in2.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::correctFileIsEmpty;
        errors.printInputDataMessage();
        file1.close();
        file2.close();
        return;
    }
    correctSentence = in2.readLine();
    if (in2.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::posTagsAreEmpty;
        errors.printInputDataMessage();
        file1.close();
        file2.close();
        return;
    }
    posTags = in2.readLine();

    // Установить успешный результат обработки файлов в объекте InputDataError
    errors.fileProcessingResult = fileProcessingCodes::filesProcessed;

    // Закрыть оба файла
    file1.close();
    file2.close();
}

//int main(int argc, char *argv[]) {
//    // QCoreApplication a(argc, argv);

////    if (argc < 4) {
////        std::cerr << "Usage: " << argv[0] << " <path_to_incorrect_sentence_file> <path_to_correct_sentence_file> <path_to_output_file>" << std::endl;
////        return 1;
////    }

//    QString wrongSentence;
//    QString correctSentence;
//    QString posTags;
//    InvalidInputError errors;
//    SentenceDataError sentenceErrors;

//    //readFiles(argv[1], argv[2], wrongSentence, correctSentence, posTags, errors);
//    readFiles("C:\\Users\\Acer\\WordFormCheckerApp\\incorrect.txt", "C:\\Users\\Acer\\WordFormCheckerApp\\correct.txt", wrongSentence, correctSentence, posTags, errors);

//    // Объекты для хранения предложений
//    Sentence incorrectSentence;
//    Sentence correctSentenceObject;

//    // Заполнение объектов Sentence данными из предложений
//    writeToSentenceObjects(wrongSentence, correctSentence, posTags, incorrectSentence, correctSentenceObject, sentenceErrors);

//    //Поиск ошибок в предложениях
//    QList<ErrorInfo> errorsList = correctSentenceObject.compare(incorrectSentence);

//    // Запись ошибок в выходной файл
//    // writeErrorsToFile(errorsList, argv[3], incorrectSentence, correctSentenceObject, errors);
//    writeErrorsToFile(errorsList, "C:\\Users\\Acer\\WordFormCheckerApp\\output.txt", incorrectSentence, correctSentenceObject, errors);

//    //return a.exec();
//    return 0;

////    return 0;
//}


int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    int status = 0;

    // Создаем экземпляр класса тестов
    test_sentence_compare test_compare;
    test_word_findMistakeNum test_num;
    test_word_findMistakeAdj test_adj;
    TestWordfindMistakeNoun test_noun;
    Test_word_findMistakeVerb test_verb;
    test_word_compareWords test_compare_words;


    // Запускаем тесты
    status |= QTest::qExec(&test_compare, argc, argv);
    status |= QTest::qExec(&test_num, argc, argv);
    status |= QTest::qExec(&test_adj, argc, argv);
    status |= QTest::qExec(&test_noun, argc, argv);
    status |= QTest::qExec(&test_verb, argc, argv);
    status |= QTest::qExec(&test_compare_words, argc, argv);

    return status;
}
