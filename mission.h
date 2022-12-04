#ifndef MISSION_H
#define MISSION_H
#include <QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QDate>
#include<QTableView>
#include<QMessageBox>
class mission
{
    int ID_Mission,ID_Log,ID_TRAN,CIN_C;
        QString TYPE_MISSION,DIRECTION,rech;
        QDate DATE_DEPART,DATE_RETOUR;
public:
        mission();
            mission(int,int,int,int,QDate,QDate,QString,QString);
            int getID_Mission();
            int getID_Log();
            int getID_Transportation();
            int getCIN_Client();
            int getID_Mission_a_supprimer();
            QDate getDATE_DEPART();
            QDate getDATE_RETOUR();
            QString getTYPE_MISSION();
            QString getdirection();
            QString get_rech();

            //setters
            void setID_Mission(int );
            void setID_Log(int);
            void setID_Transportation(int);
            void setCIN_Client(int);
            void setDATE_DEPART(QDate );
            void setDATE_RETOUR(QDate);
            void setTYPE_MISSION(QString);
            void setdirection(QString);

    void ajouter_mission(mission m);
    void supprimer_mission(mission m);
    void modifier_mission(mission m);
    int calculer_m(QString choix);

void ajouter_valid(int ID_Mission);
void supprimer_valid(int ID_Mission);

    QSqlQueryModel* chercher_mission(QString rech);
    QSqlQueryModel* afficher_mission_trie_direction();
    QSqlQueryModel* afficher_mission_trie_type();
    QSqlQueryModel* afficher_mission();
    QSqlQueryModel* afficher_historique();

};

#endif // MISSION_H
