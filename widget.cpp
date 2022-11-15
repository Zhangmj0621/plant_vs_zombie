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
#include"plant.h"
#include"peashooter.h"
#include"sunflower.h"
#include"wallnut.h"
#include<QRandomGenerator>
#include"zombie.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化信息
    setFixedSize(1500,900);
    setWindowTitle("PVZ");

    setMouseTracking(true);

    selectplantnum=-1;
    plant=NULL;
    timer=new QTimer(this);
    timersun=new QTimer(this);
    timer->start(30);
    timersun->start(10000);
    timerzombie=new QTimer(this);
    timerzombie->start(5000);


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
            //监听草丛鼠标右击
//            connect(newgrass,&Grass::rightclick,[=](){
//                setCursor(Qt::ArrowCursor);
//                selectplantnum=-1;
//            });
        }

    //创建阳光label
    sunLabel=new QLabel(this);
    sunLabel->setText(QString::number(sunsum));
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

    //监听定时器
    connect(timer,&QTimer::timeout,[=](){
        //植物活动
        for(int i=1;i<=grassrow;i++)
            for(int j=1;j<=grasscol;j++)
            {
                if(!grass[i][j]->getiffree())
                {
                    grass[i][j]->plant->now+=30;
                    if(grass[i][j]->plant->now<grass[i][j]->plant->actcount)
                    {
                        continue;
                    }
                    else
                    {
                        //进行一次活动
                        grass[i][j]->plant->act();
                        grass[i][j]->plant->now=0;
                    }
                }
            }

        //阳光活动
        for(QVector<Sun*>::iterator it=sunlist.begin();it!=sunlist.end();it++)
        {
            if((*it)->type==1&& (*it)->btn->y()<=grassrowpos[(*it)->x-1]/3+grassrowpos[(*it)->x]*2/3)
            {
                //qDebug()<<"the desy= "<<grassrowpos[(*it)->x-1]/3+grassrowpos[(*it)->x]*2/3;
                //qDebug()<<"the sun have to move to "<<(*it)->btn->x()<<" "<<(*it)->btn->y()+0.07;
                (*it)->btn->move((*it)->btn->x(),(*it)->btn->y()+2);
            }
        }

        //未进入草地僵尸活动
        for(QVector<Zombie*>::iterator it=zombielist.begin();it!=zombielist.end();)
        {
            (*it)->label->move((*it)->label->x()-1,(*it)->label->y());
            if((*it)->label->x()<=grasscolpos[9]-118)
            {
                (*it)->sety(9);
                grass[(*it)->getx()][9]->zombielist.push_back((*it));
                if(grass[(*it)->getx()][9]->getiffree()==false)
                {
                    (*it)->setifatk(true);    //开始攻击
                    (*it)->changeatk(); //更换gif图像
                }
                zombielist.erase(it);
            }
            else
            {
                it++;
            }
        }

        //进入草地僵尸活动
        for(int i=1;i<=grassrow;i++)
            for(int j=1;j<=grasscol;j++)
            {
                for(QVector<Zombie*>::iterator it=grass[i][j]->zombielist.begin();
                    it!=grass[i][j]->zombielist.end();)
                {
                    //是否在攻击状态
                    if((*it)->ifheatk())
                    {
                        (*it)->now+=30;
                        if((*it)->actacount<=(*it)->now)
                        {
                            grass[i][j]->plant->hit((*it));

                            (*it)->now=0;
                        }
                        it++;
                        continue;
                    }
                    //在行走中
                    else
                    {
                        (*it)->label->move((*it)->label->x()-1,(*it)->label->y());
                        //进入新地块
                        if(j>=2)
                        {
                            if((*it)->label->x()<=grasscolpos[j-1]-118)
                            {
                                (*it)->sety(j-1);
                                grass[i][j-1]->zombielist.push_back((*it));
                                if(grass[i][j-1]->getiffree()==false)
                                {
                                    (*it)->setifatk(true);    //开始攻击
                                    (*it)->changeatk(); //更换gif图像
                                }
                                grass[i][j]->zombielist.erase(it);
                            }
                            //还可以在本块被阻挡
                            else if((*it)->label->x()>=grasscolpos[j]-158)
                            {
                                if(grass[i][j]->getiffree()==false)
                                {
                                    (*it)->setifatk(true);    //开始攻击
                                    (*it)->changeatk(); //更换gif图像
                                }
                                it++;
                            }
                            //无事发生继续向前
                            else
                            {
                                it++;
                            }
                        }
                        else
                        {
                            if((*it)->label->x()<=grasscolpos[j-1]-118)
                            {
                                //你输了，或者引入小推车

                            }
                        }
                    }
                }
            }

    });

    //生成太阳掉落
    connect(timersun,&QTimer::timeout,[=](){
        int _x=QRandomGenerator::global()->bounded(1,5);
        int _y=QRandomGenerator::global()->bounded(1,9);
        Sun* sun=new Sun(this,1,_x,_y);
        sun->btn->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);}");
        sun->btn->setFixedSize(70,70);
        sun->btn->move((grasscolpos[_y]+grasscolpos[_y-1])/2,-sun->btn->height());
        sun->btn->show();
        qDebug()<<"you have generate the sun at "<<_x<<" "<<_y;
        sunlist.push_back(sun);
        //监听点击太阳事件
        connect(sun->btn,&QPushButton::clicked,[=](){
            sunsum+=25;
            sunLabel->setText(QString::number(sunsum));
            for(QVector<Sun*>::iterator it=sunlist.begin();it!=sunlist.end();)
            {
                if((*it)==sun)
                {
                    sunlist.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            delete sun->btn;
            //delete sun->parent;
            delete sun;
        });
    });


    //随机生成僵尸
    connect(timerzombie,&QTimer::timeout,[=](){
        int nxtinterval=QRandomGenerator::global()->bounded(5000,10000);  //下次定时器时间
        timerzombie->setInterval(nxtinterval);
        int _x=QRandomGenerator::global()->bounded(1,5);
        Zombie* newzombie=new Zombie(this,_x);
        qDebug()<<"you have the new zombie at line "<<_x;
        newzombie->updateinfo();
        zombielist.push_back(newzombie);
    });
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
    else if(event->button()==Qt::LeftButton)
    {
        //判断是否在草丛上
        if(event->x()>=grasscolpos[0]&&event->x()<=grasscolpos[9] && event->y()>=grassrowpos[0]&&event->y()<=grassrowpos[5])
        {
            QPair<int,int> an=thegrass(event->x(),event->y());
            qDebug()<<an.first<<" "<<an.second;
            putdownplant(an.first,an.second);
        }
    }

}

 void Widget::putdownplant(int i,int j)
 {
     if(grass[i][j]->getiffree())
     {
         if(selectplantnum!=-1)
         {
             QString plantname=seedname[selectplantnum-1];
             if(sunsum<sunneed[selectplantnum-1])
             {
                 setCursor(Qt::ArrowCursor);
                 selectplantnum=-1;
                 return;
             }
             sunsum-=sunneed[selectplantnum-1];
             sunLabel->setText(QString::number(sunsum));
             if(plantname=="Peashooter"){
                 Peashooter* newplant2=new Peashooter(this,i,j);
                 plant=newplant2;
             }
             else if(plantname=="SunFlower"){
                 SunFlower* newplant2=new SunFlower(this,i,j);
                 plant=newplant2;
             }
             else if(plantname=="WallNut"){
                 WallNut* newplant2=new WallNut(this,i,j);
                 plant=newplant2;
             }
             else
             {
                 setCursor(Qt::ArrowCursor);
                 selectplantnum=-1;
                 return;
             }
             grass[i][j]->setiffree(false);
             //草坪监听植物是否死亡
             grass[i][j]->plant=plant;
             connect(plant,&Plant::die,[=](){
                 grass[i][j]->plant=NULL;
                 grass[i][j]->setiffree(true);
                 for(QVector<Zombie*>::iterator it=grass[i][j]->zombielist.begin();
                     it!=grass[i][j]->zombielist.end();it++)
                 {
                     (*it)->setifatk(false);
                     (*it)->changewalk();
                 }
             });
             setCursor(Qt::ArrowCursor);
             selectplantnum=-1;
         }
         else
         {
             setCursor(Qt::ArrowCursor);
             selectplantnum=-1;
         }
     }
     else
     {
         setCursor(Qt::ArrowCursor);
         selectplantnum=-1;
     }
 }
