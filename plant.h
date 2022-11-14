#ifndef PLANT_H
#define PLANT_H

#include <QLabel>
#include<grass.h>

class Plant : public QLabel
{
    Q_OBJECT
    //放在哪块草地上

public:
    Grass* grass;
    int x,y;    //第几行第几列
    int hp; //血量和攻击力
    int sunneed;    //需要的阳光
    int actcount;   //植物活动一次所需的时间，以s为单位
    QString plantmovie;

    Plant(Grass* grass,int x,int y){
        this->grass=grass;
        this->x=x;
        this->y=y;
    }
    virtual void act()=0;   //植物活动，向日葵为释放太阳，豌豆射手为攻击
signals:

};

#endif // PLANT_H
