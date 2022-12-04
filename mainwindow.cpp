#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "arduino.h"
#include <QDebug>

//*******Arduino declaration******
int nb=0;
int test=0;
int pas=0;
int data1=0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



 }


MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::arduino_init()
{
    serial->setPortName(portname);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        serial->open(QIODevice::ReadWrite);
}*/
void MainWindow::on_pushButton_2_clicked()
{


    QString username,password;
        username =ui->lineEdit_user->text();
        password = ui->lineEdit_pw->text();

       Employee E;
        QSqlQuery qry,query;

    if(qry.exec("select CIN_E,NOM_E,MDP from EMPOLYE where CIN_E='"+username +"' and MDP='"+password+"'")||((serial->isWritable())))
    {
            int count=0;
    while(qry.next())
    {
          count++;





         if(count==1)
     {

         query.prepare("INSERT INTO EMPOLYE(CIN_E,NOM_E,MDP) "
                       "VALUES (:CIN, :Nom, :Mdp)");

         query.bindValue(":CIN",qry.value(0).toString());
         query.bindValue(":Nom",qry.value(1).toString());
         query.bindValue(":Mdp",qry.value(2).toString());

         query.exec();

          this->hide();
            ui->lineEdit_user->clear();
                 ui->lineEdit_pw->clear();
                 QMessageBox::critical(nullptr, QObject::tr("database is open"),
                             QObject::tr("connection successful.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
                 int test=A.close_arduino();
                               if(test==0){
                                   qDebug()<<"arduino Closed!!";
                               }
            Dialog dialog;
            dialog.setModal(true);
            dialog.exec();






            }

    }

            if(count<1)
            {
                QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                            QObject::tr("connection failed.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);


             }
    }

}


void MainWindow::on_pushButton_3_clicked()
{
    int ret=A.connect_arduino(); // lancer la connexion à arduino
       switch(ret){
       case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
           break;
       case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
          break;
       case(-1):qDebug() << "arduino is not available";
       }
       QMessageBox::critical(nullptr, QObject::tr("arduino"),
                           QObject::tr("Put your card to the reader."), QMessageBox::Cancel);
       QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_nb()));

       data=A.read_from_arduino();

       qDebug()<<"data from arduino :"<<data;




}

void MainWindow::update_nb()
{ QSqlQuery qry;

qry.prepare ("SELECT ID_CARTE EMPOLYE WHERE ID_CARTE = '83 C1 9A 92' OR ID_CARTE = 'F3 6E 97 A7'" );
qry.exec();
A.read_from_arduino();

      qDebug()<<"Accepter";

A.close_arduino();
qry.prepare ("UPDATE EMPOLYE SET STATUS = 'ONLINE' WHERE ID_CARTE = '83 C1 9A 92' " );
qry.exec();
      QMessageBox::critical(nullptr, QObject::tr("arduino"),
                  QObject::tr("login with card."), QMessageBox::Cancel);

      this->hide();
      Dialog dialog;
      dialog.setModal(true);
      dialog.exec();






}








void MainWindow::read()
{

}
