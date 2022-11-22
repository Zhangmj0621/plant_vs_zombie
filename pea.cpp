#include "pea.h"
#include"globalconfig.h"
#include<QDebug>
#include"grass.h"

Pea::Pea(QWidget* parent,int atk,int x,int y):Bullet(parent,atk,x,y){
    this->flypix=":/resource/images/Pea/Pea.gif";
    label=new QLabel(this->parent);
    label->setFixedSize(50,50);
    movie=new QMovie(flypix);
    movie->start();
    label->setMovie(movie);
    label->move((grasscolpos[y]+grasscolpos[y-1])/2-5,grassrowpos[x-1]/3+grassrowpos[x]*2/3-90);
    qDebug()<<"the pea is constructed at x= "<<label->x()<<" y= "<<label->y();
    label->show();
}

int Pea::move(){
    if(y<=8)
    {
        label->move(label->x()+2,label->y());
        if(label->x()>=grasscolpos[y])
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
        label->move(label->x()+2,label->y());
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
