#include "docentwindow.h"

DocentWindow::DocentWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::DocentWindow)
{
	ui->setupUi(this);

    QString string = ":/new/prefix1/plaatjes/poweroff.png";
    goLogin = false;
    sqlplayer = new SqlHandler();
    achieve = new AchievementHandler();
    QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);

    setWindowIcon(QIcon(string));
	ui->tableWidget->setHorizontalHeader(headerView);
	headerView->setSectionResizeMode(0, QHeaderView::Stretch);
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
	this->refresh();


	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
    timer->start(5000);
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
    message = "UPDATE `assignment_status` AS a, `accounts` AS b SET a.score = '"+score+"', a.submitted = 0 WHERE a.assID = "+opdrachtNaam+" AND b.username = '"+ opdrachtMaker + "' AND a.accID = b.accID";
	sqlplayer->alter(x);
    query = sqlplayer->select("SELECT `accID` FROM `accounts` WHERE `username` = '" + opdrachtMaker + "'");
    int accID = 0;
    if(query.next())
        accID = query.value(0).toInt();
    achieve->SubmitDocent(opdrachtNaam.toInt(), accID);
	ui->tableWidget->removeRow(opdrachtRij);

	ui->checkboxLayout->setChecked(false);
	ui->checkboxWerking->setChecked(false);
	ui->checkboxCompiler->setChecked(false);
	ui->checkboxOverig->setChecked(false);
	ui->opdrachtCode->setText("");
	ui->opdrachtText->setText("");
	ui->compileButton->setDisabled(true);
	ui->submitButton->setDisabled(true);
    ui->funnyButton->setDisabled(true);
}

void DocentWindow::on_tableWidget_cellDoubleClicked(int row)
{
	ui->compileButton->setDisabled(false);
	ui->submitButton->setDisabled(false);
    ui->funnyButton->setDisabled(false);

	opdrachtRij = row;
	QLabel *opdracht = (QLabel*) ui->tableWidget->cellWidget(row, 0);
	opdrachtNaam = opdracht->text();
	QStringList opdrachtList= opdrachtNaam.split(" - ");
	opdrachtNaam = opdrachtList[0];
	opdrachtMaker = opdrachtList[1];

    message = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
    query = sqlplayer->select(message);
    query.next();
    opdrachtNaam = query.value(0).toString();

    message = "SELECT `instructions` FROM `assignments` WHERE `assID` = " + opdrachtNaam ;
    query = sqlplayer->select(message);
    query.next();
    ui->opdrachtText->setText(query.value(0).toString());

    message = "SELECT a.solution FROM `assignment_status` AS a, `accounts` AS b WHERE a.assID = " + opdrachtNaam + " AND b.username = '"+ opdrachtMaker + "' AND a.accID = b.accID";
    query = sqlplayer->select(message);
    query.next();
    ui->opdrachtCode->setText(query.value(0).toString());
}

void DocentWindow::refresh() {
	ui->tableWidget->setRowCount(0);
	if(sqlplayer != NULL) {
        message = "SELECT c.naam, b.username FROM `assignment_status` AS a, `accounts` AS b, `assignments` AS c WHERE a.submitted = 1 AND a.accID = b.accID AND c.assID = a.assID";
        query = sqlplayer->select(message);
        while(query.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel((query.value(0).toString()) + " - " + (query.value(1).toString())));
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

void DocentWindow::on_funnyButton_clicked()
{
    message = "SELECT `accID` FROM `accounts` WHERE `username` = '" + opdrachtMaker + "'";
    query = sqlplayer->select(message);
    query.first();
    achieve->Prankster(query.value(0).toInt());

}
