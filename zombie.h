#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QObject>
#include<QLabel>
#include<QMovie>
#include"globalconfig.h"

class Zombie : public QObject
{
    Q_OBJECT
protected:
    QWidget* parent;

    int hp,atk;

    int fullhp; //记录满血

    QString zombiemovie;
    QString attackmovie;
    QString diemovie;
    QString zombieloseheadmovie;
    QString zombieattackloseheadmovie;


    bool ifatk;
public:
    int x,y;
    QLabel* label;
    QLabel* backbloodlabel;
    QLabel* bloodlabel;
    //冰冻buff和流血buff
    QLabel* coldbufflabel;
    QLabel* bloodbufflabel;
    QMovie* movie;
    //执行吃操作和移动操作所用的帧数
    int actacount;
    int movenow;
    int moveacount;
    int now;
    //流血所用的帧数和经历的帧数
    //设定为一秒钟留5滴血，相当于30帧里7个循环执行扣1滴血，即bloodacount=7，进入流血状态状态永恒
    int bloodnow;
    int bloodacount;
    bool ifdie;

    int speed;  //走路速度，普通僵尸设定为1

    bool ifcold;    //是否处于减速状态
    bool ifblood;   //是否处于流血状态

    Zombie(QWidget* parent,int x);

    int getx(){return x;};
    int gety(){return y;};
    void setx(int x){this->x=x;};
    void sety(int y){this->y=y;};
    int getatk(){return atk;};
    void setatk(int newatk){atk=newatk;}
    int getactacount(){return actacount;};
    int getnow(){return now;};
    int gethp(){return hp;}
    int getfullhp(){return fullhp;}
    void setnow(int _now){now=_now;};
    bool ifheatk(){return ifatk;};
    void setifatk(bool newif){ifatk=newif;};


    virtual void behit(int atk,bool ifcold,bool ifblood);

    void changeatk();
    void changewalk();
    void changedie();
    void changedelete();
    virtual void attack();

    virtual void updateinfo();

signals:
    void hit(int atk,bool ifcold,bool ifblood);
    void die();
};

#endif // ZOMBIE_H
