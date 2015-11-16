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
	explicit StudentWindow(QWidget *parent = 0);
	~StudentWindow();

public slots:

private slots:
	void on_compileButton_clicked();
	void on_submitButton_clicked();
	void on_opslaanButton_clicked();
	void on_tableWidget_cellDoubleClicked(int row, int column);

private:
	Ui::StudentWindow *ui;
	QString opdrachtNummer;
	int opdrachtMaker;
};

#endif // STUDENTWINDOW_H
