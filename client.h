#ifndef CLIENT_H
#define CLIENT_H
#include <QApplication>
#include"connection.h"
#include<QMessageBox>
#include<QString>
#include<qsqlquerymodel.h>
class client
{
    int cin,age,budget,pts;
    QString nom,prenom,phone,email,rech;
public:
    void set_cin(int );
    void set_nom(QString );
    void set_prenom(QString );
    void set_age(int );
    void set_email(QString );
    void set_phone(QString );
    void set_budget(int );
    void set_pts(int );
    int get_cin();
    QString get_nom();
    QString get_prenom();
    int get_age();
    QString get_email();
    QString get_phone();
    int get_budget();
     QString get_rech();
    void ajouter_client(client c);
    void supprimer_client(client c);
    void modifier_client(client c);
    void calcul(client c);
    int calculer1(int choix,int choix2);


    QSqlQueryModel* chercher_client(QString rech);
    QSqlQueryModel* afficher_client_trie_nom();
    QSqlQueryModel* afficher_client_trie_prenom();
    QSqlQueryModel* afficher_client_trie_age();
    QSqlQueryModel* afficher_client();
    client();
    client(int,QString,QString,int,QString,QString,int);

};

#endif // CLIENT_H
