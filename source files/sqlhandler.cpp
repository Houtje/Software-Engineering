/*

//selectNW("accounts", "username", "password");
//selectOW("accounts", "username", "password", "`accID` = 1");
//selectMW("accounts", "username", "password", "`accID` = 1","`admin` = 1" );
//alterOW("accounts", "username", "1","`accID` = 1");
//alterMW("accounts", "username", "1","`accID` = 1","`admin` = 1");
*/
#include "sqlhandler.h"
#include "QDebug"
#include "iostream"



//Connect to the database
SqlHandler::SqlHandler() {

}

QSqlDatabase SqlHandler::connect(){
    //initizazing the variables of connecting to the database
	QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("SE Project");
    db.setUserName("root");
	db.setPassword("");
	return db;
}

//All the different nmbr of Where statemens Selects
//None Where statements
QSqlQuery SqlHandler::selectNW(QString table, QString column1, QString column2){
    QString str = "select `" + column1 + "`, `" + column2 + "` from `" + table;
	return select(str);
}

//One Where Statement
QSqlQuery SqlHandler::selectOW(QString table, QString column1, QString column2 , QString whereState1 ){
    QString str = "select `" + column1 + "`, `" + column2 + "` from `" + table + "` where " + whereState1 ;
	return select(str);
}

//Two Where Statements
QSqlQuery SqlHandler::selectMW(QString table, QString column1, QString column2 , QString whereState1 , QString whereState2){
    QString str = "select `" + column1 + "`, `" + column2 + "` from `" + table + "` where " + whereState1 + " and " + whereState2;
	return select(str);
}


//All the different nmbr of Where statemens Alter
//One Where Statement
void SqlHandler::alterOW(QString table ,QString column1 , QString waarde, QString whereState1 ){
    QString str = "UPDATE `"+ table + "SET `(" + column1 + "`) = (`" + waarde +"`) Where" + whereState1 ;
	alter(str);
}

//Two Where Statements
void SqlHandler::alterMW(QString table ,QString column1 , QString waarde, QString whereState1 , QString whereState2 ){
    QString str = "UPDATE `"+ table + "SET `(" + column1 + "`) = (`" + waarde +"`) Where" + whereState1 + "and" + whereState2;
    alter(str);
}

QSqlQuery SqlHandler::select(QString str){
    QSqlDatabase db = connect();
	QSqlQuery q;
    if(db.open()){
		//creating all the collumns
		//this is the actual query
        q.exec(str);
        QSqlRecord x = q.record();
        int y = x.count();
        //for each hit/row in the database he will give back a q as long as their is a new q.
		/*
		 * while(q.next()){
            //converting the row in to seperate items that will be pushed into the table
            for(int i = 0; i < y ; i++){
			   // q.value(i).toString();
                
            }
        }
		*/
     }
    //this will give errors if the database cannot befound
	else{
		std::cout << "Error: " << std::endl;
    }
	return q;
}
/*
void SqlHandler::insert(QString table ,QString column1 , QString Waarde, QString whereState1 , QString whereState2 ){
    //initizazing the variables of connecting to the database
    QSqlDatabase db = Connect();

    if(db.open()){
        QSqlQuery q;
        QString str = "INSERT INTO '"+ table + "'(" + column1 + "') VALUES ('" + Waarde +"') Where" + whereState1 + "and" + whereState2;
        q.exec(str);
        q.first();
    }
    else{
        std::cout << "Error: " << std::endl;
    }
}
*/

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
