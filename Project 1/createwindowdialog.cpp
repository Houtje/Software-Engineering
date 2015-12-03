#include "createwindowdialog.h"
#include "ui_createwindowdialog.h"
#include "sqlhandler.h"

CreateWindowDialog::CreateWindowDialog(int assignment, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateWindowDialog)
{
	ui->setupUi(this);

    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
    setWindowIcon(QIcon(string));

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

CreateWindowDialog::~CreateWindowDialog()
{
	delete ui;
}

void CreateWindowDialog::on_createknop_clicked()
{
	SqlHandler *sqlplayer = new SqlHandler();
	if(assID) {
        QString alter = "UPDATE `assignments` SET `naam` = '" + ui->opdrachtnaam->toPlainText() + "', `instructions` = '" + ui->beschrijving->toPlainText() + "', `video` = '" + ui->ytlink->toPlainText() + "', `skeletcode` = '" + ui->skeletcode->toPlainText() + "', `category` = '" + ui->Category->toPlainText() + "', `sets` = " + ui->comboBox->itemData(ui->comboBox->currentIndex()).toString() + "' WHERE `assID` = " + QString::number(assID);
		sqlplayer->alter(alter);
	} else {
        QString alter = "INSERT INTO Assignments (assID, naam, instructions, video, skeletcode, category, sets) VALUES ('0','" + ui->opdrachtnaam->toPlainText() + "','" + ui->beschrijving->toPlainText() + "','" + ui->ytlink->toPlainText() + "','" + ui->skeletcode->toPlainText() + "'," + ui->Category->toPlainText() + "','" + ui->comboBox->itemData(ui->comboBox->currentIndex()).toString() + "')";
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

void CreateWindowDialog::on_cancelknop_clicked()
{
	this->close();
}

