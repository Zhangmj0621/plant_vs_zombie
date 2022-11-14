#include "grass.h"
#include"globalconfig.h"
#include<QDebug>

Grass::Grass()
{
    row=0;
    col=0;
    x=-1;
    y=-1;
    width=0;
    height=0;
}

Grass::Grass(int r,int c)
{
    row=r;
    col=c;
    x=grasscolpos[c-1];
    y=grassrowpos[r-1];
    width=grasscolpos[c]-grasscolpos[c-1];
    height=grassrowpos[r]-grassrowpos[r-1];
    qDebug()<<row<<" "<<col<<" "<<x<<""<<y<<" "<<width<<" "<<height;
    plant=NULL;
    iffree=true;
}

void Grass::mousePressEvent(QMouseEvent* ev)
{
    if(ev->button()==Qt::LeftButton)
    {
        QString str =QString("you have press the grass at row= %1 col=%2").arg(row).arg(col);
        qDebug()<<str;
        emit this->leftclick(row,col);
    }
    else if(ev->button()==Qt::RightButton)
    {
        emit this->rightclick();
    }
}
