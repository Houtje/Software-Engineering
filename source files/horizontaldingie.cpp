#include "horizontaldingie.h"
#include "ui_horizontaldingie.h"

Horizontaldingie::Horizontaldingie(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Horizontaldingie)
{
	ui->setupUi(this);
}

Horizontaldingie::~Horizontaldingie()
{
	delete ui;
}
