#include "form.h"
#include "ui_form.h"

//the dropdown achievementlist
Form::Form(QPixmap image, QString name, QString tooltip, QString score, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
	ui->setupUi(this);
	ui->image->setPixmap(image);
	ui->name->setText(name);
	ui->points->setText(score);
	setToolTip(tooltip);
}

Form::~Form()
{
	delete ui;
}
