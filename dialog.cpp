#include "dialog.h"
#include "ui_dialog.h"
#include "employee.h"
#include "client.h"
#include"mission.h"
#include "statistiques.h"
#include "statistique.h"
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
#include<QTimer>
#include<QDateTime>
#include "transport.h"
#include <limits>
#include"logement.h"
#include "stat_log.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    //controle de saisie EMPLOYE
    ui->setupUi(this);
    ui->lineEdit_CIN->setValidator(new QIntValidator(0, 99999999, this));
    ui->tab_employee->setModel(E.afficher());

    //controle de saisie CLIENT
    QRegularExpression QRegExp2("[a-zA-Z0-9]+@[a-zA-Z]+.[a-zA-Z]+");
                  QRegularExpressionValidator *validator2 = new QRegularExpressionValidator(QRegExp2,this);
                  ui->lineEdit_email_2->setValidator(validator2);
                  ui->lineEdit_cin_2->setValidator(new QIntValidator(0,99999999,this));
                  ui->lineEdit_phone_2->setValidator(new QIntValidator(0,99999999,this));
                  ui->lineEdit_age_2->setValidator(new QIntValidator(0,100,this));
                  ui->lineEdit_cinfidele_2->setValidator(new QIntValidator(0,99999999,this));

    //contorle de saisie TRANSPORT



    //controle de saisie MISSION

                  ui->le_id->setValidator (new QIntValidator (0,999999,this));
                        ui->le_log->setValidator(new QIntValidator (0,999999,this));
                        ui->le_cin->setValidator(new QIntValidator (0,999999,this));
                        ui->le_tran->setValidator(new QIntValidator (0,999999,this));
                       ui->le_type->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));
                        ui->le_direction->setValidator(new QRegExpValidator(  QRegExp("[A-z]*")  ));

    //controle de saisie LOGEMENT

    //qtimer
    //ui->countdown->setText("1:00");
       QTimer *timer=new QTimer(this);
       connect(timer ,SIGNAL(timeout()),this,SLOT(showTime()));
       timer->start();
       QDateTime session=QDateTime::currentDateTime();
       QString sessiontext=session.toString();
       ui->session->setText(sessiontext);

       //arduino gadour
       arduino = new seriallink;

           arduino->openConnection();

           /*if(arduino->isWritable()){
               arduino->write("G");
               qDebug() << "message written";
           }
           QByteArray t = arduino->read();
           qDebug() << t;*/

           //connect(arduino, &seriallink::gotNewData, this, &MainWindow::updateGUI);
}

Dialog::~Dialog()
{
    delete ui;
}
/*******timer*******/
void Dialog::showTime()
{
    QTime time=QTime::currentTime();
    QString time_text=time.toString("hh : mm : ss");
    ui->Digital_clock->setText(time_text);


}
/****************************************EMPLOYEE***********************************************/

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
                ui->tab_employee->setModel(E.afficher());


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
               QString Phone=ui->lineEdit_Phone->text();
               QString Email=ui->lineEdit_Email->text();
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
            else
                QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                                   QObject::tr("row not updated and not saved.\n"
                                               "Click Cancel to exit."), QMessageBox::Cancel);


}


//tri employe nom
void Dialog::on_pb_TrieNom_clicked()
{
    ui->tab_employee->setModel(E.afficher_Employee_trie_Nom());
}



//tri employe prenom
void Dialog::on_TriePrenom_clicked()
{
    ui->tab_employee->setModel(E.afficher_Employee_trie_prenom());
}


//chercher employe
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


//stat employe
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

//chat
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

//ajouter client
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


//modifier client
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

//affichage client
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


//chercher client
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


//tableview activated
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


//export excel client
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


//qrcode client
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


//stat client
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

//ajouter mission
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


//modifier mission
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


//suppression mission
void Dialog::on_pb_supprimer_2_clicked()
{
    mission m;
        m.setID_Mission(ui->le_id->text().toInt());
        m.supprimer_valid(ui->le_id->text().toInt());
        m.supprimer_mission(m);
    ui->le_id->setText("");

}

//affichage mission
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


//recherche mission
void Dialog::on_pushButton_rech_clicked()
{
    mission m;
  QString rech =ui->le_recherche->text();
  ui->tab_mission->setModel(m.chercher_mission(rech));
}


//stat mission
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

//afficher historique mission
void Dialog::on_pushButton_3_clicked()
{
    mission m;
       ui->tab_historique->setModel(m.afficher_historique());
}


/***************************************TRANSPORT**********************************************************/

//ajout transport
void Dialog::on_pb_ajouter_3_clicked()
{
    int id_tran=ui->le_id_tran->text().toInt();
       QString type=ui->le_type_2->text();
       float prix=ui->le_prix->text().toFloat();
       int nb_moy=ui->le_nb_moy->text().toInt();

       Transport T(id_tran,type,prix,nb_moy);
       bool test=T.ajouter();
       if(test){
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("ajout effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           ui->tab_tran->setModel(T.afficher());
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("ajout non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       QString textajouter;
       QSqlQuery qry;
       qry.prepare("select * from APPAREILS");
       textajouter="L'ajout d'un site a la base de donnees de nom = "+QString(type)+" a ete effectue avec succees";
}


//get from tableview
int Dialog::getselectedtran(){
        int s=ui->tab_tran->selectionModel()->currentIndex().row();
        QModelIndex index =ui->tab_tran->model()->index(s, 0,QModelIndex());
        int aff=ui->tab_tran->model()->data(index).toString().toInt();
        return aff;

  }


//suppression transport
void Dialog::on_pb_supprimer_3_clicked()
{
Transport T;
T.setid_tran(ui->le_id_tran->text().toInt());
T.supprimer(T);
ui->le_id_tran->setText("");

}


//modifier transport
void Dialog::on_UpdateTran_clicked()
{

    int id_tran=ui->le_id_tran->text().toInt();
       QString type=ui->le_type_2->text();
       float prix=ui->le_prix->text().toFloat();
       int nb_moy=ui->le_nb_moy->text().toInt();

       Transport T(id_tran,type,prix,nb_moy);
       T.ModifierTransport(T);
       ui->tab_tran->setModel(T.afficher());
}


//chercher transport
void Dialog::on_rec_textChanged(const QString &arg1)
{
    Transport T;
      ui->tab_tran->setModel(T.rechercher(arg1));
}



//tri transport
void Dialog::on_pushButton_01_clicked()
{    Transport T;

     ui->tab_tran->setModel(T.TriCASC());
}

//tri transport
void Dialog::on_pushButton_02_clicked()
{    Transport T;

    ui->tab_tran->setModel(T.TriCDESC());
}

//tri transport
void Dialog::on_pushButton_03_clicked()
{    Transport T;

    ui->tab_tran->setModel(T.TriDASC());
}

//tri transport
void Dialog::on_pushButton_04_clicked()
{    Transport T;

    ui->tab_tran->setModel(T.TriDDESC());

}

//tri transport
void Dialog::on_pushButton_05_clicked()
{    Transport T;

 ui->tab_tran->setModel(T.TriEASC());
}

//tri transport
void Dialog::on_pushButton_06_clicked()
{    Transport T;

    ui->tab_tran->setModel(T.TriEDESC());

}



//pdf
void Dialog::on_pb_print_clicked()
{
    int id_tran=ui->le_id_tran->text().toInt();
    QString idtran_pdf=QString::number(id_tran);

           QString type=ui->le_type_2->text();

           int prix=ui->le_prix->text().toInt();
           QString prix_pdf=QString::number(prix);

           int nb_moy=ui->le_nb_moy->text().toInt();
           QString moy_pdf=QString::number(nb_moy);

        QPrinter printer;
             printer.setOutputFormat(QPrinter::PdfFormat);
             printer.setOutputFileName("transport.pdf");
             QPainter painter;
             painter.begin(&printer);
             QFont font;

             font.setPixelSize(40);
             painter.setFont(font);
             painter.setPen(Qt::red);
             painter.drawText(250,150,"MOYEN DE TRANSPORT : ");
             font.setPixelSize(20);
             painter.setFont(font);
             painter.setPen(Qt::red);
             painter.drawText(100,300,"ID_TRAN: ");
             painter.drawText(100,350,"TYPE: ");
             painter.drawText(100,400,"PRIX:");
             painter.drawText(100,450,"NB_MOY:");
             painter.setFont(font);
                  painter.setPen(Qt::black);
                  painter.drawText(300,300,idtran_pdf);
                  painter.drawText(300,350,type);
                  painter.drawText(300,400,prix_pdf);
                  painter.drawText(300,450,moy_pdf);


    QDesktopServices::openUrl(QUrl("transport.pdf"));

             painter.end();
}



//archiver transport
void Dialog::on_Archiver_clicked()
{
    Transport T;
    QMessageBox::StandardButton reply =QMessageBox::information(this,"Archiver la liste","Etes-vous sur?",QMessageBox::Yes|QMessageBox::No);

           if(reply == QMessageBox::Yes){

       int k=getselectedtran();
       bool test=T.ArchiverTransport(k);
       if(test){
           QMessageBox::information(nullptr, QObject::tr("ok"),
                       QObject::tr("Archivage effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           ui->tab_tran->setModel(T.afficher());
       }
       else
           QMessageBox::critical(nullptr, QObject::tr("not ok"),
                       QObject::tr("Archivage non effectué.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
   }
}



//afficher archive
void Dialog::on_List_clicked()
{
    Transport T;
    ui->tab_tran->setModel(T.listearchive());
}




//affichage normal
void Dialog::on_List_2_clicked()
{
    Transport T;
     ui->tab_tran->setModel(T.afficher());
}


//inarchiver transport
void Dialog::on_Archiver_2_clicked()
{
    Transport T;
    QMessageBox::StandardButton reply =QMessageBox::information(this,"Inarchiver la liste","Etes-vous sur?",QMessageBox::Yes|QMessageBox::No);

            if(reply == QMessageBox::Yes){

        int k=getselectedtran();
        bool test=T.InarchiverTransport(k);
        if(test){
            QMessageBox::information(nullptr, QObject::tr("ok"),
                        QObject::tr("Inarchivage effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_tran->setModel(T.afficher());
        }
        else
            QMessageBox::critical(nullptr, QObject::tr("not ok"),
                        QObject::tr("Inarchivage non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


//stat transport
void Dialog::on_Statistique_clicked()
{
    int res;
              statistique w(this);
               w.setWindowTitle("Statistiques transport");

               res = w.exec();
               qDebug() << res;
               if (res == QDialog::Rejected)
                 return;
}

//*********************************LOGEMENT*****************************************//

//ajout
void Dialog::on_pushButton_4_clicked()
{
    int id=ui->le_idlog->text().toInt();
        QString  type=ui->le_type_3->text();
        QString  duree=ui->le_duree->text();
       QString  adresse=ui->le_adresse->text();
       float prix=ui->le_prix_2->text().toFloat();
       logement l(id,type,duree,adresse,prix);
        l.ajouter_log(l);
}

//suppression
void Dialog::on_pb_supprimer_4_clicked()
{
    logement l;
        l.setID_LOG(ui->le_id_supp->text().toInt());
        l.supprimer_log(l);
    ui->le_id_supp->setText("");

}

//modifier
void Dialog::on_pb_update_2_clicked()
{
    int id=ui->le_idlog->text().toInt();
        QString  type=ui->le_type_3->text();
        QString  duree=ui->le_duree->text();
       QString  adresse=ui->le_adresse->text();
       float prix=ui->le_prix_2->text().toFloat();
       logement l(id,type,duree,adresse,prix);
        l.modifier_log(l);
}

//affichage
void Dialog::on_pushButton_afficherlog_clicked()
{
    logement l;
  ui->tab_logement->setModel(l.afficher());
  //tri selon prix
  if(QString::number(ui->comboBox_3->currentIndex())=="0"){
   ui->tab_logement->setModel(l.triPRIX());
  }
  //afficher selon le type
  else if(QString::number(ui->comboBox_3->currentIndex())=="1"){
      ui->tab_logement->setModel(l.triTYPE());
  }
  //afficher selon id
  else if(QString::number(ui->comboBox_3->currentIndex())=="2"){
      ui->tab_logement->setModel(l.triID());
}
}

//chercher
void Dialog::on_pushButton_cherch_clicked()
{
    logement l;
  QString rech =ui->le_recherche_2->text();
  ui->tab_logement->setModel(l.chercher_log(rech));
}

//pdf
void Dialog::on_le_PDF_clicked()
{
    int id=ui->le_idlog->text().toInt();
    QString id_pdf=QString::number(id);
        QString  type=ui->le_type_3->text();
        QString  duree=ui->le_duree->text();
       QString  adresse=ui->le_adresse->text();
       float prix=ui->le_prix_2->text().toFloat();
       QString prix_pdf=QString::number(prix);
    QPrinter printer;
         printer.setOutputFormat(QPrinter::PdfFormat);
         printer.setOutputFileName("logement.pdf");
         QPainter painter;
         painter.begin(&printer);
         QFont font;

         font.setPixelSize(40);
         painter.setFont(font);
         painter.setPen(Qt::red);
         painter.drawText(250,150,"LOGEMENT : ");
         font.setPixelSize(20);
         painter.setFont(font);
         painter.setPen(Qt::red);
         painter.drawText(100,300,"ID_LOG: ");
         painter.drawText(100,350,"TYPE: ");
         painter.drawText(100,400,"DUREE:");
         painter.drawText(100,450,"PRIX_LOG:");
         painter.drawText(100,500,"LIEU:");

         painter.setFont(font);
              painter.setPen(Qt::black);
              painter.drawText(300,300,id_pdf);
              painter.drawText(300,350,type);
              painter.drawText(300,400,duree);
              painter.drawText(300,450,prix_pdf);
              painter.drawText(300,500,adresse);



QDesktopServices::openUrl(QUrl("logement.pdf"));

         painter.end();
}

//stat
void Dialog::on_le_stat_2_clicked()
{
    int res;
              statistiqueee w(this);
               w.setWindowTitle("Statistiques logement");

               res = w.exec();
               qDebug() << res;
               if (res == QDialog::Rejected)
                 return;
}
//arduino gadour

void Dialog::on_Check_clicked()
{
      QSqlQuery q;
    QString state = "";
        QByteArray data = arduino->read();
        float tmp = ui->temperature->text().toInt();
        QString test = QString::fromStdString(arduino->read().toStdString());
        qDebug() << arduino->read();
        if(tmp > 21){
            arduino->write("s");
            state = "Danger";
            QMessageBox::critical(nullptr, QObject::tr("Danger"),
                        QObject::tr("Danger detecte\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        } else {
            arduino->write("i");
            state = "Ok";
        }
        q.prepare("INSERT INTO ARDUINO_TEMP (TEMPERATURE, ETAT) VALUES(:temp, :etat)");
        q.bindValue(":temp", QString::number(tmp));
        q.bindValue(":etat", state);
        q.exec();
}
