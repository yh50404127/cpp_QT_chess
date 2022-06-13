#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPoint>
#include "stone.h"
#include <QLabel>
#include "stop.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    stone _s[32];

    bool _victory;

    bool end = false;

    int _selectid;

    int _r;

    bool _bRedTrue;

    QLabel lab;

    QPoint center(int row,int col);
    QPoint center(int id);

    void paintEvent(QPaintEvent *);
    void drawStone(QPainter &painter, int id);


    void mouseReleaseEvent(QMouseEvent *);


    bool getRowCol(QPoint pt,int &row,int &col);
    int getStoneId(int fRow,int fCol);
    int getStoneCountAtLIne(int row1, int col1, int row2,  int col2);

    bool canMove(int moveid,int row, int col, int killid);
    bool canMove1(int moveid,int row, int col, int killid);
    bool canMove2(int moveid,int row, int col, int killid);
    bool canMove3(int moveid,int row, int col, int killid);
    bool canMove4(int moveid,int row, int col, int killid);
    bool canMove5(int moveid,int row, int col, int killid);
    bool canMove6(int moveid,int row, int col, int killid);
    bool canMove7(int moveid,int row, int col, int killid);

    void click(QPoint pt);
    virtual void click(int id,int row,int col);
    void moveStone(int moveid,int killid,int row,int col);
    void moveStone(int moveid,int row,int col);
    void saveStep(int moveid,int killid,int row,int col,QVector<Stop*> &steps);

    void killStone(int killid);

    void reliveStone(int killid);


};

#endif // WIDGET_H
