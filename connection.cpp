#include "connection.h"

Connection::Connection() {}

bool Connection::createconnect() {
    bool test=false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A");
    db.setUserName("badis");
    db.setPassword("distex");
    if (db.open()) test=true;
    return test;
}

void Connection::closeConnection() {
    db.close();
}
