#include "wallnut.h"
#include<QPainter>
#include<QMovie>

void WallNut::act(){

}

void WallNut::mousePressEvent(QMouseEvent*){

}

void WallNut::paintEvent(QPaintEvent *){

}

void WallNut::hit(Zombie* zombie){
    if(hp>=zombie->getatk()) hp-=zombie->getatk();
    else hp=0;
    if(hp==0)//判断是否死亡
    {
        //植物死亡，涉及到一下方面
        //僵尸由临战状态变为继续行走
        //草坪状态更新
        //删除植物内存，包括指针等等
        zombie->setifatk(false);
        emit this->die();   //告诉草坪去更新状态
        delete label;
        delete movie;   //删除额外申请空间
    }
    else if(hp+zombie->getatk()>200&&hp<=200)   //切换受伤1
    {
        QMovie* movie1=new QMovie(this->hit1);
        //movie1->resized(QSize(50,50));
        movie1->start();
        label->setMovie(movie1);
        //label->show();
        delete movie;
        movie=movie1;
    }
    else if(hp+zombie->getatk()>100&&hp<=100)
    {
        QMovie* movie1=new QMovie(this->hit2);
        //movie1->resized(QSize(50,50));
        movie1->start();
        label->setMovie(movie1);
        //label->show();
        delete movie;
        movie=movie1;
    }
}
