#ifndef ACHIEVE_H
#define ACHIEVE_H

#include <QObject>
#include <QWidget>

#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>

class Achieve : public QWidget
{
    Q_OBJECT

private:
    QComboBox *c_box;
    QPushButton *btn;
    QLineEdit *edit;

public:
    explicit Achieve(QWidget *parent = nullptr);

public slots:
    void btnClicked();

signals:
    void sendName(QString name);
};

#endif // ACHIEVE_H
