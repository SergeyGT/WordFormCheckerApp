#include <QCoreApplication>
#include "wn.h"
#include <iostream>
#include <fstream>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char *bf;

    if (wninit()) {
      fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
      exit(-1);
    }

    bf = morphstr("pianos", NOUN);
// Если слово уже в начальной форме то будет ФЕЙЛ
    printf("%s\n", bf ? bf : "FAIL");

    return a.exec();
}
