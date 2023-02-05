#ifndef FINDFILESWIDGET_H
#define FINDFILESWIDGET_H

#include <QObject>
#include <QWidget>

#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>

class FindFilesWidget : public QWidget
{
    Q_OBJECT
private:
    QPushButton *btn;
    QLineEdit *name_f;
    QLineEdit *name_d;
    QListWidget *files;
public:
    explicit FindFilesWidget(QWidget *parent = nullptr);

public slots:
    void find();
    void contextMenu(QPoint p);
    void go_to();
signals:
    void sendPath(QString path);

};

#endif // FINDFILESWIDGET_H
