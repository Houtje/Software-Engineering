#include "studentwindow.h"
#include "ui_studentwindow.h"
#include "sqlhandler.h"

StudentWindow::StudentWindow(QWidget *parent) :
    QMainWindow(parent),
	ui(new Ui::StudentWindow)
{
	ui->setupUi(this);
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
	if(sqlplayer != NULL) {
		QSqlQuery q = sqlplayer->selectOW("assignment_status", "assID", "score", "`accID` = 2");
		while(q.next()) {
			ui->tableWidget->insertRow(ui->tableWidget->rowCount());
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 0, new QLabel("Opdracht " + QString::number(q.value(0).toInt())));
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 1, new QROCheckBox("", (q.value(1).toInt() / 1000) & 1));
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 2, new QROCheckBox("", (q.value(1).toInt() / 100) & 1));
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 3, new QROCheckBox("", (q.value(1).toInt() / 10) & 1));
			ui->tableWidget->setCellWidget(ui->tableWidget->rowCount()-1, 4, new QROCheckBox("", (q.value(1).toInt() & 1)));
			/*
			 * AssignmentListItem *assignmentItem = new AssignmentListItem( q.value(0).toInt(), q.value(1).toInt(), this);
			 * QListWidgetItem *newitem = new QListWidgetItem(ui->assignmentList);
			 * newitem->setSizeHint(assignmentItem->minimumSizeHint());
			 * ui->assignmentList->addItem(newitem);
			 * ui->assignmentList->setItemWidget(newitem, assignmentItem);
			 * connect( assignmentItem, SIGNAL(mouseDoubleClickEvent()), this, SLOT(on_testButton_clicked()));
			*/
		}
		QStringList headers = QStringList();
		headers.append(QString("Naam"));
		headers.append(QString("L"));
		headers.append(QString("T"));
		headers.append(QString("C"));
		headers.append(QString("O"));
		ui->tableWidget->setHorizontalHeaderLabels(headers);
		ui->tableWidget->horizontalHeader()->setVisible(true);
	}
}

StudentWindow::~StudentWindow()
{
	delete ui;
}

void StudentWindow::on_ietsButton_clicked()
{
	QIcon achievementItem(":/new/prefix1/plaatjes/EYO.jpg");
	QListWidgetItem *newItem = new QListWidgetItem(ui->achievementList);
	newItem->setIcon(achievementItem);
	newItem->setSizeHint(achievementItem.actualSize(QSize(100, 100)));
	ui->achievementList->addItem( newItem);
}

void StudentWindow::on_compileButton_clicked()
{

}

void StudentWindow::on_submitKnop_clicked()
{
	ui->opdrachtText->setText("Hallo");
}
