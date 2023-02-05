#include "rename.h"

#include <QMessageBox>
#include <iostream>

Rename::Rename(QWidget *parent)
    : QWidget{parent}
{
    new_name = new QLineEdit();
    btn = new QPushButton("OK");
    QVBoxLayout *lay = new QVBoxLayout(this);

    lay->addWidget(new_name);
    lay->addWidget(btn);

    this->setWindowTitle("Input name");

    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

void Rename::btnClicked(){
    QString name = new_name->text();

    if(name.size() == 0){

        QMessageBox *m_box = new QMessageBox(
                    QMessageBox::Critical,
                    QObject::tr("Error"),
                    QObject::tr("Name cannot be empty")//,
                    );
        m_box->setGeometry(this->geometry());
        m_box->show();

        return;
    }
    else{
        emit setName(name);
        this->close();
    }
}
