#include "widget.h"
#include <QApplication>
#include "singlegame.h"
#include "netgame.h"
#include<QMessageBox>
#include"mydialog.h"
#include<QPushButton>
#include<QDialog>

/*
基礎象棋:
第1節   1.畫家類  2.滑鼠點擊事件  3.按鈕類
第2節   開始時用對話框選擇模式 遊戲父類->1人機  棋類  走棋類
                                   2雙人
                                   3網絡

第3節   畫棋盤 1.畫水平線 2.畫垂直線 3.畫九宮格
第4節   定義棋類 在棋盤上畫32個棋子 初始化棋子
第5節   點擊把座標轉成行列 判斷行列上有沒有棋子 選中棋子移動後判斷目的有沒有棋子 有的話就吃掉
第6節   總結以上
第7節   判斷棋子能不能走 1.看顏色是否相同 如果是就換顏色 寫每種棋的移動函數 然後再輪流走
第8節   其他棋子的走法規則

人工智慧:
第9節   走1步算法:寫一個人工智慧類 我方移動一步後換電腦移動一步
       移動函數:將每個電腦方的棋移動到每個位置存到容器裡 試著走一下 計算局面分 走局面分最好的一步

第10節  走2步算法:最小最大值算法 取出最底中的每個最小值再取出這之中的最大值 釋放step內存
第11節  走N步算法:把走2步擴展成走三步 然後用遞歸設定終止條件 用定時器讓電腦有思考時間 然後更新
第12節  最小最大值算法有優化方法 就是剪枝優化 如果找到一個最大值其他比較小的就不用計算了
第13節  最小最大值算法複習

網絡:
第14節  網絡連線 決定誰下紅棋誰下黑棋 發送點選位置 限制不能按對方的棋
第15節  安卓移植 需要配置環境 配好就可以移植了





*/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Mydialog dia;
    if(dia.exec() == QDialog::Accepted){


        if(dia._type == 1){
            Widget w;
            w.show();
            return a.exec();

        }else if (dia._type == 2) {
            SingleGame S;
            S.show();
            return a.exec();

        }else if (dia._type == 3) {
            NetGame N1(true);
            N1.show();
            return a.exec();

        }else if (dia._type == 4) {
            NetGame N2(false);
            N2.show();
            return a.exec();
        }

    }

    return 0;
}

