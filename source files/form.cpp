#include "form.h"
#include "ui_form.h"

Form::Form(QPixmap image, QString name, QString tooltip, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
	ui->setupUi(this);
	ui->image->setPixmap(image);
	ui->name->setText(name);
	setToolTip(tooltip);
}

Form::~Form()
{
	delete ui;
}
