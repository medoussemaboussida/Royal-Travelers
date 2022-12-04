#include "mission.h"

//constructeur
mission::mission()
{
ID_Mission=0; ID_Log=0; ID_TRAN=0; CIN_C=0 ; TYPE_MISSION =" ";DIRECTION=" ";rech="";
}

//constructeur
mission ::mission(int id,int log,int tran,int  cin ,QDate date_depart,QDate date_retour,QString TYPE_MISSION,QString DIRECTION)
{this->ID_Mission=id;
    this->ID_Log=log;
    this->ID_TRAN=tran;
    this-> CIN_C= cin;
   this->DATE_DEPART=date_depart;
    this->DATE_RETOUR=date_retour;
   this-> TYPE_MISSION=TYPE_MISSION;
    this-> DIRECTION=DIRECTION;
}
//getters
int mission::getID_Mission(){return ID_Mission;}
int mission::getID_Log(){return ID_Log;}
int mission::getID_Transportation(){return ID_TRAN;}
int mission::getCIN_Client(){return CIN_C;}
QDate mission::getDATE_DEPART(){return  DATE_DEPART;}
QDate mission::getDATE_RETOUR(){return  DATE_RETOUR;}
QString mission::getTYPE_MISSION(){return TYPE_MISSION;}
QString mission::getdirection(){return DIRECTION;}
QString mission::get_rech(){return rech;}


//setters
void mission::setID_Mission(int id) {this->ID_Mission=id;}
void mission::setID_Log(int ID_Log){this->ID_Log=ID_Log;}
void mission::setID_Transportation(int tran)  {this->ID_TRAN=tran;}
void mission::setCIN_Client(int cin){this->CIN_C=cin;}
void mission::setDATE_DEPART(QDate date_depart){this->DATE_DEPART=date_depart;}
void mission::setDATE_RETOUR(QDate date_retour){this->DATE_RETOUR=date_retour;}
void mission::setTYPE_MISSION(QString type){this->TYPE_MISSION=TYPE_MISSION;}
void mission::setdirection(QString dir){this->DIRECTION=DIRECTION;}



//ajout d'une mission
void mission::ajouter_mission(mission m){
    QString id_string=QString::number(ID_Mission);
        QString id_string2=QString::number(ID_Log);
        QString id_string3=QString::number(ID_TRAN);
        QString id_string4=QString::number(CIN_C);
    QString sQuery="INSERT INTO MISSION  (ID_MISSION, ID_LOG,ID_TRAN,CIN_C,DATE_DEPART,DATE_RETOUR,TYPE_MISSION,DIRECTION) "
                   "VALUES (:ID_MISSION , :ID_LOG , :ID_TRAN , :CIN_C, :DATE_DEPART, :DATE_RETOUR, :TYPE_MISSION, :DIRECTION)";

    QSqlQuery query;

    query.prepare(sQuery);
    query.bindValue(":ID_MISSION", id_string);
      query.bindValue(":ID_LOG", id_string2);
      query.bindValue(":ID_TRAN", id_string3);
      query.bindValue(":CIN_C", id_string4);
      query.bindValue(":DATE_DEPART",DATE_DEPART);
      query.bindValue(":DATE_RETOUR",DATE_RETOUR);
      query.bindValue(":TYPE_MISSION",TYPE_MISSION);
      query.bindValue(":DIRECTION",DIRECTION);


    if(query.exec())
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


//modifier mission
void mission::modifier_mission(mission m){
 QSqlQuery query;
 QString id= QString::number(ID_Mission);
QString log= QString::number(ID_Log);
QString cin = QString::number (CIN_C);
QString tran= QString::number(ID_TRAN);


    query.prepare("UPDATE MISSION SET  ID_LOG= :ID_LOG ,ID_TRAN= :ID_TRAN ,CIN_C = :CIN_C,DATE_DEPART= :DATE_DEPART,DATE_RETOUR= :DATE_RETOUR,TYPE_MISSION= :TYPE_MESSION,DIRECTION= :DIRECTION WHERE ID_MISSION= :ID_MISSION");
    query.bindValue(":ID_MISSION",id);
    query.bindValue(":ID_LOG",log);
    query.bindValue(":ID_TRAN",tran);
    query.bindValue(":CIN_C",cin);
    query.bindValue(":DATE_DEPART",DATE_DEPART);
    query.bindValue(":DATE_RETOUR",DATE_RETOUR);
query.bindValue(":TYPE_MISSION",TYPE_MISSION);
query.bindValue(":DIRECTION",DIRECTION);
        if(query.exec())
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
void mission::supprimer_mission(mission m){

    QString id= QString::number(ID_Mission);



    QString sQuery="DELETE FROM MISSION WHERE ID_MISSION='"+id+"'";

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

//afficher
QSqlQueryModel* mission::afficher_mission(){

    QString sQuery="SELECT * FROM MISSION";

      QSqlQueryModel* model=new QSqlQueryModel();

      QSqlQuery qry;

      qry.prepare(sQuery);

      qry.exec();
      model->setQuery(qry);

                return model;
}



//trie direction
QSqlQueryModel* mission::afficher_mission_trie_direction(){
    QString sQuery="SELECT * FROM MISSION ORDER BY DIRECTION";

    QSqlQueryModel*model2=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model2->setQuery(qry);
return model2;
}



//trie type
QSqlQueryModel* mission::afficher_mission_trie_type(){
    QString sQuery="SELECT * FROM MISSION ORDER BY TYPE_MISSION";

    QSqlQueryModel*model3=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model3->setQuery(qry);
return model3;
}


QSqlQueryModel* mission::chercher_mission(QString rech){
    QString sQuery="SELECT * FROM MISSION WHERE TYPE_MISSION LIKE'%"+rech+"%' or DIRECTION LIKE'%"+rech+"%'";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}
int mission :: calculer_m(QString choix)
{

    QSqlQuery query;
          query.prepare("SELECT * FROM MISSION WHERE TYPE_MISSION =:choix");
          query.bindValue(":choix",choix);


          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
}
          return total;
}

//ajouter a la bd historique en cliquant sur boutton valider
void mission::ajouter_valid(int ID_Mission){
     QString id_string=QString::number(ID_Mission);
QString desc="ajout";
QSqlQuery qry;
qry.prepare("INSERT INTO HISTORIQUE (ID_M,DESCRI)"
            "VALUES(:ID_M,:DESCRI)");
qry.bindValue(":ID_M",id_string);
qry.bindValue(":DESCRI",desc);
if(qry.exec())
{
QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                   QObject::tr("enregistre\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}
else

{
QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                   QObject::tr("n est pas enregistre.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}
}
//historique suppression
void mission::supprimer_valid(int ID_Mission){
     QString id_string=QString::number(ID_Mission);
QString desc="suppression";
QSqlQuery qry;
qry.prepare("INSERT INTO HISTORIQUE (ID_M,DESCRI)"
            "VALUES(:ID_M,:DESCRI)");
qry.bindValue(":ID_M",id_string);
qry.bindValue(":DESCRI",desc);
if(qry.exec())
{
QMessageBox::critical(nullptr, QObject::tr("sql query successful"),
                   QObject::tr("enregistre\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}
else

{
QMessageBox::critical(nullptr, QObject::tr("sql query unsuccessful"),
                   QObject::tr("n est pas enregistre.\n"
                               "Click Cancel to exit."), QMessageBox::Cancel);
}
}
QSqlQueryModel * mission::afficher_historique(){
    QSqlQueryModel * modelhisto =new QSqlQueryModel();
    QSqlQuery qry;
    QString query="SELECT ID_M,DESCRI FROM HISTORIQUE";
    qry.prepare(query);
    qry.exec();
    modelhisto->setQuery(qry);

    return modelhisto;

}
