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
	void on_ietsButton_clicked();

	void on_compileButton_clicked();

	void on_submitKnop_clicked();

private:
	Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
