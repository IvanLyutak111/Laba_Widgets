#ifndef MAINWINDOW_SECOND_H
#define MAINWINDOW_SECOND_H
#include "collectionoflamps.h"
#include <QMainWindow>

namespace Ui {
class MainWindow_Second;
}

class MainWindow_Second : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow_Second(QWidget *parent = nullptr);
    ~MainWindow_Second();

public slots:
    void calculate();
    void loadFromFile();
    void loadToFile();
private:
    Ui::MainWindow_Second *ui;
    int n=0,m=0;
};

#endif // MAINWINDOW_SECOND_H
