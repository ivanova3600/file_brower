#include "openimagewidget.h"

#include <QGridLayout>
#include <QLabel>

OpenImageWidget::OpenImageWidget(QString path, QWidget *parent)
    : QWidget{parent}
{
    QPixmap pic(path);
    QLabel *l = new QLabel();

    int w = l->width();
    int h = l->height();

    //pic.scaled(200, 100);

    l->setPixmap(pic.scaled(w, h, Qt::KeepAspectRatio));

//l->set
    QGridLayout *lay = new QGridLayout(this);
    lay->addWidget(l);
}
