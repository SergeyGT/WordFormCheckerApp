#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <fstream>
#include "word.h"



//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);

//    char *bf;

//    if (wninit()) {
//      fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
//      exit(-1);
//    }

//    bf = morphstr("Better", ADJ);
//// Если слово уже в начальной форме то будет ФЕЙЛ
//    printf("%s\n", bf ? bf : "FAIL");

////    return a.exec();
//    return 0;
//}



int main() {
    // Инициализация тестовых данных
    Word word1;
    word1.wordText = "go";
    word1.postag = Verb;
    word1.id = 1;

    Word word2;
    word2.wordText = "goes";
    word2.postag = Verb;
    word2.id = 1;

    ErrorInfo error = word1.findMistakeVerb(word2);

    if (error.error == errorType::verbendES) {
            std::cout << "Test 1 passed: verbendES" << std::endl;
        } else {
            std::cout << "Test 1 failed" << std::endl;
        }

    return 0;
}
