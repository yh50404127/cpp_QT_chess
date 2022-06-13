#ifndef STOP_H
#define STOP_H


class Stop
{
public:
    Stop();

    int _colFrom;
    int _colTo;
    int _rowFrom;
    int _rowTo;
    int _moveid;
    int _killid;

    void init(){
        _colFrom=0;
        _colTo=0;
        _rowFrom=0;
        _rowTo=0;
        _moveid=20;
        _killid=-1;
    }
};

#endif // STOP_H
