#include "mainwindow_second.h"
#include "ui_mainwindow_second.h"
#include "collectionoflamps.h"
#include "lamps.h"
#include "ledlamps.h"
#include <stdlib.h>
#include <iostream>
#include <QMessageBox>
using namespace std;
MainWindow_Second::MainWindow_Second(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow_Second)
{
    ui->setupUi(this);
    QObject::connect(ui->calculate,SIGNAL(clicked()), this, SLOT(calculate()));
    QObject::connect(ui->loadToFile,SIGNAL(clicked()), this, SLOT(loadToFile()));
     QObject::connect(ui->loadFromFile,SIGNAL(clicked()), this, SLOT(loadFromFile()));

}

MainWindow_Second::~MainWindow_Second()
{
    delete ui;
}
int c=0;
double  illuminance;
void MainWindow_Second::calculate(){
    QString name = ui->lineEditFromFile->text();
    std::ifstream in(name.toStdString());
    if(in.is_open()){
        in.close();
      auto pur = new Lamps();
       CollectionOfLamps square(ui->lineEditN->text().toInt(), ui->lineEditM->text().toInt(), *pur);

       for (int i=0;i < c;i++){
           QTableWidgetItem *item = ui->tableWidget->item(i,1);
           QTableWidgetItem *item1 = ui->tableWidget->item(i,0);
           QTableWidgetItem *item2 = ui->tableWidget->item(i,2);
           QTableWidgetItem *item3 = ui->tableWidget->item(i,3);
            square.setLamp(item2->text().toInt(), item3->text().toInt(),*(new Lamps(item1->text().toInt(), item->text().toInt())));
       }
       illuminance=square.getIlluminance(ui->lineEditX->text().toInt(), ui->lineEditY->text().toInt(),  ui->lineEditZ->text().toInt(), 3);
       ui->textBrowser->setText("Illuminance= "+QString::number(illuminance));
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Cначала загрузите файл");
    }
}
void MainWindow_Second::loadFromFile(){
    cout << "Download" << endl;
    double x,y,z;
    int count=0;
     QString name = ui->lineEditFromFile->text();
     std::ifstream in(name.toStdString());
     if(in.is_open()){
         in.close();
      CollectionOfLamps led;
      led.getFileLEDSize(name.toStdString(),n,m);
      CollectionOfLamps pur = led.getFile(name.toStdString(),count, x, y, z);
      ui->tableWidget->setColumnCount(4);
      ui->tableWidget->setRowCount(count);
      QStringList name_table;
      name_table << "Power" << "Intensity" << "X" << "Y";
      int p=0,in=0;
      ui->tableWidget->setHorizontalHeaderLabels(name_table);
      c=0;
      for(int i=0; i< n;i++){
          for (int j=0;j<m;j++){
           pur.outputCollect(i,j, p,in);
           if (p!=0){
               QTableWidgetItem *itm = new QTableWidgetItem(tr("%1").arg(p));
           ui->tableWidget->setItem(c,0,itm);
            QTableWidgetItem *itm1 = new QTableWidgetItem(tr("%1").arg(in));
           ui->tableWidget->setItem(c,1,itm1);
           QTableWidgetItem *itm2 = new QTableWidgetItem(tr("%1").arg(i));
          ui->tableWidget->setItem(c,2,itm2);
          QTableWidgetItem *itm3 = new QTableWidgetItem(tr("%1").arg(j));
         ui->tableWidget->setItem(c,3,itm3);
           c++;
           }
          }
      }
      cout << x << y<<z<<endl;
      ui->lineEditX->setText(QString::number(x));
      ui->lineEditY->setText(QString::number(y));
      ui->lineEditZ->setText(QString::number(z));
      ui->lineEditN->setText(QString::number(n));
      ui->lineEditM->setText(QString::number(m));
      cout << count << endl;
     }
      else
     {
          cout << "didnot open"<< endl;
          QMessageBox::critical(this, "Ошибка", "Файл не существует");
     }
}
void MainWindow_Second::loadToFile(){
    cout <<"load"<<endl;
    QString name = ui->lineEditToFile->text();
    ofstream fout(name.toStdString() , std::ios::app);
    if(fout.is_open()){
        QMessageBox:: StandardButton reply = QMessageBox::question(this, "Сохранение файла", "Уверены что хотите сохранить ", QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
             std::ofstream ofs;
            ofs.open(name.toStdString(), std::ofstream::out | std::ofstream::trunc);
            ofs.close();
         fout << ui->lineEditN->text().toInt() << endl;
         fout << ui->lineEditM->text().toInt() << endl;
         for (int i=0;i < c;i++){
             QTableWidgetItem *item = ui->tableWidget->item(i,1);
             QTableWidgetItem *item1 = ui->tableWidget->item(i,0);
             QTableWidgetItem *item2 = ui->tableWidget->item(i,2);
             QTableWidgetItem *item3 = ui->tableWidget->item(i,3);
             fout << item1->text().toStdString() << endl;
             fout << item->text().toStdString() <<endl;
             fout << item2->text().toStdString() << endl;
             fout << item3->text().toStdString() << endl;

         }
         fout << "/\n" << ui->lineEditX->text().toInt() << " "<< ui->lineEditY->text().toInt()<<" " << ui->lineEditZ->text().toInt()<< " " << 3<< endl;
         fout <<"/" <<endl;
         fout << illuminance << endl;
         fout.close();
         QMessageBox::information(this, "Информация", "Файл успешно сохранен");
    }
    }
    else{
        QMessageBox::critical(this, "Ошибка", "Не допустимое название файла");
    }
}

