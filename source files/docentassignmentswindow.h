#ifndef DOCENTASSIGNMENTSWINDOW_H
#define DOCENTASSIGNMENTSWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QMessageBox>
#include "createwindowdialog.h"
#include "sqlhandler.h"

namespace Ui {
class DocentAssignmentsWindow;
}

class DocentAssignmentsWindow : public QDialog
{
	Q_OBJECT

public:
	explicit DocentAssignmentsWindow(QWidget *parent = 0);
	~DocentAssignmentsWindow();


private slots:
	void on_changeButton_clicked();
	void on_addButton_clicked();
	void on_removeButton_clicked();
	void on_tableWidget_itemSelectionChanged();

private:
	Ui::DocentAssignmentsWindow *ui;
	CreateWindowDialog *cw;
	int row;
};

#endif // DOCENTASSIGNMENTSWINDOW_H
