#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QtNetwork>
#include <QNetworkProxyFactory>
#include <QLabel>
#include <QMessageBox>
#include "qrocheckbox.h"

namespace Ui {
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
	void on_tableWidget_cellDoubleClicked(int row, int column);
	void on_logOutButton_clicked();
	void on_resetButton_clicked();

private:
	Ui::StudentWindow *ui;
	QString opdrachtNaam;
	int ingelogde;
	bool goLogin;
};

#endif // STUDENTWINDOW_H
