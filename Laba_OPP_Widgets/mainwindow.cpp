#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collectionoflamps.h"
#include "lamps.h"
#include "ledlamps.h"
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <sstream>
#include <QMessageBox>
using namespace std;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(ui->download,SIGNAL(clicked()), this, SLOT(downloadClicked()));
    QObject::connect(ui->output,SIGNAL(clicked()), this, SLOT(outputClicked()));
    QObject::connect(ui->calculate,SIGNAL(clicked()), this, SLOT(calculateClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
#include <iostream>
int q=0;
void MainWindow::downloadClicked(){
    cout << "Download" << endl;
    int count=0;
   QString name = ui->lineEdit->text();
   std::ifstream in(name.toStdString());
   if(in.is_open()){
       in.close();
    CollectionOfLamps led;
    led.getFileLEDSize(name.toStdString(), n, m);
    cout << n << " " << m << endl;
    int p=0,r=0,g=0,bl=0;
   CollectionOfLamps pur =  led.getFileLED(name.toStdString(), count);
   ui->tableWidget_1->setColumnCount(6);
   ui->tableWidget_1->setRowCount(count);
   QStringList name_table;
   name_table << "Power" << "RED" << "GREEN" << "BLUE"<<"X"<< "Y";
   ui->tableWidget_1->setHorizontalHeaderLabels(name_table);
   cout << "----------------"<<endl;
   q=0;
   for(int i=0;i<n;i++)
       for(int j=0;j<m;j++){
           pur.outputCollectLED(i,j, p,r,g,bl);
           if (p!=0){
               QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(p));
               ui->tableWidget_1->setItem(q,0,itm);
               QTableWidgetItem *itm1 = new QTableWidgetItem(tr("%1").arg(r));
               ui->tableWidget_1->setItem(q,1,itm1);
               QTableWidgetItem *itm2 = new QTableWidgetItem(tr("%1").arg(g));
               ui->tableWidget_1->setItem(q,2,itm2);
               QTableWidgetItem *itm3 = new QTableWidgetItem(tr("%1").arg(bl));
               ui->tableWidget_1->setItem(q,3,itm3);
               QTableWidgetItem *itm4 = new QTableWidgetItem(tr("%1").arg(i));
               ui->tableWidget_1->setItem(q,4,itm4);
               QTableWidgetItem *itm5 = new QTableWidgetItem(tr("%1").arg(j));
               ui->tableWidget_1->setItem(q,5,itm5);
               q++;
           }
        }
   }
   else{
       QMessageBox::about(this, "Ошибка", "Файл не существует");
   }
}
double force;
void MainWindow::outputClicked()
{
    cout << "OUTPUT" << endl;
    QString name = ui->lineEdit2->text();
    ofstream fout(name.toStdString() , std::ios::app);
    if(fout.is_open()){
        QMessageBox:: StandardButton reply = QMessageBox::question(this, "Сохранение файла", "Уверены что хотите сохранить ", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
             std::ofstream ofs;
            ofs.open(name.toStdString(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();
            fout << n << endl;
            fout << m << endl;
            fout << ui->textBrowser->toPlainText().toStdString()<<endl;

            fout.close();
            QMessageBox::information(this, "Информация", "Файл успешно сохранен");
        }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Не допустимое название файла");
    }
}
void MainWindow::calculateClicked()
{
    QString name = ui->lineEdit->text();
    std::ifstream in(name.toStdString());
    if(in.is_open()){
        in.close();
      auto pur = new LEDLamps();
       CollectionOfLamps square(n, m, *pur);
       ui->textBrowser->setText("");
       for (int i=0;i < q;i++){
           QTableWidgetItem *item = ui->tableWidget_1->item(i,0);
           QTableWidgetItem *item1 = ui->tableWidget_1->item(i,1);
           QTableWidgetItem *item2 = ui->tableWidget_1->item(i,2);
           QTableWidgetItem *item3 = ui->tableWidget_1->item(i,3);
           QTableWidgetItem *item4 = ui->tableWidget_1->item(i,4);
           QTableWidgetItem *item5 = ui->tableWidget_1->item(i,5);
            square.setLamp(item4->text().toInt(), item5->text().toInt(),*(new LEDLamps(item->text().toInt(), item1->text().toInt(), item2->text().toInt(), item3->text().toInt())));
            force=square.getNowForce(item4->text().toInt(), item5->text().toInt());
            ui->textBrowser->append("Power= "+QString::number(item->text().toInt()));
            ui->textBrowser->append("RED= "+QString::number(item1->text().toInt()));
            ui->textBrowser->append("GREEN= "+QString::number(item2->text().toInt()));
             ui->textBrowser->append("BLUE= "+QString::number(item3->text().toInt()));
            ui->textBrowser->append("Force= "+QString::number(force));
       }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Cначала загрузите файл");
    }

    cout << "Calculate" << endl;
    //ui->textBrowser->setText("Calculate");
}
