#include "registerwindows.h"
#include "ui_registerwindows.h"

//the registerwindow where a new student account can be made.
RegisterWindows::RegisterWindows(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegisterWindows)
{
	ui->setupUi(this);
    QString string = ":/new/prefix1/plaatjes/icon.png";
    sqlplayer = new SqlHandler();

    setWindowIcon(QIcon(string));
}

RegisterWindows::~RegisterWindows()
{
	delete ui;
}

//the confirming button to make a new student account.
void RegisterWindows::on_pushButton_clicked()
{
	QString password = ui->passwordLine->text();
	if(!password.compare(ui->password2Line->text())) {
		if(password.compare("")) {
			QString username = ui->usernameLine->text();
			QStringList namen = username.split(" ");
			if(namen.length() == 2) {
				message = "INSERT INTO `accounts`(accID, username, password, admin) VALUES ('0','" + username + "','" + password + "','0')";
				sqlplayer->alter(message);
				qDebug(message.toStdString().c_str());
				message = "INSERT INTO `assignment_status`(`assID`, `accID`, `solution`) SELECT a.assID, MAX(b.accID), a.skeletcode FROM `assignments` as a JOIN `accounts` as b GROUP BY a.assID";
				sqlplayer->alter(message);
				qDebug(message.toStdString().c_str());
				this->close();
			} else {
				ui->errorLabel->setText("Foute naam");
			}
		} else {
			ui->errorLabel->setText("Geen wachtwoord");
		}
	} else {
		ui->errorLabel->setText("Wachtwoorden ongelijk");
	}
}
