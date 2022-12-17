#include "shovel.h"
#include<QPainter>
#include<QMouseEvent>

Shovel::Shovel()
{
    pix=":/resource/images/interface/Shovel.png";
}

void Shovel::mousePressEvent(QMouseEvent *ev){
      //emit this->clickSeed();
    if(ev->button()==Qt::LeftButton)
    {
        emit this->clickshovel();
    }
}

void Shovel::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
}
