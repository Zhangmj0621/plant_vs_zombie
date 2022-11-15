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
    int x,y;
    int hp,atk;

    QString zombiemovie;
    QString attackmovie;
    QString diemovie;
    QString zombieloseheadmovie;
    QString zombieattackloseheadmovie;

    QMovie* movie;
    bool ifatk;
public:
    QLabel* label;
    int actacount;
    int now;

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


    void changeatk();
    void changewalk();
    virtual void attack();

    virtual void updateinfo();

signals:

};

#endif // ZOMBIE_H
