#include "mainwindow.h"

#include "dirview.h"
//#include <QMenuBar>

#include <QToolBar>
#include <QLabel>
#include <QWidget>
#include <QPlainTextEdit>

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    DirView *d = new DirView(this);

    //this->setStyleSheet("background-color: red");
/*
    QMenu *menu = menuBar()->addMenu("&Additionally");

    QAction *help = new QAction("Help");
    QAction *find = new QAction("Find");

    menu->addAction(find);
    menu->addAction(help);
*/
    QToolBar *bar = addToolBar("main toolbar");

    QAction *help = new QAction("Help");
    QAction *find = new QAction("Find");
    //QAction *go = new QAction("Go to");

    bar->addAction(help);
    bar->addAction(find);

    setCentralWidget(d);


    QObject::connect(find, SIGNAL(triggered(bool)), d, SLOT(findFile()));
    QObject::connect(help, SIGNAL(triggered(bool)), this, SLOT(helpClicked()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::helpClicked(){
    QPlainTextEdit *edit = new QPlainTextEdit();
    edit->setPlainText(
                "Нажатие правой кнопкой мыши по файлу или свободному пространству открывает контекстное меню. С помощью зажатия левой кнопкой мыши можно выбрать несколько файлов и вызвать контекстное меню. В поиске можно нажатием правой кнопки мыши перейти к файлу. Двойное нажатие открывает папку или файл. Специфические форматы не открываются."
                );
    edit->setReadOnly(true);
    edit->show();
}
