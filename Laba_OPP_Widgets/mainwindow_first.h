#ifndef MAINWINDOW_FIRST_H
#define MAINWINDOW_FIRST_H

#include <QMainWindow>
#include "mainwindow.h"
namespace Ui {
class MainWindow_First;
}

class MainWindow_First : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_First(QWidget *parent = nullptr);
    ~MainWindow_First();
public slots:
    void toLED();
    void tolamps();
private:
    Ui::MainWindow_First *ui;
};

#endif // MAINWINDOW_FIRST_H
