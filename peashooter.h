#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <QObject>
#include"globalconfig.h"
#include"plant.h"
#include<QPair>

class Peashooter :public Plant
{
    Q_OBJECT
    QString superpix;
public:
    Peashooter(QWidget* parent,int x,int y):Plant(parent,x,y){
        this->plantmovie=":/resource/images/Plants/Peashooter/Peashooter.gif";
        this->violentpix=":/resource/images/Plants/Repeater/Repeater.gif";
        this->coldpix=":/resource/images/Plants/SnowPea/SnowPea.gif";
        this->superpix=":/resource/images/Plants/GatlingPea/GatlingPea.gif";
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

    void changenormel() override;
    void changeviolent() override;

    void changecold() override;
    void changesuper() override;

signals:

};

#endif // PEASHOOTER_H
