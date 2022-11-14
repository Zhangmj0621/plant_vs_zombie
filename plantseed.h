#ifndef PLANTSEED_H
#define PLANTSEED_H

#include <QWidget>

class PlantSeed :public QWidget
{
    Q_OBJECT
    QString plantname;
    QString plantseedpix;
    int num;    //第几个卡槽，在move时使用
    int percentge;  //冷却百分比

public:
    PlantSeed();
    PlantSeed(QString name,int num);

    int getnum(){return num;};

    void mousePressEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *) override;
signals:
    void clickSeed(int num);
};

#endif // PLANTSEED_H
