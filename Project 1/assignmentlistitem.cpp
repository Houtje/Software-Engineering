#include "assignmentlistitem.h"
#include "QDebug"

AssignmentListItem::AssignmentListItem(int assignmentNumber, int score, QWidget *parent) : QWidget(parent)
{
	QString assignmentNameString = "Opdracht " + QString::number(assignmentNumber);
	QLabel *assignmentName = new QLabel(assignmentNameString);
	assignmentName->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	/*QTableWidget *checkTable = new QTableWidget(1, 4, this);
	checkTable->setMinimumSize(QSize(100, 100));
	checkTable->setItem(0,0, new QTableWidgetItem(((score / 1000) & 1) ? QIcon(":/new/prefix1/achievement dingen/check.png") : QIcon(":/new/prefix1/achievement dingen/check.png"), (QString) ""));
	*/
	QWidget *checkTable = new QWidget();
	//checkTable->setFixedHeight();
	QHBoxLayout *tableItem = new QHBoxLayout();
	tableItem->setSizeConstraint(QLayout::SetFixedSize);
	tableItem->setSpacing(0);
	tableItem->addWidget(new QROCheckBox("", (score / 1000) & 1));
	tableItem->addWidget(new QROCheckBox("", (score / 100) & 1));
	tableItem->addWidget(new QROCheckBox("", (score / 10) & 1));
	tableItem->addWidget(new QROCheckBox("", score & 1));
	//checkTable->setLayout(tableItem);
	checkTable->setFixedHeight(20);
	QGridLayout *itemLayout = new QGridLayout();
	itemLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	itemLayout->addWidget(assignmentName, 0, 0, 1, 1);
	itemLayout->addLayout(tableItem, 0, 1, 1, 1, Qt::AlignRight);
	//itemLayout->addWidget(checkTable, 0, 1, 1, 1);
	setLayout(itemLayout);

}

QSize AssignmentListItem::minimumSizeHint() {
	return QSize(20, 40);
}
