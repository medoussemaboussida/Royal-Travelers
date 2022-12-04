#include "dialog.h"
#include "ui_dialog.h"
#include "employee.h"
#include "client.h"
#include"mission.h"
#include "statistiques.h"
#include "widget.h"
#include "excel.h"
#include"stat_client.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QIntValidator>
#include<QWidget>
#include <QTextDocument>
#include <QTextEdit>
#include <fstream>
#include <QTextStream>
#include <QRadioButton>
#include <QFileDialog>
#include <QPixmap>
#include <QPainter>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QSvgGenerator>
#include<QDir>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QAbstractPrintDialog>
#include<QDirModel>
#include <QtPrintSupport/QPrintDialog>
#include<QPdfWriter>
#include<QDesktopServices>
#include <QHeaderView>
#include "QImage"
#include <QPainter>
#include "iostream"
#include<QtCharts/QtCharts>
#include<QtCharts/QBarSeries>
#include<QtCharts/QBarSet>
#include<QtCharts/QLegend>
#include<QtCharts/QBarCategoryAxis>
#include<QtCharts/QHorizontalStackedBarSeries>
#include<QtCharts/QLineSeries>
#include<QtCharts/QCategoryAxis>
#include "qrcode.h"
#include "qrwidget.h"
#include "qrcodegenerateworker.h"
#include"stat_mission.h"
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit_CIN->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_employee->setModel(E.afficher());
}

Dialog::~Dialog()
{
    delete ui;
}
/*****************EMPLOYEE***********************************************/

//ajouter
void Dialog::on_pb_ajouter_clicked()
{
    int CIN=ui->lineEdit_CIN->text().toInt();
        QString Nom=ui->lineEdit_Nom->text();
        QString Prenom=ui->lineEdit_Prenom->text();
        QString Phone=ui->lineEdit_Phone->text();
        QString Email=ui->lineEdit_Email->text();
        QString Function=ui->lineEdit_Function->text();
        QString Mdp=ui->lineEdit_Mdp->text();
        Employee E(CIN,Nom,Prenom,Phone,Email,Function,Mdp);
        bool test=E.ajouter();
            if(test){
                QMessageBox::information(nullptr, QObject::tr("ok"),
                            QObject::tr("ajout effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else
                QMessageBox::critical(nullptr, QObject::tr("not ok"),
                            QObject::tr("ajout non effectué.\n"
                                        "Click Cancel to exit."), QMessageBox::Cancel);

}

//suppression
void Dialog::on_pb_supprimer_clicked()
{
    Employee E1; E1.setCIN(ui->lineEdit_Supp->text().toInt());
       bool test=E1.supprimer(E1.getCIN());
       if(test){
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("Suppresion effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           ui->lineEdit_Supp->setText("");
           ui->tab_employee->setModel(E.afficher());

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("Suppresion non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
}

//modifier
void Dialog::on_pb_modifier_clicked()
{
    int CIN=ui->lineEdit_CIN->text().toInt();
               QString Nom=ui->lineEdit_Nom->text();
               QString Prenom=ui->lineEdit_Prenom->text();
               QString Email=ui->lineEdit_Email->text();
               QString Phone=ui->lineEdit_Phone->text();
               QString Function=ui->lineEdit_Function->text();
               QString Mdp=ui->lineEdit_Mdp->text();

          Employee E(CIN,Nom,Prenom,Phone,Email,Function,Mdp);
          bool test=E.modifier_Employee();
          if(test)
            {
                QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                                   QObject::tr("row updated and saved.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);

            }
            else{
                QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                                   QObject::tr("row not updated and not saved.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
            }

}

//tri
void Dialog::on_pb_TrieNom_clicked()
{
    ui->tab_employee->setModel(E.afficher_Employee_trie_Nom());
}

void Dialog::on_TriePrenom_clicked()
{
    ui->tab_employee->setModel(E.afficher_Employee_trie_prenom());
}

//chercher
void Dialog::on_pb_chercher_clicked()
{
    Employee E;
       QString Re =ui->lineEdit_chercher->text();
       ui->table_chercher->setModel(E.chercher_Employee(Re));
}

//pdf
void Dialog::on_pb_export_clicked()
{
    {
            int CIN=ui->lineEdit_CIN->text().toInt();
            QString CIN_pdf=QString::number(CIN);
               QString Nom=ui->lineEdit_Nom->text();
               QString Prenom=ui->lineEdit_Prenom->text();
               QString Email=ui->lineEdit_Email->text();
               QString Phone=ui->lineEdit_Phone->text();
               QString Function=ui->lineEdit_Function->text();
               QString Mdp=ui->lineEdit_Mdp->text();



            QPrinter printer;
                 printer.setOutputFormat(QPrinter::PdfFormat);
                 printer.setOutputFileName("Employee.pdf");
                 QPainter painter;
                 painter.begin(&printer);
                 QFont font;

                 font.setPixelSize(40);
                 painter.setFont(font);
                 painter.setPen(Qt::red);
                 painter.drawText(250,150,"Fiche Des Employees : ");
                 font.setPixelSize(20);
                 painter.setFont(font);
                 painter.setPen(Qt::red);
                 painter.drawText(100,300,"CIN: ");
                 painter.drawText(100,350,"Nom: ");
                 painter.drawText(100,400,"Prenom:");
                 painter.drawText(100,500,"email:");
                 painter.drawText(100,550,"phone:");
                 painter.drawText(100,600,"Function: ");
                 painter.drawText(100,650,"Mdp:");
                 painter.setFont(font);
                      painter.setPen(Qt::black);
                      painter.drawText(300,300,CIN_pdf);
                      painter.drawText(300,350,Nom);
                      painter.drawText(300,400,Prenom);
                      painter.drawText(300,500,Email);
                      painter.drawText(300,550,Phone);
                      painter.drawText(300,600,Function);
                      painter.drawText(300,650,Mdp);

                      QDesktopServices::openUrl(QUrl("Employee.pdf"));



                 painter.end();

        }
}

//stat
void Dialog::on_pb_statistique_clicked()
{
    int Nawres;
                   Statistiques w(this);
                   w.setWindowTitle("Statistiques des employees");

                   Nawres = w.exec();
                   qDebug() << Nawres;
                   if (Nawres == QDialog::Rejected)
                     return;
}

void Dialog::openDialog()
{
      DuarteCorporation::widget *neww = new DuarteCorporation::widget();
        neww->show();
}

//chat
void Dialog::on_pb_chat_clicked()
{
    openDialog();
}
/***************************CLIENT********************************/

//ajouter
void Dialog::on_pushButton_ajouter_2_clicked()
{
    int cin=ui->lineEdit_cin_2->text().toInt();
              QString nom=ui->lineEdit_nom_2->text();
              QString prenom=ui->lineEdit_prenom_2->text();
              int age=ui->lineEdit_age_2->text().toInt();
              QString email=ui->lineEdit_email_2->text();
              QString phone=ui->lineEdit_phone_2->text();
               int budget=ui->lineEdit_budget_2->text().toInt();
            client c(cin,nom,prenom,age,email,phone,budget);

           c.ajouter_client(c);
           ui->tableView->setModel(c.afficher_client());

}

//modifier

void Dialog::on_pushButton_modifier_2_clicked()
{
    int cin=ui->lineEdit_cin_2->text().toInt();
              QString nom=ui->lineEdit_nom_2->text();
              QString prenom=ui->lineEdit_prenom_2->text();
              int age=ui->lineEdit_age_2->text().toInt();
              QString email=ui->lineEdit_email_2->text();
              QString phone=ui->lineEdit_phone_2->text();
               int budget=ui->lineEdit_budget_2->text().toInt();
            client c(cin,nom,prenom,age,email,phone,budget);
    c.modifier_client(c);
    ui->tableView->setModel(c.afficher_client());


}

//suppression
void Dialog::on_pushButton_supprimer_2_clicked()
{
    client c;
        c.set_cin(ui->lineEdit_cin_2->text().toInt());
        c.supprimer_client(c);
    ui->lineEdit_cin_2->setText("");
    ui->tableView->setModel(c.afficher_client());

}

void Dialog::on_groupBox_clicked()
{

}

//affichage
void Dialog::on_pushButton_afficher_clicked()
{
    client c;
       //affichage simple
       ui->tableView->setModel(c.afficher_client());
       //afficher selon le nom
       if(QString::number(ui->comboBox->currentIndex())=="0"){
        ui->tableView->setModel(c.afficher_client_trie_prenom());
       }
       //afficher selon le prenom
       else if(QString::number(ui->comboBox->currentIndex())=="1"){
           ui->tableView->setModel(c.afficher_client_trie_nom());
       }
       //afficher selon l'age
       else if(QString::number(ui->comboBox->currentIndex())=="2"){
           ui->tableView->setModel(c.afficher_client_trie_age());

   }
}
//chercher
void Dialog::on_pushButton_chercher_clicked()
{
    client c;
  QString rech =ui->lineEdit_chercher_3->text();
  ui->tableView->setModel(c.chercher_client(rech));
}

//pdf
void Dialog::on_pushButton_pdf_clicked()
{
    int cin=ui->lineEdit_cin_2->text().toInt();
        QString cin_pdf=QString::number(cin);
           QString nom=ui->lineEdit_nom_2->text();
           QString prenom=ui->lineEdit_prenom_2->text();
           int age=ui->lineEdit_age_2->text().toInt();
           QString age_pdf=QString::number(age);
           QString email=ui->lineEdit_email_2->text();
           QString phone=ui->lineEdit_phone_2->text();
           int budget=ui->lineEdit_budget_2->text().toInt();
           QString budget_pdf=QString::number(budget);

        QPrinter printer;
             printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setOutputFileName("clients.pdf");
             QPainter painter;
             painter.begin(&printer);
             QFont font;

             font.setPixelSize(40);
             painter.setFont(font);
             painter.setPen(Qt::red);
             painter.drawText(250,150,"Fiche Des clients : ");
             font.setPixelSize(20);
             painter.setFont(font);
             painter.setPen(Qt::red);
             painter.drawText(100,300,"CIN: ");
             painter.drawText(100,350,"Nom: ");
             painter.drawText(100,400,"Prenom:");
             painter.drawText(100,450,"age:");
             painter.drawText(100,500,"email:");
             painter.drawText(100,550,"phone:");
             painter.drawText(100,600,"budget: ");
             painter.setFont(font);
                  painter.setPen(Qt::black);
                  painter.drawText(300,300,cin_pdf);
                  painter.drawText(300,350,nom);
                  painter.drawText(300,400,prenom);
                  painter.drawText(300,450,age_pdf);
                  painter.drawText(300,500,email);
                  painter.drawText(300,550,phone);
                  painter.drawText(300,600,budget_pdf);

    QDesktopServices::openUrl(QUrl("clients.pdf"));

             painter.end();
}
//activated
void Dialog::on_tableView_activated(const QModelIndex &index)
{
    QString val=ui->tableView->model()->data(index).toString();
            QString sQuery="SELECT CIN_C,NOM_C,PRENOM_C,AGE_C,EMAIL_C,PHONE_C,BUDGET_C FROM CLIENT WHERE CIN_C='"+val+"' or NOM_C='"+val+"' or PRENOM_C='"+val+"' or AGE_C='"+val+"' or EMAIL_C='"+val+"' or PHONE_C='"+val+"'or BUDGET_C='"+val+"'";
            QSqlQuery qry;
            qry.prepare(sQuery);

            if(qry.exec()){
                while(qry.next())
                {
                    ui->lineEdit_cin_2->setText(qry.value(0).toString());
                    ui->lineEdit_nom_2->setText(qry.value(1).toString());
                    ui->lineEdit_prenom_2->setText(qry.value(2).toString());
                    ui->lineEdit_age_2->setText(qry.value(3).toString());
                    ui->lineEdit_email_2->setText(qry.value(4).toString());
                    ui->lineEdit_phone_2->setText(qry.value(5).toString());
                    ui->lineEdit_budget_2->setText(qry.value(6).toString());


                }
            }
            else{
                QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                                   QObject::tr("row not shown.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);
            }
}
//calcul fidelite
void Dialog::on_pushButton_calcul_2_clicked()
{
    client c;

       c.set_cin(ui->lineEdit_cinfidele_2->text().toInt());
        c.calcul(c);
        ui->lineEdit_cinfidele_2->setText("");
        ui->tableView->setModel(c.afficher_client());
}
//excel
void Dialog::on_pushButton_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                      tr("Excel Files (*.xls)"));
      if (fileName.isEmpty())
          return;

      ExportExcel obj(fileName, "LES POINTS DE FIDELITE DE CHAQUE CLIENT", ui->tableView);

      //colums to export
      obj.addField(0, "cin", "int");
      obj.addField(1, "nom", "char(20)");
      obj.addField(2, "prenom", "char(20)");
      obj.addField(7, "pts_de_fidelite", "int");





      int retVal = obj.export2Excel();
      if( retVal > 0)
      {
          QMessageBox::information(this, tr("Done"),
                                   tr("Toutes les informations ont été enregistrée"));
      }
}
//qrcode
void Dialog::on_pushButton_qr_2_clicked()
{
    if(ui->tableView->currentIndex().row()==-1)
                               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                                        QObject::tr("Veuillez Choisir un employé du Tableau.\n"
                                                                    "Click Ok to exit."), QMessageBox::Ok);
                           else
                           {
                                int  cin=ui->tableView->model()->data(ui->tableView->model()->index(ui->tableView->currentIndex().row(),0)).toInt();
                                const qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(std::to_string(cin).c_str(), qrcodegen::QrCode::Ecc::LOW);
                                std::ofstream myfile;
                                myfile.open ("qrcode.svg") ;
                                   myfile << qr.toSvgString(2);
                                   myfile.close();
                                   QSvgRenderer svgRenderer(QString("qrcode.svg"));
                                   QPixmap pix( QSize(90, 90));
                                   QPainter pixPainter( &pix );
                                   svgRenderer.render(&pixPainter);
                                ui->label_19->setPixmap(pix);
                           }
}
//stat
void Dialog::on_pushButton_stat_clicked()
{
    int res;
               statistiques w(this);
               w.setWindowTitle("Statistiques des clients");

               res = w.exec();
               qDebug() << res;
               if (res == QDialog::Rejected)
                 return;
}

//*************************************MISSION********************************************

//ajouter
void Dialog::on_pb_ajouter_2_clicked()
{
    int id=ui->le_id->text().toInt();
        int log=ui->le_log->text().toInt();
        int cin=ui->le_cin->text().toInt();
       int tran=ui->le_tran->text().toInt();
         QDate DATE_DEPART=ui->le_depart->date();
         QDate DATE_RETOUR=ui->le_retour->date();
         QString TYPE_MISSION=ui->le_type->text();
        QString DIRECTION=ui->le_direction->text();

        mission m(id,log,tran,cin,DATE_DEPART,DATE_RETOUR,TYPE_MISSION,DIRECTION);
        m.ajouter_valid(ui->le_id->text().toInt());

        m.ajouter_mission(m);

}


//modifier
void Dialog::on_pb_update_clicked()
{
    int id=ui->le_id->text().toInt();
        int log=ui->le_log->text().toInt();
        int cin=ui->le_cin->text().toInt();
       int tran=ui->le_tran->text().toInt();
         QDate DATE_DEPART=ui->le_depart->date();
         QDate DATE_RETOUR=ui->le_retour->date();
         QString TYPE_MISSION=ui->le_type->text();
        QString DIRECTION=ui->le_direction->text();

        mission m(id,log,tran,cin,DATE_DEPART,DATE_RETOUR,TYPE_MISSION,DIRECTION);
        m.modifier_mission(m);
}


//suppression
void Dialog::on_pb_supprimer_2_clicked()
{
    mission m;
        m.setID_Mission(ui->le_id->text().toInt());
        m.supprimer_valid(ui->le_id->text().toInt());
        m.supprimer_mission(m);
    ui->le_id->setText("");

}

//affichage
void Dialog::on_pushButton_aff_clicked()
{
    mission m;
       //affichage simple
       ui->tab_mission->setModel(m.afficher_mission());
       if(QString::number(ui->comboBox_2->currentIndex())=="0"){
        ui->tab_mission->setModel(m.afficher_mission_trie_direction());
       }
       //afficher selon le prenom
       else if(QString::number(ui->comboBox_2->currentIndex())=="1"){
           ui->tab_mission->setModel(m.afficher_mission_trie_type());
       }
}

void Dialog::on_pushButton_rech_clicked()
{
    mission m;
  QString rech =ui->le_recherche->text();
  ui->tab_mission->setModel(m.chercher_mission(rech));
}


//stat
void Dialog::on_le_stat_clicked()
{
    int res;
               statistiquee w(this);
               w.setWindowTitle("Statistiques des missions");

               res = w.exec();
               qDebug() << res;
               if (res == QDialog::Rejected)
                 return;
}


//pdf
void Dialog::on_pushButton_2_clicked()
{
    QPdfWriter pdf("C:/Users/Hp/Desktop/missions.pdf");
          QPainter painter(&pdf);
         int i = 4000;
              painter.setPen(Qt::green);
              painter.setFont(QFont("Arial", 30));
              painter.drawText(1100,1200,"Liste Des missions");
              painter.setPen(Qt::red);
              painter.setFont(QFont("Arial", 10));
              painter.drawRect(100,100,7300,2600);
              painter.drawRect(0,3000,9600,500);
              painter.setFont(QFont("Arial", 9));
              painter.drawText(200,3300,"ID_MISSION");
              painter.drawText(1300,3300,"ID_LOG");
              painter.drawText(2400,3300,"ID_TRAN");
              painter.drawText(3500,3300,"CIN_C");
                 painter.drawText(4500,3300,"DATE_DEPART");
                    painter.drawText(6000,3300,"DATE_RETOUR");
                    painter.drawText(8000,3300,"TYPE");
                       painter.drawText(8500,3300,"DIRECTION");

              QSqlQuery query;
              query.prepare("select * from MISSION");
              query.exec();
              while (query.next())
              {
                  painter.drawText(200,i,query.value(0).toString());
                  painter.drawText(1300,i,query.value(1).toString());
                  painter.drawText(2400,i,query.value(2).toString());
                  painter.drawText(3500,i,query.value(3).toString());
                  painter.drawText(4500,i,query.value(4).toString());
                  painter.drawText(6000,i,query.value(5).toString());
                  painter.drawText(8000,i,query.value(6).toString());
                  painter.drawText(9000,i,query.value(7).toString());



                 i = i + 500;
              }
              QMessageBox::information(this, QObject::tr("PDF Enregistré"),
                        QObject::tr("PDF Enregistré!.\n" "Click Cancel to exit."), QMessageBox::Cancel);


         painter.end();
}

void Dialog::on_tab_mission_activated(const QModelIndex &index)
{

}

//afficher historique
void Dialog::on_pushButton_3_clicked()
{
    mission m;
       ui->tab_historique->setModel(m.afficher_historique());
}
