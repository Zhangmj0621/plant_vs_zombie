#include "zombie.h"
#include"globalconfig.h"
#include<QTimer>
#include<QDebug>

Zombie::Zombie(QWidget* parent,int x)
{
    this->parent=parent;
    this->x=x;
    this->y=10;
    this->now=0;
    this->hp=250;
    this->fullhp=250;
    this->atk=50;
    this->now=0;
    this->ifdie=false;
    this->actacount=1000;
    this->zombiemovie=":/resource/images/Zombies/Zombie/Zombie.gif";
    this->attackmovie=":/resource/images/Zombies/Zombie/ZombieAttack.gif";
    this->zombieloseheadmovie=":/resource/images/Zombies/Zombie/ZombieLostHead.gif";
    this->zombieattackloseheadmovie=":/resource/images/Zombies/Zombie/ZombieLostHeadAttack.gif";
    this->diemovie=":/resource/images/Zombies/Zombie/ZombieDie.gif";
    this->ifatk=false;
    this->ifcold=false;
    this->ifblood=false;
    this->moveacount=1;
    this->movenow=0;
    this->bloodacount=7;
    this->bloodnow=0;
}

void Zombie::attack(){

}

void Zombie::updateinfo(){
    label=new QLabel(parent);
    movie=new QMovie(this->zombiemovie);
    movie->resized(QSize(50,50));
    label->setFixedSize(160,160);

    movie->start();
    label->setMovie(movie);
    label->move(parent->width()+label->width(),grassrowpos[x-1]/3+grassrowpos[x]*2/3-140);
    label->show();

    backbloodlabel=new QLabel(parent);
    backbloodlabel->setFixedSize(80,20);
    bloodlabel=new QLabel(parent);
    bloodlabel->resize(76,16);
    backbloodlabel->move(parent->width()+label->width()+40,grassrowpos[x-1]/3+grassrowpos[x]*2/3-140);
    bloodlabel->move(parent->width()+label->width()+42,grassrowpos[x-1]/3+grassrowpos[x]*2/3-140+2);

    backbloodlabel->setStyleSheet("QLabel{background-color:rgb(255,255,255);}");
    bloodlabel->setStyleSheet("QLabel{background-color:rgb(255,0,0);}");

    backbloodlabel->show();
    bloodlabel->show();

    coldbufflabel=new QLabel(parent);
    coldbufflabel->setPixmap(QPixmap(":/resource/images/Seed/cold2.png"));
    coldbufflabel->setFixedSize(20,20);
    coldbufflabel->move(backbloodlabel->x()+backbloodlabel->width()+5,backbloodlabel->y());
    coldbufflabel->hide();

    bloodbufflabel=new QLabel(parent);
    bloodbufflabel->setPixmap(QPixmap(":/resource/images/Seed/blood2.png"));
    bloodbufflabel->setFixedSize(20,20);
    bloodbufflabel->move(backbloodlabel->x()-25,backbloodlabel->y());
    bloodbufflabel->hide();
}

void Zombie::changeatk()
{
    QMovie* movie1=new QMovie(this->attackmovie);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}

void Zombie::changewalk()
{
    QMovie* movie1=new QMovie(this->zombiemovie);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}

void Zombie::changedie(){
    QMovie* movie1;
    if(ifatk) movie1=new QMovie(this->zombieattackloseheadmovie);
    else movie1=new QMovie(this->zombieloseheadmovie);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}

void Zombie::changedelete()
{
    QMovie* movie1;
    movie1=new QMovie(this->diemovie);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}

void Zombie::behit(int atk,bool ifcold,bool ifblood){
    qDebug()<<"the zombie have be hit";
    if(hp>atk)
    {
        hp-=atk;
        if(!this->ifcold&&ifcold) this->coldbufflabel->show();
        if(!this->ifblood&&ifblood) this->bloodbufflabel->show();
        if(!this->ifcold) this->ifcold=ifcold;
        if(!this->ifblood) this->ifblood=ifblood;
        if(ifcold) this->moveacount=2;
    }
    else if(hp!=0)
    {
        hp=0;
        if(!this->ifcold&&ifcold) this->coldbufflabel->show();
        if(!this->ifcold) this->ifcold=ifcold;
        if(ifcold) this->moveacount=2;
        changedie();
        ifdie=true;
        QTimer::singleShot(2000,this,[=](){
            emit this->die();
        });
    }
}
