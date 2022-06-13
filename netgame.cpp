#include "netgame.h"
#include<QDebug>
NetGame::NetGame(bool server)
{

    _server = nullptr;
    _socket = nullptr;

    if(server){
        _bSide = true;
        _server = new QTcpServer(this);
        _server->listen(QHostAddress::Any,9999);
        connect(_server,SIGNAL(newConnection()),
                this,SLOT(slotNewConnection()));
    }else {
        _bSide = false;
        _socket = new QTcpSocket(this);
        _socket->connectToHost(QHostAddress("127.0.0.1"),9999);
        connect(_socket,SIGNAL(readyRead()),
                this,SLOT(slotRecv()));

    }
}

void NetGame::click(int id, int row, int col)
{
//    if(_selectid == -1 && id != -1){
//        if(_s[id]._red != _bSide){
//            return;
//        }
//    }
    if(_bRedTrue != _bSide){
        return;
    }



    Widget::click(id,row,col);

    char buf[4];
    buf[0] = 2;
    buf[1] = row;
    buf[2] = col;
    buf[3] = id;
    _socket->write(buf,4);
}

void NetGame::slotNewConnection()
{

    if(_socket){return;}

    _socket = _server->nextPendingConnection();
    connect(_socket,SIGNAL(readyRead()),
            this,SLOT(slotRecv()));

    char buf[2];
    buf[0] = 1;//第1個字節固定是1
    buf[1] = 0;//1代表我執黑棋 0代表我執紅棋
    _socket->write(buf,2);


}

void NetGame::slotRecv()
{
    QByteArray ba = _socket->readAll();
    char cmd = ba[0];

    if(cmd == 2){
        int row = ba[1];
        int col = ba[2];
        int id  = ba[3];

        Widget::click(id,row,col);
    }



}
