#ifndef PLANT_H
#define PLANT_H

#include <QWidget>
#include<QLabel>
#include<QMovie>
#include"zombie.h"
//#include"grass.h"
#include"buff.h"

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
    int bh; //0为向日葵，1为豌豆射手，2为坚果，初始赋-1
    QString plantmovie;
    QLabel* label;
    QMovie* movie;

    int buffstate;    //目前所持有的buff栏状态，0为两个都没有，1为左有buff，2为右有buff，3为buff已满
    bool bufflist[5];
    Buff* buffpoint[5];

    //设置加倍和冰冻两种不同buff下的图片路径
    //设计有加倍状态的时候优先显示加倍
    QString violentpix;
    QString coldpix;


    Plant(QWidget* parent,int x,int y){
        this->parent=parent;
        this->x=x;
        this->y=y;
        this->now=0;
        this->bh=-1;
        this->buffstate=0;
        for(int i=0;i<5;i++)
        {
            bufflist[i]=false;
            buffpoint[i]=NULL;
        }
    }
    int getx(){return x;};
    int gety(){return y;};
    int gethp(){return hp;};
    int getactcount(){return actcount;};
    void setactcount(int num){actcount=num;};
    virtual void hit(Zombie* zombie);   //被僵尸攻击
    virtual void act(){};   //植物活动，向日葵为释放太阳，豌豆射手为攻击
    virtual void changelight(){};
    virtual void changegeneral(){};
signals:
    void die();
};

#endif // PLANT_H
