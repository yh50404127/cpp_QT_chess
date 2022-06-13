#include "singlegame.h"
#include <QTimer>

void SingleGame::click(int id, int row, int col)
{
    if(!this->_bRedTrue){
        return;
    }

    Widget::click(id ,row ,col);

    if(!end){
        if(!this->_bRedTrue){

            QTimer::singleShot(200,this,SLOT(mainMove()));

        }
    }

}

void SingleGame::mainMove()
{

    Stop *step = computerMove();
    moveStone(step->_moveid,step->_killid,step->_rowTo,step->_colTo);

    delete step;
    update();
}

Stop* SingleGame::computerMove()
{
    /*
        1.看看有那些可以走
        2.試著走走看
        3.評估最好的結果
        4.走最好的結果
    */

    //第1步
    QVector<Stop*> steps;
    getAllPossibleMove(steps);

    //第2步 第3步
    int maxScore = INT_MIN;
    Stop* ret = nullptr;


    while(steps.count()){
        Stop *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(_level - 1 , maxScore);
        unfakeMove(step);

        if(score > maxScore){
            maxScore = score;
            ret = step;
        }else{
            delete step;
        }

    }

    //第4步
    return ret;


}

void SingleGame::getAllPossibleMove(QVector<Stop *> &steps)
{
    for (int i=16;i<32;i++) {
        if(_s[i]._dead){continue;}
        for(int row=0;row<=9;row++){
            for(int col=0;col<=8;col++){

                int killid = this->getStoneId(row,col);

                if(killid != -1){
                    if(_s[killid]._red == _s[i]._red){
                        continue;
                    }
                }

                if(canMove(i,row,col,killid)){
                    saveStep(i,killid,row,col,steps);
                }

            }
        }
    }

}

void SingleGame::getAllPossibleMoveRed(QVector<Stop *> &steps)
{
    for (int i=0;i<16;i++) {
        if(_s[i]._dead){continue;}
        for(int row=0;row<=9;row++){
            for(int col=0;col<=8;col++){

                int killid = this->getStoneId(row,col);

                if(killid != -1){
                    if(_s[killid]._red == _s[i]._red){
                        continue;
                    }
                }

                if(canMove(i,row,col,killid)){
                    saveStep(i,killid,row,col,steps);
                }

            }
        }
    }

}

void SingleGame::fakeMove(Stop *step)
{
    killStone(step->_killid);
    moveStone(step->_moveid,step->_rowTo,step->_colTo);

}

int SingleGame::calcScore()
{
    //分數計算黑棋-紅棋 因為電腦方是黑棋
    int redScore = 0;
    int blackScore = 0;
    //enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};
    static int chessScore[]={3000,200,200,100,10,10,10};

    for(int i=0;i<16;i++){
        if(_s[i]._dead){
            continue;
        }
        redScore += chessScore[_s[i]._type];
    }

    for(int i=16;i<32;i++){
        if(_s[i]._dead){
            continue;
        }
        blackScore += chessScore[_s[i]._type];
    }

    return blackScore - redScore;

}

void SingleGame::unfakeMove(Stop *step)
{
    reliveStone(step->_killid);
    moveStone(step->_moveid,step->_rowFrom,step->_colFrom);

}

int SingleGame::getMinScore(int level,int curMaxScore)
{

    if(level == 0){
        return calcScore();
    }

    QVector<Stop*> steps;
    getAllPossibleMoveRed(steps);//收集紅棋的移動

    int minscore = INT_MAX;

    while(steps.count()){
        Stop *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMaxScore(level - 1,minscore);
        unfakeMove(step);
        delete step;

        if(score <= curMaxScore){
            while(steps.count()){
                Stop *step = steps.back();
                steps.removeLast();
                delete step;
            }

            return score;
        }

        if(score < minscore){
            minscore = score;
        }



    }

    return minscore;



}

int SingleGame::getMaxScore(int level ,int curMinScore)
{

    if(level == 0){
        return calcScore();
    }

    QVector<Stop*> steps;
    getAllPossibleMoveRed(steps);//收集紅棋的移動

    int maxscore = INT_MIN;

    while(steps.count()){
        Stop *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(level - 1,maxscore);
        unfakeMove(step);
        delete step;

        if(score >= curMinScore){
            while(steps.count()){
                Stop *step = steps.back();
                steps.removeLast();
                delete step;
            }

            return score;
        }

        if(score > maxscore){
            maxscore = score;
        }

        delete step;
    }

    return maxscore;






}


