#ifndef BUFFSEED_H
#define BUFFSEED_H

#include <QObject>
#include <QWidget>

class BuffSeed : public QWidget
{
    Q_OBJECT
    QString plantname;
    QString plantseedpix;
    int num;    //第几个卡槽，在move时使用
public:
    explicit BuffSeed(QWidget *parent = nullptr);

    BuffSeed(QString name,int num);

    int getnum(){return num;};

    void mousePressEvent(QMouseEvent *ev) override;

    void paintEvent(QPaintEvent *) override;
signals:
    void clickSeed(int num);
};

#endif // BUFFSEED_H
