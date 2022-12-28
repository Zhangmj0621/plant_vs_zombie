#include "polevaultingzombie.h"
#include<QTimer>

PoleVaultingZombie::PoleVaultingZombie(QWidget* parent,int x):Zombie(parent,x)
{
    this->hp=250;
    this->iffast=true;
    this->fullhp=250;
    this->zombiemovie=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieWalk.gif";
    this->attackmovie=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieAttack.gif";
    this->zombieloseheadmovie=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieLostHeadWalk.gif";
    this->zombieattackloseheadmovie=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieLostHeadAttack.gif";
    this->diemovie=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieDie.gif";
    this->fastwalkpix=":/resource/images/Zombies/PoleVaultingZombie/PoleZombie.gif";
    this->jumppix1=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieJump.gif";
    this->jumppix2=":/resource/images/Zombies/PoleVaultingZombie/PoleVaultingZombieJump2.gif";
    this->speed=2;
    this->num=2;
    this->polelength=100;
}

void PoleVaultingZombie::updateinfo()
{
    label=new QLabel(parent);
    movie=new QMovie(this->fastwalkpix);
    movie->resized(QSize(100,50));
    label->setFixedSize(300,200);

    movie->start();
    label->setMovie(movie);
    label->move(parent->width()+label->width(),grassrowpos[x-1]/3+grassrowpos[x]*2/3-160);
    label->show();

    backbloodlabel=new QLabel(parent);
    backbloodlabel->setFixedSize(80,20);
    bloodlabel=new QLabel(parent);
    bloodlabel->resize(76,16);
    backbloodlabel->move(parent->width()+label->width()+180,grassrowpos[x-1]/3+grassrowpos[x]*2/3-140);
    bloodlabel->move(parent->width()+label->width()+182,grassrowpos[x-1]/3+grassrowpos[x]*2/3-140+2);

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

void PoleVaultingZombie::changejump1()
{
    QMovie* movie1=new QMovie(this->jumppix1);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;

}

void PoleVaultingZombie::changejump2()
{
    QMovie* movie1=new QMovie(this->jumppix2);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;

}
