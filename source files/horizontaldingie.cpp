#include "horizontaldingie.h"
#include "ui_horizontaldingie.h"

//the dividing line in the dropdown achievementlist(form.cpp)
Horizontaldingie::Horizontaldingie(QString textLabel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Horizontaldingie)
{
	ui->setupUi(this);
	ui->textLabel->setText(textLabel);
}

Horizontaldingie::~Horizontaldingie()
{
	delete ui;
}
