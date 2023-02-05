#include "achieve.h"

#include <QGridLayout>
#include <QMessageBox>

#include <iostream>

Achieve::Achieve(QWidget *parent)
    : QWidget{parent}
{
    QGridLayout *lay = new QGridLayout(this);

    c_box = new QComboBox();
    c_box->addItem(".zip");
    c_box->addItem(".tar");
   // c_box->addItem(".rar");
   // c_box->addItem(".7z");

    edit = new QLineEdit();
    btn = new QPushButton("Ok");

    lay->addWidget(edit, 0, 0);
    lay->addWidget(c_box, 0, 1);
    lay->addWidget(btn, 1, 0, 1, 1);

    QObject::connect(btn, SIGNAL(clicked()), this, SLOT(btnClicked()));
}

void Achieve::btnClicked(){
    QString extension = c_box->currentText();
    QString name = edit->text();

    if(name.size() == 0){
        QMessageBox *m_box = new QMessageBox(
                    QMessageBox::Critical,
                    QObject::tr("Error"),
                    QObject::tr("Name cannot be empty")
                    );
        m_box->setGeometry(this->geometry());
        m_box->show();

        return;
    }
    else{
   //     QString f = name + extension;
   //     std::cout << f.toStdString() << std::endl;
        emit sendName(name + extension);
        this->close();
    }
}
