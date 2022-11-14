#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QMediaPlayer>
#include"grass.h"
#include"globalconfig.h"
#include<QDebug>
#include<QFont>
#include<QMovie>
#include"plantseed.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(1500,900);
    setWindowTitle("PVZ");

    setMouseTracking(true);

    selectplantnum=-1;

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
            //监听草丛鼠标右击
            connect(newgrass,&Grass::rightclick,[=](){
                setCursor(Qt::ArrowCursor);
                selectplantnum=-1;
            });
        }

    //创建阳光label
    QLabel* sunLabel=new QLabel(this);
    sunLabel->setText("50");
    sunLabel->setAlignment(Qt::AlignCenter);
    //sunLabel->move()101,134,24,99
    sunLabel->setFixedSize(77,35);
    sunLabel->move(24,99);
    QFont font("微软雅黑",15);
    sunLabel->setFont(font);

    //创建seed槽卡片
    for(int i=0;i<seednum;i++)
    {
        PlantSeed* newseed=new PlantSeed(seedname[i],i+1);
        newseed->setFixedSize(seedwidth,seedheight);
        newseed->setParent(this);
        newseed->move(seedstartx+seedwidth*i,seedstarty);
        //点击了卡片
        connect(newseed,&PlantSeed::clickSeed,[=](int num){
            qDebug()<<"you have enter the clickseend slots!";
            QPixmap pix;
            QString str=QString(":/resource/images/Cursor/%1.png").arg(seedname[num-1]);
            pix.load(str);
            QSize size(50,50);
            pix.scaled(size);
            setCursor(QCursor(pix));
            selectplantnum=num;
        });
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

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton)
    {
        setCursor(Qt::ArrowCursor);
        selectplantnum=-1;
    }
}
