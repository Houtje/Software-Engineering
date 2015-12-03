#ifndef CREATEWINDOWDIALOG_H
#define CREATEWINDOWDIALOG_H

#include <QDialog>
#include "ui_createwindowdialog.h"
#include "sqlhandler.h"

namespace Ui {
class CreateWindowDialog;
}

class CreateWindowDialog : public QDialog
{
	Q_OBJECT

public:
	explicit CreateWindowDialog(int assignment, QWidget *parent = 0);
	~CreateWindowDialog();

private slots:
	void on_createknop_clicked();
	void on_cancelknop_clicked();

private:
	Ui::CreateWindowDialog *ui;
	int assID;
    SqlHandler *sqlplayer;
    QString message;
    QSqlQuery query;

};


#endif // CREATEWINDOWDIALOG_H
