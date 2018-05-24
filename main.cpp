#include "bento.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Bento w;
    w.show();

    return a.exec();
}
