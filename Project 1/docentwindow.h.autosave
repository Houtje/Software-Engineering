#ifndef DocentWindow_H
#define DocentWindow_H

#include <QMainWindow>
#include <QWebView>
#include <QtNetwork>
#include <QNetworkProxyFactory>
#include <QLabel>
#include "qrocheckbox.h"
#include "achievementhandler.h"
#include "docentassignmentswindow.h"
#include "ui_docentwindow.h"
#include "sqlhandler.h"


namespace Ui {
class DocentWindow;
}

class DocentWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit DocentWindow(QWidget *parent = 0);
	~DocentWindow();
	bool keepGoing();

public slots:
	void refresh();

private slots:
	void on_opdrachtBeheerButton_clicked();
	void on_compileButton_clicked();
	void on_submitButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row);

	void on_logOutButton_clicked();

    void on_funnyButton_clicked();

private:
	Ui::DocentWindow *ui;
	QString opdrachtNaam;
	QString opdrachtMaker;
    SqlHandler *sqlplayer;
    AchievementHandler *achieve;
    QString message;
    QSqlQuery query;
	int opdrachtRij;
	bool goLogin;
};

#endif // DocentWindow_H
