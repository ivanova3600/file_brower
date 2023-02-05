#ifndef RENAME_H
#define RENAME_H

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>

#include <QListWidgetItem>
#include <QLineEdit>
#include <QStringList>

class Rename : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *new_name;
    QPushButton *btn;

public:
    explicit Rename(QWidget *parent = nullptr);

public slots:
    void btnClicked();

signals:
    void setName(QString name);
};

#endif // RENAME_H
