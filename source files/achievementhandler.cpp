#include "achievementhandler.h"

///////////////////////////////////////////////////////////////////////////////////////
//The Constructors
//The constructor for and student side achievement handler
AchievementHandler::AchievementHandler(int accID){
    sqlplayer = new SqlHandler();
    accountID = accID;
    all = AllAssignments();
    allNormals = AllNormals();
}

//the constructor for the docent side achievement handler
AchievementHandler::AchievementHandler(){
    sqlplayer = new SqlHandler();
    all = AllAssignments();
    allNormals = AllNormals();
}
//////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////
//ALL the Achievements
//Builder achievement and the architect achievement (DocentSide)
void AchievementHandler::BuilderAchievement(){
    int builder = NmrCompletedAssignments();
    int nmbrofRestAchievements = 87;
    //builder LVL 1
    if(builder > 0){
        if(InsertAchievement(accountID, nmbrofRestAchievements)){
            NewAchieve();
        }
        //Builder LVL 2
        if(builder > 4){
            if(InsertAchievement(accountID, nmbrofRestAchievements + 1)){
                NewAchieve();
            }
            //builder LVL 3 >
            int x = 10;
            for(int i = 1; i < builder / x; i++ ){
                if(InsertAchievement(accountID, nmbrofRestAchievements + 1 + i)){
                    NewAchieve();
                }
                if(builder == x){
                    x = x * 10;
                }
            }
            all = AllAssignments();

            //Architect
            if(builder == all){
                if(InsertAchievement(accountID, 0)){
                    NewAchieve();
                }
            }
        }
	}
}

//the Cheater achievement (StudentSide)
void AchievementHandler::Cheater(QString Parent){
    QString code = Parent;
    QString match = "cheat";
    if(code.contains(match)){
        if(InsertAchievement(accountID,86)){
            NewAchieve();
        }
	}
}

//the TurnOffTheLights achievement (StudentSide)
void AchievementHandler::TurnOffTheLights(){
	message = "SELECT MAX(`timestamp`) FROM `assignment_status` WHERE `accID` = " + QString::number(accountID);
    query = sqlplayer->select(message);
    query.first();
    QDateTime timeDate = query.value(0).toDateTime();
    QTime time = timeDate.time();
    QTime afterWork(20,0,0);
    QTime beforeWork(6,0,0);
    if(time < beforeWork || time > afterWork ){
        InsertAchievement(accountID,82);
        NewAchieve();
	}
}

// the twisted achievement (StudentSide)
void AchievementHandler::Twisted(){
	 message = "SELECT EXISTS(SELECT `assID` FROM `assignment_status` WHERE `assID` < "+ QString::number(assignmentID) + " AND `accID` = " + QString::number(accountID) + " AND `score` = '')";
     query = sqlplayer->select(message);
     query.first();
     if(query.value(0).toBool()){
         if(InsertAchievement(accountID,49)){
            NewAchieve();
         }
	 }
}

//the achiever achievement, binary achiever achievement and the over achiever achievement (StudentSide)(DocentSide)
void AchievementHandler::Achiever(){
	message = "SELECT COUNT(`achID`) FROM `achievements` WHERE `accID` = " + QString::number(accountID) + " AND (`achID` > 66 OR `achID` < 56)";
    query = sqlplayer->select(message);
    query.first();
    int storeInt = query.value(0).toInt();
    int logInt = log(storeInt)/log(2);

    //binachiever
    for(int i = 1; i < logInt  && logInt < 6 ; i++){
        if(InsertAchievement(accountID,60 + i)){
            NewAchieve();
        }
    }
    //achiever
    int tenInt = storeInt/10;
    for(int i = 1; i < tenInt && tenInt < 6; i++){
        if(InsertAchievement(accountID,55 + i)){
            NewAchieve();
        }
    }

	message = "SELECT COUNT(`achID`) FROM `achievements` WHERE `accID` = " + QString::number(accountID) + " AND `achID` < 66 OR `achID` > 86";
    query = sqlplayer->select(message);
    query.first();
    int normals = query.value(0).toInt();
    if(normals == allNormals){
        if(InsertAchievement(accountID, 66)){
            NewAchieve();
        }
	}
}


//the scorer achievement (StudentSide)(DocentSide)
void AchievementHandler::Scorer(){
   message = "SELECT SUM(A.score) FROM `achievement_list` as A  JOIN `achievements` as B ON A.achID = B.achID WHERE B.accID = " + accountID;
   query = sqlplayer->select(message);
   query.first();
   int points = query.value(0).toInt();
   if(points > 9){
       if(InsertAchievement(accountID, 51)){
           NewAchieve();
       }
       if(points > 100){
           if(InsertAchievement(accountID, 52)){
               NewAchieve();
           }
           if(points > 2000){
               if(InsertAchievement(accountID, 53)){
                   NewAchieve();
               }
               if(points > 5000){
                   if(InsertAchievement(accountID, 54)){
                       NewAchieve();
                   }
               }
           }
       }
   }
}

// the flawles achievement (DocentSide)
void AchievementHandler::Flawless(){
	message = "SELECT COUNT(`flawless`) FROM `accounts` WHERE `accID` = " + QString::number(accountID);
    query = sqlplayer->select(message);
    query.first();
    int flawless = query.value(0).toInt();
    if(flawless > 0){
        if(InsertAchievement(accountID,1)){
            NewAchieve();
        }
        if(flawless > 4){
            if(InsertAchievement(accountID,2)){
                NewAchieve();
            }
            if(flawless > 9){
                if(InsertAchievement(accountID,3)){
                    NewAchieve();
                }
                if(flawless > 19){
                    if(InsertAchievement(accountID,4)){
                        NewAchieve();
                    }
                    if(flawless > 29){
                        if(InsertAchievement(accountID,5)){
                            NewAchieve();
                        }
                    }
                }
            }
        }
	}
}

//the lets twist again achievement (DocentSide)
void AchievementHandler::TwistedAgain(){
	message = "SELECT EXISTS(SELECT * FROM `assignment_status` WHERE `score` = 1111 AND `accID` = " + QString::number(accountID) + ")";
    query = sqlplayer->select(message);
    query.first();
    if(query.value(0).toBool()){
		message = "SELECT EXISTS(SELECT `assID` FROM `assignment_status` WHERE `assID` < "+ QString::number(assignmentID) + " AND `accID` = " + QString::number(accountID) + " AND `score` = '')";
        query = sqlplayer->select(message);
        query.first();
        if(query.value(0).toBool()){
            if(InsertAchievement(accountID,50)){
               NewAchieve();
            }
        }
	}
}

//the steady flow achievement (DocentSide)
void AchievementHandler::SteadyFlow(){

    message = "SELECT COUNT(`timestamp`) FROM `assignment_status` WHERE (SELECT (`timestamp` -10000 ) FROM `assignment_status` WHERE `assID` = 1 AND `accID` = 2) < `timestamp` AND (SELECT `timestamp` FROM `assignment_status` WHERE `assID` = 1 AND `accID` = 2) >= `timestamp` AND `accID` = 2";
    query = sqlplayer->select(message);
    query.first();
    int count = query.value(0).toInt();
    int count2;
    int count3;
    int lowest;
    if(count > 5){
		message = "SELECT COUNT(`timestamp`) FROM `assignment_status` WHERE (SELECT (`timestamp` -20000 ) FROM `assignment_status` WHERE `assID` = " + QString::number(assignmentID) + " AND `accID` = " + QString::number(accountID) + ") < `timestamp` AND (SELECT `timestamp` FROM `assignment_status` WHERE `assID` = " + QString::number(assignmentID) + " AND `accID` = " + QString::number(accountID) + ") >= (`timestamp` - 10000) AND `accID` = " + QString::number(accountID);
        query = sqlplayer->select(message);
        query.first();
        count2 = query.value(0).toInt();
        if(count2 > 5){
			message = "SELECT COUNT(`timestamp`) FROM `assignment_status` WHERE (SELECT (`timestamp` -30000 ) FROM `assignment_status` WHERE `assID` = " + QString::number(assignmentID) + " AND `accID` = "+ QString::number(accountID) + ") < `timestamp` AND (SELECT `timestamp` FROM `assignment_status` WHERE `assID` = " + QString::number(assignmentID) + " AND `accID` = " + QString::number(accountID) + ") >= (`timestamp` - 20000) AND `accID` = " + QString::number(accountID);
            query = sqlplayer->select(message);
            query.first();
            count3 = query.value(0).toInt();
            if(count3 > 5){
                if(count < count2) {
                    if(count3 < count) {
                        lowest = count3;
                    } else {
                        lowest = count;
                    }
                } else {
                    if(count3 < count2) {
                        lowest = count3;
                    } else {
                        lowest = count2;
                    }
                }
                for(int i = 6; i < lowest + 1; i++){
                    if(i > 5){
                         if(InsertAchievement(accountID,37 + i)){
                            NewAchieve();
                         }
                    }

                    if(i > 8){
                        if(InsertAchievement(accountID, 66 + i )){
                           NewAchieve();
                        }
                    }
                }
            }
        }
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//All the helper functions of the achievement handler
bool AchievementHandler::InsertAchievement(int accountID, int achievementID ){
	message = "SELECT EXISTS(SELECT * FROM `achievements` WHERE `achID` = " + QString::number(achievementID) + " AND `accID` = " + QString::number(accountID) + ")";
    query = sqlplayer->select(message);
	qDebug(message.toStdString().c_str());
    query.first();
    if(!(query.value(0).toBool())){
		message = "INSERT INTO `achievements`(`achID`, `accID`) VALUES (" + QString::number(achievementID) + "," + QString::number(accountID) + ")";
		sqlplayer->alter(message);
		qDebug(message.toStdString().c_str());
        return true;
    }
    return false;
}

int AchievementHandler::NmrCompletedAssignments(){
	message = "SELECT COUNT(`assID`) FROM `assignment_status` WHERE `score` = '1111' AND accID = " + QString::number(accountID);
    query = sqlplayer->select(message);
    query.first();
    return (query.value(0).toInt());
}

int AchievementHandler::AllAssignments(){
    message = "SELECT COUNT(`achID`) FROM `achievement_list`";
    query = sqlplayer->select(message);
    query.first();
    return 0;
}

int AchievementHandler::AllNormals(){
    message = "SELECT COUNT(`achID`) FROM `achievement_list` WHERE `achID` < 66 AND `achID` > 87";
    query = sqlplayer->select(message);
    query.first();
    return (query.value(0).toInt());
}

void AchievementHandler::NewAchieve(){
    qDebug("New Achievement");
    return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// the sumbit functions for both studennt and docent
//Student
void AchievementHandler::SubmitStudent(int assID, QString code){
    assignmentID = assID;
    Cheater(code);
    TurnOffTheLights();
    Twisted();
    Achiever();
	Scorer();
}

//Docent
void AchievementHandler::SubmitDocent(int assID, int accID){
    assignmentID = assID;
    accountID = accID;
    BuilderAchievement();
    Achiever();
    Scorer();
    TwistedAgain();
    SteadyFlow();
	Flawless();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
