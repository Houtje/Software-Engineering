#include "logindialog.h"
#include "studentwindow.h"
#include "docentwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogInDialog login;
	if(login.exec() == QDialog::Accepted) {
		int accountID = 0;
		bool docent = false;
		login.getValues(accountID, docent);
		StudentWindow s(accountID);
		DocentWindow d;
		if(!docent) {
			s.show();
		} else {
			d.show();
		}
		return a.exec();

	} else {
		return 1;
	}
}
