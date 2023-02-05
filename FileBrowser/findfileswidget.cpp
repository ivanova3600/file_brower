#include "findfileswidget.h"

#include <QGridLayout>
#include <QDir>
#include <QDirIterator>
#include <QLabel>
#include <QMessageBox>
#include <iostream>
#include <QStringList>
#include <QMenu>

FindFilesWidget::FindFilesWidget(QWidget *parent)
    : QWidget{parent}
{
    btn = new QPushButton("Ok");
    name_f = new QLineEdit();
    name_d = new QLineEdit();

    files = new QListWidget();
    files->setContextMenuPolicy(Qt::CustomContextMenu);


    name_d->setText(QDir::homePath());

    QGridLayout *lay = new QGridLayout(this);

    lay->addWidget(new QLabel("Filter"), 0, 0);
    lay->addWidget(new QLabel("Dir name"), 1, 0);

    lay->addWidget(name_f, 0, 1);
    lay->addWidget(name_d, 1, 1);
    lay->addWidget(btn, 2, 0);
    lay->addWidget(files, 3, 0, 1, 2);

    QObject::connect(btn, SIGNAL(clicked(bool)), this, SLOT(find()));
    QObject::connect(files, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
}

void FindFilesWidget::contextMenu(QPoint p){
    if(files->selectedItems().size() == 1){
        QMenu *menu = new QMenu(this);

        QAction *go = new QAction("Go to");

        menu->addAction(go);


        QObject::connect(go, SIGNAL(triggered(bool)), this, SLOT(go_to()));

        menu->popup(files->viewport()->mapFromGlobal(p));
    }
}

void FindFilesWidget::go_to(){
    QFileInfo f(files->selectedItems()[0]->text());
    emit sendPath(f.absolutePath());
    this->close();
}

void FindFilesWidget::find(){
    files->clear();

    QString file = name_f->text();

    std::cout << " My input " << file.toStdString() << std::endl;

    if(file.size() == 0){
        QMessageBox *m_box = new QMessageBox(
                    QMessageBox::Critical,
                    QObject::tr("Error"),
                    QObject::tr("Filter cannot be empty")
                    );
        m_box->setGeometry(this->geometry());
        m_box->show();
        return;
    }

    QStringList filter;
    filter << file;

    QString dir = name_d->text();
    if(dir.size() == 0)
        dir = QDir::homePath(); // по умолчанию поиск в домашней директории

    QDir cur_dir(dir);
    if(!cur_dir.exists()){
        QMessageBox *m_box = new QMessageBox(
                    QMessageBox::Critical,
                    QObject::tr("Error"),
                    QObject::tr("Directory with such name doesn't exist")
                    );
        m_box->setGeometry(this->geometry());
        m_box->show();
        return;
    }

    QDirIterator it(dir, filter, QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
    QStringList files_;

    while(it.hasNext()){
        files_ << it.next();
    }


    files_.sort();
    files->addItems(files_);
}
