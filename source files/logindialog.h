#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "sqlhandler.h"
#include "registerwindows.h"

namespace Ui {
	class LogInDialog;
}

class LogInDialog : public QDialog
{
	Q_OBJECT

public:
	explicit LogInDialog(QWidget *parent = 0);
	~LogInDialog();
	void getValues(int & accID, bool & doc);

private slots:
	void on_logInButton_clicked();

	void on_registerButton_clicked();

private:
	Ui::LogInDialog *ui;
	int accountID;
	bool docent;
};

#endif // DIALOG_H
