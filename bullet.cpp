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
}
