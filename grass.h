#ifndef GRASS_H
#define GRASS_H
#include<QMouseEvent>
#include<QLabel>

class Grass: public QLabel
{
    Q_OBJECT
    //行数和列数
    int row,col;
    //在主场景中的位置
    int x,y;
    //宽度高度
    int width,height;
public:
    Grass();
    Grass(int r,int c);

    int getx(){return x;};
    int gety(){return y;};
    int getwidth(){return width;};
    int getheight(){return height;};

    void mousePressEvent(QMouseEvent* ev);
signals:
    void rightclick();
};

#endif // GRASS_H
