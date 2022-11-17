#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
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


void MainWindow::on_pushButton_2_clicked()
{
    QString username,password;
        username =ui->lineEdit_user->text();
        password = ui->lineEdit_pw->text();

       Employee E;
        QSqlQuery qry,query;

    if(qry.exec("select CIN_E,NOM_E,MDP from EMPOLYE where CIN_E='"+username +"' and MDP='"+password+"'"))
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
