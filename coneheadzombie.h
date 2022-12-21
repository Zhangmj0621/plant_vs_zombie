#ifndef CONEHEADZOMBIE_H
#define CONEHEADZOMBIE_H

#include <QObject>
#include "zombie.h"

class ConeheadZombie : public Zombie
{
    Q_OBJECT
public:
    //explicit ConeheadZombie(QObject *parent = nullptr);

    ConeheadZombie(QWidget* parent,int x);


signals:

};

#endif // CONEHEADZOMBIE_H
