#include "buffseed.h"
#include<QDebug>
#include<QMouseEvent>
#include"globalconfig.h"
#include<QPainter>

BuffSeed::BuffSeed(QWidget *parent) : QWidget(parent)
{

}

BuffSeed::BuffSeed(QString name,int num){
    this->plantname=name;
    this->num=num;
    this->plantseedpix=QString(":/resource/images/Seed/%1.png").arg(name);
    qDebug()<<this->plantseedpix;

}

void BuffSeed::mousePressEvent(QMouseEvent *ev){
      //emit this->clickSeed();
    if(ev->button()==Qt::LeftButton)
    {
        QString str=QString("you have press the seed %1").arg(seedname[num-1]);
        qDebug()<<str;
        emit this->clickSeed(num);
    }
}

void BuffSeed::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,40,40,plantseedpix);
}
