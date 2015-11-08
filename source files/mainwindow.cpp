#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <fstream>
#include <sstream>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_b_terug_clicked()
{

}

void MainWindow::on_b_submit_clicked()
{

	ui->l_opdrachttitel->setText("hoho");
	QString hlep = ui->t_code->toPlainText();
	//help kan gebruikt worden om te submitten
}

void MainWindow::on_b_compile_clicked()
{
	/*QFile Compile("c.cc");
	Compile.open(QIODevice::WriteOnly);
	QDataStream out(&Compile);
	out << QString(ui->t_code->toPlainText());
	system("g++ -o test c");*/
}
