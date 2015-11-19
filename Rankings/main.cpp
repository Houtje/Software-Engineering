#include "leaderboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    leaderboard w;
    w.show();

    return a.exec();
}
