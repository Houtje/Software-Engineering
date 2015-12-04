#include "studentwindow.h"

//the main studentwindow where the student can see his assignments and how they are
//graded. Also the possibility to open up a assignment bij double clicking on it, when
//the student does, sees the selected assignment. Their is also an his code enviroment.
//By selecting an assignment their is sometimes given an skeletcode. And that can be retrieved
//with the reset button the code of the student is forgotten and the skeletcode is given to
//the student. With the save button the student can save his code to pick up later on.
//With the sumbit button the student send his code to the docent to rate his code.
//With the compile button the student compiles his code with output send back to the
//terminal window.
//In this window also the student can track his last achieved achievements and his overall
//progress of getting achievements.
StudentWindow::StudentWindow(int accID, QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::StudentWindow)
{
	ui->setupUi(this);

    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
    setWindowIcon(QIcon(string));

	lastAchievement = 0;
    achieving = new AchievementList(ui->centralWidget);
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
    achieve = new AchievementHandler(ingelogde);
    headerView = new QHeaderView(Qt::Horizontal, ui->tableWidget);
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
	ui->achievementList->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	ui->achievementList->setIconSize(QSize(50,50));
	QNetworkProxyFactory::setUseSystemConfiguration(true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
    sqlplayer = new SqlHandler();
    message = "SELECT MAX(`achID`) FROM `achievement_list`";
    query = sqlplayer->select(message);
	allAchievementListSize = 0;
    query.first();
    allAchievementListSize = query.value(0).toInt() + 1;
	achieveList = new Ui::AchievementInfo [allAchievementListSize];
    message = "SELECT `username` FROM `accounts` WHERE `accID` = " + QString::number(accID);
    query = sqlplayer->select(message);
    if(query.next()) {
        ui->nameLabel->setText(query.value(0).toString().toStdString().c_str());
	} else {
		ui->nameLabel->setText("Database ERROR");
	}
    message = "SELECT * FROM `achievement_list` WHERE `hidden` = 0";
    query = sqlplayer->select(message);
    while(query.next()) {
        int pointylist = query.value(0).toInt();
		if(pointylist > 82) {
			pointylist -= 5;
		}
        int imageloader = query.value(0).toInt();
		if(imageloader > 91) {
			imageloader = 91;
		}
		QString imageString = ":/new/prefix1/plaatjes/achievements/notachieved/" + QString::number(imageloader) + ".png";
		Ui::AchievementInfo info;
		info.image.load(imageString);
        info.name = query.value(1).toString();
        info.info = query.value(2).toString();
        info.score = query.value(3).toString();
		achieveList[pointylist] = info;
	}
    message = "SELECT * FROM `achievement_list` WHERE `hidden` = 1";
    query = sqlplayer->select(message);
    while(query.next()) {
        int pointylist = query.value(0).toInt() + (allAchievementListSize - 87);
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

//the code is sent to a compiler to compile and gives back the output
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

//refresh the list of assignments
void StudentWindow::refresh() {
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
        message ="SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " AND a.`sets` = 'easy' ORDER BY a.`assID` ASC";
        query = sqlplayer->select(message);
        while(query.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(query.value(0).toString()));
			ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0)->setContentsMargins(5, 0, 0, 0);
            if(query.value(1).toString().compare("")){
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (query.value(1).toInt() / 1000) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (query.value(1).toInt() / 100) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (query.value(1).toInt() / 10) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (query.value(1).toInt() & 1)));

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
        message ="SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " AND a.`sets` = 'medium' ORDER BY a.`assID` ASC";
        query = sqlplayer->select(message);
        while(query.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(query.value(0).toString()));
			ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0)->setContentsMargins(5, 0, 0, 0);
            if(query.value(1).toString().compare("")){
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (query.value(1).toInt() / 1000) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (query.value(1).toInt() / 100) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (query.value(1).toInt() / 10) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (query.value(1).toInt() & 1)));

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
        message = "SELECT a.`naam`, b.`score` FROM `assignments` AS a, `assignment_status` AS b WHERE a.`assID` = b.`assID` AND b.`accID` = " + QString::number(ingelogde) + " AND a.`sets` = 'hard' ORDER BY a.`assID` ASC";
        query = sqlplayer->select(message);
        while(query.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
            ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel(query.value(0).toString()));
			ui->tableWidget->cellWidget(ui->tableWidget->rowCount()-1, 0)->setContentsMargins(5, 0, 0, 0);
            if(query.value(1).toString().compare("")){
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (query.value(1).toInt() / 1000) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (query.value(1).toInt() / 100) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (query.value(1).toInt() / 10) & 1));
                ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (query.value(1).toInt() & 1)));

			}
		}
		ui->achievementList->clear();
        message = "SELECT `achID` FROM `achievements` WHERE `accID` = " + QString::number(ingelogde);
        query = sqlplayer->select(message);
        while(query.next()) {
            int achievementNumber = query.value(0).toInt();
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
        message = "SELECT b.`achID`, b.`name`, b.`description`, b.`score` FROM `achievements` AS a, `achievement_list` AS b WHERE a.`accID` = " + QString::number(ingelogde) + " AND a.achID = b.achID";;
        query = sqlplayer->select(message);
        while(query.next()) {
            int pointylist = query.value(0).toInt();
			if((pointylist - 81)>0) {
				if((pointylist - 87) <0) {
					pointylist = ((pointylist-82)+(allAchievementListSize-5));
				}else {
					pointylist -= 5;
				}
			}
            int imageloader = query.value(0).toInt();
			if(imageloader > 91) {
				imageloader = 91;
			}
			QString rankAchieved = ":/new/prefix1/plaatjes/achievements/achieved/" + QString::number(imageloader) + ".png";
            achieveList[pointylist].name = query.value(1).toString();
            achieveList[pointylist].info = query.value(2).toString();
            achieveList[pointylist].score = query.value(3).toString();
			achieveList[pointylist].image.load(rankAchieved);
		};
	}
}

//submits the code to the docent and saves the code in the database.
void StudentWindow::on_submitButton_clicked(){
    message = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
    query = sqlplayer->select(message);
    query.next();
    QString nummertje = query.value(0).toString();
    int nummer = query.value(0).toInt();
    message = "UPDATE `assignment_status` SET `submitted` = 1, `solution` = '" + ui->opdrachtCode->toPlainText() + "' WHERE `assID` = " + nummertje +" AND `accID` = "+QString::number(ingelogde);
    sqlplayer->alter(message);
	achieve->SubmitStudent(nummer,ui->opdrachtCode->toPlainText());
	QMessageBox msgBox;
	msgBox.setText("Opdracht succesvol ingeleverd.");
	msgBox.exec();
}

//saves the code in the database
void StudentWindow::on_opslaanButton_clicked(){
    message = "SELECT `assID` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
    query = sqlplayer->select(message);
    query.first();
    QString nummertje = query.value(0).toString();
    message = "UPDATE `assignment_status` SET `solution` = '" + ui->opdrachtCode->toPlainText() + "' WHERE `assID` = " + nummertje +" AND `accID` = " + QString::number(ingelogde);
    sqlplayer->alter(message);
	QMessageBox msgBox;
	msgBox.setText("Opdracht Opgeslagen.");
	msgBox.exec();
}

//select an assignment by doubleclicking
void StudentWindow::on_tableWidget_cellDoubleClicked(int row)
{
	ui->opslaanButton->setDisabled(false);
	ui->submitButton->setDisabled(false);
	QLabel *opdracht = (QLabel*) ui->tableWidget->cellWidget(row, 0);
	if(opdracht != NULL) {
		opdrachtNaam = opdracht->text();
        message = "SELECT `instructions`, `video` FROM `assignment_status` AS a, `assignments` AS b WHERE b.`naam` = '" + opdrachtNaam + "' AND a.`assID` = b.`assID`";
        query = sqlplayer->select(message);
        ui->opdrachtText->setText(query.value(0).toString());
        ui->youtubeView->setUrl(query.value(1).toString());

        message = "SELECT a.`solution` FROM `assignment_status` AS a, `assignments` AS b WHERE b.`naam` = '" + opdrachtNaam + "' AND a.`accID` = " + QString::number(ingelogde)+ " AND a.`assID` = b.`assID`";
        query = sqlplayer->select(message);
        query.first();
        ui->opdrachtCode->setText(query.value(0).toString());
	} else {
		ui->opdrachtText->setText("");
		ui->youtubeView->setUrl(QString::fromStdString(""));
		ui->opdrachtCode->setText("");
	}
}

//logout and exit to the inlogscreen
void StudentWindow::on_logOutButton_clicked()
{
	goLogin = true;
	this->close();
}

//preventing this window to shutdown when opening an other window.
bool StudentWindow::keepGoing() {
	bool tempLogin = goLogin;
	goLogin = false;
	return tempLogin;
}

//resetting the code in the code text to the original skeletcode
void StudentWindow::on_resetButton_clicked()
{
    message = "SELECT `skeletcode` FROM `assignments` WHERE `naam` = '" + opdrachtNaam + "'";
    query = sqlplayer->select(message);
    if(query.next()) {
        ui->opdrachtCode->setText(query.value(0).toString());
	} else {
		QMessageBox msgBox;
		msgBox.setText("Kan geen verbinding maken met de database.");
		msgBox.exec();
	}
}

void StudentWindow::on_achievementList_clicked(){}

//opens up the all progress achievement list
void StudentWindow::on_achievementList_clickie() {
    Form *newAchievement ;
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
            newAchievement = new Form(achieveList[i].image, achieveList[i].name, achieveList[i].info, achieveList[i].score);
			if((i+1)%2)
				ui->allAchievements->insertRow(ui->allAchievements->rowCount());
			ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, i%2, newAchievement);
		}
		rememberInt = i;
		ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 0, new Horizontaldingie("Hard"));
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 1, new Horizontaldingie());
		for(i = 0; i < allAchievementListSize-hiddenAchievements-rememberInt; i++) {
            newAchievement = new Form(achieveList[i+rememberInt].image, achieveList[i+rememberInt].name, achieveList[i+rememberInt].info, achieveList[i+rememberInt].score);
			if((i+1)%2)
				ui->allAchievements->insertRow(ui->allAchievements->rowCount());
			ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, (i)%2, newAchievement);
		}
		rememberInt += i;
		ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 0, new Horizontaldingie("Secret"));
		ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 1, new Horizontaldingie());
		for(i = 0; i < allAchievementListSize-rememberInt; i++) {
            newAchievement = new Form(achieveList[i+rememberInt].image, achieveList[i+rememberInt].name, achieveList[i+rememberInt].info, achieveList[i+rememberInt].score);
			if((i+1)%2)
				ui->allAchievements->insertRow(ui->allAchievements->rowCount());
			ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, i%2, newAchievement);
		}
		ui->allAchievements->show();
	} else {
		ui->allAchievements->hide();
	}

}
