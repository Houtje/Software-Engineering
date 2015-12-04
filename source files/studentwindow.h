#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QtNetwork>
#include <QNetworkProxyFactory>
#include <QLabel>
#include <QMessageBox>
#include "qrocheckbox.h"
#include "sqlhandler.h"
#include "form.h"
#include "achievementlist.h"
#include "horizontaldingie.h"
#include "achievementhandler.h"
#include "ui_studentwindow.h"
#include "QDebug"

namespace Ui {

struct AchievementInfo {
	QPixmap image;
	QString name;
	QString info;
	QString score;
};

class StudentWindow;
}

class StudentWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit StudentWindow(int accID, QWidget *parent = 0);
	~StudentWindow();
	bool keepGoing();

public slots:
	void refresh();

private slots:
	void on_compileButton_clicked();
	void on_submitButton_clicked();
	void on_opslaanButton_clicked();
    void on_tableWidget_cellDoubleClicked(int row);
	void on_logOutButton_clicked();
	void on_resetButton_clicked();
    void on_achievementList_clicked();
	void on_achievementList_clickie();

private:
	Ui::StudentWindow *ui;
	Ui::AchievementInfo *achieveList;
	int allAchievementListSize;
	int lastAchievement;
	QString opdrachtNaam;
	int ingelogde;
	bool goLogin;
    AchievementList *achieving;
    QHeaderView *headerView;
    SqlHandler *sqlplayer;
    QString message;
    QSqlQuery query;
    AchievementHandler * achieve;
};

#endif // STUDENTWINDOW_H
