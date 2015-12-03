#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "QDebug"

StudentWindow::StudentWindow(int accID, QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::StudentWindow)
{
	ui->setupUi(this);

    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
    setWindowIcon(QIcon(string));

	lastAchievement = 0;
	AchievementList *achieving = new AchievementList(ui->centralWidget);
	achieving->setObjectName(QStringLiteral("achievementList"));
	achieving->setGeometry(ui->achievementList->geometry());
	achieving->setSizePolicy(ui->achievementList->sizePolicy());
	achieving->setAutoScroll(false);
	achieving->setIconSize(QSize(50, 50));
	achieving->setFlow(QListView::LeftToRight);
	achieving->setResizeMode(QListView::Fixed);
	achieving->setGridSize(QSize(60, 60));
	achieving->setViewMode(QListView::IconMode);
	achieving->setModelColumn(0);
	delete ui->achievementList;
	ui->achievementList = achieving;
	connect(achieving, SIGNAL(clicked()), this, SLOT(on_achievementList_clickie()));
	ui->allAchievements->raise();
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
	SqlHandler *sqlplayer = new SqlHandler();
	QString sizearray = "SELECT MAX(`achID`) FROM `achievement_list`";
	QSqlQuery sizey = sqlplayer->select(sizearray);
	allAchievementListSize = 0;
	if(sizey.next())
		allAchievementListSize = sizey.value(0).toInt() + 1;
	achieveList = new Ui::AchievementInfo [allAchievementListSize];
	QString username = "SELECT `username` FROM `accounts` WHERE `accID` = " + QString::number(accID);
	QSqlQuery n = sqlplayer->select(username);
	if(n.next()) {
		ui->nameLabel->setText(n.value(0).toString().toStdString().c_str());
	} else {
		ui->nameLabel->setText("Database ERROR");
	}
	QString achievements = "SELECT * FROM `achievement_list` WHERE `hidden` = 0";
	QSqlQuery q = sqlplayer->select(achievements);
	while(q.next()) {
		int pointylist = q.value(0).toInt();
		if(pointylist > 82) {
			pointylist -= 5;
		}
		int imageloader = q.value(0).toInt();
		if(imageloader > 91) {
			imageloader = 91;
		}
		QString imageString = ":/new/prefix1/plaatjes/achievements/notachieved/" + QString::number(imageloader) + ".png";
		Ui::AchievementInfo info;
		info.image.load(imageString);
		info.name = q.value(1).toString();
		info.info = q.value(2).toString();
		info.score = q.value(3).toString();
		achieveList[pointylist] = info;
	}
	achievements = "SELECT * FROM `achievement_list` WHERE `hidden` = 1";
	q = sqlplayer->select(achievements);
	while(q.next()) {
		int pointylist = q.value(0).toInt() + (allAchievementListSize - 87);
		QString imageString = ":/new/prefix1/plaatjes/achievements/notachieved/hidden.png";
		achieveList[pointylist].image.load(imageString);
		achieveList[pointylist].name = "???";
		achieveList[pointylist].info = "???";
		achieveList[pointylist].score = "???";
	}

	ui->allAchievements->hide();
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
	QFile Compile("hello1.cs");
	Compile.open(QIODevice::WriteOnly);
	QTextStream out(&Compile);
	out << (ui->opdrachtCode->toPlainText());
	out.flush(); //wait until write is done.
	Compile.close();
	QString CompilerLocation="C:/Windows/Microsoft.NET/Framework/v4.0.30319/csc.exe";
	//TODO: allow the user to select a compiler.

	QStringList CompilerArgs;
	CompilerArgs.append("hello1.cs");
	//Tested with the first example at https://msdn.microsoft.com/en-us/library/aa288463%28v=vs.71%29.aspx?f=255&MSPPError=-2147217396

	QProcess *Compiler = new QProcess();
	Compiler->start(CompilerLocation, CompilerArgs);
	Compiler->waitForFinished(5000); //give the compiler at most 5 seconds (for now)

	if(Compiler->exitStatus()==0&&Compiler->exitCode()==0){
		QProcess *TestProgram = new QProcess();
		TestProgram->start("./hello1.exe");
		TestProgram->waitForFinished(5000); //give the program at most 5 seconds (for now)
		QByteArray result=TestProgram->readAll();
		ui->opdrachtTerminal->setText(result);
	}
	else {
		QByteArray compileError=Compiler->readAll();
		ui->opdrachtTerminal->setText(compileError);
	}
}


void StudentWindow::refresh() {
	SqlHandler *sqlplayer = new SqlHandler();
	ui->tableWidget->setRowCount(0);
	if(sqlplayer != NULL) {
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		QTableWidgetItem *item = new QTableWidgetItem("easy");
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		QFont fonty;
		fonty.setBold(true);
		item->setFont(fonty);
		item->setBackgroundColor(Qt::gray);
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);
		item = new QTableWidgetItem();
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		item->setBackgroundColor(Qt::gray);
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(*item));
		delete item;
		QSqlQuery q = sqlplayer->select("SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " AND a.`sets` = 'easy' ORDER BY a.`assID` ASC");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
			ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0)->setContentsMargins(5, 0, 0, 0);
			if(q.value(1).toString().compare("")){
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (q.value(1).toInt() / 1000) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (q.value(1).toInt() / 100) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (q.value(1).toInt() / 10) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (q.value(1).toInt() & 1)));

			}
		}
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		item = new QTableWidgetItem("medium");
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		item->setFont(fonty);
		item->setBackgroundColor(Qt::gray);
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);
		item = new QTableWidgetItem();
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		item->setBackgroundColor(Qt::gray);
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(*item));
		delete item;
		q = sqlplayer->select("SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " AND a.`sets` = 'medium' ORDER BY a.`assID` ASC");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
			ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0)->setContentsMargins(5, 0, 0, 0);
			if(q.value(1).toString().compare("")){
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (q.value(1).toInt() / 1000) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (q.value(1).toInt() / 100) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (q.value(1).toInt() / 10) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (q.value(1).toInt() & 1)));

			}
		}
		ui->tableWidget->insertRow(ui->tableWidget->rowCount());
		item = new QTableWidgetItem("hard");
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		item->setFont(fonty);
		item->setBackgroundColor(Qt::gray);
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0, item);
		item = new QTableWidgetItem();
		item->setFlags(item->flags() ^ Qt::ItemIsEditable);
		item->setBackgroundColor(Qt::gray);
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3, new QTableWidgetItem(*item));
		ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 4, new QTableWidgetItem(*item));
		delete item;
		q = sqlplayer->select("SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " AND a.`sets` = 'hard' ORDER BY a.`assID` ASC");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(q.value(0).toString()));
			ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0)->setContentsMargins(5, 0, 0, 0);
			if(q.value(1).toString().compare("")){
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (q.value(1).toInt() / 1000) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (q.value(1).toInt() / 100) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (q.value(1).toInt() / 10) & 1));
				ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (q.value(1).toInt() & 1)));

			}
		}
		ui->achievementList->clear();
		QString achieve = "SELECT `achID` FROM `achievements` WHERE `accID` = " + QString::number(ingelogde);
		q = sqlplayer->select(achieve);
		while(q.next()) {
			int achievementNumber = q.value(0).toInt();
			QIcon achievementItem(":/new/prefix1/plaatjes/achievements/achieved/" + QString::number(achievementNumber) + ".png");
			QListWidgetItem *newItem = new QListWidgetItem(ui->achievementList);
			ui->achievementList->setResizeMode(QListView::Adjust);
			newItem->setIcon(achievementItem);
			newItem->setSizeHint(achievementItem.actualSize(QSize(100, 50)));
			ui->achievementList->addItem(newItem);
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
		QString achievements = "SELECT b.`achID`, b.`name`, b.`description`, b.`score` FROM `achievements` AS a, `achievement_list` AS b WHERE a.`accID` = " + QString::number(ingelogde) + " AND a.achID = b.achID";;
		q = sqlplayer->select(achievements);
		while(q.next()) {
			int pointylist = q.value(0).toInt();
			if((pointylist - 81)>0) {
				if((pointylist - 87) <0) {
					pointylist = ((pointylist-82)+(allAchievementListSize-5));
				}else {
					pointylist -= 5;
				}
			}
			int imageloader = q.value(0).toInt();
			if(imageloader > 91) {
				imageloader = 91;
			}
			QString rankAchieved = ":/new/prefix1/plaatjes/achievements/achieved/" + QString::number(imageloader) + ".png";
			achieveList[pointylist].name = q.value(1).toString();
			achieveList[pointylist].info = q.value(2).toString();
			achieveList[pointylist].score = q.value(3).toString();
			achieveList[pointylist].image.load(rankAchieved);
		};
	}
}

void StudentWindow::on_submitButton_clicked()
{
	SqlHandler *sqlplayer = new SqlHandler();
	QString namegetter = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
	QSqlQuery q = sqlplayer->select(namegetter);
	q.next();
	QString nummertje = q.value(0).toString();
	int nummer = q.value(0).toInt();
	QString alter = "UPDATE `assignment_status` SET `submitted` = 1, `solution` = '" + ui->opdrachtCode->toPlainText() + "' WHERE `assID` = " + nummertje +" AND `accID` = "+QString::number(ingelogde);
	sqlplayer->alter(alter);
	AchievementHandler * achieve = new AchievementHandler(ingelogde);
	achieve->SubmitStudent(nummer,ui->opdrachtCode->toPlainText());
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
	sqlplayer->alter(alter);
	QMessageBox msgBox;
	msgBox.setText("Opdracht Opgeslagen.");
	msgBox.exec();
}

void StudentWindow::on_tableWidget_cellDoubleClicked(int row)
{
	ui->opslaanButton->setDisabled(false);
	ui->submitButton->setDisabled(false);
	QLabel *opdracht = (QLabel*) ui->tableWidget->cellWidget(row, 0);
	if(opdracht != NULL) {
		opdrachtNaam = opdracht->text();
		QString x = "SELECT `instructions`, `video` FROM `assignment_status` AS a, `assignments` AS b WHERE b.`naam` = '" + opdrachtNaam + "' AND a.`assID` = b.`assID`";
		QString y = "SELECT a.`solution` FROM `assignment_status` AS a, `assignments` AS b WHERE b.`naam` = '" + opdrachtNaam + "' AND a.`accID` = " + QString::number(ingelogde)+ " AND a.`assID` = b.`assID`";
		SqlHandler *sqlplayer = new SqlHandler();
		QSqlQuery q = sqlplayer->select(x);
		ui->opdrachtText->setText(q.value(0).toString());
		ui->youtubeView->setUrl(q.value(1).toString());

		QSqlQuery m = sqlplayer->select(y);
		m.next();
		ui->opdrachtCode->setText(m.value(0).toString());
	} else {
		ui->opdrachtText->setText("");
		ui->youtubeView->setUrl(QString::fromStdString(""));
		ui->opdrachtCode->setText("");
	}
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

void StudentWindow::on_achievementList_clicked(){}

void StudentWindow::on_achievementList_clickie() {
	if(ui->allAchievements->isHidden()) {
		ui->allAchievements->setRowCount(0);
		//'andere' achievements
		int hiddenAchievements = 5;
		int specialAchievements = 21;
		int rememberInt = 0;
		int i;
		ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 0, new Horizontaldingie("Easy"));
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 1, new Horizontaldingie());
		for(i = 0; i < allAchievementListSize-hiddenAchievements-specialAchievements-1; i++) {
			Form *newAchievement = new Form(achieveList[i].image, achieveList[i].name, achieveList[i].info, achieveList[i].score);
			if((i+1)%2)
				ui->allAchievements->insertRow(ui->allAchievements->rowCount());
			ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, i%2, newAchievement);
		}
		rememberInt = i;
		ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 0, new Horizontaldingie("Hard"));
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 1, new Horizontaldingie());
		for(i = 0; i < allAchievementListSize-hiddenAchievements-rememberInt; i++) {
			Form *newAchievement = new Form(achieveList[i+rememberInt].image, achieveList[i+rememberInt].name, achieveList[i+rememberInt].info, achieveList[i+rememberInt].score);
			if((i+1)%2)
				ui->allAchievements->insertRow(ui->allAchievements->rowCount());
			ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, (i)%2, newAchievement);
		}
		rememberInt += i;
		ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 0, new Horizontaldingie("Secret"));
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 1, new Horizontaldingie());
		for(i = 0; i < allAchievementListSize-rememberInt; i++) {
			Form *newAchievement = new Form(achieveList[i+rememberInt].image, achieveList[i+rememberInt].name, achieveList[i+rememberInt].info, achieveList[i+rememberInt].score);
			if((i+1)%2)
				ui->allAchievements->insertRow(ui->allAchievements->rowCount());
			ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, i%2, newAchievement);
		}
		ui->allAchievements->show();
	} else {
		ui->allAchievements->hide();
	}

}
