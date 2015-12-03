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
         if(InsertAchievement(accountID,48)){
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
        if(InsertAchievement(accountID,59 + i)){
            NewAchieve();
        }
    }
    //achiever
    int tenInt = storeInt/10;
    for(int i = 1; i < tenInt && tenInt < 6; i++){
        if(InsertAchievement(accountID,54 + i)){
            NewAchieve();
        }
    }

    message = "SELECT COUNT(`achID`) FROM `achievements` WHERE `accID` = " + QString::number(accountID) + " AND `achID` < 66 OR `achID` > 86";
    query = sqlplayer->select(message);
    query.first();
    int normals = query.value(0).toInt();
    if(normals == allNormals){
        if(InsertAchievement(accountID, 65)){
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
       if(InsertAchievement(accountID, 50)){
           NewAchieve();
       }
       if(points > 99){
           if(InsertAchievement(accountID, 51)){
               NewAchieve();
           }
           if(points > 1999){
               if(InsertAchievement(accountID, 52)){
                   NewAchieve();
               }
               if(points > 4999){
                   if(InsertAchievement(accountID, 53)){
                       NewAchieve();
                   }
                   if(points > 9999){
                       if(InsertAchievement(accountID, 54)){
                           NewAchieve();
                       }
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
            if(InsertAchievement(accountID,49)){
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
                        if(InsertAchievement(accountID, 65 + i )){
                           NewAchieve();
                        }
                    }
                }
            }
        }
    }
}
//GEEN IDEEE
void AchievementHandler::Watcher(){

}
//NIET IMPLEMENTEREN
void AchievementHandler::Helper(){

}

void AchievementHandler::SpeedyWorker(){
    message = "SELECT COUNT(`timestamp`) FROM `assignment_status` WHERE `timestamp` < (SELECT (MAX(`timestamp`) + 1) FROM `assignment_status` WHERE `accID` = " + QString::number(accountID) + ") AND `timestamp` > ((SELECT MAX(`timestamp`) FROM `assignment_status` WHERE `accID` = " + QString::number(accountID) + ") - 1000) AND `accID` = " + QString::number(accountID) + " AND `score` = 1111";
    query = sqlplayer->select(message);
    query.first();
    int x = query.value(0).toInt();
    for(int i = 1; i < x; i++){
        if(i > 1){
            if(InsertAchievement(accountID,14 + i )){
                NewAchieve();
            }
        }
        if(i > 3){
            if(InsertAchievement(accountID, 62 + i )){
                NewAchieve();
            }
        }
    }
}

void AchievementHandler::Accuracy(){

}

void AchievementHandler::Agility(){

}

void AchievementHandler::Catergory(){
    message = "SELECT DISTINCT(`category`) FROM `assignments`";
    QSqlQuery q = sqlplayer->select(message);
    int x = 0;

    while(q.next()){
        message = "SELECT COUNT(b.assID) FROM `assignment_status` as b WHERE b.accID = " + QString::number(accountID) + " AND b.score = 1111 AND EXISTS (SELECT a.assID FROM `assignments` as a WHERE a.category = '" + q.value(0).toString() + "' AND a.assID = b.assID)";
        QSqlQuery m = sqlplayer->select(message);
        message = "SELECT COUNT(`category`) FROM `assignments` WHERE `category` = '" + q.value(0).toString() + "'";
        query = sqlplayer->select(message);
        if(m.value(0).toInt() == query.value(0).toInt()){
            x++;
        }
    }
    for(int y = 0; y < x / (pow(2,y)); y++){
        if(InsertAchievement(accountID, 20 + y )){
            NewAchieve();
        }
    }
}

void AchievementHandler::EasyPeasy(){
    message = "SELECT DISTINCT(`category`) FROM `assignments`";
    QSqlQuery q = sqlplayer->select(message);
    int x = 0;

    while(q.next()){
        message = "SELECT COUNT(b.assID) FROM `assignment_status` as b WHERE b.accID = " + QString::number(accountID) + " AND b.score = 1111 AND EXISTS (SELECT a.assID FROM `assignments` as a WHERE a.category = '" + q.value(0).toString() + "' AND a.assID = b.assID) AND a.sets = 'easy'";
        QSqlQuery m = sqlplayer->select(message);
        message = "SELECT COUNT(`category`) FROM `assignments` WHERE `category` = '" + q.value(0).toString() + "' AND `sets` = easy";
        query = sqlplayer->select(message);
        if(m.value(0).toInt() == query.value(0).toInt()){
            x++;
        }
    }
    for(int y = 0; y < x / (pow(2,y)); y++){
        if(InsertAchievement(accountID, 25 + y )){
            NewAchieve();
        }
    }
}

void AchievementHandler::MiddleOfTheRoad(){
    message = "SELECT DISTINCT(`category`) FROM `assignments`";
    QSqlQuery q = sqlplayer->select(message);
    int x = 0;

    while(q.next()){
        message = "SELECT COUNT(b.assID) FROM `assignment_status` as b WHERE b.accID = " + QString::number(accountID) + " AND b.score = 1111 AND EXISTS (SELECT a.assID FROM `assignments` as a WHERE a.category = '" + q.value(0).toString() + "' AND a.assID = b.assID) AND a.sets = 'medium'";
        QSqlQuery m = sqlplayer->select(message);
        message = "SELECT COUNT(`category`) FROM `assignments` WHERE `category` = '" + q.value(0).toString() + "' AND `sets` = medium";
        query = sqlplayer->select(message);
        if(m.value(0).toInt() == query.value(0).toInt()){
            x++;
        }
    }
    for(int y = 0; y < x / (pow(2,y)); y++){
        if(InsertAchievement(accountID, 30 + y )){
            NewAchieve();
        }
    }
}

void AchievementHandler::MrHarder(){
    message = "SELECT DISTINCT(`category`) FROM `assignments`";
    QSqlQuery q = sqlplayer->select(message);
    int x = 0;

    while(q.next()){
        message = "SELECT COUNT(b.assID) FROM `assignment_status` as b WHERE b.accID = " + QString::number(accountID) + " AND b.score = 1111 AND EXISTS (SELECT a.assID FROM `assignments` as a WHERE a.category = '" + q.value(0).toString() + "' AND a.assID = b.assID) AND a.sets = 'hard'";
        QSqlQuery m = sqlplayer->select(message);
        message = "SELECT COUNT(`category`) FROM `assignments` WHERE `category` = '" + q.value(0).toString() + "' AND `sets` = hard";
        query = sqlplayer->select(message);
        if(m.value(0).toInt() == query.value(0).toInt()){
            x++;
        }
    }
    for(int y = 0; y < x / (pow(2,y)); y++){
        if(InsertAchievement(accountID, 35 + y )){
            NewAchieve();
        }
    }
}

void AchievementHandler::Prankster(int accountID){
    if(InsertAchievement(accountID,83 )){
        NewAchieve();
    }
}

void AchievementHandler::OneSmallStep(){
    message = "SELECT COUNT(`accID`) FROM `assignment_status` WHERE `assID` = 2 AND `score` = 1111";
    query = sqlplayer->select(message);
    int x = query.value(0).toInt();
    if(x == 1){
        if(InsertAchievement(query.value(0).toInt(), 76 )){
            NewAchieve();
        }
    }
}

void AchievementHandler::Follower(){
    QDateTime time = QDateTime::currentDateTime();
    message = "SELECT COUNT(accID) FROM `achievements` ORDER BY `achievements`.`time` DESC WHERE `timestamp` > " + time.toString();
    query = sqlplayer->select(message);
    int x = query.value(0).toInt();
    if(x == 1){
        message = "SELECT d.accID, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 DESC LIMIT 1";
        query = sqlplayer->select(message);
        query.first();
        if(InsertAchievement(query.value(0).toInt(), 77 )){
            NewAchieve();
        }

        message = "SELECT d.accID, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 ASC LIMIT 1";
        query = sqlplayer->select(message);
        query.first();
        if(InsertAchievement(query.value(0).toInt(), 78 )){
            NewAchieve();
        }
    }
}
void AchievementHandler::Followed(){
    message = "SELECT d.accID, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 DESC LIMIT 1";
    query = sqlplayer->select(message);
    query.first();
    if(InsertAchievement(query.value(0).toInt(), 79 )){
       NewAchieve();
    }

    message = "SELECT d.accID, SUM(a.score) FROM `accounts` as d JOIN `achievements` as b ON b.accID = d.accID JOIN `achievement_list` as a ON b.achID = a.achID WHERE d.admin = 0 GROUP BY d.username ORDER BY 2 ASC LIMIT 1";
    query = sqlplayer->select(message);
    query.first();
    if(InsertAchievement(query.value(0).toInt(), 80 )){
        NewAchieve();
    }
}

void AchievementHandler::Compressed(QString Parent){
    QString code = Parent;
    QStringList c = code.split("\n");
    int x = c.count();
    if(x > 49){
        if(InsertAchievement(accountID, 84)){
           NewAchieve();
        }
    }
    if(x < 4){
        if(InsertAchievement(accountID, 85)){
           NewAchieve();
        }
    }
 }

/////////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//All the helper functions of the achievement handler
bool AchievementHandler::InsertAchievement(int accountID, int achievementID ){
    message = "SELECT EXISTS(SELECT * FROM `achievements` WHERE `achID` = " + QString::number(achievementID) + " AND `accID` = " + QString::number(accountID) + ")";
    query = sqlplayer->select(message);
    query.first();
    if(!(query.value(0).toBool())){
        message = "INSERT INTO `achievements`(`achID`, `accID`) VALUES (" + QString::number(achievementID) + "," + QString::number(accountID) + ")";
        sqlplayer->alter(message);
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
    message = "SELECT COUNT(`achID`) FROM `achievement_list` WHERE `achID` < 65 AND `achID` > 86";
    query = sqlplayer->select(message);
    query.first();
    return (query.value(0).toInt());
}

void AchievementHandler::NewAchieve(){
    Followed();
    Follower();
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
    Compressed(code);
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
    OneSmallStep();
    SpeedyWorker();
    Catergory();
    EasyPeasy();
    MiddleOfTheRoad();
    MrHarder();
    Prankster(accountID);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
