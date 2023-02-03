#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QVector>

class PropertyWidget : public QWidget
{
    Q_OBJECT

private:
    QLabel *name;
    QLabel *path;
    QLabel *owner;
    QLabel *time;
    QLabel *l_mod;
    QLabel *r, *w, *e;
public:
    PropertyWidget(QWidget *parent = nullptr);

    void setName(QString name);
    void setPath(QString path);
    void setOwner(QString owner);
    void setBirth(QString birth);
    void setLastMod(QString l_mod);
    void setReadMod(bool r);
    void setWriteMod(bool w);
    void setExcutMod(bool e);

};

#endif // PROPERTYWIDGET_H
