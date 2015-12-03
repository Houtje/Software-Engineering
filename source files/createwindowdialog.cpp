#include "createwindowdialog.h"

//we are clicked the alter or the create button in docentassignmentswindow
//we are altering an assignment(assignment > 0) or creating a new assignment(assignment = 0)
CreateWindowDialog::CreateWindowDialog(int assignment, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateWindowDialog)
{
    //Declaration
	ui->setupUi(this);
    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
	assID = assignment;
    sqlplayer = new SqlHandler();

    setWindowIcon(QIcon(string));
	if(assID) {
        message = "SELECT `naam`,`instructions`,`video`,`skeletcode` FROM `assignments` WHERE assID = " + QString::number(assID);
        query = sqlplayer->select(message);
        if(query.next()){
			setWindowTitle("Opdracht bewerken");
			ui->createknop->setText("Verander");
            ui->opdrachtnaam->setText(query.value(0).toString());
            ui->beschrijving->setText(query.value(1).toString());
            ui->ytlink->setText(query.value(2).toString());
            ui->skeletcode->setText(query.value(3).toString());
		}
	}

}

CreateWindowDialog::~CreateWindowDialog()
{
	delete ui;
}

//
void CreateWindowDialog::on_createknop_clicked(){
    //if we want to edit the assignment we selected
    if(assID) {
		message = "UPDATE `assignments` SET `naam` = '" + ui->opdrachtnaam->text() + "', `instructions` = '" + ui->beschrijving->toPlainText() + "', `video` = '" + ui->ytlink->text() + "', `skeletcode` = '" + ui->skeletcode->toPlainText() + "', `category` = '" + ui->category->text() + "', `sets` = '" + ui->comboBox->itemText(ui->comboBox->currentIndex()) + "' WHERE `assID` = " + QString::number(assID);
		qDebug(message.toStdString().c_str());
		sqlplayer->alter(message);
    }
    //else we want to make a new assignment
    else {
		message = "INSERT INTO Assignments (assID, naam, instructions, video, skeletcode, category, sets) VALUES ('0','" + ui->opdrachtnaam->text() + "','" + ui->beschrijving->toPlainText() + "','" + ui->ytlink->text() + "','" + ui->skeletcode->toPlainText() + "','" + ui->category->text() + "','" + ui->comboBox->itemText(ui->comboBox->currentIndex()) + "')";
        sqlplayer->alter(message);

        message = "INSERT INTO `assignment_status`(`assID`, `accID`, `solution`) SELECT MAX(a.assID), b.accID, (SELECT `skeletcode` FROM `assignments` WHERE `assID` = (SELECT MAX(`assID`) FROM `assignments`)) \
				FROM `assignments` as a \
				JOIN `accounts` as b \
				WHERE b.admin = 0 \
				GROUP BY b.accID";
        sqlplayer->alter(message);

	}
	this->close();
}

void CreateWindowDialog::on_cancelknop_clicked(){
	this->close();
}

