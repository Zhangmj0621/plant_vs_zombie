#include "wallnut.h"
#include<QPainter>
#include<QMovie>
#include<QDebug>

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
        qDebug()<<"the wallnut has died!";
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
    else if(hp+zombie->getatk()>200&&hp<=200)   //切换受伤1
    {
        qDebug()<<"you have turn to hit1";
        QMovie* movie1;
        if(!bufflist[0]) movie1=new QMovie(this->hit1);
        else movie1=new QMovie(this->violent_hit1);
        movie1->resized(QSize(50,50));
        //movie1->resized(QSize(50,50));
        movie1->start();
        label->setMovie(movie1);
        //label->show();
        delete movie;
        movie=movie1;
    }
    else if(hp+zombie->getatk()>100&&hp<=100)
    {
        qDebug()<<"you have turn to hit2";
        QMovie* movie1;
        if(!bufflist[0]) movie1=new QMovie(this->hit2);
        else movie1=new QMovie(this->violent_hit2);
        //movie1->resized(QSize(50,50));
        movie1->start();
        label->setMovie(movie1);
        //label->show();
        delete movie;
        movie=movie1;
    }
    parent->update();
}

void WallNut::changenormel(){
    QMovie* movie1;
    movie1=new QMovie(this->plantmovie);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}

void WallNut::changeviolent(){
    QMovie* movie1;
    movie1=new QMovie(this->violentpix);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}
