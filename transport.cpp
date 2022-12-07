#include "transport.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include<QMessageBox>
#include<QString>
Transport::Transport()
{
    id_tran=0; type=""; prix=0; nb_moy=0;
}


Transport::Transport(int id_tran, QString type,float prix,int nb_moy){
    this->id_tran=id_tran ; this->type=type ;  this->prix=prix ; this->nb_moy=nb_moy ;
}


int Transport::getid_tran(){return id_tran;}
QString Transport::gettype(){return type;}
float Transport::getprix(){return prix;}
int Transport::getnb_moy(){return nb_moy;}

void Transport::setid_tran(int id_tran){this->id_tran=id_tran ;}
void Transport::settype(QString type){this->type=type ;}
void Transport::setprix(float prix){this->prix=prix ;}
void Transport::setnb_moy(int nb_moy){this->nb_moy=nb_moy ;}


bool Transport::ajouter(){

    QSqlQuery query;
    QString id_string= QString::number(id_tran);
    QString prix_string= QString::number(prix);
    QString nb_moy_string= QString::number(nb_moy);

         query.prepare("INSERT INTO MOYEN_DE_TRANSPORT (ID_TRAN,TYPE,PRIX,NB_MOY,ETAT) "
                       "VALUES (:id_tran, :type, :prix, :nb_moy,1)");
         query.bindValue(":id_tran", id_string);
         query.bindValue(":type", type);
         query.bindValue(":prix", prix_string);
         query.bindValue(":nb_moy", nb_moy_string);

         return query.exec();
}


void Transport::supprimer(Transport T){
    QSqlQuery query;
        QString res=QString::number(id_tran);
         query.prepare("DELETE FROM MOYEN_DE_TRANSPORT WHERE ID_TRAN='"+res+"'");
         query.bindValue(":id_tran",res);

         if(query.exec())
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
bool Transport::ArchiverTransport(int id_tran)
{
       QSqlQuery query;
       QString res=QString::number(id_tran);

       query.prepare(" UPDATE MOYEN_DE_TRANSPORT SET ETAT=0 WHERE ID_TRAN = :id_tran");
                          query.bindValue(":id_tran", res);
                         return query.exec();

}





QSqlQueryModel* Transport::afficher(){
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_transport"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("temps restant"));


    return model;
}
QSqlQueryModel* Transport::listearchive(){
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=0");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_transport"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));

    return model;
}



void Transport::ModifierTransport(Transport T)
{
       QSqlQuery query;
       QString id_tran_string=QString::number(id_tran);
       QString prix_string= QString::number(prix);
       QString nb_moy_string= QString::number(nb_moy);

       query.prepare(" UPDATE MOYEN_DE_TRANSPORT SET TYPE = :type ,PRIX = :prix, NB_MOY = :nb_moy WHERE  ID_TRAN = :id_tran");
                          query.bindValue(":id_tran", id_tran_string);
                          query.bindValue(":type", type);
                          query.bindValue(":prix", prix_string);
                          query.bindValue(":nb_moy", nb_moy_string);

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


QSqlQueryModel * Transport::rechercher(QString a)
{

    QSqlQueryModel * model=new QSqlQueryModel();
        model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ID_TRAN LIKE'%"+a+"%' OR TYPE LIKE '%"+a+"%' OR  PRIX LIKE '%"+a+"%' OR  NB_MOY LIKE '%"+a+"%' and ETAT=1 ");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("id_transport"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));

        return model;

}



QSqlQueryModel* Transport::TriCASC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1 ORDER BY TYPE ASC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
  return  model;
}
QSqlQueryModel* Transport::TriCDESC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1 ORDER BY TYPE DESC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
  return  model;
}

QSqlQueryModel* Transport::TriDASC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1 ORDER BY PRIX ASC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
  return  model;
}
QSqlQueryModel* Transport::TriDDESC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1 ORDER BY PRIX DESC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
  return  model;
}


QSqlQueryModel* Transport::TriEASC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1 ORDER BY NB_MOY ASC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
  return  model;
}

QSqlQueryModel* Transport::TriEDESC()
{
  QSqlQueryModel* model=new QSqlQueryModel();
   model->setQuery("SELECT ID_TRAN,TYPE,PRIX,NB_MOY FROM MOYEN_DE_TRANSPORT WHERE ETAT=1 ORDER BY NB_MOY DESC");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("Id"));
   model->setHeaderData(1, Qt::Horizontal, QObject::tr("type"));
   model->setHeaderData(2, Qt::Horizontal, QObject::tr("prix"));
   model->setHeaderData(3, Qt::Horizontal, QObject::tr("capacité"));
  return  model;
}
bool Transport::InarchiverTransport(int id_tran)
{
    QSqlQuery query;
    QString ret=QString::number(id_tran);

    query.prepare(" UPDATE MOYEN_DE_TRANSPORT SET ETAT=1 WHERE ID_TRAN = :id_tran");
                       query.bindValue(":id_tran", ret);
                      return query.exec();


}
//calcul stat
int Transport::calculer1(int choix,int choix2)
{
    QSqlQuery query;
          query.prepare("SELECT * FROM MOYEN_DE_TRANSPORT WHERE NB_MOY BETWEEN (:choix) AND (:choix2) AND ETAT=1");
                        query.bindValue(":choix",choix);
                        query.bindValue(":choix2",choix2);


          query.exec();
          int total = 0;
          while (query.next()) {
            total++;
 }

          return total;
}

