#include "achievementlist.h"
#include "ui_achievementlist.h"

AchievementList::AchievementList(QWidget *parent) :
	QListWidget(parent),
	ui(new Ui::AchievementList)
{
	ui->setupUi(this);
}

AchievementList::~AchievementList()
{
	delete ui;
}

void AchievementList::mousePressEvent(QMouseEvent *e) {
	emit clicked();
	QListWidget::mousePressEvent(e);
}
