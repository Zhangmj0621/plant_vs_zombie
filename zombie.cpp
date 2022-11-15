#include "zombie.h"
#include"globalconfig.h"

Zombie::Zombie(QWidget* parent,int x)
{
    this->parent=parent;
    this->x=x;
    this->y=10;
    this->now=0;
    this->hp=400;
    this->atk=50;
    this->now=0;
    this->actacount=1000;
    this->zombiemovie=":/resource/images/Zombies/Zombie/Zombie.gif";
    this->attackmovie=":/resource/images/Zombies/Zombie/ZombieAttack.gif";
    this->zombieloseheadmovie=":/resource/images/Zombies/Zombie/ZombieLostHead.gif";
    this->zombieattackloseheadmovie=":/resource/images/Zombies/Zombie/ZombieLostHeadAttack.gif";
    this->diemovie=":/resource/images/Zombies/Zombie/ZombieDie.gif";
    this->ifatk=false;
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
