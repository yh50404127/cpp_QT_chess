#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "widget.h"

class SingleGame : public Widget
{
    Q_OBJECT

public:

    SingleGame(){
        _level = 4;
    }

    virtual void click(int id,int row,int col);
    Stop* computerMove();
    void getAllPossibleMove(QVector<Stop*> &steps);
    void getAllPossibleMoveRed(QVector<Stop*> &steps);

    void fakeMove(Stop *step);
    int calcScore();
    void unfakeMove(Stop *step);

    int getMinScore(int level , int curMaxScore);
    int getMaxScore(int level , int curMinxScore);

    int _level;

public slots:
    void mainMove();

};

#endif // SINGLEGAME_H
