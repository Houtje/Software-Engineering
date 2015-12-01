#include "horizontaldingie.h"
#include "ui_horizontaldingie.h"

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
