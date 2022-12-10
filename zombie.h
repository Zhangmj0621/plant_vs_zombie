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

    QString zombiemovie;
    QString attackmovie;
    QString diemovie;
    QString zombieloseheadmovie;
    QString zombieattackloseheadmovie;


    bool ifatk;
public:
    int x,y;
    QLabel* label;
    QMovie* movie;
    int actacount;
    int movenow;
    int moveacount;
    int now;
    bool ifdie;

    bool ifcold;    //是否处于减速状态
    bool ifblood;   //是否处于流血状态

    Zombie(QWidget* parent,int x);

    int getx(){return x;};
    int gety(){return y;};
    void setx(int x){this->x=x;};
    void sety(int y){this->y=y;};
    int getatk(){return atk;};
    int getactacount(){return actacount;};
    int getnow(){return now;};
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
