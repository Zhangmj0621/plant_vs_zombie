#ifndef SNOWPEA_H
#define SNOWPEA_H

#include <QObject>
#include"bullet.h"

class SnowPea : public Bullet
{
    Q_OBJECT
public:
    //explicit SnowPea(QObject *parent = nullptr);

    SnowPea(QWidget* parent,int atk,int x,int y);

    int move() override;


signals:

};

#endif // SNOWPEA_H
