#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWebView>
#include <QtNetwork>
#include <QNetworkProxyFactory>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:

	void on_b_submit_clicked();

	void on_b_compile_clicked();

	void on_b_terug_clicked();

private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
