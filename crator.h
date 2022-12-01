#ifndef CRATOR_H
#define CRATOR_H

#include <QObject>
#include"globalconfig.h"
#include"plant.h"
#include<QPair>

class Crator : public Plant
{
    Q_OBJECT
public:
    Crator(QWidget* parent,int x,int y):Plant(parent,x,y){
        this->plantmovie=":/resource/images/interface/crater1.png";
        //this->hp=150;
        //this->bh=1;
        this->label=new QLabel(this->parent);
        this->movie=new QMovie(plantmovie);
        movie->start();
        label->setFixedSize(plantwidth,plantheight);
        label->setMovie(movie);
        label->move((grasscolpos[y]+grasscolpos[y-1])/2-35,grassrowpos[x-1]/3+grassrowpos[x]*2/3-90);
        label->show();
        this->actcount=0;
    }

signals:

};

#endif // CRATOR_H
