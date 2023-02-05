#include "mainwindow.h"

#include <QApplication>
#include <iostream>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.resize(QSize(800, 800));
    w.show();
    return a.exec();
}
