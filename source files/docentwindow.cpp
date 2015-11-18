#include "docentwindow.h"
#include "ui_DocentWindow.h"
#include "sqlhandler.h"
#include "createwindow.h"

DocentWindow::DocentWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::DocentWindow)
{
	ui->setupUi(this);

	QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);
	ui->tableWidget->setHorizontalHeader(headerView);
	headerView->setSectionResizeMode(0, QHeaderView::Stretch);
	//ui->tableWidget->setColumnWidth(0, ui->tableWidget->width() - 88);
	//ui->assignmentList->setStyleSheet( "QListWidget::item { border: 1px solid black; } " );
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
	SqlHandler *sqlplayer = new SqlHandler();
	if(sqlplayer != NULL) {
		QSqlQuery q = sqlplayer->select("SELECT a.assID, b.username FROM `assignment_status` AS a, `accounts` AS b WHERE a.submitted = 1 AND a.accID = b.accID ORDER BY a.timestamp");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel("Opdracht " + QString::number(q.value(0).toInt()) + " - " + (q.value(1).toString())));
		}
		QStringList headers = QStringList();
		headers.append(QString("Opdracht - Naam Student"));
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		ui->tableWidget->horizontalHeader()->setVisible(true);
	}
}

DocentWindow::~DocentWindow()
{
	delete ui;
}

void DocentWindow::on_opdrachtBeheerButton_clicked()
{
    CreateWindow* w = new CreateWindow();
    w->show();
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
	QString x = "UPDATE `assignment_status` AS a, `accounts` AS b SET a.score = '"+score+"', a.submitted = 0 WHERE a.assID = "+opdrachtNummer+" AND b.username = '"+ opdrachtMaker + "' AND a.accID = b.accID";
	qDebug(x.toStdString().c_str());
	SqlHandler *sqlplayer = new SqlHandler();
	sqlplayer->alter(x);
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
	opdrachtNummer = opdracht->text().mid(9, opdracht->text().length()-9);
	QStringList opdrachtList= opdrachtNummer.split(" - ");
	opdrachtNummer = opdrachtList[0];
	opdrachtMaker = opdrachtList[1];

	QString x = "SELECT `instructions` FROM `assignments` WHERE `assID` = ";
	QString y = "SELECT a.solution FROM `assignment_status` AS a, `accounts` AS b WHERE a.assID = " + opdrachtNummer + " AND b.username = '"+ opdrachtMaker + "' AND a.accID = b.accID";
	SqlHandler *sqlplayer = new SqlHandler();
	QSqlQuery q = sqlplayer->select(x + opdrachtNummer);
	q.next();
	ui->opdrachtText->setText(q.value(0).toString());

	QSqlQuery m = sqlplayer->select(y);
	m.next();
	ui->opdrachtCode->setText(m.value(0).toString());
}
