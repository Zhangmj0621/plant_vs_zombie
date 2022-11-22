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

    QMovie* movie;
    QString flypix;
    QString hitpix;

    int x,y;    //  在那个草丛
public:
    QLabel* label;
    int atk;

    explicit Bullet(QObject *parent = nullptr);

    Bullet(QWidget* parent,int atk,int x,int y);

    virtual int move()=0;   //返回0代表在同一块地上运动，返回1代表进入下一块草地，返回2代表移出边界

signals:

};

#endif // BULLET_H
