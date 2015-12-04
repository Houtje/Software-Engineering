#ifndef SqlHandler_H
#define SqlHandler_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include "QDebug"
#include "iostream"

class SqlHandler
{
public:
	SqlHandler();
	~SqlHandler();
	QSqlDatabase connect();
    //The Selects
	QSqlQuery selectNW(QString table, QString column1, QString column2);
	QSqlQuery selectOW(QString table, QString column1, QString column2 , QString whereState1 );
	QSqlQuery selectMW(QString table, QString column1, QString column2 , QString whereState1 , QString whereState2);

	QSqlQuery select(QString str);

    //The Inserts
    //void insert();

    //The Alters
    void alterOW(QString table ,QString column1 , QString waarde, QString whereState1);
    void alterMW(QString table ,QString column1 , QString waarde, QString whereState1 , QString whereState2 );

    void alter(QString str );


private:
    QString str;
    QSqlDatabase db;
};

#endif // SqlHandler_H
