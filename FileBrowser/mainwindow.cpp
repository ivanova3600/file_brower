#include "mainwindow.h"

#include "dirview.h"
//#include <QMenuBar>

#include <QToolBar>
#include <QLabel>

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
}

MainWindow::~MainWindow()
{
}

