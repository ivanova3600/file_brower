#include "dirview.h"
#include <QGridLayout>
#include <QDebug>
#include <iostream>
#include <string>
#include <QIcon>
#include <QFile>
#include <QProcess>
#include <QMessageBox>
#include <QMenu>
#include <QDateTime>
#include <QLineEdit>

#include <cstdlib>
#include <string>

#include "propertywidget.h"
#include "rename.h"
#include "achieve.h"
#include "findfileswidget.h"
#include "openimagewidget.h"


// получение формата файла
std::string get_extension(std::string file){
    size_t pos = file.rfind('.');
    return file.substr(pos+1, std::string::npos);
}



DirView::DirView(QWidget *parent)
    : QWidget(parent)
{   
    label_path = new QLabel(QDir::homePath());
    dirs = new QListWidget();
    dirs->setSelectionMode(QAbstractItemView::ExtendedSelection);


    QDir d(label_path->text());
    setItems(d);

    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->addWidget(label_path);
    lay->addWidget(dirs);
    dirs->setContextMenuPolicy(Qt::CustomContextMenu);

    QObject::connect(dirs, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(dir_change(QListWidgetItem*)));
    QObject::connect(dirs, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenu(QPoint)));
}


// обновление ListWidget
void DirView::refreshDir(){
    dirs->clear();
    setItems(QDir(this->label_path->text()));
}


// занесение в ListWidhet значений вместе с иконками

// cpp h html py архив неизвестный тип норм вида добавить
// форматов можно сколько угодно подобрать, но мне лень
// если выкладываю, то указать авторство (по папки поиск)
void DirView::setItems(QDir dd){

    QStringList list = dd.entryList(QDir::NoDot | QDir::Files | QDir::Dirs, QDir::DirsFirst);


    for(int i = 0; i < list.size(); i++){
        QFileInfo f(dd, list[i]);
        QString name = f.fileName();
        if(f.isDir()){
            QIcon icon(":/icons/folder.png");
            QListWidgetItem *item = new QListWidgetItem(name);
            item->setIcon(icon);
            dirs->addItem(item);
        }
        else{
            std::string a = get_extension(name.toStdString());
            QListWidgetItem *item = new QListWidgetItem(name);

            // можно переделать на switch
            if(a == "cpp")
                item->setIcon(QIcon(":/icons/pr_c.png"));
            else if(a == "docx")
                 item->setIcon( QIcon(":/icons/free-icon-docx-file-2266784.png"));
            else if(a == "doc")
                 item->setIcon( QIcon(":/icons/free-icon-doc-716935.png"));
            else if(a == "png" || a == "jpg" || a == "jpeg")
                 item->setIcon( QIcon(":/icons/free-icon-picture-4861322.png"));
            else if(a == "txt")
                item->setIcon( QIcon(":/icons/free-icon-png-file-2868147.png"));
            else if(a == "java")
                item->setIcon(QIcon(":/icons/java.png"));
            else if(a == "docx")
               item->setIcon(QIcon(":/icons/docx.png"));
            else if(a == "pdf")
                item->setIcon(QIcon(":/icons/free-icon-pdf-337946.png"));
            else if(a == "xls")
                item->setIcon(QIcon(":/icons/free-icon-xls-2306055.png"));
            else if(a == "tar" || a == "zip" || a == "7z")
                item->setIcon(QIcon(":/icons/arch.jpg"));
            else if(f.isExecutable())
                item->setIcon(QIcon(":/icons/free-icon-exe-7817595.png"));
            else
                item->setIcon(QIcon(":/icons/non.png"));
            dirs->addItem(item);
        }

        dirs->setIconSize(QSize(50, 50));

    }
}


// Нажатие правой кнопкой мыши по item
void DirView::contextMenu(QPoint pos){

    switch(dirs->selectedItems().size()){
    case 0:{
        QMenu *menu = new QMenu(this);

        QAction *past = new QAction("Paste");
        QAction *diri_ = new QAction("Create empty directory");
        QAction *file_ = new QAction("Create empty file");
        QAction *prop = new QAction("Properties");

        menu->addAction(past);
        menu->addAction(diri_);
        menu->addAction(file_);
        menu->addAction(prop);

        QObject::connect(diri_, SIGNAL(triggered(bool)), this, SLOT(createDirWidget()));
        QObject::connect(file_, SIGNAL(triggered(bool)), this, SLOT(createFileWidget()));
        QObject::connect(prop, SIGNAL(triggered(bool)), this, SLOT(file_properties()));
        QObject::connect(past, SIGNAL(triggered(bool)), this, SLOT(paste()));

        menu->popup(dirs->viewport()->mapFromGlobal(pos));

        break;
    }
    case 1:{
        QString name = dirs->selectedItems()[0]->text();
        if(name == "..")
            return;

        QMenu *menu = new QMenu(this);


        std::string ext = get_extension(name.toStdString());

        if(ext == "tar" || ext == "zip" || ext == "7z" || ext == "gz"){
            std::cout << "Unzup" << std::endl;

            QAction *unzip = new QAction("Unzip");


            QAction *del = new QAction("Delete");
            QAction *rename = new QAction("Rename");
            QAction *prop = new QAction("Properties");

            menu->addAction(unzip);
            menu->addAction(del);
            menu->addAction(prop);
            menu->addAction(rename);

            QObject::connect(del, SIGNAL(triggered(bool)), this, SLOT(remove()));
            QObject::connect(prop, SIGNAL(triggered(bool)), this, SLOT(file_properties()));
            QObject::connect(rename, SIGNAL(triggered(bool)), this, SLOT(renameWidget()));
            QObject::connect(unzip, SIGNAL(triggered(bool)), this, SLOT(unzip()));


            menu->popup(dirs->viewport()->mapFromGlobal(pos));
        }
        else{
            QAction *open = new QAction("Open");
            QAction *zip = new QAction("Zip");
            QAction *del = new QAction("Delete");
            QAction *rename = new QAction("Rename");
            QAction *prop = new QAction("Properties");
            QAction *cop = new QAction("Copy");

            menu->addAction(open);
            menu->addAction(del);
            menu->addAction(cop);
            menu->addAction(prop);
            menu->addAction(rename);
            menu->addAction(zip);

            QObject::connect(del, SIGNAL(triggered(bool)), this, SLOT(remove()));
            QObject::connect(prop, SIGNAL(triggered(bool)), this, SLOT(file_properties()));
            QObject::connect(rename, SIGNAL(triggered(bool)), this, SLOT(renameWidget()));
            QObject::connect(open, SIGNAL(triggered(bool)), this, SLOT(open()));
            QObject::connect(cop, SIGNAL(triggered(bool)), this, SLOT(copy()));
            QObject::connect(zip, SIGNAL(triggered(bool)), this, SLOT(zip()));

            menu->popup(dirs->viewport()->mapFromGlobal(pos));
        }

        break;
    }
    default:{
        QMenu *menu = new QMenu(this);
        QAction *zip = new QAction("Zip");
        QAction *del = new QAction("Delete");
        QAction *cop = new QAction("Copy");


        menu->addAction(cop);
        menu->addAction(del);
        menu->addAction(zip);



        QObject::connect(del, SIGNAL(triggered(bool)), this, SLOT(remove()));
        QObject::connect(cop, SIGNAL(triggered(bool)), this, SLOT(copy()));
        QObject::connect(zip, SIGNAL(triggered(bool)), this, SLOT(zip()));


        menu->popup(dirs->viewport()->mapFromGlobal(pos));

        break;
    }
    }
}

// Открытие файла
void DirView::open(){
    if(dirs->selectedItems().size() > 0){
        QListWidgetItem *item = dirs->selectedItems()[0];
        QString new_path = label_path->text() + "/" + item->text();
        QFileInfo f(new_path);
        if(f.isFile()){
            std::string name = get_extension(item->text().toStdString());
            if(name == "pdf"){
                QProcess *pdf = new QProcess(this);
                pdf->start("/bin/evince", {f.absoluteFilePath()});
            }
            else if(name == "png" || name == "jpg" || name == "jpeg"){
                OpenImageWidget *w = new OpenImageWidget(f.absoluteFilePath());
                w->show();
            }
            else if(name == "html" || name == "xml"){
                QProcess *text = new QProcess(this);
                text->start("/bin/firefox", {f.absoluteFilePath()});
            }
            else{
                QProcess *text = new QProcess(this);
                text->start("/bin/gedit", {f.absoluteFilePath()});
            }
        }
        else if(f.isDir()){
            dir_change(item);
        }
    }

    if(dirs->selectedItems().size() > 0){
        dirs->selectedItems()[0]->setSelected(false);
    }

}


// Обработка двойного нажатия по item
void DirView::dir_change(QListWidgetItem *item){
    QString new_path = label_path->text() + "/" + item->text();
    QFileInfo f(new_path);

    if(f.isDir()){                                  // если директория, то переходим в эту папку
        if(new_path == QDir::homePath() + "/.."){
            return;
        }

        label_path->setText(f.absoluteFilePath());
        refreshDir();
    }
    else{                                              // если файл, то пытаемся его открыть
        std::string name = get_extension(item->text().toStdString());
        if(name == "pdf"){
            QProcess *pdf = new QProcess(this);
            pdf->start("/bin/evince", {f.absoluteFilePath()});
        }
        else if(name == "png" || name == "jpg" || name == "jpeg"){
            OpenImageWidget *w = new OpenImageWidget(f.absoluteFilePath());
            w->show();
        }
        else if(name == "html" || name == "xml"){
            QProcess *text = new QProcess(this);
            text->start("/bin/firefox", {f.absoluteFilePath()});
        }
        else{
            QProcess *text = new QProcess(this);
            text->start("/bin/gedit", {f.absoluteFilePath()});
        }

    }
}


// архивация файлов

// !!! переделать скрипт на нормальный

void DirView::zip(){
    Achieve *a = new Achieve();

    QObject::connect(a, SIGNAL(sendName(QString)), this, SLOT(zip(QString)));
    a->show();
}


void DirView::zip(QString name){
    std::string command = std::string(PRO_FILE_PWD) + "/archiver.sh '" + label_path->text().toStdString() + "/" + name.toStdString() + "'";

    for(int i = 0; i < dirs->selectedItems().size(); i++){
        command += (" '" + label_path->text() + "/" + dirs->selectedItems()[i]->text()).toStdString() + "'";
    }

    std::system(command.c_str());
    refreshDir();
}


// копирование файлов
void DirView::copy(){
    if(!copy_list.isEmpty())
        copy_list.clear();
    for(int i = 0; i < dirs->selectedItems().size(); i++)
        copy_list.push_back(label_path->text() + "/" + dirs->selectedItems()[i]->text());
}


// вставка файлов в текущую директорию
void DirView::paste(){
    for(int i = 0; i < copy_list.size(); i++){
        QFileInfo f(copy_list[i]);
        if(f.isFile()){
            QFile::copy(copy_list[i], label_path->text() + "/" + f.fileName());
        }
        else if(f.isDir()){
            QDir d(label_path->text());
            d.mkdir(f.fileName());
            QDir c_dir(f.absoluteFilePath());

            QStringList list = c_dir.entryList(QDir::NoDot | QDir::Files | QDir::Dirs, QDir::DirsFirst);

            for(int j = 0; j < list.size(); j++){
                if(list[j] == "..") continue;
                QFile::copy(f.absoluteFilePath() + "/" + list[j], label_path->text() + "/" + f.fileName() + "/" +list[j]);
            }
        }
    }

    refreshDir();
}



//  распаковка архива
void DirView::unzip(){

    QString name = label_path->text() + "/" + dirs->selectedItems()[0]->text();
    std::string str = std::string(PRO_FILE_PWD) + "/unarchiver.sh " + name.toStdString();
    std::system(str.c_str());

  //  QDir dd(label_path->text());
  //  dirs->clear();
  //  setItems(dd);

    refreshDir();
}


// Проверка имени на уникальность
bool DirView::checkName(QString name){
    QDir dd(label_path->text());
    QStringList list = dd.entryList(QDir::NoDot | QDir::Files | QDir::Dirs, QDir::DirsFirst);

    for(QString i : list){
        if(i == name){
            QMessageBox *m_box = new QMessageBox(
                        QMessageBox::Critical,
                        QObject::tr("Error"),
                        QObject::tr("File or directory with such name exits")
                        );
            m_box->setGeometry(this->geometry());
            m_box->show();

            return false;
        }
    }

    return true;
}


// Создание пустой папки
// из r отправляет введенное имя в :createDir(QString str)
void DirView::createDirWidget(){
    Rename *r = new Rename();
    QObject::connect(r, SIGNAL(setName(QString)), this, SLOT(createDir(QString)));
    r->show();
}

void DirView::createDir(QString str){
    bool a = checkName(str);
    if(a){
        QDir d(label_path->text());
        bool b = d.mkdir(str);
        if(b){
            dirs->clear();
            setItems(d);
        }
        else{
            QMessageBox *m_box = new QMessageBox(
                        QMessageBox::Critical,
                        QObject::tr("Error"),
                        QObject::tr("Cannot create directory")
                        );
            m_box->setGeometry(this->geometry());
            m_box->show();
        }
    }
}


// Создание пустого файла
// аналогично
void DirView::createFileWidget(){
    Rename *r = new Rename();
    QObject::connect(r, SIGNAL(setName(QString)), this, SLOT(createFile(QString)));
    r->show();
}

void DirView::createFile(QString str){
    bool a = checkName(str);
    if(a){
        QFile file(label_path->text() + "/" + str);
        bool b = file.open(QIODevice::ReadWrite);
        if(b){
            QDir d(label_path->text());
            dirs->clear();
            setItems(d);
        }
        else{
            QMessageBox *m_box = new QMessageBox(
                        QMessageBox::Critical,
                        QObject::tr("Error"),
                        QObject::tr("Cannot create file")
                        );
            m_box->setGeometry(this->geometry());
            m_box->show();
        }
    }
}


// переименовывание
// аналогично
void DirView::renameWidget(){
    Rename *r = new Rename();

    QObject::connect(r, SIGNAL(setName(QString)), this, SLOT(rename(QString)));

    r->show();
}

void DirView::rename(QString str){
    bool b = checkName(str);

    if(b){
        bool a = QFile::rename(label_path->text() + "/" + dirs->selectedItems()[0]->text(),label_path->text() + "/" +  str);
        if(a){
            QDir dd(label_path->text());
            dirs->clear();
            setItems(dd);
        }
        else{
            QMessageBox *m_box = new QMessageBox(
                        QMessageBox::Critical,
                        QObject::tr("Error"),
                        QObject::tr("Cannot rename file")
                        );
            m_box->setGeometry(this->geometry());
            m_box->show();
        }
    }

}

// удаление файла
void DirView::remove(){
    for(int i = 0; i < dirs->selectedItems().size(); i++){
        QListWidgetItem *item = dirs->selectedItems()[i];
        QString new_path = label_path->text() + "/" + item->text();
        QFileInfo f(new_path);

        if(f.isDir()){
            QDir dir(new_path);
            dir.removeRecursively();
        }

        else if(f.isFile()){
            QFile::remove(new_path);
        }
    }

    //dirs->clear();
    //setItems(QDir(this->label_path->text()));

    refreshDir();
}



// свойства файла
void DirView::file_properties(){
    QString new_path;

    if(dirs->selectedItems().size() > 0)
        new_path = label_path->text() + "/" + dirs->selectedItems()[0]->text();
    else
        new_path = label_path->text();

    QFileInfo f(new_path);

    PropertyWidget *pr = new PropertyWidget();
    pr->setName(f.baseName());
    pr->setPath(f.absolutePath());
    pr->setBirth(f.birthTime().toString("yyyy-MM-dd"));
    pr->setOwner(f.owner());
    pr->setLastMod(f.lastModified().toString("yyyy-MM-dd"));
    pr->setReadMod(f.isReadable());
    pr->setWriteMod(f.isWritable());
    pr->setExcutMod(f.isExecutable());
    pr->show();
}


// поиск файла выполняется в отдельном классе
void DirView::findFile(){
    FindFilesWidget *f = new FindFilesWidget();
    f->show();

    QObject::connect(f, SIGNAL(sendPath(QString)), this, SLOT(go_to(QString)));
}


// переход в указанную папку из FindFilesWidget
void DirView::go_to(QString path){
    if(!QDir(path).exists()){
        QMessageBox *m_box = new QMessageBox(
                    QMessageBox::Critical,
                    QObject::tr("Error"),
                    QObject::tr("Path is incorrect")
                    );
        m_box->setGeometry(this->geometry());
        m_box->show();
        return;
    }

    label_path->setText(path);
    refreshDir();
}
