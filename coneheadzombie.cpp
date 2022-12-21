#include "coneheadzombie.h"

ConeheadZombie::ConeheadZombie(QWidget* parent,int x):Zombie(parent,x)
{
    this->hp=400;
    this->fullhp=400;
    this->zombiemovie=":/resource/images/Zombies/ConeheadZombie/ConeheadZombie.gif";
    this->attackmovie=":/resource/images/Zombies/ConeheadZombie/ConeheadZombieAttack.gif";
    this->speed=1;
    this->num=3;
}
