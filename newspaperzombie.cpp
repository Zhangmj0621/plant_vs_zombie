#include "newspaperzombie.h"

NewspaperZombie::NewspaperZombie(QWidget* parent,int x):Zombie(parent,x)
{
    this->hp=125;
    this->fullhp=125;
    this->zombiemovie=":/resource/images/Zombies/NewspaperZombie/HeadWalk0.gif";
    this->attackmovie=":/resource/images/Zombies/NewspaperZombie/HeadAttack0.gif";
    this->zombieloseheadmovie=":/resource/images/Zombies/NewspaperZombie/LostHeadWalk0.gif";
    this->zombieattackloseheadmovie=":/resource/images/Zombies/NewspaperZombie/LostHeadAttack0.gif";
    this->diemovie=":/resource/images/Zombies/NewspaperZombie/Die.gif";
    this->speed=2;
    this->num=1;
}
