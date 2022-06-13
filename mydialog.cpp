#include "mydialog.h"
#include<QPushButton>

Mydialog::Mydialog()
{

    this->setFixedSize(200,250);
    QPushButton *but1 = new QPushButton("雙人對戰",this);
    but1->move(55,30);
    QPushButton *but2 = new QPushButton("人機對戰",this);
    but2->move(55,80);
    QPushButton *but3 = new QPushButton("網路對戰(伺服端)",this);
    but3->move(40,130);
    QPushButton *but4 = new QPushButton("網絡對戰(客戶端)",this);
    but4->move(40,170);

    connect(but1,&QPushButton::clicked,this,[this](){
        _type = 1;
        accept();
    });

    connect(but2,&QPushButton::clicked,this,[this](){
        _type = 2;
        accept();
    });

    connect(but3,&QPushButton::clicked,this,[this](){
        _type = 3;
        accept();
    });

    connect(but4,&QPushButton::clicked,this,[this](){
        _type = 4;
        accept();
    });

}
