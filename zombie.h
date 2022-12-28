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
    int num;    //僵尸编号，0为普通僵尸，1为报纸僵尸，2为跨栏僵尸,3为路障僵尸,4为铁桶僵尸
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
    bool iffast;    //是否可以跨栏
    bool ifinjump;  //是否在跳跃状态中
    int polelength;

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

    void changeatk();   //更换攻击形态
    void changewalk();  //更换走路形态
    void changedie();   //更换死亡形态
    void changedelete();    //更换消失形态
    virtual void changejump1(){};  //切换跳跃形态，仅对撑杆僵尸所留接口
    virtual void changejump2(){};
    void changenormalzombie();  //切换普通僵尸形态，对于路障和铁桶僵尸生效
    virtual void attack();

    virtual void updateinfo();


signals:
    void hit(int atk,bool ifcold,bool ifblood);
    void die();
};

#endif // ZOMBIE_H
