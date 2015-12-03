#include "achievementhandler.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//ALL the Achievements
//Builder achievement and the architect achievement (DocentSide)
void AchievementHandler::BuilderAchievement(){
    int builder = NmrCompletedAssignments();
    int nmbrofRestAchievements = 87;

    //builder LVL 1
    //number of completed assignments is atleast 1
    if(builder > 0){
        if(InsertAchievement(accountID, nmbrofRestAchievements)){
            NewAchieve();
        }
        //Builder LVL 2
        //number of completed assignments is atleast 5
        if(builder > 4){
            if(InsertAchievement(accountID, nmbrofRestAchievements + 1)){
                NewAchieve();
            }
            //builder LVL 3 and higher
            //number of completed assignments is atleast 10 and every when a new 10 power
            // is gained every new 10 power assignments a new lvl in this achievement is gained.
            //max achievement is lvl 5 but the point are endless going if their are enough assignments.
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
            //if all available assignments are made and are approved.
            //gain the architect achievement
            if(builder == all){
                if(InsertAchievement(accountID, 0)){
                    NewAchieve();
                }
            }
        }
    }
}

//the Cheater achievement (StudentSide)
//looks for the word cheat in your code
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
//looks if the moment you submit if your within the work hours or out.
//Workhours 06:00 - 24:00.
void AchievementHandler::TurnOffTheLights(){
    message = "SELECT MAX(`timestamp`) FROM `assignment_status` WHERE `accID` = " + QString::number(accountID);
    query = sqlplayer->select(message);
    query.first();
    QDateTime timeDate = query.value(0).toDateTime();
    QTime time = timeDate.time();
    QTime afterWork(23,59,59);
    QTime beforeWork(6,0,1);
    if(time < beforeWork || time > afterWork ){
        InsertAchievement(accountID,82);
        NewAchieve();
    }
}

// the twisted achievement (StudentSide)
// looks if their is an achievement which is in a earlier priority
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

    //binaryachiever
    //if you get an binary number of achievers excluding this one and achiever you get a
    //lvl in this achievement.
    for(int i = 1; i < logInt  && logInt < 6 ; i++){
        if(InsertAchievement(accountID,59 + i)){
            NewAchieve();
        }
    }
    //achiever
    //every 10 achievements exluding this one and binaryachiever you get a lvl in
    //this  achievement.
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

    //Over Achiever
    //If all achievements except this one are achieved by this account you earn this
    //achievement
    if(normals == allNormals){
        if(InsertAchievement(accountID, 65)){
            NewAchieve();
        }
    }
}


//the scorer achievement (StudentSide)(DocentSide)
//every time there is a possibilty to get a achievement this function is called.
//if an certain amount of points is achieved get a lvl in this achievement.
void AchievementHandler::Scorer(){
   message = "SELECT SUM(A.score) FROM `achievement_list` as A  JOIN `achievements` as B ON A.achID = B.achID WHERE B.accID = " + accountID;
   query = sqlplayer->select(message);
   query.first();
   int points = query.value(0).toInt();

   //atleast 10 points are earned
   //Level 1 of this achievement is achieved.
   if(points > 9){
       if(InsertAchievement(accountID, 50)){
           NewAchieve();
       }
       //atleast 100 points are earned
       //Level 2 of this achievement is achieved.
       if(points > 99){
           if(InsertAchievement(accountID, 51)){
               NewAchieve();
           }
           //atleast 2000 points are earned
           //Level 3 of this achievement is achieved.
           if(points > 1999){
               if(InsertAchievement(accountID, 52)){
                   NewAchieve();
               }
               //atleast 5000 points are earned
               //Level 4 of this achievement is achieved.
               if(points > 4999){
                   if(InsertAchievement(accountID, 53)){
                       NewAchieve();
                   }
                   //atleast 10000 points are earned
                   //Level 5 of this achievement is achieved.
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
//a number of assignments first time correctly made.
void AchievementHandler::Flawless(){
    message = "SELECT COUNT(`flawless`) FROM `accounts` WHERE `accID` = " + QString::number(accountID);
    query = sqlplayer->select(message);
    query.first();
    int flawless = query.value(0).toInt();

    //atleast 1 assignment first time correctly made.
    //Level 1 of this achievement is achieved.
    if(flawless > 0){
        if(InsertAchievement(accountID,1)){
            NewAchieve();
        }
        //atleast 5 assignment first time correctly made.
        //Level 2 of this achievement is achieved.
        if(flawless > 4){
            if(InsertAchievement(accountID,2)){
                NewAchieve();
            }
            //atleast 10 assignment first time correctly made.
            //Level 3 of this achievement is achieved.
            if(flawless > 9){
                if(InsertAchievement(accountID,3)){
                    NewAchieve();
                }
                //atleast 20 assignment first time correctly made.
                //Level 4 of this achievement is achieved.
                if(flawless > 19){
                    if(InsertAchievement(accountID,4)){
                        NewAchieve();
                    }
                    //atleast 5 assignment first time correctly made.
                    //Level 30 of this achievement is achieved.
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
//if an assignment is twisted made and is rated as good by the docent.
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
//if an steady flow of good assignments have been delivered and rated as good by the docent
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
                //atleast 18,21,24 assignment in the last past three ours and atleast 6,7,8 per hour correctly made .
                //Level 1,2,3 respectively of this achievement is achieved.
                for(int i = 6; i < lowest + 1; i++){
                    if(i > 5){
                         if(InsertAchievement(accountID,37 + i)){
                            NewAchieve();
                         }
                    }
                //atleast 27,30 assignment in the last past three ours and atleast 9,10 per hour correctly made .
                //Level 4,5 respectively of this achievement is achieved.
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

//the speedy worker achievement (docentside)
//fast deliverd assignment within 10 minutes and gaining a lvl in this achievement when two or more
//assignments where delivered and rated as good by the docent.
void AchievementHandler::SpeedyWorker(){
    message = "SELECT COUNT(`timestamp`) FROM `assignment_status` WHERE `timestamp` < (SELECT (MAX(`timestamp`) + 1) FROM `assignment_status` WHERE `accID` = " + QString::number(accountID) + ") AND `timestamp` > ((SELECT MAX(`timestamp`) FROM `assignment_status` WHERE `accID` = " + QString::number(accountID) + ") - 1000) AND `accID` = " + QString::number(accountID) + " AND `score` = 1111";
    query = sqlplayer->select(message);
    query.first();
    int x = query.value(0).toInt();
    for(int i = 1; i < x; i++){
        //Level 1 t/m 3
        //2,3 opdrachten goed ingeleverd in 10 minuten
        if(i > 1){
            if(InsertAchievement(accountID,15 + i )){
                NewAchieve();
            }
        }
        //Level 3 t/m 5
        //4,5,6 opdrachten goed ingeleverd in 10 minuten
        if(i > 2){
            if(InsertAchievement(accountID, 63 + i )){
                NewAchieve();
            }
        }
    }
}

//the Catergory collector achievement(docentside)
//if an all assignments in a catergory is made and rated as good by the docent.
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
//the easy peasy achievement(docentside)
//if all easy assignments in a category is made and rate as good by the docent
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
//the middleoftheroad achievement(docentside)
//if all medium assignments in a category is made and rate as good by the docent
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
//the MrHarder achievement(docentside)
//if all hard assignments in a category is made and rate as good by the docent
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
//the prankster achievement(docentside)
//an assignment is rated as funny
void AchievementHandler::Prankster(int accountID){
    if(InsertAchievement(accountID,83 )){
        NewAchieve();
    }
}
//the onesmallstep achievement(docentside)
//the student has handed in a assignment as first and the docent rated it as good.
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
//the follower achievement and the leader achievement (docentside)(studentside)
//the follower achievement is given to the person which has the least points at the end of the day.
//the leader achievement is given to the person which has the most points at the end of the day.
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

//the followed achievement and the lead achievement (docentside)(studentside)
//the followed achievement is given to the person which has the least points.
//the lead achievement is given to the person which has the most points.
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

//the compressed achievement and decompressed achievement(studentside)
//check if the submitted code is longer then 50 lines (decompressed) or smaller then
//3 lines(compressed).
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//All the helper functions of the achievement handler

//is a function to make sure their will be only one entry for each accountID and achievementID.
//if their is not such unique combination their is a new achievement inserted into the database.
bool AchievementHandler::InsertAchievement(int accountID, int achievementID ){
    achievetracker = achievementID;
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

//return an integer for all completed and rated as good assignments for a given accountID.
int AchievementHandler::NmrCompletedAssignments(){
    message = "SELECT COUNT(`assID`) FROM `assignment_status` WHERE `score` = '1111' AND accID = " + QString::number(accountID);
    query = sqlplayer->select(message);
    query.first();
    return (query.value(0).toInt());
}

//return an integer for all assignments available as student.
int AchievementHandler::AllAssignments(){
    message = "SELECT COUNT(`achID`) FROM `achievement_list`";
    query = sqlplayer->select(message);
    query.first();
    return 0;
}

//return an integer for all achievements that are not special and are not hidden.
int AchievementHandler::AllNormals(){
    message = "SELECT COUNT(`achID`) FROM `achievement_list` WHERE `achID` < 65 AND `achID` > 86";
    query = sqlplayer->select(message);
    query.first();
    return (query.value(0).toInt());
}

// a function called when ever their is an new achievement entry in the database.
void AchievementHandler::NewAchieve(){
    qDebug("New Achievement achieve:" + achievetracker);
    Followed();
    Follower();
    return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////




/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
