#include "pea.h"
#include"globalconfig.h"
#include<QDebug>
//#include"grass.h"

//大致Movie和label左右间隔8像素
//左侧间隔35，右侧间隔8
Pea::Pea(QWidget* parent,int atk,int x,int y):Bullet(parent,atk,x,y){
    this->flypix=":/resource/images/Pea/Pea.gif";
    this->hitpix=":/resource/images/Pea/PeaHit.gif";
    label=new QLabel(this->parent);
    label->setFixedSize(80,40);
    movie=new QMovie(flypix);
    movie->start();
    label->setMovie(movie);
    label->setScaledContents(true);
    label->show();
    //label->move((grasscolpos[y]+grasscolpos[y-1])/2-label->width()/2,grassrowpos[x-1]/3+grassrowpos[x]*2/3-70);
    label->move(grasscolpos[y]-label->width()+8,grassrowpos[x-1]/3+grassrowpos[x]*2/3-70);
    qDebug()<<label->width();
    //label->move(grasscolpos[y]-35,grassrowpos[x-1]/3+grassrowpos[x]*2/3-70);
    //label->move(parent->width()/2,80);
    qDebug()<<"the pea is constructed at x= "<<label->x()<<" y= "<<label->y();
}

int Pea::move(){
    if(y<=8)
    {
        label->move(label->x()+10,label->y());
        if(label->x()>=(grasscolpos[y]-label->width()+10))
        {
            qDebug()<<"the pea have enter the next grass,x= "<<label->x()<<" y= "<<label->y();
            y++;
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        label->move(label->x()+10,label->y());
        if(label->x()>=parent->width())
        {
            return 2;
        }
        else
        {
            return 0;
        }
    }
}
