#ifndef PLANT_H
#define PLANT_H

#include <QWidget>
#include<QLabel>
#include<QMovie>
//#include"grass.h"

class Plant : public QWidget
{
    Q_OBJECT
    //放在哪块草地上

public:
    //Grass* grass;
    QWidget* parent;
    int x,y;    //第几行第几列
    int hp; //血量和攻击力
    int actcount;   //植物活动一次所需的时间，以s为单位
    int now;    //目前的毫秒数
    QString plantmovie;
    QLabel* label;
    QMovie* movie;

    Plant(QWidget* parent,int x,int y){
        this->parent=parent;
        this->x=x;
        this->y=y;
        this->now=0;
    }
    int getx(){return x;};
    int gety(){return y;};
    int gethp(){return hp;};
    int getactcount(){return actcount;};
    void setactcount(int num){actcount=num;};
    virtual void act()=0;   //植物活动，向日葵为释放太阳，豌豆射手为攻击
signals:

};

#endif // PLANT_H
