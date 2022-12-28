#ifndef BUCKETHEADZOMBIE_H
#define BUCKETHEADZOMBIE_H

#include <QObject>
#include "zombie.h"

class BucketheadZombie : public Zombie
{
    Q_OBJECT
public:
    //explicit BucketheadZombie(QObject *parent = nullptr);

    BucketheadZombie(QWidget* parent,int x);

signals:

};

#endif // BUCKETHEADZOMBIE_H
