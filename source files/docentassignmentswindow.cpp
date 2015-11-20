#include "docentassignmentswindow.h"
#include "ui_docentassignmentswindow.h"

DocentAssignmentsWindow::DocentAssignmentsWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DocentAssignmentsWindow)
{
	ui->setupUi(this);
	row = 0;
	QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);
	ui->tableWidget->setHorizontalHeader(headerView);
	headerView->setSectionResizeMode(0, QHeaderView::Stretch);
	SqlHandler *sqlplayer = new SqlHandler();
	QSqlQuery q = sqlplayer->select("SELECT `naam` FROM `assignments` ORDER BY `assID` DESC");
	while(q.next()) {
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
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

void DocentAssignmentsWindow::on_changeButton_clicked()
{
	QModelIndexList dinges = ui->tableWidget->selectionModel()->selectedRows();
	if(dinges.length() != 0) {
		row = dinges.at(0).row();
		QLabel *label = (QLabel*) ui->tableWidget->cellWidget(row, 0);
		SqlHandler *sqlplayer = new SqlHandler();
		QString query = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + label->text() + "'";
		QSqlQuery q = sqlplayer->select(query);
		qDebug(query.toStdString().c_str());
		q.next();
		int assignment = q.value(0).toInt();
		cw = new CreateWindowDialog(assignment);
		cw->exec();
		ui->tableWidget->setRowCount(0);
		q = sqlplayer->select("SELECT `naam` FROM `assignments` ORDER BY `assID` DESC");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
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

void DocentAssignmentsWindow::on_addButton_clicked()
{
	cw = new CreateWindowDialog(0, this);
	cw->exec();
	ui->tableWidget->setRowCount(0);
	SqlHandler *sqlplayer = new SqlHandler();
	QSqlQuery q = sqlplayer->select("SELECT `naam` FROM `assignments` ORDER BY `assID` DESC");
	while(q.next()) {
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
	}
	QStringList strings = QStringList();
	strings.append("Naam");
	ui->tableWidget->setHorizontalHeaderLabels(strings);
	ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
}

void DocentAssignmentsWindow::on_removeButton_clicked()
{
	QModelIndexList dinges = ui->tableWidget->selectionModel()->selectedRows();
	if(dinges.length() != 0) {
		row = dinges.at(0).row();
		QLabel *label = (QLabel*) ui->tableWidget->cellWidget(row, 0);
		SqlHandler *sqlplayer = new SqlHandler();
		QString query = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + label->text() + "'";
		QSqlQuery q = sqlplayer->select(query);
		qDebug(query.toStdString().c_str());
		q.next();
		int assignment = q.value(0).toInt();
		query = "DELETE FROM `assignments` WHERE `assID` = " + QString::number(assignment) ;
		sqlplayer->alter(query);
		query = "DELETE FROM `assignment_status` WHERE `assID` = " + QString::number(assignment) ;
		sqlplayer->alter(query);
		qDebug(query.toStdString().c_str());
		qDebug(QString::number(row).toStdString().c_str());
		ui->tableWidget->removeRow(row);
		qDebug(QString::number(row).toStdString().c_str());
	}
}

void DocentAssignmentsWindow::on_tableWidget_itemSelectionChanged()
{
}
