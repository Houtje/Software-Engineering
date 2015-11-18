#include "createwindow.h"
#include "sqlhandler.h"
#include "ui_createwindow.h"

CreateWindow::CreateWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CreateWindow)
{
    ui->setupUi(this);
}

CreateWindow::~CreateWindow()
{
    delete ui;
}

void CreateWindow::on_createknop_clicked()
{
    SqlHandler *sqlplayer = new SqlHandler();
    QString alter = "INSERT INTO Assignments (assID, instructions, video, skeletcode) VALUES ('0','" + ui->opdrachtnaam->toPlainText() + ": " + ui->beschrijving->toPlainText() + "','" + ui->ytlink->toPlainText() + "','" + ui->skeletcode->toPlainText() + "')";
    qDebug(alter.toStdString().c_str());
    sqlplayer->alter(alter);
    this->close();
}

void CreateWindow::on_cancelknop_clicked()
{
    this->close();
}

