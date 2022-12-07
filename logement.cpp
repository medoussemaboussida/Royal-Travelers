#include "logement.h"

//constructor
logement::logement()
{
ID_LOG=0; PRIX_LOG=0;  TYPE_LOG =" ";ADRESSE=" ",DUREE_LOG=" ",rech="";
}

//constructor
logement ::logement(int id,QString type,QString duree,QString adresse,float prix)
{   this->ID_LOG=id;
    this->TYPE_LOG=type;
    this-> DUREE_LOG= duree;
    this-> ADRESSE=adresse;
    this->PRIX_LOG=prix;
}

//getters
int logement::getID_LOG(){return ID_LOG;}
QString logement::getTYPELOG(){return TYPE_LOG;}
QString logement::getIDUREELOG(){return DUREE_LOG;}
QString logement::getADRESSELOG(){return ADRESSE;}
float logement::getPRIXLOG(){return  PRIX_LOG;}
QString logement::get_rech(){return rech;}
//setters
void logement::setID_LOG(int id) {this->ID_LOG=id;}
void logement::setTYPELOG(QString type){this-> TYPE_LOG=type;}
void logement::setIDUREELOG(QString duree){DUREE_LOG= duree;}
void logement::setADRESSELOG(QString adresse){this-> ADRESSE=adresse;}
void logement::setPRIXLOG(float prix){this-> PRIX_LOG=prix; }


//ajout d'un logement
void logement::ajouter_log(logement l){
    QSqlQuery query;
    QString id_string=QString::number(ID_LOG);
    QString id_string2=QString::number(PRIX_LOG);

             query.prepare("INSERT INTO LOGEMENT  (ID_LOG,TYPE_LOG,DUREE_LOG,PRIX_LOG,LIEU) "
                           "VALUES (:ID_LOG, :TYPE_LOG,:DUREE_LOG, :PRIX_LOG,:LIEU)");
            query.bindValue(":ID_LOG",id_string);
            query.bindValue(":TYPE_LOG", TYPE_LOG);
            query.bindValue(":DUREE_LOG",DUREE_LOG);
            query.bindValue(":PRIX_LOG",id_string2);
            query.bindValue(":LIEU", ADRESSE);


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

//suppression
void logement::supprimer_log(logement l){

    QString id_string=QString::number(ID_LOG);

    QString sQuery="DELETE FROM LOGEMENT WHERE ID_LOG='"+id_string+"'";

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

//modifier
void logement::modifier_log(logement l){
    QSqlQuery query;
        QString id_string=QString::number(ID_LOG);
        QString id_string2=QString::number(PRIX_LOG);

        query.prepare("UPDATE LOGEMENT SET TYPE_LOG=:TYPE_LOG ,DUREE_LOG =:DUREE_LOG,PRIX_LOG=:PRIX_LOG,LIEU=:ADRESSE "
         "WHERE ID_LOG= :ID_LOG");
        query.bindValue(":ID_LOG", id_string);
        query.bindValue(":TYPE_LOG", TYPE_LOG);
        query.bindValue(":DUREE_LOG",DUREE_LOG);
        query.bindValue(":PRIX_LOG", id_string2);
        query.bindValue(":ADRESSE", ADRESSE);


    if(query.exec())
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
//affichage
QSqlQueryModel * logement::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM LOGEMENT");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_LOG"));
      model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_LOG"));
      model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE_LOG"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_LOG"));
      model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));



       return model;

}

//tri prix
QSqlQueryModel * logement::triPRIX()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM LOGEMENT ORDER BY PRIX_LOG");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_LOG"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_LOG"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE_LOG"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_LOG"));
     model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));

       return model;



}

//triID
QSqlQueryModel * logement::triID()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM LOGEMENT ORDER BY ID_LOG");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_LOG"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_LOG"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE_LOG"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_LOG"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));

       return model;



}

//tritype
QSqlQueryModel * logement::triTYPE()
{
    QSqlQueryModel * model=new QSqlQueryModel();

    model->setQuery("SELECT * FROM LOGEMENT ORDER BY TYPE_LOG");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID_LOG"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TYPE_LOG"));
     model->setHeaderData(2,Qt::Horizontal,QObject::tr("DUREE_LOG"));
      model->setHeaderData(3,Qt::Horizontal,QObject::tr("PRIX_LOG"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("ADRESSE"));

       return model;

}

//chercher
QSqlQueryModel* logement::chercher_log(QString rech){
    QString sQuery="SELECT * FROM LOGEMENT WHERE ID_LOG LIKE '%"+rech+"%'OR TYPE_LOG LIKE '%"+rech+"%' OR DUREE_LOG LIKE '%"+rech+"%' OR PRIX_LOG LIKE '%"+rech+"%' OR LIEU LIKE '%"+rech+"%' ";

    QSqlQueryModel*model4=new QSqlQueryModel();

    QSqlQuery qry;

    qry.prepare(sQuery);

    qry.exec();
    model4->setQuery(qry);
    return model4;
}
int logement::calculer(int choix,int choix2)
{
    QSqlQuery query;
          query.prepare("SELECT * FROM LOGEMENT WHERE PRIX_LOG BETWEEN (:choix) AND (:choix2)");
          query.bindValue(":choix",choix);
          query.bindValue(":choix2",choix2);

          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
 }

          return total;
}
