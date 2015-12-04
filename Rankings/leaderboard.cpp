#include "leaderboard.h"

leaderboard::leaderboard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::leaderboard)
{

    ui->setupUi(this);
    QString string = ":/new/prefix1/plaatjes/icon.png";
    setWindowIcon(QIcon(string));
    sqlplayer = new SqlHandler();
    headerview = new QHeaderView(Qt::Horizontal, ui->losers);
    verticalview = new QHeaderView(Qt::Vertical, ui->losers);
    ui->losers->setHorizontalHeader(headerview);
    ui->losers->setVerticalHeader(verticalview);

    headerview->setSectionResizeMode(0, QHeaderView::Stretch);
    headerview->setSectionResizeMode(1, QHeaderView::Fixed);
    headerview->resizeSection(1, 200);
    headerview->setVisible(false);

    verticalview->sectionResizeMode(QHeaderView::Fixed);
    verticalview->setDefaultSectionSize(20);

    verticalview->setFont(QFont("Seqoe UI", 6));

    this->rerank();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(rerank()));
    timer->start(15000);

}

leaderboard::rerank(){
    ui->losers->setRowCount(0);
    message = "SELECT d.username, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 DESC";
    query = sqlplayer->select(message);

    while(query.next()){
        ui->losers->insertRow(ui->losers->rowCount());
        ui->losers->setCellWidget(ui->losers->rowCount()-1, 0, new QLabel(query.value(0).toString()));
        ui->losers->setCellWidget(ui->losers->rowCount()-1, 1, new QLabel(query.value(1).toString()));
    }
    return 0;
}

leaderboard::~leaderboard()
{
    delete ui;
}


