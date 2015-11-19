#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <QMainWindow>
#include "sqlhandler.h"
#include <QLabel>
#include <QTimer>
#include <QTime>


namespace Ui {
class leaderboard;
}

class leaderboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit leaderboard(QWidget *parent = 0);
    ~leaderboard();

public slots:
    rerank();


private:
    Ui::leaderboard *ui;
};

#endif // MAINWINDOW_H
