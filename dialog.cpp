#include "dialog.h"
#include "ui_dialog.h"
#include "employee.h"
#include "statistiques.h"
#include <QMessageBox>
#include <QPainter>
#include <QDesktopServices>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QAbstractPrintDialog>
#include <QUrl>
#include <QDebug>
#include "widget.h"

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

void Dialog::on_pb_TrieNom_clicked()
{
    ui->tab_employee->setModel(E.afficher_Employee_trie_Nom());
}

void Dialog::on_TriePrenom_clicked()
{
    ui->tab_employee->setModel(E.afficher_Employee_trie_prenom());
}

void Dialog::on_pb_chercher_clicked()
{
    Employee E;
       QString Re =ui->lineEdit_chercher->text();
       ui->table_chercher->setModel(E.chercher_Employee(Re));
}

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

void Dialog::on_pb_chat_clicked()
{
    openDialog();
}
