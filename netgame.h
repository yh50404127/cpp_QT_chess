#ifndef NETGAME_H
#define NETGAME_H
#include "widget.h"
#include<QTcpServer>
#include<QTcpSocket>


class NetGame : public Widget
{
    Q_OBJECT
public:
    NetGame(bool server);

    bool _bSide;

    QTcpServer *_server;
    QTcpSocket *_socket;

    void click(int id,int row,int col);

public slots:
    void slotNewConnection();
    void slotRecv();


};

#endif // NETGAME_H
