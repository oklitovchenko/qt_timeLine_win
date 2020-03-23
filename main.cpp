#include "testtaskmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestTaskMainWindow w;
    w.show();

    return a.exec();
}
