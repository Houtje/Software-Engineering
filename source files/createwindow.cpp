#include "createwindow.h"
#include "sqlhandler.h"
#include "ui_createwindow.h"

CreateWindow::CreateWindow(int assignment, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateWindow)
{
    ui->setupUi(this);
	assID = assignment;
	if(assID) {
		SqlHandler *sqlplayer = new SqlHandler();
		QString assignmentQuery = "SELECT `naam`,`instructions`,`video`,`skeletcode` FROM `assignments` WHERE assID = " + QString::number(assID);
		QSqlQuery assignmentInfo = sqlplayer->select(assignmentQuery);
		if(assignmentInfo.next()){
			setWindowTitle("Opdracht bewerken");
			ui->createknop->setText("Verander");
			ui->opdrachtnaam->setText(assignmentInfo.value(0).toString());
			ui->beschrijving->setText(assignmentInfo.value(1).toString());
			ui->ytlink->setText(assignmentInfo.value(2).toString());
			ui->skeletcode->setText(assignmentInfo.value(3).toString());
		}
	}

}

CreateWindow::~CreateWindow()
{
    delete ui;
}

void CreateWindow::on_createknop_clicked()
{
    SqlHandler *sqlplayer = new SqlHandler();
	if(assID) {
		QString alter = "UPDATE `assignments` SET `naam` = '" + ui->opdrachtnaam->toPlainText() + "', `instructions` = '" + ui->beschrijving->toPlainText() + "', `video` = '" + ui->ytlink->toPlainText() + "', `skeletcode` = '" + ui->skeletcode->toPlainText() + "' WHERE `assID` = " + QString::number(assID);
		sqlplayer->alter(alter);
	} else {
		QString alter = "INSERT INTO Assignments (assID, naam, instructions, video, skeletcode) VALUES ('0','" + ui->opdrachtnaam->toPlainText() + "','" + ui->beschrijving->toPlainText() + "','" + ui->ytlink->toPlainText() + "','" + ui->skeletcode->toPlainText() + "')";
		sqlplayer->alter(alter);

		alter = "INSERT INTO `assignment_status`(`assID`, `accID`, `solution`) SELECT MAX(a.assID), b.accID, (SELECT `skeletcode` FROM `assignments` WHERE `assID` = (SELECT MAX(`assID`) FROM `assignments`)) \
				FROM `assignments` as a \
				JOIN `accounts` as b \
				WHERE b.admin = 0 \
				GROUP BY b.accID";
		sqlplayer->alter(alter);

	}
    this->close();
}

void CreateWindow::on_cancelknop_clicked()
{
    this->close();
}

