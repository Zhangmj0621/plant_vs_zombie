#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include <QObject>
#include"plant.h"

class Peashooter :public Plant
{
    Q_OBJECT
public:
    Peashooter(Grass* grass,int x,int y):Plant(grass,x,y){
        this->plantmovie=":/resource/images/Plants/Peashooter/Peashooter.gif";
        this->hp=150;
    }

signals:

};

#endif // PEASHOOTER_H
