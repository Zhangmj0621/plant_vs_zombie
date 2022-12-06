#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSound>
#include<QMediaPlayer>
#include<QMediaPlaylist>
#include<grass.h>
#include<QMouseEvent>
#include"plant.h"
#include"sun.h"
#include<QVector>
#include<QTimer>
#include"zombie.h"
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    QMediaPlayer* player;
    QMediaPlaylist* playerlist;
    Grass* grass[6][10];
    int selectplantnum;
    int selectbuffnum;
    Plant* plant;
    QMovie* plantmovie;
    QLabel* sunLabel;
    QVector<Sun*>sunlist;
    QTimer* timer;
    QTimer* timersun;
    QTimer* timerzombie;
    QVector<Zombie*> zombielist;    //用来保存还未正式进入草地僵尸
    bool islose;

    QLabel* loselabel;
    QPixmap losepix;

    QLabel* startlabel;
    QPixmap startpix;
    QPropertyAnimation* a1;
    QPropertyAnimation* a2;
    int num_of_zombies[6];

    QGraphicsOpacityEffect* m_pGraphicsOpacityEffect;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    void paintEvent(QPaintEvent *) override;
    //void mousePressEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    Ui::Widget *ui;
public slots:
    void putdownplant(int i,int j);
};
#endif // WIDGET_H
