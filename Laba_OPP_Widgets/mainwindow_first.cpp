#include "mainwindow_first.h"
#include "ui_mainwindow_first.h"
#include "mainwindow.h"
#include <QStandardItem>
#include <QStandardItemModel>
#include "mainwindow_second.h"
MainWindow_First::MainWindow_First(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_First)
{
    ui->setupUi(this);
    QObject::connect(ui->to_LED,SIGNAL(clicked()), this, SLOT(toLED()));
    QObject::connect(ui->to_lamps,SIGNAL(clicked()), this, SLOT(tolamps()));
    this->setWindowTitle("Главная");
}

MainWindow_First::~MainWindow_First()
{
    delete ui;
}
void MainWindow_First::toLED(){
    auto swindow = new MainWindow();
    swindow->setWindowTitle("Светодиодные лампы");
    swindow->show();
}
void MainWindow_First::tolamps(){
    auto swindow1 = new MainWindow_Second();
      swindow1->setWindowTitle("Обычные лампы");
    swindow1->show();
}
