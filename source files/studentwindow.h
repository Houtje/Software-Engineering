#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QtNetwork>
#include <QNetworkProxyFactory>
#include "qrocheckbox.h"
#include <QLabel>

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

private slots:
	void on_compileButton_clicked();
	void on_submitButton_clicked();
	void on_opslaanButton_clicked();
	void on_tableWidget_cellDoubleClicked(int row, int column);

	void on_logOutButton_clicked();

private:
	Ui::StudentWindow *ui;
	QString opdrachtNummer;
	int ingelogde;
	bool goLogin;
};

#endif // STUDENTWINDOW_H
