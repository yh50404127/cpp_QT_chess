#ifndef MYDIALOG_H
#define MYDIALOG_H
#include<QDialog>


class Mydialog : public QDialog
{
    Q_OBJECT
public:
    Mydialog();

    int _type;


    QPushButton *but1;
    QPushButton *but2;
    QPushButton *but3;
    QPushButton *but4;

};

#endif // MYDIALOG_H
