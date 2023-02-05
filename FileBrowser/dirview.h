#ifndef DIRVIEW_H
#define DIRVIEW_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QStringList>
#include <QLabel>
#include <QDir>

class DirView : public QWidget
{
    Q_OBJECT
private:
    QListWidget *dirs;
  //  QListWidget *rules;
    QLabel *label_path;
    QStringList copy_list;
    bool cut_mode;

    void setItems(QDir d);
    bool checkName(QString name);
    void refreshDir();

    //void copyDir()

public:
    DirView(QWidget *parent = nullptr);
    ~DirView() { }

public slots:
    void dir_change(QListWidgetItem *item);
    void contextMenu(QPoint pos);

    void open();
    void remove();
    void file_properties();

    void renameWidget();
    void rename(QString str);

    void createDirWidget();
    void createDir(QString str);

    void createFileWidget();
    void createFile(QString str);

    void unzip();

    void copy();
    void paste();

    void zip();
    void zip(QString name);

    void findFile();

    void go_to(QString path);

    void cut();
};

#endif // DIRVIEW_H
