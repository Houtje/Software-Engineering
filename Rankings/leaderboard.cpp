#include "leaderboard.h"
#include "ui_leaderboard.h"

leaderboard::leaderboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leaderboard)
{

    ui->setupUi(this);
    QString string = ":/new/prefix1/plaatjes/golden_cup.png";
    setWindowIcon(QIcon(string));
    QHeaderView *headerView = new QHeaderView(Qt::Horizontal, ui->losers);
    QHeaderView *x = new QHeaderView(Qt::Vertical, ui->losers);
    ui->losers->setHorizontalHeader(headerView);
    ui->losers->setVerticalHeader(x);

    headerView->setSectionResizeMode(0, QHeaderView::Stretch);
    headerView->setSectionResizeMode(1, QHeaderView::Fixed);
    headerView->resizeSection(1, 200);
    headerView->setVisible(false);

    x->sectionResizeMode(QHeaderView::Fixed);
    x->setDefaultSectionSize(20);

    x->setFont(QFont("Seqoe UI", 6));

    this->rerank();
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rerank()));
    timer->start(15000);

}

leaderboard::rerank(){
    ui->losers->setRowCount(0);
    SqlHandler *q = new SqlHandler();
    QString str = "SELECT d.username, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 DESC";
    QSqlQuery p = q->select(str);

    while(p.next()){
        ui->losers->insertRow(ui->losers->rowCount());
        ui->losers->setCellWidget(ui->losers->rowCount()-1, 0, new QLabel(p.value(0).toString()));
        ui->losers->setCellWidget(ui->losers->rowCount()-1, 1, new QLabel(p.value(1).toString()));
    }
}

leaderboard::~leaderboard()
{
    delete ui;
}


