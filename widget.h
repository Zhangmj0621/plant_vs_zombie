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
    int selectplantnum; //所选择的植物num
    int selectbuffnum;  //所选择的buffnum
    bool ifselectshovel;    //是否选择了shovel
    int thezombielevel; //僵尸危险等级，初始为1级
    //1级只生成普通僵尸，2级生成普通僵尸和路障僵尸，3级生成普通、路障、铁桶僵尸
    //4级加上报纸和跨栏僵尸，5级生成僵尸间隔调为3-5秒，6级不生成任何僵尸，视作游戏胜利，需要跳胜利动画和音效
    int zombienamejs;   //僵尸数量计数，每生成十只僵尸将等级加高一级，等级5时为生成了二十只僵尸
    int diezombienum;  //记录死亡僵尸数量，若为20
    int zombienumtotal; //记录总共生成的僵尸数量
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

    QLabel* winlabel;
    QPixmap winpix;

    QLabel* startlabel;
    QPixmap startpix;
    QPropertyAnimation* a1; //失败动画
    QPropertyAnimation* a2; //显示请放植物
    QPropertyAnimation* a3; //胜利动画
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
