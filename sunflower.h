#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include <QObject>
#include"plant.h"
#include"globalconfig.h"

class SunFlower : public Plant
{
    Q_OBJECT
    QString lightmovie;
    QString violentlightmovie;
public:
    SunFlower(QWidget* parent,int x,int y):Plant(parent,x,y)
    {
        this->lightmovie=":/resource/images/Plants/SunFlower/SunFlower2.gif";
        this->hp=100;
        this->bh=0;
        this->plantmovie=":/resource/images/Plants/SunFlower/SunFlower1.gif";
        this->violentpix=":/resource/images/Plants/TwinSunflower/TwinSunflower1.gif";
        this->violentlightmovie=":/resource/images/Plants/TwinSunflower/TwinSunflower2.gif";
        this->label=new QLabel(this->parent);
        this->movie=new QMovie(plantmovie);
        movie->start();
        label->setFixedSize(plantwidth,plantheight);
        label->setMovie(movie);
        label->move((grasscolpos[y]+grasscolpos[y-1])/2-15,grassrowpos[x-1]/3+grassrowpos[x]*2/3-90);
        label->show();
        this->actcount=10000;

    }
    void act() override;
    void mousePressEvent(QMouseEvent*) override;
    void paintEvent(QPaintEvent *) override;
    void changelight() override;
    void changegeneral() override;
    void changenormel() override;
    void changeviolent() override;

signals:

};

#endif // SUNFLOWER_H
