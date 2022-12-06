#include "buff.h"
#include<QDebug>
#include<QMouseEvent>
#include"globalconfig.h"
#include<QPainter>

Buff::Buff(QWidget* parent,int x,int y,int num,int fw):parent(parent){
    this->x=x;
    this->y=y;
    this->num=num;
    this->fw=fw;
    pix=QString(":/resource/images/Seed/%1.png").arg(seedname_buff[num-1]);
}

void Buff::mousePressEvent(QMouseEvent *ev){
      //emit this->clickSeed();
    if(ev->button()==Qt::LeftButton)
    {
        QString str=QString("you have press the seed %1").arg(seedname_buff[num-1]);
        qDebug()<<str;
    }
}

void Buff::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,40,40,pix);
}
