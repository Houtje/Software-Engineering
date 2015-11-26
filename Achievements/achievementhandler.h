#ifndef ACHIEVEMENTHANDLER_H
#define ACHIEVEMENTHANDLER_H

#include "sqlhandler.h"
#include "QDebug"
#include <QDateTime>
#include <cmath>

class AchievementHandler
{
public:
    ///////////VARIABLES//////////
    //Query Handlers
    SqlHandler * sqlplayer;
    QString message;
    QSqlQuery query;

    //int to keep track of input
    int all;
    int allNormals;
    int assignmentID;
    int accountID;

    ///////////FUNCTIONS//////////
    //Constructors
    AchievementHandler();
    AchievementHandler(int accID);

    //Achievements
    BuilderAchievement();
    TurnOffTheLights();
    Cheater(QString Parent);
    Twisted();
    Achiever();
    Scorer();
    Flawless();
    TwistedAgain();
    SteadyFlow();

    //Helper functions
    int NmrCompletedAssignments();
    bool InsertAchievement(int accountID, int achievementID );
    int AllAssignments();
    int AllNormals();

    //Submit functions
    SubmitStudent(int assID, QString code);
    SubmitDocent(int assID, int accID);
};

#endif // ACHIEVEMENTHANDLER_H
