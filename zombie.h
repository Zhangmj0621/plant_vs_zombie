#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <QObject>
#include<QLabel>
#include<QMovie>
#include"globalconfig.h"

class Zombie : public QObject
{
    Q_OBJECT
    QWidget* parent;
    int x,y;
    int hp,atk;
    int actacount;
    int now;
    QString zombiemovie;
    QString attackmovie;
    QLabel* label;
    QMovie* movie;
public:
    Zombie(QWidget* parent,int x);

signals:

};

#endif // ZOMBIE_H
