#include "widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(800,700);

    for(int i = 0;i<32;i++){
        _s[i].init(i);
    }

    _selectid = -1;

    _bRedTrue = true;

    _victory = false;

    lab.setParent(this);
    lab.setText("紅方進攻");
    lab.move(600,270);
    lab.setFont(QFont("標楷體",20));

}

Widget::~Widget()
{

}

QPoint Widget::center(int row, int col)
{
    QPoint ret;
    ret.rx() = (col+1)*_r*2;
    ret.ry() = (row+1)*_r*2;
    return ret;

}

QPoint Widget::center(int id)
{
    return center(_s[id]._row, _s[id]._col);
}

void Widget::paintEvent(QPaintEvent *)
{



    QPainter painter(this);
    int d = 60;
    _r = d/2;

    //畫水平線
    for(int i = 1; i<=10; i++){
        painter.drawLine(QPoint(d,i*d),QPoint(9*d,i*d));
    }

    //畫垂直線
    for(int i = 1; i<=9; i++){
        if(i == 1 || i == 9){
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,10*d));
        }else{
            painter.drawLine(QPoint(i*d,d),QPoint(i*d,5*d));
            painter.drawLine(QPoint(i*d,6*d),QPoint(i*d,10*d));
        }
    }

    //畫九宮格
    painter.drawLine(QPoint(4*d,1*d),QPoint(6*d,3*d));
    painter.drawLine(QPoint(6*d,1*d),QPoint(4*d,3*d));

    painter.drawLine(QPoint(4*d,8*d),QPoint(6*d,10*d));
    painter.drawLine(QPoint(6*d,8*d),QPoint(4*d,10*d));

    //畫32個棋子
    for(int i = 0;i<32;i++){
        drawStone(painter,i);
    }

    if(_bRedTrue == true){
        lab.setText("紅方進攻");
    }else{
        lab.setText("黑方進攻");
    }

    if(!_victory){

        if(_s[4]._dead){
            end = true;
            _victory = true;
            QMessageBox::information(this,"勝利提示","黑棋勝利",QMessageBox::Ok);

        }
        if(_s[20]._dead){
            end = true;
            _victory = true;
            QMessageBox::information(this,"勝利提示","紅棋勝利",QMessageBox::Ok);

        }

    }


}

void Widget::drawStone(QPainter &painter, int id)
{

    if(_s[id]._dead)
        return;



    QPoint c=center(id);
    QRect rect=QRect(c.x()-_r,c.y()-_r,_r*2,_r*2);

    if(id == _selectid)
        painter.setBrush(QColor(Qt::yellow));
    else
        painter.setBrush(QBrush(QColor(135,206,235)));

    if(_s[id]._red)
        painter.setPen(QColor(Qt::red));
    else
        painter.setPen(QColor(Qt::black));

    painter.drawEllipse(center(id),_r,_r);

    painter.setFont(QFont("標楷體",_r,700));
    painter.drawText(rect,_s[id].getText(),QTextOption(Qt::AlignCenter));

}

void Widget::mouseReleaseEvent(QMouseEvent *ev)
{

    if(ev->button() != Qt::LeftButton){
        return;
    }

    QPoint pt = ev->pos();
    click(pt);

}

bool Widget::getRowCol(QPoint pt, int &row, int &col)
{
    for(row=0;row<=9;row++){
        for(col=0;col<=8;col++){
            QPoint c = center(row,col);
            int dx = c.x()-pt.x();
            int dy = c.y()-pt.y();
            int dist = dx*dx + dy*dy;
            if(dist<_r*_r){return true;}

        }
    }
    return false;
}

int Widget::getStoneId(int fRow, int fCol)
{
    for (int i=0;i<32;i++) {
        if(_s[i]._col == fCol && _s[i]._row == fRow && _s[i]._dead == false){
            return i;
        }
    }

    return -1;

}

int Widget::getStoneCountAtLIne(int row1, int col1, int row2, int col2)
{
    int ret = 0;
    if(row1 != row2 && col1 != col2){
        return -1;
    }
    if(row1 == row2 && col1 == col2){
        return -1;
    }

    if(row1 == row2){
        int min = col1 < col2 ? col1 : col2;
        int max = col1 < col2 ? col2 : col1;
        for (int col = min+1;col<max;col++) {
            if(getStoneId(row1, col) != -1){
                ret++;
            }

        }
    }else{
        int min = row1 < row2 ? row1 : row2;
        int max = row1 < row2 ? row2 : row1;
        for (int row = min+1;row<max;row++) {
            if(getStoneId(row, col1) != -1){
                ret++;
            }

        }

    }
    return ret;


}

bool Widget::canMove(int moveid, int row, int col, int killid)
{
    if(_s[moveid]._red == _s[killid]._red){//顏色相同換顏色
        _selectid = killid;
        update();
        return false;
    }

    switch (_s[moveid]._type) {

    case stone::JIANG:
        return canMove1(moveid,row,col,killid);

    case stone::SHI:
        return canMove2(moveid,row,col,killid);

    case stone::XIANG:
        return canMove3(moveid,row,col,killid);

    case stone::CHE:
        return canMove4(moveid,row,col,killid);

    case stone::MA:
        return canMove5(moveid,row,col,killid);

    case stone::PAO:
        return canMove6(moveid,row,col,killid);

    case stone::BING:
        return canMove7(moveid,row,col,killid);



    }

    return true;




}

bool Widget::canMove1(int moveid, int row, int col, int)
{
    if(_s[moveid]._red){
        if(row > 2)return false;
    }else{
        if(row < 7)return false;
    }

    if(col < 3)return false;
    if(col > 5)return false;

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d == 1 || d == 10){
        return true;
    }

    return false;
}

bool Widget::canMove2(int moveid, int row, int col, int )
{
    if(_s[moveid]._red){
        if(row > 2)return false;
    }else{
        if(row < 7)return false;
    }

    if(col < 3)return false;
    if(col > 5)return false;

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d == 11){
        return true;
    }

    return false;

}

bool Widget::canMove3(int moveid, int row, int col, int )
{

    //qDebug()<<"_s,row:"<<_s[moveid]._row<<"_s,col:"<<_s[moveid]._col;

    if(_s[moveid]._red){
        if(row > 4)return false;
    }else{
        if(row < 5)return false;
    }

    int rEye = (row + _s[moveid]._row) / 2;
    int cEye = (col + _s[moveid]._col) / 2;

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);

    if(getStoneId(rEye,cEye) == -1 && d == 22){
        return true;
    }

    return false;
}

bool Widget::canMove4(int moveid, int row, int col, int )
{

    int ret = getStoneCountAtLIne(_s[moveid]._row, _s[moveid]._col, row, col);


    if(ret != 0){
        return false;
    }

    return true;
}

bool Widget::canMove5(int moveid, int row, int col, int )
{


    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);
    if(d != 12 && d != 21){
        return false;
    }

    if(d == 12){
        if(getStoneId(_s[moveid]._row,(col+_s[moveid]._col)/2) != -1){
            return false;
        }
    }else {
        if(getStoneId((row+_s[moveid]._row)/2,_s[moveid]._col) != -1){
            return false;
        }
    }

    return true;
}

bool Widget::canMove6(int moveid, int row, int col, int killid)
{

    int ret = getStoneCountAtLIne(row, col, _s[moveid]._row, _s[moveid]._col);

    if(killid != -1){
        if(ret == 1){
            return true;
        }
    }else{
        if(ret == 0){
            return true;
        }

    }

    return false;

}

bool Widget::canMove7(int moveid, int row, int col, int )
{

    int dr = _s[moveid]._row - row;
    int dc = _s[moveid]._col - col;
    int d = abs(dr)*10 + abs(dc);

    if(_s[moveid]._red){

        if(row > 4){
            if(d == 1 || d == 10){
                return true;
            }
        }else if(dr == -1 && dc == 0){
            return true;
        }
    }else{

        if(row < 5){
            if(d == 1 || d == 10){
                return true;
            }
        }else if(dr == 1 && dc == 0){
            return true;
        }
    }


    return false;
}

void Widget::click(QPoint pt)
{

    int row,col;
    bool bRet = getRowCol(pt,row,col);
    if(bRet == false){return;}

    int id = getStoneId(row,col);
    click(id,row,col);



}

void Widget::click(int id, int row, int col)
{

//    int i;
    int clickid = -1;
//    for(i=0;i<32;i++){
//        if(_s[i]._row==row && _s[i]._col==col && _s[i]._dead==false)
//            break;
//    }

    if(id<32){
        clickid = id;
    }


    if(_selectid == -1){

        if(clickid != -1){

            if(_bRedTrue == _s[clickid]._red){
                _selectid = clickid;
                update();
            }
        }

    }else{

        if(canMove(_selectid,row,col,clickid)){/*判斷是否能走棋*/

        /*走棋代碼*/
            moveStone(_selectid,clickid,row,col);
            _selectid = -1;
            update();
        }
    }

}

void Widget::moveStone(int moveid, int killid, int row, int col)
{
    _s[moveid]._row = row;
    _s[moveid]._col = col;
    if(killid != -1){
        _s[killid]._dead = true;
    }

    _bRedTrue = !_bRedTrue;

}

void Widget::moveStone(int moveid, int row, int col)
{

    int killid = getStoneId(row,col);
    if(killid != -1){
        _s[killid]._dead = true;
    }

    _s[moveid]._row = row;
    _s[moveid]._col = col;

    //_bRedTrue = !_bRedTrue;

}

void Widget::saveStep(int moveid, int killid, int row, int col, QVector<Stop *> &steps)
{

    Stop* step = new Stop;
    step->_colFrom = _s[moveid]._col;
    step->_colTo = col;
    step->_rowFrom = _s[moveid]._row;
    step->_rowTo = row;
    step->_moveid = moveid;
    step->_killid = killid;

    steps.append(step);



}

void Widget::killStone(int killid)
{
    if(killid == -1){return;}

    _s[killid]._dead = true;

}

void Widget::reliveStone(int killid)
{
    if(killid == -1){return;}

    _s[killid]._dead = false;
}
