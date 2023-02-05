#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>




class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void helpClicked();
};
#endif // MAINWINDOW_H
