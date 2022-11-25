#include "connection.h"
//Test Git
Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("projet");
db.setUserName("oussema");//inserer nom de l'utilisateur
db.setPassword("esprit38");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
