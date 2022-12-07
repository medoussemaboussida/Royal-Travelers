#ifndef LOGEMENT_H
#define LOGEMENT_H
#include <QApplication>
#include<QMessageBox>
#include<QString>
#include<qsqlquerymodel.h>
#include<QTableView>
#include<QSqlQuery>
class HOTEL
{
public:
    int NOMBRE_ETOIL;
    void rechercheHOTEEL(QTableView * table, QString rech1);
    QSqlQueryModel * afficherHOTEL();

};

class logement
{
public:
    //Constructors
    logement();
    logement(int,QString,QString,QString,float);
    int getID_LOG();
    QString getTYPELOG();
    QString getIDUREELOG();
    float getPRIXLOG();
    QString getADRESSELOG();
 QString get_rech();

    //setters
    void setID_LOG(int );
    void setTYPELOG(QString);
    void setPRIXLOG(float);
    void setADRESSELOG(QString);
    void setIDUREELOG(QString );
//methods
    void ajouter_log(logement l);
    QSqlQueryModel * afficher();
    void supprimer_log(logement l);
    void modifier_log(logement l);
     QSqlQueryModel * triPRIX();
     QSqlQueryModel * triID();
     QSqlQueryModel * triTYPE();
QSqlQueryModel* chercher_log(QString );
int calculer(int choix,int choix2);
     QSqlQueryModel * triPRIXHOTEL();


public:
    int ID_LOG;
    QString TYPE_LOG,DUREE_LOG,ADRESSE,rech;
    float PRIX_LOG;;

};


#endif // LOGEMENT_H
