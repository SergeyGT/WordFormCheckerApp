#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QRegularExpression>
#include <fstream>
#include "word.h"
#include "test_sentence_compare.h"
#include "test_word_findmistakenum.h"
#include "test_word_comparewords.h"
#include "test_word_findMistakeNoun.h"
#include "test_word_findmistakeadj.h"
#include "test_word_findmistakeverb.h"

/**
 * @brief Перечисление ошибок при обработке предложений
 */
enum class sentencesProcessingCodes {
    sentencesProcessed,     /**< Предложения обработаны успешно.*/
    fewerWordsThanTags,     /**< Ошибка: меньше слов, чем POS-тегов.*/
    fewerTagsThanWords,     /**< Ошибка: меньше POS-тегов, чем слов.*/
    wrongPosTag             /**< Ошибка: встречен неправильный POS-тег.*/
};

/**
 * @brief Класс для обработки ошибок данных предложения.
 */
class SentenceDataError {
public:
    sentencesProcessingCodes sentenceProcessingResult; /**< Результат обработки предложения.*/
    int countWords = 0; /**< Количество слов в предложении.*/

    /**
     * @brief Выводит сообщение об ошибке данных предложения в стандартный вывод.
     */
    void printSentenceDataMessage() {
        switch (sentenceProcessingResult) {
            case sentencesProcessingCodes::sentencesProcessed:
                std::cout << "Sentences processed successfully."<< std::endl;
                break;
            case sentencesProcessingCodes::fewerWordsThanTags:
                std::cout << "Error: Fewer words than POS tags."<< std::endl;
                break;
            case sentencesProcessingCodes::fewerTagsThanWords:
                std::cout << "Error: Fewer POS tags than words." << std::endl;
                break;
            case sentencesProcessingCodes::wrongPosTag:
                std::cout << "Error: Incorrect POS tag encountered." << std::endl;
                break;
            default:
                std::cout << "Unknown error." << std::endl;
                break;
        }
    }
};

/**
 * @brief Перечисление кодов обработки файлов.
 */
enum class fileProcessingCodes {
    filesProcessed,                     /**< Файлы обработаны успешно.*/
    inputCorrectFileNotExist,           /**< Ошибка: отсутствует входной корректный файл.*/
    inputIncorrectFileNotExist,         /**< Ошибка: отсутствует входной некорректный файл.*/
    cantCreateOutputFile,               /**< Ошибка: невозможно создать выходной файл.*/
    wrongStrCountInCorrectFile,         /**< Ошибка: неправильное количество строк в корректном файле.*/
    wrongStrCountInVerifiedFile,        /**< Ошибка: неправильное количество строк в проверенном файле.*/
    correctFileIsEmpty,                 /**< Ошибка: корректный файл пуст.*/
    invalidFileIsEmpty,                 /**< Ошибка: некорректный файл пуст.*/
    posTagsAreEmpty                     /**< Ошибка: POS-теги отсутствуют.*/
};

/**
 * @brief Класс для обработки ошибок неверного ввода.
 */
class InvalidInputError {
public:
    fileProcessingCodes fileProcessingResult;    /**< Результат обработки файла.*/
    int countOfWordsInFile = 0;                  /**< Количество слов в файле.*/
    int countOfPosTagsInFile = 0;                /**< Количество POS-тегов в файле.*/

    /**
     * @brief Выводит сообщение об ошибке неверного ввода в стандартный вывод.
     */
    void printInputDataMessage() const {
        switch (fileProcessingResult) {
            case fileProcessingCodes::filesProcessed:
                std::cout << "Files processed successfully.\n";
                break;
            case fileProcessingCodes::inputCorrectFileNotExist:
                std::cout << "Input correct file does not exist.\n";
                break;
            case fileProcessingCodes::inputIncorrectFileNotExist:
                std::cout << "Input incorrect file does not exist.\n";
                break;
            case fileProcessingCodes::cantCreateOutputFile:
                std::cout << "Cannot create output file.\n";
                break;
            case fileProcessingCodes::wrongStrCountInCorrectFile:
                std::cout << "Wrong string count in incorrect file.\n";
                break;
            case fileProcessingCodes::wrongStrCountInVerifiedFile:
                std::cout << "Wrong string count in verified file.\n";
                break;
            case fileProcessingCodes::correctFileIsEmpty:
                std::cout << "Correct file is empty.\n";
                break;
            case fileProcessingCodes::invalidFileIsEmpty:
                std::cout << "Invalid file is empty.\n";
                break;
            case fileProcessingCodes::posTagsAreEmpty:
                std::cout << "POS tags are empty.\n";
                break;
            default:
                std::cout << "Unknown file processing result.\n";
                break;
        }
    }
};

/**
  @brief функция преобразования строки в часть речи
  @param posTagStr - pos-тег в виде строки
*/
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

    return posTagMap.value(posTagStr, PosTag::Noun); /**< Дефолтный pos-тег*/
}

/**
 * @brief Записывает ошибки в файл.
 *
 * Функция записывает информацию об ошибках в указанный файл.
 * Каждая ошибка представлена в списке `errors` объектом типа ErrorInfo.
 *
 * @param errors Список ошибок для записи.
 * @param fileName Имя файла, в который нужно записать ошибки.
 * @param incorrect Некорректное предложение.
 * @param correct Корректное предложение.
 * @param errorsObj Объект ошибок неверного ввода для дополнительной информации.
 */
void writeErrorsToFile(const QList<ErrorInfo>& errors, const QString& fileName, const Sentence& incorrect, const Sentence& correct, InvalidInputError& errorsObj) {
    QFile file(fileName);

    /**< Попытка открыть выходной файл для записи*/
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        errorsObj.fileProcessingResult = fileProcessingCodes::cantCreateOutputFile;
        errorsObj.printInputDataMessage();
        return;
    }

    QTextStream out(&file);

    /**< Подсчет количества ошибок, исключая zeroMistakes*/
    int nonZeroMistakesCount = 0;
    for (const ErrorInfo& error : errors) {
        if (error.getErrorType() != errorType::zeroMistakes) {
            nonZeroMistakesCount++;
        }
    }

    /**< Печать сообщения об отсутсвии ошибок в предложении, если ошибок 0*/
    if (nonZeroMistakesCount == 0) {
        out << "Zero mistakes in sentence.\n";
        file.close();
        return;
    }

    /**< Если ошибки есть - выести сообщение с кол-вом ошибок*/
    if(nonZeroMistakesCount > 0)
    {
        QString numErrors = QString::number(nonZeroMistakesCount) + " mistake(s) found.\n";
        out <<  numErrors;
    }

    /**< Запись информации об ошибках*/
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

           /**< Формируем текст ошибки - на основании определенного типа ошибки*/
           QString errorText = errorType + " Incorrectly used - " + wrongWord + " (word №" + QString::number(wordIndex + 1) + ") Correct form: " + correctWord + "\n";

           /**< Записываем текст ошибки в файл*/
           out << errorText;

       }

    /**< Будем считать, что файлы записаны без ошибок*/
    errorsObj.fileProcessingResult = fileProcessingCodes::filesProcessed;

    /**< Закрываем выходной файл*/
    file.close();
}

/**
 * @brief Функция для заполнения объектов класса Sentence.
 *
 * Функция заполняет объекты класса Sentence на основе предоставленных строк некорректного предложения,
 * корректного предложения и POS-тегов. Результаты заполнения сохраняются в переданных объектах incorrect и correct.
 * В случае ошибок заполняется объект errors.
 *
 * @param wrongSentence Строка, содержащая некорректное предложение.
 * @param correctSentence Строка, содержащая корректное предложение.
 * @param posTags Строка, содержащая POS-теги.
 * @param incorrect Объект класса Sentence, представляющий некорректное предложение.
 * @param correct Объект класса Sentence, представляющий корректное предложение.
 * @param errors Объект класса SentenceDataError для хранения информации об ошибках.
 */
void writeToSentenceObjects(const QString& wrongSentence, const QString& correctSentence, const QString& posTags, Sentence& incorrect, Sentence& correct, SentenceDataError& errors) {

    /**< Регулярное выражение для разбиение строки на слова*/
    QRegularExpression regex("[\\s,\\.]+");

    /**< Разделение строк на слова и теги*/
    QStringList wrongWords = wrongSentence.split(regex, QString::SkipEmptyParts);
    QStringList correctWords = correctSentence.split(regex, QString::SkipEmptyParts);
    QStringList posTagList = posTags.split(" ", QString::SkipEmptyParts);

    /**< Проверка на наличие ошибок в количестве слов и тегов*/
    if (posTagList.size() != correctWords.size() || posTagList.size() != wrongWords.size()) {
        /**< Если тегов меньше чем слов*/
        if (posTagList.size() < wrongWords.size()) {
            errors.sentenceProcessingResult = sentencesProcessingCodes::fewerTagsThanWords;
        }
        /**< Если слов меньше чем тегов*/
        else if (posTagList.size() > wrongWords.size()) {
            errors.sentenceProcessingResult = sentencesProcessingCodes::fewerWordsThanTags;
        } else {
            errors.sentenceProcessingResult = sentencesProcessingCodes::wrongPosTag;
        }
        /**< Сообщение об ошибке*/
        errors.printSentenceDataMessage();
        return;
    }

    /**< Заполнение объектов Sentence - некорректного слова*/
    for (int i = 0; i < wrongWords.size(); ++i) {
        Word wrongWord;
        wrongWord.wordText = wrongWords[i];
        wrongWord.postag = stringToPosTag(posTagList[i]);
        wrongWord.id = i;
        incorrect.words.append(wrongWord);
    }

    /**< Заполнение объектов Sentence - корректного слова*/
    for (int i = 0; i < correctWords.size(); ++i) {
        Word correctWord;
        correctWord.wordText = correctWords[i];
        correctWord.postag = stringToPosTag(posTagList[i]);
        correctWord.id = i;
        correct.words.append(correctWord);
    }

    /**< Сохранение текстов предложений*/
    incorrect.sentenceText = wrongSentence;
    correct.sentenceText = correctSentence;

    /**< Установка успешного результата обработки*/
    errors.sentenceProcessingResult = sentencesProcessingCodes::sentencesProcessed;
}

/**
 * @brief Читает содержимое двух файлов и заполняет строки для некорректного предложения, корректного предложения и POS-тегов.
 *
 * Функция читает содержимое файлов с именами filename1 и filename2, заполняя строки wrongSentence, correctSentence и posTags.
 * В случае возникновения ошибок заполняется объект errors.
 *
 * @param filename1 Имя первого файла, содержащего некорректное предложение.
 * @param filename2 Имя второго файла, содержащего корректное предложение и POS-теги.
 * @param wrongSentence Строка для хранения некорректного предложения, считанного из первого файла.
 * @param correctSentence Строка для хранения корректного предложения, считанного из второго файла.
 * @param posTags Строка для хранения POS-тегов, считанных из второго файла.
 * @param errors Объект класса InvalidInputError для хранения информации об ошибках при чтении файлов.
 */
void readFiles(const QString& filename1, const QString& filename2, QString& wrongSentence, QString& correctSentence, QString& posTags, InvalidInputError& errors) {
    /**< Открыть некорректный файл по имени, полученному в качестве входного параметра*/
    QFile file1(filename1);
    if (!file1.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors.fileProcessingResult = fileProcessingCodes::inputIncorrectFileNotExist;
        errors.printInputDataMessage();
        return;
    }

    /**< Прочитать первую строку из некорректного файла*/
    QTextStream in1(&file1);
    if (in1.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::invalidFileIsEmpty;
        errors.printInputDataMessage();
        file1.close();
        return;
    }

    /**< Сохранение некорректного предложения*/
    wrongSentence = in1.readLine();

    /**< Проверка на наличие второй строки (которая не должна быть)*/
    if (!in1.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::wrongStrCountInCorrectFile;
        errors.printInputDataMessage();
        file1.close();
        return;
    }

    /**< Открыть корректный файл по имени, полученному в качестве входного параметра*/
    QFile file2(filename2);
    if (!file2.open(QIODevice::ReadOnly | QIODevice::Text)) {
        errors.fileProcessingResult = fileProcessingCodes::inputCorrectFileNotExist;
        errors.printInputDataMessage();
        file1.close();
        return;
    }

    /**< Прочитать первые две строки из корректного файла*/
    QTextStream in2(&file2);
    if (in2.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::correctFileIsEmpty;
        errors.printInputDataMessage();
        file1.close();
        file2.close();
        return;
    }

    /**< Сохранение корректного предложения*/
    correctSentence = in2.readLine();

    /**< Проверка на наличие частей речи во второй строке*/
    if (in2.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::posTagsAreEmpty;
        errors.printInputDataMessage();
        file1.close();
        file2.close();
        return;
    }

    /**< Сохранение частей речи*/
    posTags = in2.readLine();

    /**< Проверка на наличие третьей строки (которая не должна быть)*/
    if (!in2.atEnd()) {
        errors.fileProcessingResult = fileProcessingCodes::wrongStrCountInVerifiedFile;
        errors.printInputDataMessage();
        file2.close();
        return;
    }

    /**< Установить успешный результат обработки файлов в объекте InputDataError*/
    errors.fileProcessingResult = fileProcessingCodes::filesProcessed;

    /**< Закрыть оба файла*/
    file1.close();
    file2.close();
}

int main(int argc, char *argv[]) {
    // QCoreApplication a(argc, argv);

//    if (argc < 4) {
//        std::cerr << "Usage: " << argv[0] << " <path_to_incorrect_sentence_file> <path_to_correct_sentence_file> <path_to_output_file>" << std::endl;
//        return 1;
//    }

    QString wrongSentence; /**< Строка для хранения некорректного предложения*/
    QString correctSentence; /**< Строка для хранения корректного предложения*/
    QString posTags; /**< Строка для хранения pos-tags*/
    InvalidInputError errors; /**< Объект для хранения ошибок при чтении файлов*/
    SentenceDataError sentenceErrors; /**< Объект для храннеия ошибок при обработке предложений*/

    /**< Чтение содержимого файлов*/
    //readFiles(argv[1], argv[2], wrongSentence, correctSentence, posTags, errors);
    readFiles("C:\\Users\\Acer\\WordFormCheckerApp\\incorrect.txt", "C:\\Users\\Acer\\WordFormCheckerApp\\correct.txt", wrongSentence, correctSentence, posTags, errors);

    /**< Проверка на ошибки при чтении файлов*/
    if (errors.fileProcessingResult != fileProcessingCodes::filesProcessed) {

        return -1; // Завершаем программу с кодом ошибки
    }

    /**< Объекты для хранения предложений*/
    Sentence incorrectSentence; /**< Объект некорректного предложения*/
    Sentence correctSentenceObject; /**< Объект корректного предложения*/

    /**< Заполнение объектов Sentence данными из предложений*/
    writeToSentenceObjects(wrongSentence, correctSentence, posTags, incorrectSentence, correctSentenceObject, sentenceErrors);

    /**< Проверка на ошибки при обработке предложений*/
    if (sentenceErrors.sentenceProcessingResult != sentencesProcessingCodes::sentencesProcessed) {

        return -1; // Завершаем программу с кодом ошибки
    }

    /**< Поиск ошибок в предложениях*/
    QList<ErrorInfo> errorsList = correctSentenceObject.compare(incorrectSentence);

    /**< Запись ошибок в выходной файл*/
    // writeErrorsToFile(errorsList, argv[3], incorrectSentence, correctSentenceObject, errors);
    writeErrorsToFile(errorsList, "C:\\Users\\Acer\\WordFormCheckerApp\\output.txt", incorrectSentence, correctSentenceObject, errors);

    /**< Проверка на ошибки при чтении файла*/
    if (errors.fileProcessingResult != fileProcessingCodes::filesProcessed) {

        return -1; // Завершаем программу с кодом ошибки
    }

    //return a.exec();
    return 0;

//    return 0;
}


/**< main для запусков тестов*/
//int main(int argc, char *argv[]) {
//    QCoreApplication app(argc, argv);

//    int status = 0;

//    // Создаем экземпляр класса тестов
//    test_sentence_compare test_compare;
//    test_word_findMistakeNum test_num;
//    test_word_findMistakeAdj test_adj;
//    TestWordfindMistakeNoun test_noun;
//    Test_word_findMistakeVerb test_verb;
//    test_word_compareWords test_compare_words;


//    // Запускаем тесты
//    status |= QTest::qExec(&test_compare, argc, argv);
//    status |= QTest::qExec(&test_num, argc, argv);
//    status |= QTest::qExec(&test_adj, argc, argv);
//    status |= QTest::qExec(&test_noun, argc, argv);
//    status |= QTest::qExec(&test_verb, argc, argv);
//    status |= QTest::qExec(&test_compare_words, argc, argv);

//    return status;
//}
