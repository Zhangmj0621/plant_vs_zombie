#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QMediaPlayer>
#include"grass.h"
#include"globalconfig.h"
#include<QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(1500,900);
    setWindowTitle("PVZ");

//    player=new QMediaPlayer(this);
//    playerlist=new QMediaPlaylist(this);
//    playerlist->addMedia(QUrl(":/resouce/audio/background.mp3"));
//    playerlist->setCurrentIndex(0);
//    //playerlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
//    player->setPlaylist(playerlist);
//    player->setVolume(150);
//    player->play();

    //设置背景音乐（为什么这么肝啊！！！）
    player = new QMediaPlayer;
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setMedia(QUrl::fromLocalFile("D://QT/QTCODE/pvz/resource/audio/background.mp3"));
    player->setVolume(50);
    player->play();

    //创建草坪对象
    for(int i=1;i<=grassrow;i++)
        for(int j=1;j<=grasscol;j++)
        {
            Grass* newgrass=new Grass(i,j);
            this->grass[i][j]=newgrass;
            newgrass->setAttribute(Qt::WA_TranslucentBackground);
            newgrass->setStyleSheet("background:transparent");
            newgrass->setParent(this);
            newgrass->setFixedSize(newgrass->getwidth(),newgrass->getheight());
            newgrass->move(newgrass->getx(),newgrass->gety());
        }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/resource/images/interface/mainbackground.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    pix.load(":/resource/images/interface/SeedBank.png");

    painter.drawPixmap(10,10,pix.width()*1.5,pix.height()*1.5,pix);
}
