#ifndef WALLNUT_H
#define WALLNUT_H

#include <QObject>
#include"plant.h"
#include"globalconfig.h"

class WallNut : public Plant
{
    Q_OBJECT
public:
    WallNut(QWidget* parent,int x,int y):Plant(parent,x,y){
        this->hp=400;
        this->plantmovie=":/resource/images/Plants/WallNut/WallNut.gif";
        this->label=new QLabel(this->parent);
        this->movie=new QMovie(plantmovie);
        movie->start();
        label->setFixedSize(plantwidth,plantheight);
        label->setMovie(movie);
        label->move((grasscolpos[y]+grasscolpos[y-1])/2-20,grassrowpos[x-1]/3+grassrowpos[x]*2/3-90);
        label->show();
        this->actcount=100000;
    }
    void act() override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent *) override;

signals:

};

#endif // WALLNUT_H
