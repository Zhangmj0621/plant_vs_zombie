#include "plantseed.h"
#include<QDebug>
#include<QMouseEvent>
#include<QPainter>
#include"globalconfig.h"

PlantSeed::PlantSeed()
{
    num=0;
    plantname="";
    plantseedpix="";
}

PlantSeed::PlantSeed(QString name,int num){
    this->plantname=name;
    this->num=num;
    this->plantseedpix=QString(":/resource/images/Seed/%1.png").arg(name);
    qDebug()<<this->plantseedpix;

}

void PlantSeed::mousePressEvent(QMouseEvent *ev){
      //emit this->clickSeed();
    if(ev->button()==Qt::LeftButton)
    {
        QString str=QString("you have press the seed %1").arg(seedname[num-1]);
        qDebug()<<str;
        emit this->clickSeed(num);
    }
}

void PlantSeed::paintEvent(QPaintEvent *){
    QPainter painter(this);
    painter.drawPixmap(0,0,this->width(),this->height(),plantseedpix);
}
