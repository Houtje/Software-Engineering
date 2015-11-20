#include "registerwindows.h"
#include "ui_registerwindows.h"

RegisterWindows::RegisterWindows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWindows)
{
	ui->setupUi(this);
}

RegisterWindows::~RegisterWindows()
{
	delete ui;
}

void RegisterWindows::on_pushButton_clicked()
{
	QString password = ui->passwordLine->text();
	if(!password.compare(ui->password2Line->text())) {
		QString username = ui->usernameLine->text();
		QStringList namen = username.split(" ");
		if(namen.length() == 2) {
			SqlHandler *sqlplayer = new SqlHandler();
			QString alter = "INSERT INTO Accounts (accID, username, password, admin) VALUES ('0','" + username + "','" + password + "','0')";
			qDebug(alter.toStdString().c_str());
			sqlplayer->alter(alter);
			alter = "INSERT INTO `assignment_status`(`assID`, `accID`, `solution`) SELECT a.assID, MAX(b.accID), a.skeletcode FROM `assignments` as a JOIN `accounts` as b GROUP BY a.assID";
			sqlplayer->alter(alter);
			this->close();
		} else {
			ui->errorLabel->setText("Foute naam");
		}
	} else {
		ui->errorLabel->setText("Wachtwoorden ongelijk");
	}
}
