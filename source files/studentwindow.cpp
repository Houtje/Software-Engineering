#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "sqlhandler.h"
#include "QDebug"

StudentWindow::StudentWindow(int accID, QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::StudentWindow)
{
	ui->setupUi(this);
	goLogin = false;
	ingelogde = accID;
	QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);
	ui->tableWidget->setHorizontalHeader(headerView);
	headerView->setSectionResizeMode(0, QHeaderView::Stretch);
	headerView->setSectionResizeMode(1, QHeaderView::Fixed);
	headerView->resizeSection(1, 22);
	headerView->setSectionResizeMode(2, QHeaderView::Fixed);
	headerView->resizeSection(2, 22);
	headerView->setSectionResizeMode(3, QHeaderView::Fixed);
	headerView->resizeSection(3, 22);
	headerView->setSectionResizeMode(4, QHeaderView::Fixed);
	headerView->resizeSection(4, 22);
	//ui->tableWidget->setColumnWidth(0, ui->tableWidget->width() - 88);
	//ui->assignmentList->setStyleSheet( "QListWidget::item { border: 1px solid black; } " );
	ui->achievementList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	ui->achievementList->setIconSize(QSize(50,50));
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
	QString username = "SELECT `username` FROM `accounts` WHERE `accID` = " + QString::number(accID);
	qDebug(username.toStdString().c_str());
	SqlHandler *sqlplayer = new SqlHandler();
	QSqlQuery n = sqlplayer->select(username);
	if(n.next()) {
		ui->nameLabel->setText(n.value(0).toString().toStdString().c_str());
	} else {
		ui->nameLabel->setText("Database ERROR");
	}
	this->refresh();
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(refresh()));
	timer->start(15000);
}

StudentWindow::~StudentWindow()
{
	delete ui;
}

void StudentWindow::on_compileButton_clicked()
{

}

void StudentWindow::refresh() {
	SqlHandler *sqlplayer = new SqlHandler();
	ui->tableWidget->setRowCount(0);
	if(sqlplayer != NULL) {
		QSqlQuery q = sqlplayer->select("SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " ORDER BY a.`assID` ASC");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
			if(q.value(1).toString().compare("")){
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (q.value(1).toInt() / 1000) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (q.value(1).toInt() / 100) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (q.value(1).toInt() / 10) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (q.value(1).toInt() & 1)));

			}
			/*
			 * AssignmentListItem *assignmentItem = new AssignmentListItem( q.value(0).toInt(), q.value(1).toInt(), this);
			 * QListWidgetItem *newitem = new QListWidgetItem(ui->assignmentList);
			 * newitem->setSizeHint(assignmentItem->minimumSizeHint());
			 * ui->assignmentList->addItem(newitem);
			 * ui->assignmentList->setItemWidget(newitem, assignmentItem);
			 * connect( assignmentItem, SIGNAL(mouseDoubleClickEvent()), this, SLOT(on_testButton_clicked()));
			*/
		}
		ui->achievementList->clear();
		QString achieve = "SELECT `achID` FROM `achievements` WHERE `accID` = " + QString::number(ingelogde);
		q = sqlplayer->select(achieve);
		while(q.next()) {
			int achievementNumber = q.value(0).toInt();
			QIcon achievementItem(":/new/prefix1/plaatjes/achievements/" + QString::number(achievementNumber) + ".jpg");
			QListWidgetItem *newItem = new QListWidgetItem(ui->achievementList);
			ui->achievementList->setResizeMode(QListView::Adjust);
			newItem->setIcon(achievementItem);
			newItem->setSizeHint(achievementItem.actualSize(QSize(100, 50)));
			ui->achievementList->addItem( newItem);
		}
		QStringList headers = QStringList();
		headers.append(QString("Naam"));
		headers.append(QString("L"));
		headers.append(QString("W"));
		headers.append(QString("C"));
		headers.append(QString("O"));
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		ui->tableWidget->horizontalHeaderItem(0)->setTextAlignment(Qt::AlignLeft);
		ui->tableWidget->horizontalHeader()->setVisible(true);
	}
}

void StudentWindow::on_submitButton_clicked()
{
	SqlHandler *sqlplayer = new SqlHandler();
	QString namegetter = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
	QSqlQuery q = sqlplayer->select(namegetter);
	q.next();
	QString nummertje = q.value(0).toString();
	QString alter = "UPDATE `assignment_status` SET `submitted` = 1, `solution` = '" + ui->opdrachtCode->toPlainText() + "' WHERE `assID` = " + nummertje +" AND `accID` = "+QString::number(ingelogde);
	qDebug(alter.toStdString().c_str());
	sqlplayer->alter(alter);
	QMessageBox msgBox;
	msgBox.setText("Opdracht succesvol ingeleverd.");
	msgBox.exec();
}

void StudentWindow::on_opslaanButton_clicked()
{

	SqlHandler *sqlplayer = new SqlHandler();
	QString namegetter = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
	QSqlQuery q = sqlplayer->select(namegetter);
	q.next();
	QString nummertje = q.value(0).toString();
	QString alter = "UPDATE `assignment_status` SET `solution` = '" + ui->opdrachtCode->toPlainText() + "' WHERE `assID` = " + nummertje +" AND `accID` = " + QString::number(ingelogde);
	qDebug(alter.toStdString().c_str());
	sqlplayer->alter(alter);
	QMessageBox msgBox;
	msgBox.setText("Opdracht Opgeslagen.");
	msgBox.exec();
}

void StudentWindow::on_tableWidget_cellDoubleClicked(int row, int column)
{
	ui->opslaanButton->setDisabled(false);
	ui->submitButton->setDisabled(false);
	QLabel *opdracht = (QLabel*) ui->tableWidget->cellWidget(row, 0);
	opdrachtNaam = opdracht->text();
	QString x = "SELECT `instructions`, `video` FROM `assignment_status` AS a, `assignments` AS b WHERE b.`naam` = '" + opdrachtNaam + "' AND a.`assID` = b.`assID`";
	QString y = "SELECT a.`solution` FROM `assignment_status` AS a, `assignments` AS b WHERE b.`naam` = '" + opdrachtNaam + "' AND a.`accID` = " + QString::number(ingelogde)+ " AND a.`assID` = b.`assID`";
	qDebug(y.toStdString().c_str());
	SqlHandler *sqlplayer = new SqlHandler();
	QSqlQuery q = sqlplayer->select(x);
	q.next();
	ui->opdrachtText->setText(q.value(0).toString());
	ui->youtubeView->setUrl(q.value(1).toString());

	QSqlQuery m = sqlplayer->select(y);
	m.next();
	ui->opdrachtCode->setText(m.value(0).toString());
}

void StudentWindow::on_logOutButton_clicked()
{
	goLogin = true;
	this->close();
}

bool StudentWindow::keepGoing() {
	bool tempLogin = goLogin;
	goLogin = false;
	return tempLogin;
}

void StudentWindow::on_resetButton_clicked()
{
	SqlHandler *sqlplayer = new SqlHandler();
	QString x = "SELECT `skeletcode` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
	QSqlQuery q = sqlplayer->select(x);
	if(q.next()) {
		ui->opdrachtCode->setText(q.value(0).toString());
	} else {
		QMessageBox msgBox;
		msgBox.setText("Kan geen verbinding maken met de database.");
		msgBox.exec();
	}
}
