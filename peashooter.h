#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <QObject>
#include"globalconfig.h"
#include"plant.h"
#include<QPair>

class Peashooter :public Plant
{
    Q_OBJECT
public:
    Peashooter(QWidget* parent,int x,int y):Plant(parent,x,y){
        this->plantmovie=":/resource/images/Plants/Peashooter/Peashooter.gif";
        this->violentpix=":/";
        this->hp=150;
        this->bh=1;
        this->label=new QLabel(this->parent);
        this->movie=new QMovie(plantmovie);
        movie->start();
        label->setFixedSize(plantwidth,plantheight);
        label->setMovie(movie);
        label->move((grasscolpos[y]+grasscolpos[y-1])/2-15,grassrowpos[x-1]/3+grassrowpos[x]*2/3-90);
        label->show();
        this->actcount=3000;

    }
    void act() override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent *) override;

signals:

};

#endif // PEASHOOTER_H
