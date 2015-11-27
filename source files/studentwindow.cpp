#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "QDebug"

StudentWindow::StudentWindow(int accID, QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::StudentWindow)
{
	ui->setupUi(this);
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
	qDebug(username.toStdString().c_str());
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
		qDebug(imageString.toStdString().c_str());
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
		QString imageString = ":/new/prefix1/plaatjes/achievements/notachieved/hidden.jpg";
		achieveList[pointylist].image.load(imageString);
		achieveList[pointylist].name = "???";
		achieveList[pointylist].info = "???";
		achieveList[pointylist].score = "???";
	}
	achievements = "SELECT `achID` FROM `achievements` WHERE `accID` = " + QString::number(ingelogde);
	qDebug(achievements.toStdString().c_str());
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
		qDebug(rankAchieved.toStdString().c_str());
		achieveList[pointylist].image.load(rankAchieved);
	};
	for(int i = 0; i < allAchievementListSize-5; i++) {
		Form *newAchievement = new Form(achieveList[i].image, achieveList[i].name, achieveList[i].info);
		if((i+1)%2)
			ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget(i/2, i%2, newAchievement);
	}
	ui->allAchievements->insertRow(ui->allAchievements->rowCount());
	ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 0, new Horizontaldingie());
	ui->allAchievements->setCellWidget(ui->allAchievements->rowCount()-1, 1, new Horizontaldingie());
	int hiddenlocator = 1;
	if(allAchievementListSize%2) hiddenlocator = 0;
	for(int i = allAchievementListSize-5; i < allAchievementListSize; i++) {
		Form *newAchievement = new Form(achieveList[i].image, achieveList[i].name, achieveList[i].info);
		if((i+hiddenlocator+1)%2)
			ui->allAchievements->insertRow(ui->allAchievements->rowCount());
		ui->allAchievements->setCellWidget((i+hiddenlocator)/2+1, (i+hiddenlocator)%2, newAchievement);
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
	int nummer = q.value(0).toInt();
	QString alter = "UPDATE `assignment_status` SET `submitted` = 1, `solution` = '" + ui->opdrachtCode->toPlainText() + "' WHERE `assID` = " + nummertje +" AND `accID` = "+QString::number(ingelogde);
	qDebug(alter.toStdString().c_str());
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

void StudentWindow::on_achievementList_clicked(const QModelIndex &index)
{
	qDebug("Hallo");
	if(ui->allAchievements->isHidden())
		ui->allAchievements->show();
	else
		ui->allAchievements->hide();
}

void StudentWindow::on_achievementList_clickie() {
	qDebug("Hallo2");
	if(ui->allAchievements->isHidden())
		ui->allAchievements->show();
	else
		ui->allAchievements->hide();

}
