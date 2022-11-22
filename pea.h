#ifndef PEA_H
#define PEA_H

#include <QObject>
#include"bullet.h"

class Pea : public Bullet
{
    Q_OBJECT
public:
    //explicit Pea(QObject *parent = nullptr);

    Pea(QWidget* parent,int atk,int x,int y);

    int move() override;

signals:

};

#endif // PEA_H
