#include <QCoreApplication>
#include "wn.h"




class Word
{
private:
    QString wordText;
    int id;
};


class Sentence
{
private:
    QString sentenceText;
    QList<Word> words;
};






int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    char *bf;

    if (wninit()) {
      fprintf(stderr, "morphy: Fatal error - cannot open WordNet database\n");
      exit(-1);
    }

    bf = morphstr("fatter", ADJ);
// Если слово уже в начальной форме то будет ФЕЙЛ
    printf("%s\n", bf ? bf : "FAIL");

    return a.exec();
}
