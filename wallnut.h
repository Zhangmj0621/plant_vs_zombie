#ifndef WALLNUT_H
#define WALLNUT_H

#include <QObject>
#include"plant.h"
#include"globalconfig.h"

class WallNut : public Plant
{
    Q_OBJECT
    QString hit1;
    QString hit2;
    QString violent_hit1;
    QString violent_hit2;
public:
    WallNut(QWidget* parent,int x,int y):Plant(parent,x,y){
        this->hp=400;
        this->bh=2;
        this->hit1=":/resource/images/Plants/WallNut/Wallnut_cracked1.gif";
        this->hit2=":/resource/images/Plants/WallNut/Wallnut_cracked2.gif";
        this->plantmovie=":/resource/images/Plants/WallNut/WallNut.gif";
        this->violentpix=":/resource/images/Plants/TallNut/TallNut.gif";
        this->violent_hit1=":/resource/images/Plants/TallNut/TallnutCracked1.gif";
        this->violent_hit2=":/resource/images/Plants/TallNut/TallnutCracked2.gif";
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
    void hit(Zombie *zombie) override;
    void changenormel() override;
    void changeviolent() override;

signals:

};

#endif // WALLNUT_H
