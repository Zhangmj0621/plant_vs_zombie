#ifndef NEWSPAPERZOMBIE_H
#define NEWSPAPERZOMBIE_H

#include <QObject>
#include"zombie.h"

class NewspaperZombie : public Zombie
{
    Q_OBJECT
public:
    //explicit NewspaperZombie(QObject *parent = nullptr);

    NewspaperZombie(QWidget* parent,int x);

signals:

};

#endif // NEWSPAPERZOMBIE_H
