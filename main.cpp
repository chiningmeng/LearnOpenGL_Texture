#include "mainwindow.h"
#include <QApplication>
#include "openglwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    OpenglWidget w;
    w.show();

    return a.exec();
}
