#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QString>
#include <QSqlQueryModel>
class Employee
{
    int CIN;
    QString Nom,Prenom,Phone,Email,Mdp,Function,Recherche;
public:
    Employee();
    Employee(int,QString,QString,QString,QString,QString,QString);
        int getCIN();
        QString getNom();
        QString getPrenom();
        QString getEmail();
        QString getPhone();
        QString getFunction();
        QString getMdp();
        QString getRecherche();
        void setCIN(int);
        void setNom(QString);
        void setPrenom(QString);
        void setEmail(QString);
        void setPhone(QString);
        void setFunction(QString);
        void setMdp(QString);
        bool ajouter();
        QSqlQueryModel* afficher();
        bool supprimer(int);
        bool modifier_Employee();
        QSqlQueryModel* afficher_Employee_trie_Nom();
        QSqlQueryModel* afficher_Employee_trie_prenom();
        QSqlQueryModel* afficher_Employee_trie_age();
        QSqlQueryModel* chercher_Employee(QString Re);
        int Calcul(QString C1);


};
#endif // EMPLOYEE_H
