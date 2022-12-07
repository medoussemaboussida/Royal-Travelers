#include "employee.h"
#include "employee.h"
#include "QSqlQuery"
#include "QtDebug"
#include <QObject>
Employee::Employee()
{
CIN=0;Nom="";Prenom="",Email="",Phone="",Function="",Mdp="", Recherche="";
}
Employee::Employee(int CIN,QString Nom,QString Prenom,QString Email,QString Phone,QString Function,QString Mdp)
{this->CIN=CIN; this->Nom=Nom; this->Prenom=Prenom; this->Email=Email; this->Phone=Phone; this->Function=Function; this->Mdp=Mdp;}
int Employee::getCIN(){return CIN;}
QString Employee::getNom(){return Nom;}
QString Employee::getPrenom(){return Prenom;}
QString Employee::getEmail(){return Email;}
QString Employee::getPhone(){return Phone;}
QString Employee::getFunction(){return Function;}
QString Employee::getMdp(){return Mdp;}
QString Employee::getRecherche(){return Recherche;}

void Employee::setCIN(int CIN){this->CIN=CIN;}
void Employee::setNom(QString Nom){this->Nom=Nom;}
void Employee::setPrenom(QString Prenom){this->Prenom=Prenom;}
void Employee::setEmail(QString Email){this->Email=Email;}
void Employee::setPhone(QString Phone){this->Phone=Phone;}
void Employee::setFunction(QString Function){this->Function=Function;}
void Employee::setMdp(QString Mdp){this->Mdp=Mdp;}


bool Employee::ajouter()
{
                         QSqlQuery query;
                                      QString CIN_string = QString::number(CIN);
                              query.prepare("INSERT INTO EMPOLYE (CIN_E,NOM_E,PRENOM_E,EMAIL_E,PHONE_E,FONCTION_E,MDP) "
                                            "VALUES (:CIN, :forNom, :forPrenom, :forEmail, :forPhone, :forFunction, :forMdp)");
                              query.bindValue(":CIN",CIN_string);
                              query.bindValue(":forNom", Nom);
                              query.bindValue(":forPrenom", Prenom);
                              query.bindValue(":forEmail", Email);
                              query.bindValue(":forPhone", Phone);
                              query.bindValue(":forFunction", Function);
                              query.bindValue(":forMdp",Mdp);
                             return query.exec();

}

bool Employee::modifier_Employee(){

           QSqlQuery query;
           QString id_string=QString::number(CIN);


          query.prepare("UPDATE EMPOLYE SET NOM_E = :nom, PRENOM_E = :prenom, EMAIL_E= :Email, PHONE_E= :Phone , FONCTION_E= :Function ; MDP=:Mdp WHERE  CIN_E = :cin");
                              query.bindValue(":cin", id_string);
                              query.bindValue(":nom", Nom);
                              query.bindValue(":prenom", Prenom);
                              query.bindValue(":Email", Email);
                              query.bindValue(":Phone", Phone);
                              query.bindValue(":Function", Function);
                              query.bindValue(":Mdp", Mdp);

                             return query.exec();

        }
bool Employee::supprimer(int CIN)
{
        QSqlQuery query;
            QString res=QString::number(CIN);
             query.prepare("DELETE FROM EMPOLYE WHERE CIN_E=:cin ");
             query.bindValue(":cin",res);
             return query.exec();
    }

QSqlQueryModel* Employee::afficher()
{
    QSqlQueryModel* model=new QSqlQueryModel();
          model->setQuery("SELECT* FROM EMPOLYE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("Phone"));
          model->setHeaderData(5, Qt::Horizontal, QObject::tr("Function"));
          model->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));

          return model;
}
//trie nom
QSqlQueryModel* Employee::afficher_Employee_trie_Nom()
{

    QSqlQueryModel*modelT=new QSqlQueryModel();
    modelT->setQuery("SELECT *FROM EMPOLYE ORDER BY NOM_E ASC");
    modelT->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    modelT->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    modelT->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    modelT->setHeaderData(4, Qt::Horizontal, QObject::tr("Phone"));
    modelT->setHeaderData(5, Qt::Horizontal, QObject::tr("Function"));
    modelT->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));



return modelT;
}
//trie prenom
QSqlQueryModel* Employee::afficher_Employee_trie_prenom()
{

    QSqlQueryModel*modelT1=new QSqlQueryModel();
    modelT1->setQuery("SELECT *FROM EMPOLYE ORDER BY PRENOM_E ASC");
    modelT1->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom"));
    modelT1->setHeaderData(2, Qt::Horizontal, QObject::tr("Prenom"));
    modelT1->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    modelT1->setHeaderData(4, Qt::Horizontal, QObject::tr("Phone"));
    modelT1->setHeaderData(5, Qt::Horizontal, QObject::tr("Function"));
    modelT1->setHeaderData(6, Qt::Horizontal, QObject::tr("Mdp"));


return modelT1;
}
QSqlQueryModel* Employee::chercher_Employee(QString Re){

    QSqlQueryModel*modelR=new QSqlQueryModel();
    modelR->setQuery("SELECT * FROM EMPOLYE WHERE CIN_E LIKE'%"+Re+"%'");


    return modelR;
}
int Employee::Calcul(QString C1)
{
    QSqlQuery query;
          query.prepare("SELECT * FROM EMPOLYE WHERE FONCTION_E =:C1");
          query.bindValue(":C1",C1);


          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
 }

          return total;
}
