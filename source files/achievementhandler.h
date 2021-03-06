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
    int achievetracker;

    ///////////FUNCTIONS//////////
    //Constructors
    AchievementHandler();
    AchievementHandler(int accID);

    //Achievements
	void BuilderAchievement();
	void TurnOffTheLights();
	void Cheater(QString Parent);
	void Twisted();
	void Achiever();
	void Scorer();
	void Flawless();
	void TwistedAgain();
	void SteadyFlow();
    void Compressed(QString Parent);
    void Follower();
    void OneSmallStep();
    void Followed();
    void SpeedyWorker();
    void Catergory();
    void EasyPeasy();
    void MiddleOfTheRoad();
    void MrHarder();
    void Prankster(int accountID);

    //Helper functions
    int NmrCompletedAssignments();
    bool InsertAchievement(int accountID, int achievementID );
    int AllAssignments();
    int AllNormals();
	void NewAchieve();

    //Submit functions
	void SubmitStudent(int assID, QString code);
	void SubmitDocent(int assID, int accID);
};

#endif // ACHIEVEMENTHANDLER_H
