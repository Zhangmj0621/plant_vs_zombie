#ifndef POLEVAULTINGZOMBIE_H
#define POLEVAULTINGZOMBIE_H

#include <QObject>
#include <zombie.h>

class PoleVaultingZombie : public Zombie
{
    Q_OBJECT
    QString fastwalkpix;
    QString jumppix1;
    QString jumppix2;
public:
    //explicit PoleVaultingZombie(QObject *parent = nullptr);


    PoleVaultingZombie(QWidget* parent,int x);

    void updateinfo() override;

    void changejump1() override;
    void changejump2() override;

signals:

};

#endif // POLEVAULTINGZOMBIE_H
