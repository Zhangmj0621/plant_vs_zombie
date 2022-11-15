#ifndef GRASS_H
#define GRASS_H
#include<QMouseEvent>
#include<QLabel>
#include"plant.h"
#include"sun.h"
#include<QVector>
#include"zombie.h"

class Grass: public QLabel
{
    Q_OBJECT
    //行数和列数
    int row,col;
    //在主场景中的位置
    int x,y;
    //宽度高度
    int width,height;
    //保存存储的植物信息

    bool iffree;
public:
    Plant* plant;
    QVector<Zombie*> zombielist;

    Grass();
    Grass(int r,int c);

    int getx(){return x;};
    int gety(){return y;};
    int getwidth(){return width;};
    int getheight(){return height;};
    Plant* getplant(){return plant;};
    bool getiffree(){return iffree;};
    void setiffree(bool zhi){
        iffree=zhi;
    }

    void mousePressEvent(QMouseEvent* ev);
signals:
    void leftclick(int i,int j);
    void rightclick();
};

#endif // GRASS_H
