#include "propertywidget.h"
#include <QGridLayout>

PropertyWidget::PropertyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->name = new QLabel();
    this->path = new QLabel();
    this->owner = new QLabel();
    this->time = new QLabel();
    this->l_mod = new QLabel();

    this->w = new QLabel();
    this->r = new QLabel();
    this->e = new QLabel();

    QGridLayout *lay = new QGridLayout(this);

    lay->addWidget(new QLabel("Name"), 0, 0);
    lay->addWidget(new QLabel("Absolute path"), 1, 0);
    lay->addWidget(new QLabel("Owner"), 2, 0);
    lay->addWidget(new QLabel("Birth time"), 3, 0);
    lay->addWidget(new QLabel("Last Modification"), 4, 0);
    lay->addWidget(new QLabel("is Readable"), 5, 0);
    lay->addWidget(new QLabel("is Writable"), 6, 0);
    lay->addWidget(new QLabel("is Exutable"), 7, 0);

    lay->addWidget(name, 0, 1);
    lay->addWidget(path, 1, 1);
    lay->addWidget(owner, 2, 1);
    lay->addWidget(time, 3, 1);
    lay->addWidget(l_mod, 4, 1);
    lay->addWidget(r, 5, 1);
    lay->addWidget(w, 6, 1);
    lay->addWidget(e, 7, 1);

    this->setWindowTitle("Properties");
}


void PropertyWidget::setName(QString name){
    this->name->setText(name);
}

void PropertyWidget::setPath(QString path){
    this->path->setText(path);
}

void PropertyWidget::setOwner(QString owner){
    this->owner->setText(owner);
}

void PropertyWidget::setBirth(QString birth){
    this->time->setText(birth);
}

void PropertyWidget::setLastMod(QString l_mod){
    this->l_mod->setText(l_mod);
}

void PropertyWidget::setReadMod(bool w){
    if(w == false) this->w->setText("No");
    else this->w->setText("Yes");
}

void PropertyWidget::setWriteMod(bool r){
    if(r == false) this->r->setText("No");
    else this->r->setText("Yes");
}

void PropertyWidget::setExcutMod(bool e){
    if(e == false) this->e->setText("No");
    else this->e->setText("Yes");
}
