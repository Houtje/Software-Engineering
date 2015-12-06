#include "logindialog.h"
#include "studentwindow.h"
#include "docentwindow.h"
#include <QApplication>

//Main function for the code. It opens the login window, and when the log in button is clicked
//returns here to login with the credentials to the right program (teacher or student side)
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LogInDialog login;
	int exitValue = 0;
	bool _continue = true;
	while(_continue) {
		if(login.exec() == QDialog::Accepted) {
			int accountID = 0;
			bool docent = false;
			login.getValues(accountID, docent);
			StudentWindow s(accountID);
			DocentWindow d;
			if(!docent) {
				s.show();
				exitValue = a.exec();
				_continue = s.keepGoing();
			} else {
				d.show();
				exitValue = a.exec();
				_continue = d.keepGoing();
			}

		} else {
			_continue = false;
			exitValue = 1;
		}
	}
	return exitValue;
}
