#include "client.h"

//constructeur
client::client()
{
    cin=0;
    nom="";
    prenom="";
    age=0;
    email="";
    phone="";
    budget=0;
    rech="";
}

//constructeur
client::client(int cin,QString nom,QString prenom,int age,QString email,QString phone,int budget)
{
      this->cin=cin;
      this->nom=nom;
      this->prenom=prenom;
      this->age=age;
      this->email=email;
      this->phone=phone;
      this->budget=budget;

}


//setters
void client::set_cin(int cin){this->cin=cin;}
void client::set_nom(QString nom){ this->nom=nom;}
void client::set_prenom(QString prenom){this->prenom=prenom;}
void client::set_age(int age){this->age=age;};
void client::set_email(QString email){this->email=email;}
void client::set_phone(QString phone){this->phone=phone;};
void client::set_budget(int budget){this->budget=budget;};
void client::set_pts(int pts){this->pts=pts;};


//getters
int client::get_cin(){return cin;}
QString client::get_nom(){return nom;}
QString client::get_prenom(){return prenom;}
int client::get_age(){return age;}
QString client::get_email(){return email;}
QString client::get_phone(){return phone;}
int client::get_budget(){return budget;}
QString client::get_rech(){return rech;}



//ajout d'un client
void client::ajouter_client(client c){
    QString cin_string= QString::number(cin);
         QString age_string= QString::number(age);
         QString budget_string= QString::number(budget);
    QString sQuery="INSERT INTO CLIENT (CIN_C,NOM_C,PRENOM_C,AGE_C,EMAIL_C,PHONE_C,BUDGET_C) VALUES (:cin,:nom,:prenom,:age,:email,:phone,:budget)";

    QSqlQuery qry;

    qry.prepare(sQuery);
    qry.bindValue(":cin",cin_string);
    qry.bindValue(":nom",nom);
    qry.bindValue(":prenom",prenom);
    qry.bindValue(":age",age_string);
    qry.bindValue(":email",email);
    qry.bindValue(":phone",phone);
    qry.bindValue(":budget",budget_string);


    if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row created and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not created and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


//modifier
void client::modifier_client(client c){
 QSqlQuery qry;
 QString cin_string= QString::number(cin);
      QString age_string= QString::number(age);
      QString budget_string= QString::number(budget);
         qry.prepare ("UPDATE CLIENT SET  NOM_C = :nom, PRENOM_C = :prenom, AGE_C = :age, EMAIL_C = :email,PHONE_C=:phone,BUDGET_C = :budget WHERE CIN_C = :cin" );

         qry.bindValue(":cin",cin_string);
         qry.bindValue(":nom",nom);
         qry.bindValue(":prenom",prenom);
         qry.bindValue(":age",age_string);
         qry.bindValue(":email",email);
         qry.bindValue(":phone",phone);
         qry.bindValue(":budget",budget_string);

        if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row updated and saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else

    {
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not updated and not saved.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


//suppression
void client::supprimer_client(client c){

    QString cin_c=QString::number(cin);


    QString sQuery="DELETE FROM CLIENT WHERE CIN_C='"+cin_c+"'";

    QSqlQuery qry;

    qry.prepare(sQuery);
    if(qry.exec())
    {
        QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                           QObject::tr("row deleted successfully.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                           QObject::tr("row not deleted.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
}


//affichage
QSqlQueryModel* client::afficher_client(){

    QString sQuery="SELECT * FROM CLIENT";

      QSqlQueryModel* model=new QSqlQueryModel();

      QSqlQuery qry;

      qry.prepare(sQuery);

      qry.exec();
      model->setQuery(qry);

                return model;
}


//trie nom
QSqlQueryModel* client::afficher_client_trie_nom(){
    QString sQuery="SELECT * FROM CLIENT ORDER BY NOM_C";

    QSqlQueryModel*model1=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model1->setQuery(qry);
return model1;
}



//trie prenom
QSqlQueryModel* client::afficher_client_trie_prenom(){
    QString sQuery="SELECT * FROM CLIENT ORDER BY PRENOM_C";

    QSqlQueryModel*model2=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model2->setQuery(qry);
return model2;
}



//trie age
QSqlQueryModel* client::afficher_client_trie_age(){
    QString sQuery="SELECT * FROM CLIENT ORDER BY AGE_C";

    QSqlQueryModel*model3=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model3->setQuery(qry);
return model3;
}


//chercher
QSqlQueryModel* client::chercher_client(QString rech){
    QString sQuery="SELECT * FROM CLIENT WHERE NOM_C LIKE'%"+rech+"%' or PRENOM_C LIKE'%"+rech+"%'";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}


//calculer les points de fidelites
void client::calcul(client c)
{

    QSqlQuery q;
    QString cin_cc=QString::number(cin);

          q.prepare("SELECT * FROM MISSION WHERE CIN_C=:cin");
          q.bindValue(":cin",cin_cc);

q.exec();
          int total=0;//calculer nbr de ligne
          while(q.next()){
              total++;
          }
          q.prepare("UPDATE CLIENT set PTS_FIDELITE_C = :pts WHERE CIN_C=:cin");
          q.bindValue(":cin",cin_cc);
          q.bindValue(":pts",total);
          if(q.exec())
      {
          QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                             QObject::tr("row calculated and saved.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
      }
      else{
          QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                             QObject::tr("row not calculated and not saved.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
      }
}


//stat pour calculer les budgets
int client::calculer1(int choix,int choix2)
{
    QSqlQuery query;
          query.prepare("SELECT * FROM CLIENT WHERE BUDGET_C BETWEEN (:choix) AND (:choix2)");
          query.bindValue(":choix",choix);
          query.bindValue(":choix2",choix2);

          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
 }

          return total;
}
