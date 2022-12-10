#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include<QMovie>
#include<QLabel>

class Bullet : public QObject
{
    Q_OBJECT
protected:
    QWidget* parent;


    QString flypix;
    QString hitpix;


public:
    int x,y;    //  在那个草丛
    QLabel* label;
    QMovie* movie;
    int atk;

    bool ifcold;    //是否可以减速敌人
    bool ifblood;   //是否可以使敌人流血

    explicit Bullet(QObject *parent = nullptr);

    Bullet(QWidget* parent,int atk,int x,int y);

    virtual int move(){return 0;};   //返回0代表在同一块地上运动，返回1代表进入下一块草地，返回2代表移出边界

    virtual void changehit();

signals:
    void die();

};

#endif // BULLET_H
