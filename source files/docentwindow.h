#ifndef DocentWindow_H
#define DocentWindow_H

#include <QMainWindow>
#include <QWebView>
#include <QtNetwork>
#include <QNetworkProxyFactory>
#include <QLabel>
#include "qrocheckbox.h"

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

private slots:
	void on_opdrachtBeheerButton_clicked();
	void on_compileButton_clicked();
	void on_submitButton_clicked();
	void on_tableWidget_cellDoubleClicked(int row, int column);

	void on_logOutButton_clicked();

private:
	Ui::DocentWindow *ui;
	QString opdrachtNummer;
	QString opdrachtMaker;
	int opdrachtRij;
	bool goLogin;
};

#endif // DocentWindow_H
