#include "docentwindow.h"
#include "docentassignmentswindow.h"
#include "ui_docentwindow.h"
#include "sqlhandler.h"

DocentWindow::DocentWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::DocentWindow)
{
	ui->setupUi(this);
	goLogin = false;
	QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);
	ui->tableWidget->setHorizontalHeader(headerView);
	headerView->setSectionResizeMode(0, QHeaderView::Stretch);
	//ui->tableWidget->setColumnWidth(0, ui->tableWidget->width() - 88);
	//ui->assignmentList->setStyleSheet( "QListWidget::item { border: 1px solid black; } " );
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
	this->refresh();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
	timer->start(15000);
}

DocentWindow::~DocentWindow()
{
	delete ui;
}

void DocentWindow::on_opdrachtBeheerButton_clicked()
{
	DocentAssignmentsWindow* w = new DocentAssignmentsWindow();
	w->exec();
	delete w;
	w = NULL;
}

void DocentWindow::on_compileButton_clicked()
{

}

void DocentWindow::on_submitButton_clicked()
{
	bool layout = ui->checkboxLayout->isChecked();
	bool werking = ui->checkboxWerking->isChecked();
	bool compileren = ui->checkboxCompiler->isChecked();
	bool overig = ui->checkboxOverig->isChecked();

	QString score = QString::number(layout) + QString::number(werking) + QString::number(compileren) + QString::number(overig);
	QString x = "UPDATE `assignment_status` AS a, `accounts` AS b SET a.score = '"+score+"', a.submitted = 0 WHERE a.assID = "+opdrachtNaam+" AND b.username = '"+ opdrachtMaker + "' AND a.accID = b.accID";
	qDebug(x.toStdString().c_str());
	SqlHandler *sqlplayer = new SqlHandler();
	sqlplayer->alter(x);
	QSqlQuery q = sqlplayer->select("SELECT `accID` FROM `accounts` WHERE `username` = '" + opdrachtMaker + "'");
	int accid = 0;
	if(q.next())
		accid = q.value(0).toInt();
	AchievementHandler *achieve = new AchievementHandler();
	achieve->SubmitDocent(opdrachtNaam.toInt(), accid);
	ui->tableWidget->removeRow(opdrachtRij);

	ui->checkboxLayout->setChecked(false);
	ui->checkboxWerking->setChecked(false);
	ui->checkboxCompiler->setChecked(false);
	ui->checkboxOverig->setChecked(false);
	ui->opdrachtCode->setText("");
	ui->opdrachtText->setText("");
	ui->compileButton->setDisabled(true);
	ui->submitButton->setDisabled(true);
}

void DocentWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
	ui->compileButton->setDisabled(false);
	ui->submitButton->setDisabled(false);

	opdrachtRij = row;
	QLabel *opdracht = (QLabel*) ui->tableWidget->cellWidget(row, 0);
	opdrachtNaam = opdracht->text();
	QStringList opdrachtList= opdrachtNaam.split(" - ");
	opdrachtNaam = opdrachtList[0];
	opdrachtMaker = opdrachtList[1];

	SqlHandler *sqlplayer = new SqlHandler();
	QString namegetter = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
	QSqlQuery q = sqlplayer->select(namegetter);
	q.next();
	QString nummertje = q.value(0).toString();
	opdrachtNaam = nummertje;

	QString x = "SELECT `instructions` FROM `assignments` WHERE `assID` = " + nummertje ;
	qDebug(x.toStdString().c_str());
	q = sqlplayer->select(x);
	QString y = "SELECT a.solution FROM `assignment_status` AS a, `accounts` AS b WHERE a.assID = " + nummertje + " AND b.username = '"+ opdrachtMaker + "' AND a.accID = b.accID";
	q.next();
	ui->opdrachtText->setText(q.value(0).toString());

	QSqlQuery m = sqlplayer->select(y);
	m.next();
	ui->opdrachtCode->setText(m.value(0).toString());
}

void DocentWindow::refresh() {
	ui->tableWidget->setRowCount(0);
	SqlHandler *sqlplayer = new SqlHandler();
	if(sqlplayer != NULL) {
		QString terror = "SELECT c.naam, b.username FROM `assignment_status` AS a, `accounts` AS b, `assignments` AS c WHERE a.submitted = 1 AND a.accID = b.accID AND c.assID = a.assID";
		QSqlQuery q = sqlplayer->select(terror);
		qDebug(terror.toStdString().c_str());
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel((q.value(0).toString()) + " - " + (q.value(1).toString())));
		}
		QStringList headers = QStringList();
		headers.append(QString("Opdracht - Naam Student"));
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		ui->tableWidget->horizontalHeader()->setVisible(true);
ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
	}
}

void DocentWindow::on_logOutButton_clicked()
{
	goLogin = true;
	this->close();
}


bool DocentWindow::keepGoing() {
	bool tempLogin = goLogin;
	goLogin = false;
	return tempLogin;
}
