#ifndef OPENIMAGEWIDGET_H
#define OPENIMAGEWIDGET_H

#include <QWidget>

class OpenImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OpenImageWidget(QString path, QWidget *parent = nullptr);

signals:

};

#endif // OPENIMAGEWIDGET_H
