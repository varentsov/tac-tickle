#include "tactickle.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TacTickle w;

    //w.resize(500, 500);
    //w.print_table();

    srand(time(NULL));
    w.show();
    return a.exec();
}
