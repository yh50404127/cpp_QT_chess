#ifndef STONE_H
#define STONE_H

#include <QString>

class stone
{
public:
    stone();

    enum TYPE{JIANG,CHE,PAO,MA,BING,SHI,XIANG};

    int _row;
    int _col;
    TYPE _type;

    int _id;
    int _dead;
    int _red;


    void init(int id){
        _id = id;
        _dead = false;
        _red = id<16; //0-15是紅棋  16-31是黑棋

        struct{
            int row,col;
            stone::TYPE type;
        }pos[16] = {
            {0,0,stone::CHE},
            {0,1,stone::MA},
            {0,2,stone::XIANG},
            {0,3,stone::SHI},
            {0,4,stone::JIANG},
            {0,5,stone::SHI},
            {0,6,stone::XIANG},
            {0,7,stone::MA},
            {0,8,stone::CHE},

            {2,1,stone::PAO},
            {2,7,stone::PAO},
            {3,0,stone::BING},
            {3,2,stone::BING},
            {3,4,stone::BING},
            {3,6,stone::BING},
            {3,8,stone::BING},

        };

        if(_id<16){
            _row = pos[id].row;
            _col = pos[id].col;
            _type = pos[id].type;
        }else{
            _row = 9-pos[id-16].row;
            _col = 8-pos[id-16].col;
            _type = pos[id-16].type;

        }

    }

    QString getText(){
        switch (this->_type) {
            case CHE:
                return "車";
            case MA:
                return "馬";
            case PAO:
                return "炮";
            case BING:
                return "兵";
            case JIANG:
                return "將";
            case SHI:
                return "士";
            case XIANG:
                return "相";
            }
        return "錯誤";
    }

};

#endif // STONE_H
