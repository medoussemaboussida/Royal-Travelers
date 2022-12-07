#ifndef TRANSPORT_H
#define TRANSPORT_H
#include <QString>
#include <QSqlQueryModel>


class Transport
{
public:
    Transport();
    Transport(int,QString,float,int);
    int getid_tran();
    QString gettype();
    float getprix();
    int getnb_moy();

    void setid_tran(int);
    void settype(QString);
    void setprix(float);
    void setnb_moy(int);
    bool ajouter();
    void ModifierTransport(Transport);
    bool ArchiverTransport(int);
    bool InarchiverTransport(int);
    QSqlQueryModel* afficher();
    QSqlQueryModel* listearchive();
    void supprimer(Transport);
    QSqlQueryModel* rechercher(QString);
    QSqlQueryModel* TriCASC();
    QSqlQueryModel* TriCDESC();
    QSqlQueryModel* TriDASC();
    QSqlQueryModel* TriDDESC();
    QSqlQueryModel* TriEASC();
    QSqlQueryModel* TriEDESC();
    int calculer1(int choix,int choix2);



private:
    int id_tran;
    QString type;
    float prix;
    int nb_moy;
};
#endif // TRANSPORT_H
