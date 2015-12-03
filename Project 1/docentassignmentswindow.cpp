#include "docentassignmentswindow.h"
#include "ui_docentassignmentswindow.h"

//the DocentAssignmentsWindow has as purpose that it makes it possible
//for a docent to make a new, alter or delete an assignment.
DocentAssignmentsWindow::DocentAssignmentsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocentAssignmentsWindow)
{
	ui->setupUi(this);

    //Declaration
    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
    row = 0;
    QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);
    sqlplayer = new SqlHandler();


    setWindowIcon(QIcon(string));
	ui->tableWidget->setHorizontalHeader(headerView);
	headerView->setSectionResizeMode(0, QHeaderView::Stretch);

    message = "SELECT `naam` FROM `assignments` ORDER BY `assID` DESC";
    query = sqlplayer->select(message);
	while(q.next()) {
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(query.value(0).toString()));
	}

	QStringList strings = QStringList();
	strings.append("Naam");
	ui->tableWidget->setHorizontalHeaderLabels(strings);
	ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
}

DocentAssignmentsWindow::~DocentAssignmentsWindow()
{
	delete ui;
}

//if their is an assignment selected the changes that are made to the assignment
//are saved and send to the database.
void DocentAssignmentsWindow::on_changeButton_clicked()
{
	QModelIndexList dinges = ui->tableWidget->selectionModel()->selectedRows();
	if(dinges.length() != 0) {
		row = dinges.at(0).row();
		QLabel *label = (QLabel*) ui->tableWidget->cellWidget(row, 0);
        message = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + label->text() + "'";
        query = sqlplayer->select(message);
        query.next();
        int assignment = query.value(0).toInt();
		cw = new CreateWindowDialog(assignment);
		cw->exec();
		ui->tableWidget->setRowCount(0);
        message = "SELECT `naam` FROM `assignments` ORDER BY `assID` DESC";
        query = sqlplayer->select(message);
        while(query.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(query.value(0).toString()));
		}
		QStringList strings = QStringList();
		strings.append("Naam");
		ui->tableWidget->setHorizontalHeaderLabels(strings);
		ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
	} else {
		QMessageBox msgBox;
		msgBox.setText("Geen opdracht geselecteerd.");
		msgBox.exec();
	}
}

//this button makes a new window the createwindowdialog which is capable of making a new
//assignment for the students.
void DocentAssignmentsWindow::on_addButton_clicked()
{
	cw = new CreateWindowDialog(0, this);
	cw->exec();
	ui->tableWidget->setRowCount(0);
    message = "SELECT `naam` FROM `assignments` ORDER BY `assID` DESC";
    query = sqlplayer->select(message);
    while(query.next()) {
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(query.value(0).toString()));
	}
	QStringList strings = QStringList();
	strings.append("Naam");
	ui->tableWidget->setHorizontalHeaderLabels(strings);
	ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
}

//if their is an assignment selected the selected assignment is deleted from the database.
void DocentAssignmentsWindow::on_removeButton_clicked()
{
	QModelIndexList dinges = ui->tableWidget->selectionModel()->selectedRows();
	if(dinges.length() != 0) {
		row = dinges.at(0).row();
		QLabel *label = (QLabel*) ui->tableWidget->cellWidget(row, 0);
        message = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + label->text() + "'";
        query = sqlplayer->select(query);
        query.next();
        int assignment = query.value(0).toInt();
        message = "DELETE FROM `assignments` WHERE `assID` = " + QString::number(assignment) ;
        sqlplayer->alter(message);
        message = "DELETE FROM `assignment_status` WHERE `assID` = " + QString::number(assignment) ;
        sqlplayer->alter(message);
        ui->tableWidget->removeRow(row);
	}
}

void DocentAssignmentsWindow::on_tableWidget_itemSelectionChanged()
{
}
