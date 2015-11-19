#include "leaderboard.h"
#include "ui_leaderboard.h"

leaderboard::leaderboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leaderboard)
{
    ui->setupUi(this);
    QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->losers);
    ui->losers->setHorizontalHeader(headerView);

    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Fixed);
    headerView->resizeSection(1, 200);
    headerView->setVisible(false);

    QHeaderView *headerViewTop = new QHeaderView(Qt::Horizontal, ui->topThree);
    ui->topThree->setHorizontalHeader(headerViewTop);

    headerViewTop->setSectionResizeMode(0, QHeaderView::Stretch);
    headerViewTop->setSectionResizeMode(1, QHeaderView::Fixed);
    headerViewTop->resizeSection(1, 200);
    headerViewTop->setVisible(false);

    this->rerank();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rerank()));
    timer->start(15000);

}

leaderboard::rerank(){
    ui->losers->setRowCount(0);
    ui->topThree->setRowCount(0);
    SqlHandler *q = new SqlHandler();
    QString top = "SELECT d.username, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 DESC LIMIT 3";
    QString str = "SELECT d.username, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 DESC";
    QSqlQuery p = q->select(str);

    while(p.next()){
        ui->losers->insertRow(ui->losers->rowCount());
        ui->losers->setCellWidget(ui->losers->rowCount()-1, 0, new QLabel(p.value(0).toString()));
        ui->losers->setCellWidget(ui->losers->rowCount()-1, 1, new QLabel(p.value(1).toString()));
    }


    QSqlQuery l = q->select(top);
    while(l.next()){
        ui->topThree->insertRow(ui->topThree->rowCount());
        ui->topThree->setCellWidget(ui->topThree->rowCount()-1,0, new QLabel(l.value(0).toString()));
        ui->topThree->setCellWidget(ui->topThree->rowCount()-1,1, new QLabel(l.value(1).toString()));
    }
}

leaderboard::~leaderboard()
{
    delete ui;
}


