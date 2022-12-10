#ifndef FIREPEA_H
#define FIREPEA_H

#include <QObject>
#include"bullet.h"

class FirePea : public Bullet
{
    Q_OBJECT
public:
    //explicit FirePea(QObject *parent = nullptr);

    FirePea(QWidget* parent,int atk,int x,int y);

    int move() override;

signals:

};

#endif // FIREPEA_H
