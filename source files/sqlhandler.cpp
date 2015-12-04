#include "sqlhandler.h"

//inizitalize the sqlhandler.
SqlHandler::SqlHandler() {
}

//Connect to the database
//and sets its values to the servers address.
QSqlDatabase SqlHandler::connect(){
    //initizazing the variables of connecting to the database
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("SE Project");
    db.setUserName("root");
	db.setPassword("");
	return db;
}

//the general function for an select statement to the database.
//general this function gives back an query of results in the form
//of a table.
QSqlQuery SqlHandler::select(QString str){
    QSqlDatabase db = connect();
    if(db.open()){
        //creating all the collumns
        QSqlQuery q;
		//this is the actual query
        q.exec(str);
		return q;
     }
    //this will give errors if the database cannot befound
	else{
		std::cout << "Error: " << std::endl;
    }
}

//the general function for an alter statement to the database.
//the gernal function giving no result back. Only makes changes in
//the database.
void SqlHandler::alter(QString str ){
    QSqlDatabase db = connect();
    if(db.open()){
        QSqlQuery q;
        q.exec(str);
        q.first();
    }
	else{
		std::cout << "Error: " << std::endl;
    }
}
