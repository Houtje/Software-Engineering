#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>

LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::LogInDialog)
{
	ui->setupUi(this);
}

LogInDialog::~LogInDialog()
{
	delete ui;
}


void LogInDialog::on_logInButton_clicked()
{
	QString name = ui->NameTextBox->text();
	QString pass = ui->PassTextBox->text();

	SqlHandler *sqlPlayer = new SqlHandler();
	QString x = "SELECT `accID`, `admin` FROM `accounts` WHERE `username` = '" + name + "' AND `password` = '" + pass + "'";
	QSqlQuery q = sqlPlayer->select(x);
	qDebug(x.toStdString().c_str());
	if(q.next()) {
		accountID = q.value(0).toInt();
		docent = q.value(1).toInt();
		ui->NameTextBox->setText("");
		ui->PassTextBox->setText("");
		QDialog::accept();
	} else {
		ui->ErrorLabel->setText("Gebruikersnaam/wachtwoord combinatie bestaat niet");
	}
}

void LogInDialog::getValues(int & accID, bool & doc) {
	accID = accountID;
	doc = docent;
}

void LogInDialog::on_registerButton_clicked()
{
	RegisterWindows *rw = new RegisterWindows();
	rw->exec();
}
