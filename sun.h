#ifndef SUN_H
#define SUN_H

#include <QWidget>
#include<QPushButton>
#include<QMovie>
#include"globalconfig.h"

class Sun : public QObject
{
    Q_OBJECT

public:
    int type;
    QPushButton* btn;
    QWidget* parent;
    QString pix;
    int x,y;//最终阳光所在的格子
    //explicit Sun(QWidget *parent = nullptr);
    Sun(QWidget* parent,int type,int x,int y);



signals:

};

#endif // SUN_H
