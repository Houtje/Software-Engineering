#include "logindialog.h"

//The login screen. This is the start up screen where we can log in or create a new account for a student.
//we can login to a student side account and a docent side account depending on the login credentials.
LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
	ui(new Ui::LogInDialog)
{
	ui->setupUi(this);
    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
    setWindowIcon(QIcon(string));
    sqlplayer = new SqlHandler();
}

LogInDialog::~LogInDialog()
{
	delete ui;
}

//The button that makes the login happen depending on what is entered in the name and password field.
//It opens de docentwindow when a user logs in with a teachers account and opens the student window
//when the user logs in with a student account.
void LogInDialog::on_logInButton_clicked()
{
	ui->NameTextBox->setFocus();
	ui->ErrorLabel->setText("");
	QString name = ui->NameTextBox->text();
	QString pass = ui->PassTextBox->text();

    message= "SELECT `accID`, `admin` FROM `accounts` WHERE `username` = '" + name + "' AND `password` = '" + pass + "'";
    query = sqlplayer->select(message);
    if(query.next()) {
        accountID = query.value(0).toInt();
        docent = query.value(1).toInt();
		ui->NameTextBox->setText("");
		ui->PassTextBox->setText("");
		QDialog::accept();
	} else {
		ui->ErrorLabel->setText("Gebruikersnaam/wachtwoord combinatie bestaat niet");
	}
}

//retrieving the account of the user that wants to log in.
void LogInDialog::getValues(int & accID, bool & doc) {
	accID = accountID;
	doc = docent;
}

//the button that takes the user to the registerwindow.
void LogInDialog::on_registerButton_clicked()
{
	RegisterWindows *rw = new RegisterWindows();
	rw->exec();
}
