#include "sqlhandler.h"


//Connect to the database
SqlHandler::SqlHandler() {
}

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
