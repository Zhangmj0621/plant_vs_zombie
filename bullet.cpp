#include "bullet.h"

Bullet::Bullet(QObject *parent) : QObject(parent)
{

}

Bullet::Bullet(QWidget* parent,int atk,int x,int y){
    hitpix=":/resource/images/Pea/PeaHit.gif";
    this->parent=parent;
    this->atk=atk;
    this->x=x;
    this->y=y;
    this->ifcold=false;
    this->ifblood=false;
}

void Bullet::changehit(){
    QMovie* movie1=new QMovie(this->hitpix);
    movie1->resized(QSize(200,200));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}
