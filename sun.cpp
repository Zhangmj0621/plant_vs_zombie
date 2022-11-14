#include "sun.h"
#include<QPainter>

Sun::Sun(QWidget* parent,int type,int x,int y)
{
    this->parent=parent;
    this->type=type;
    this->x=x;
    this->y=y;
    pix=":/resource/images/interface/Sun.gif";

    btn=new QPushButton(parent);
    btn->setFixedSize(plantwidth,plantheight);
    btn->setIcon(QIcon(pix));
    btn->setIconSize(QSize(btn->width(),btn->height()));

}
