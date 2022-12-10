#ifndef BUFF_H
#define BUFF_H

#include <QObject>
#include<QWidget>
#include<QLabel>
#include"globalconfig.h"

class Buff : public QWidget
{
    Q_OBJECT
public:
    QWidget* parent;
    int x,y;    //第几行第几列
    int num;    //是那种buff，初始化为0，1代表狂暴，2代表冰冻，3代表流血
    QString pix;    //buff图片显示
    int fw; //在buff栏的左边还是右边,左边为0，右边为1
    //QLabel* label;


    Buff(QWidget* parent,int x,int y,int num,int fw);

    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

signals:

    void die(int num);
};

#endif // BUFF_H
