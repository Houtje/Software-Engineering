#include "sqlhandler.h"

//inizitalize the sqlhandler.
SqlHandler::SqlHandler() {
}

//Connect to the database
//and sets its values to the servers address.
QSqlDatabase SqlHandler::connect(){
	QSqlDatabase db;
    db = QSqlDatabase::addDatabase("QMYSQL");
	db.setHostName("sql4.freemysqlhosting.net");
    db.setPort(3306);
	db.setDatabaseName("sql498674");
	db.setUserName("sql498674");
	db.setPassword("s1eVRTZplg");
	return db;
}

//the general function for a select statement to the database.
// this function gives back an query of results in the form
//of a table.
QSqlQuery SqlHandler::select(QString str){
	QSqlDatabase db = connect();
	QSqlQuery q;
    if(db.open()){
		//creating all the collumns
		//this is the actual query
		q.exec(str);
		db.close();
     }
    //this will give errors if the database cannot befound
	else{
		std::cout << "Error: " << db.lastError().text().toStdString().c_str() << std::endl;

	}
	return q;
}

//the general function for an alter statement to the database.
//the function returns nothing. It changes the content of the database.
void SqlHandler::alter(QString str ){
    QSqlDatabase db = connect();
    if(db.open()){
        QSqlQuery q;
        q.exec(str);
        q.first();
		db.close();
    }
	else{
		std::cout << "Error: " << std::endl;
    }
}
