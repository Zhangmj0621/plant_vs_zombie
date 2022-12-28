#include "bucketheadzombie.h"

BucketheadZombie::BucketheadZombie(QWidget* parent,int x):Zombie(parent,x)
{
    this->hp=600;
    this->fullhp=600;
    this->zombiemovie=":/resource/images/Zombies/BucketheadZombie/BucketheadZombie.gif";
    this->attackmovie=":/resource/images/Zombies/BucketheadZombie/BucketheadZombieAttack.gif";
    this->speed=1;
    this->num=4;
}
