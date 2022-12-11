#include "plant.h"

void Plant::hit(Zombie* zombie){
    if(hp>=zombie->getatk()) hp-=zombie->getatk();
    else hp=0;
    if(hp==0)//判断是否死亡
    {
        //植物死亡，涉及到一下方面
        //僵尸由临战状态变为继续行走
        //草坪状态更新
        //删除植物内存，包括指针等等
        emit this->die();   //告诉草坪去更新状态
        delete label;
        delete movie;   //删除额外申请空间
        for(int i=0;i<5;i++)
        {
            if(buffpoint[i]!=NULL)
            {
                delete buffpoint[i];
            }
        }
    }
}
