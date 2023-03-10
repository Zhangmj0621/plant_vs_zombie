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
#include<QPropertyAnimation>
#include"bullet.h"
#include"pea.h"
#include"getmap.h"
#include"crator.h"
#include"buffseed.h"
#include"snowpea.h"
#include"firepea.h"
#include"newspaperzombie.h"
#include"shovel.h"
#include"polevaultingzombie.h"
#include"coneheadzombie.h"
#include"bucketheadzombie.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //初始化信息
    //sunsum=5000;
    setFixedSize(1500,900);
    setWindowTitle("PVZ");

    setMouseTracking(true);

    selectplantnum=-1;
    selectbuffnum=-1;
    ifselectshovel=false;
    plant=NULL;
    plantmovie=NULL;
    timer=new QTimer(this);
    timersun=new QTimer(this);
    timer->start(30);
    timersun->start(10000);
    timerzombie=new QTimer(this);
    timerzombie->start(15000);

    //初始危险等级为1
    thezombielevel=1;
    zombienamejs=0;
    zombienumtotal=0;
    diezombienum=0;


    //僵尸每行数量初值设为0
    for(int i=1;i<=5;i++)
        num_of_zombies[i]=0;

    this->islose=false;


    //创建失败图片
    loselabel=new QLabel(this);
    losepix.load(":/resource/images/interface/ZombiesWon.png");
    loselabel->setGeometry(0,0,losepix.width(),losepix.height());
    loselabel->setPixmap(losepix);
    loselabel->move((this->width()-losepix.width())/2,-losepix.height());

    //动画设置
    a1=new QPropertyAnimation(loselabel,"geometry");
    a1->setDuration(1000);
    a1->setStartValue(QRect(loselabel->x(),loselabel->y(),loselabel->width(),loselabel->height()));
    a1->setEndValue(QRect(loselabel->x(),-loselabel->y(),loselabel->width(),loselabel->height()));
    a1->setEasingCurve(QEasingCurve::OutBounce);

    //创建胜利图片
    winlabel=new QLabel(this);
    winpix.load(":/resource/images/interface/trophy.png");
    winlabel->setGeometry(0,0,winpix.width(),winpix.height());
    winlabel->setPixmap(winpix);
    winlabel->move((this->width()-winpix.width())/2,-winpix.height());

    //设置胜利动画
    a3=new QPropertyAnimation(winlabel,"geometry");
    a3->setDuration(1000);
    a3->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
    a3->setEndValue(QRect(winlabel->x(),-winlabel->y(),winlabel->width(),winlabel->height()));
    a3->setEasingCurve(QEasingCurve::OutBounce);

    //创建开始图片动画
    startlabel=new QLabel(this);
    startpix.load(":/resource/images/interface/PrepareGrowPlants.png");
    startlabel->setGeometry(0,0,startpix.width(),startpix.height());
    startlabel->setPixmap(startpix);
    startlabel->move((this->width()-losepix.width())/2,startpix.height());

    //淡入淡出动画
    m_pGraphicsOpacityEffect = new QGraphicsOpacityEffect(startlabel);
    m_pGraphicsOpacityEffect->setOpacity(1);
    startlabel->setGraphicsEffect(m_pGraphicsOpacityEffect);

    a2 = new QPropertyAnimation(m_pGraphicsOpacityEffect,"opacity",this);
    a2->setEasingCurve(QEasingCurve::InOutExpo);  //淡出效果
    a2->setDuration(3000);                        //动画时间

    a2->setStartValue(1); //关闭label
    a2->setEndValue(0);
    a2->start(QAbstractAnimation::KeepWhenStopped);

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
    playerlist=NULL;

    //创建草坪对象
    for(int i=1;i<=grassrow;i++)
        for(int j=1;j<=grasscol;j++)
        {
            Grass* newgrass=new Grass(i,j,mapbool[i][j]);
            this->grass[i][j]=newgrass;
            //监听草丛鼠标右击
//            connect(newgrass,&Grass::rightclick,[=](){
//                setCursor(Qt::ArrowCursor);
//                selectplantnum=-1;
//            });
        }

    //生成不能放植物的格子
    for(int i=1;i<=grassrow;i++)
        for(int j=1;j<=grasscol;j++)
        {
            if(!mapbool[i][j]){
                Crator* newcrator=new Crator(this,i,j);
            }
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
            selectbuffnum=-1;
            ifselectshovel=false;
        });
    }

    //创建buffseed槽卡片
    for(int i=0;i<seednum_buff;i++)
    {
        BuffSeed* newseed=new BuffSeed(seedname_buff[i],i+1);
        newseed->setFixedSize(seedwidth_buff,seedheight_buff);
        newseed->setParent(this);
        newseed->move(seedstartx_buff+seedwidth_buff*i,seedstarty_buff);
        QLabel* newlabel=new QLabel(this);
        newlabel->setStyleSheet("QLabel{background-color:rgb(200,101,102);}");
        newlabel->setAlignment(Qt::AlignCenter);
        newlabel->setText(QString::number(sunneed_buff[newseed->getnum()-1]));
        newlabel->move(newseed->x()+5,newseed->y()+newseed->height());
        newlabel->setFixedSize(seedwidth_buff-10,20);
        //点击了卡片
        connect(newseed,&BuffSeed::clickSeed,[=](int num){
            qDebug()<<"you have enter the clickseend slots!";
            QPixmap pix;
            QString str=QString(":/resource/images/Cursor/%1.png").arg(seedname_buff[num-1]);
            pix.load(str);
            QSize size(50,50);
            pix.scaled(size);
            QCursor a(pix);
            setCursor(QCursor(pix));
            selectbuffnum=num;
            selectplantnum=-1;
            ifselectshovel=false;
        });
    }

    //创建铲子
    Shovel* shovel = new Shovel();
    shovel->setFixedSize(77,55);
    shovel->setParent(this);
    shovel->move(710,35);
    shovel->show();

    //点击了铲子
    connect(shovel,&Shovel::clickshovel,[=](){
        qDebug()<<"you have touch the shovel!";
        QPixmap pix;
        pix.load(":/resource/images/interface/Shovel.png");
        QSize size(50,50);
        pix.scaled(size);
        QCursor a(pix);
        setCursor(QCursor(pix));

        ifselectshovel=true;
        selectbuffnum=-1;
        selectplantnum=-1;
    });

    //测试buff
//    Buff* buff=new Buff(this,3,3,1,0);

//    buff->setFixedSize(70,70);
//    buff->setParent(this);
//    buff->move((grasscolpos[buff->x]+grasscolpos[buff->y-1])/2-30,grassrowpos[buff->x-1]/3+grassrowpos[buff->x]*2/3-70);
//    buff->show();

    //测试子弹类
//    Pea* temppea=new Pea(this,50,2,2);
//    temppea->label->show();

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
                        //向日葵切换发光和正常
                        if(grass[i][j]->plant->bh==0&&grass[i][j]->plant->now==8100)
                        {
                            grass[i][j]->plant->changelight();
                        }
                        continue;
                    }
                    else
                    {
                        //进行一次活动
                        if(grass[i][j]->plant->bh==0)//向日葵
                        {
                            grass[i][j]->plant->changegeneral();
                            Sun* producesun=new Sun(this,0,i,j);
                            producesun->btn->setStyleSheet("QPushButton{background:rgba(0,0,0,0);border:1px solid rgba(0,0,0,0);}");
                            producesun->btn->setFixedSize(70,70);
                            producesun->btn->move((grasscolpos[j]+grasscolpos[j-1])/2,grassrowpos[i-1]/3+grassrowpos[i]*2/3);
                            producesun->btn->show();
                            qDebug()<<"sunflower have generate the sun at "<<i<<" "<<j;
                            //监听点击太阳事件
                            connect(producesun->btn,&QPushButton::clicked,[=](){
                                sunsum+=25;
                                sunLabel->setText(QString::number(sunsum));
                                delete producesun->btn;
                                //delete sun->parent;
                                delete producesun;
                            });
                        }
                        else if(grass[i][j]->plant->bh==1&&num_of_zombies[i]!=0)//豌豆射手
                        {
                            if(!grass[i][j]->plant->bufflist[1]&&!grass[i][j]->plant->bufflist[2])
                            {
                                Pea* temppea=new Pea(this,50,i,j);
                                grass[i][j]->bulletlist.push_back(temppea);
                            }
                            else if(grass[i][j]->plant->bufflist[1]){
                                SnowPea* temppea=new SnowPea(this,50,i,j);
                                grass[i][j]->bulletlist.push_back(temppea);
                            }
                            else if(grass[i][j]->plant->bufflist[2]){
                                FirePea* temppea=new FirePea(this,50,i,j);
                                grass[i][j]->bulletlist.push_back(temppea);
                            }
                        }
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
            (*it)->movenow++;
            if((*it)->movenow>=(*it)->moveacount){
                (*it)->movenow=0;
                (*it)->label->move((*it)->label->x()-(*it)->speed,(*it)->label->y());
                (*it)->backbloodlabel->move((*it)->label->x()+40+(*it)->polelength,(*it)->label->y());
                (*it)->bloodlabel->move((*it)->label->x()+42+(*it)->polelength,(*it)->label->y()+2);
                (*it)->bloodlabel->resize(76*((*it)->gethp())/((*it)->getfullhp()),16);
                (*it)->coldbufflabel->move((*it)->backbloodlabel->x()+(*it)->backbloodlabel->width()+5,(*it)->backbloodlabel->y());
                (*it)->bloodbufflabel->move((*it)->backbloodlabel->x()-25,(*it)->backbloodlabel->y());
            }
            if((*it)->ifblood)
            {
                (*it)->bloodnow++;
                if((*it)->bloodnow>=(*it)->bloodacount)
                {
                    (*it)->behit(1,false,false);
                    (*it)->bloodnow=0;
                    (*it)->bloodlabel->resize(76*((*it)->gethp())/((*it)->getfullhp()),16);
                }
            }
            if((*it)->label->x()==grasscolpos[9]){
                num_of_zombies[(*it)->getx()]++;
            }
            if((*it)->label->x()<=grasscolpos[9]-118)
            {
                (*it)->sety(9);
                //num_of_zombies[(*it)->getx()]++;
                grass[(*it)->getx()][9]->zombielist.push_back((*it));
                if(grass[(*it)->getx()][9]->getiffree()==false&&!(*it)->ifdie)
                {
                    (*it)->setifatk(true);    //开始攻击
                    (*it)->changeatk(); //更换gif图像
                }
                it=zombielist.erase(it);
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
                    //是否流血
                    if((*it)->ifblood)
                    {
                        (*it)->bloodnow++;
                        if((*it)->bloodnow>=(*it)->bloodacount)
                        {
                            (*it)->behit(1,false,false);
                            (*it)->bloodnow=0;
                            (*it)->bloodlabel->resize(76*((*it)->gethp())/((*it)->getfullhp()),16);
                        }
                    }
                    //是否在攻击状态
                    if((*it)->ifheatk())
                    {
                        (*it)->now+=30;
                        (*it)->bloodlabel->resize(76*((*it)->gethp())/((*it)->getfullhp()),16);
                        if((*it)->actacount<=(*it)->now&&!(*it)->ifdie)
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
                        (*it)->movenow++;
                        if((*it)->movenow>=(*it)->moveacount){
                            (*it)->movenow=0;
                            (*it)->label->move((*it)->label->x()-(*it)->speed,(*it)->label->y());
                            (*it)->backbloodlabel->move((*it)->label->x()+40+(*it)->polelength,(*it)->label->y());
                            (*it)->bloodlabel->move((*it)->label->x()+42+(*it)->polelength,(*it)->label->y()+2);
                            (*it)->bloodlabel->resize(76*((*it)->gethp())/((*it)->getfullhp()),16);
                            (*it)->coldbufflabel->move((*it)->backbloodlabel->x()+(*it)->backbloodlabel->width()+5,(*it)->backbloodlabel->y());
                            (*it)->bloodbufflabel->move((*it)->backbloodlabel->x()-25,(*it)->backbloodlabel->y());
                        }

                        //如果该僵尸在跳跃状态
                        if((*it)->ifinjump)
                        {
                            it++;
                            continue;
                        }

                        //进入新地块
                        if(j>=2)
                        {
                            //进入下一格
                            if((*it)->label->x()<=grasscolpos[j-1]-118-(*it)->polelength&& (!(*it)->iffast))
                            {
                                (*it)->sety(j-1);
                                grass[i][j-1]->zombielist.push_back((*it));
                                if(grass[i][j-1]->getiffree()==false&&!(*it)->ifdie)
                                {
                                    (*it)->setifatk(true);    //开始攻击
                                    (*it)->changeatk(); //更换gif图像
                                }
                                it=grass[i][j]->zombielist.erase(it);
                            }
                            //还可以在本块被阻挡
                            //可以跨栏
                            else if((*it)->label->x()<=grasscolpos[j-1]-118-(*it)->polelength&&(*it)->iffast)
                            {
                                (*it)->sety(j-1);
                                grass[i][j-1]->zombielist.push_back((*it));
                                if(grass[i][j-1]->getiffree()==false&&!(*it)->ifdie)
                                {
                                    (*it)->iffast=false;
                                    (*it)->ifinjump=true;
                                    (*it)->changejump1();
                                    //(*it)->label->setFixedSize(160,120);
                                    QTimer::singleShot(1000,this,[=](){
                                        (*it)->changejump2();
                                    });

                                    QTimer::singleShot(2000,this,[=](){
                                        //(*it)->label->setFixedSize(160,120);
                                        (*it)->changewalk();
                                        (*it)->ifinjump=false;
                                        (*it)->speed=1;
                                    });
                                }
                                it=grass[i][j]->zombielist.erase(it);

                            }
                            //普通操作
                            else if((*it)->label->x()>=grasscolpos[j]-158-(*it)->polelength&&!(*it)->iffast)
                            {
                                if(grass[i][j]->getiffree()==false&&!(*it)->ifdie)
                                {
                                    (*it)->setifatk(true);    //开始攻击
                                    (*it)->changeatk(); //更换gif图像
                                }
                                it++;
                            }
                            else if((*it)->label->x()>=grasscolpos[j]-158-(*it)->polelength&&(*it)->iffast)
                            {
                                if(grass[i][j]->getiffree()==false&&!(*it)->ifdie)
                                {
                                    (*it)->iffast=false;
                                    (*it)->ifinjump=true;
                                    (*it)->changejump1();
                                    //(*it)->label->setFixedSize(160,120);
                                    QTimer::singleShot(1000,this,[=](){
                                        (*it)->changejump2();
                                    });

                                    QTimer::singleShot(2000,this,[=](){
                                        //(*it)->label->setFixedSize(160,120);
                                        (*it)->changewalk();
                                        (*it)->ifinjump=false;
                                        (*it)->speed=1;
                                    });
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
                            if((*it)->label->x()<=grasscolpos[j-1]-118-(*it)->polelength&&!(*it)->ifdie)
                            {
                                it=grass[i][j]->zombielist.erase(it);
                                //你输了，或者引入小推车
                                //停止所有计时器
                                this->islose=true;
                                timersun->stop();
                                timer->stop();
                                timerzombie->stop();
                                //显示失败图片

                                a1->start();
                                QTimer::singleShot(3000,this,[=](){
                                    //创建新窗口
                                    //删除原有内存
                                    delete player;
                                    delete playerlist;
                                    for(int i=1;i<=grassrow;i++)
                                        for(int j=1;j<=grasscol;j++)
                                        {
                                            delete grass[i][j];
                                        }
                                    delete plant;
                                    //delete plantmovie;
                                    delete sunLabel;
                                    for(QVector<Sun*>::iterator it=sunlist.begin();
                                        it!=sunlist.end();)
                                    {
                                        Sun* p=(*it);
                                        it=sunlist.erase(it);
                                        delete p;
                                    }
                                    delete timer;
                                    delete timersun;
                                    delete timerzombie;
                                    for(QVector<Zombie*>::iterator it=zombielist.begin();
                                        it!=zombielist.end();)
                                    {
                                        Zombie* p=(*it);
                                        it=zombielist.erase(it);
                                        delete p;
                                    }
                                    delete loselabel;
                                    delete startlabel;
                                    delete a2;
                                    delete a1;
                                    sunsum=100;
                                    Widget* w2=new Widget();
                                    w2->show();
                                    this->close();

                                    this->~Widget();

                                });
                            }
                            else
                            {
                                it++;
                            }
                        }
                    }
                }
            }

        //子弹活动
        for(int i=1;i<=grassrow;i++)
            for(int j=grasscol;j>=1;j--)
            {
                for(QVector<Bullet*>::iterator it=grass[i][j]->bulletlist.begin();
                    it!=grass[i][j]->bulletlist.end();)
                {
                    int temp=(*it)->move();
                    bool ifbomb=false;
                    //判断是否与僵尸发生碰撞
                    if(temp==0) //正常移动
                    {
                        int tempx=(*it)->label->x()+(*it)->label->width()-8;
                        for(QVector<Zombie*>::iterator it2=grass[i][j]->zombielist.begin();
                            it2!=grass[i][j]->zombielist.end();it2++)
                        {
                            if((*it2)->label->x()+80+(*it2)->polelength<=tempx)
                            {
                                //删除子弹
                                Bullet* temp=(*it);
                                temp->changehit();

                                ifbomb=true;
                                emit (*it2)->hit((*it)->atk,(*it)->ifcold,(*it)->ifblood);
                                it=grass[i][j]->bulletlist.erase(it);
                                QTimer::singleShot(500,this,[=](){
                                    qDebug()<<"you have delete the pea";
                                    delete temp->label;
                                    delete temp->movie;
                                    delete temp;

                                });
                                break;
                                //触发僵尸被攻击信号

                            }
                        }
                        if(!ifbomb&&(*it)->y==9)
                        {
                            for(QVector<Zombie*>::iterator it2=zombielist.begin();
                                it2!=zombielist.end();it2++)
                            {
                                if((*it2)->getx()==(*it)->x&&(*it2)->label->x()+80+(*it2)->polelength<=tempx)
                                {
                                    //删除子弹
                                    Bullet* temp=(*it);
                                    temp->changehit();

                                    ifbomb=true;
                                    emit (*it2)->hit((*it)->atk,(*it)->ifcold,(*it)->ifblood);
                                    it=grass[i][j]->bulletlist.erase(it);
                                    QTimer::singleShot(500,this,[=](){
                                        qDebug()<<"you have delete the pea";
                                        delete temp->label;
                                        delete temp->movie;
                                        delete temp;

                                    });
                                    break;
                                    //触发僵尸被攻击信号

                                }
                            }
                        }
                        if(!ifbomb) it++;
                    }
                    else if(temp==1)    //进入下一个地块
                    {
                        grass[i][j+1]->bulletlist.push_back(*it);
                        it=grass[i][j]->bulletlist.erase(it);
                    }
                    else    //移出屏幕了
                    {
                        Bullet* temp=(*it);
                        delete temp->label;
                        delete temp->movie;
                        delete temp;
                        it=grass[i][j]->bulletlist.erase(it);

                    }
                }
            }


    });

    //随机子弹

    //生成太阳掉落
    connect(timersun,&QTimer::timeout,[=](){
        //Pea* temppea=new Pea(this,50,3,4);
        //grass[1][1]->bulletlist.push_back(temppea);

        int _x=QRandomGenerator::global()->bounded(1,6);
        int _y=QRandomGenerator::global()->bounded(1,10);
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
                    it=sunlist.erase(it);
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
        if(thezombielevel>=3)
        {
            nxtinterval=QRandomGenerator::global()->bounded(3000,5000);  //下次定时器时间
            timerzombie->setInterval(nxtinterval);
        }
        if(thezombielevel>=6&&zombienumtotal==diezombienum)
        {
            //胜利啦
            this->islose=true;
            timersun->stop();
            timer->stop();
            timerzombie->stop();
            //显示失败图片

            a3->start();
            QTimer::singleShot(5000,this,[=](){
                //创建新窗口
                //删除原有内存
                delete player;
                delete playerlist;
                for(int i=1;i<=grassrow;i++)
                    for(int j=1;j<=grasscol;j++)
                    {
                        delete grass[i][j];
                    }
                delete plant;
                //delete plantmovie;
                delete sunLabel;
                for(QVector<Sun*>::iterator it=sunlist.begin();
                    it!=sunlist.end();)
                {
                    Sun* p=(*it);
                    it=sunlist.erase(it);
                    delete p;
                }
                delete timer;
                delete timersun;
                delete timerzombie;
                for(QVector<Zombie*>::iterator it=zombielist.begin();
                    it!=zombielist.end();)
                {
                    Zombie* p=(*it);
                    it=zombielist.erase(it);
                    delete p;
                }
                delete loselabel;
                delete startlabel;
                delete a2;
                delete a1;
                sunsum=100;
                Widget* w2=new Widget();
                w2->show();
                this->close();

                this->~Widget();
                return;
            });
        }
        int _x=QRandomGenerator::global()->bounded(1,6);
        //设立一个随机数来选择生成哪一个僵尸
        //如为0，则生成普通僵尸，如为1，则生成报纸僵尸
        //如为2，则生成跨栏僵尸
        //int tempsz=QRandomGenerator::global()->bounded(0,4);
        //int tempsz=4;
        int tempsz;
        if(thezombielevel==1) tempsz=0;
        else if(thezombielevel==2) tempsz=QRandomGenerator::global()->bounded(0,2);
        else if(thezombielevel==3) tempsz=QRandomGenerator::global()->bounded(0,3);
        else if(thezombielevel==4) tempsz=QRandomGenerator::global()->bounded(0,5);
        else if(thezombielevel==5)
        {
            tempsz=QRandomGenerator::global()->bounded(0,5);
            nxtinterval=QRandomGenerator::global()->bounded(1000,3000);  //下次定时器时间
            timerzombie->setInterval(nxtinterval);
        }
        else
        {
            return;
        }
        //tempsz=4;
        Zombie* newzombie;
        if(tempsz==0) newzombie=new Zombie(this,_x);
        else if(tempsz==3) newzombie=new NewspaperZombie(this,_x);
        else if(tempsz==4) newzombie=new PoleVaultingZombie(this,_x);
        else if(tempsz==1) newzombie=new ConeheadZombie(this,_x);
        else if(tempsz==2) newzombie=new BucketheadZombie(this,_x);
        else
        {
            return;
        }
        zombienamejs++;
        zombienumtotal++;
        if(thezombielevel!=5&&zombienamejs>=5)
        {
            thezombielevel++;
            zombienamejs=0;
        }
        else if(thezombielevel==5&&zombienamejs>=20)
        {
            thezombielevel++;
            zombienamejs=0;
        }
        //newzombie=new NewspaperZombie(this,_x);
        qDebug()<<"you have the new zombie at line "<<_x;
        newzombie->updateinfo();
        zombielist.push_back(newzombie);
        connect(newzombie,&Zombie::hit,[=](int atk,bool ifcold,bool ifblood){
            newzombie->behit(atk,ifcold,ifblood);
        });
        connect(newzombie,&Zombie::die,[=](){
            diezombienum++;
            newzombie->changedie();
            if(newzombie->gety()!=10)
            {
                num_of_zombies[newzombie->getx()]--;
                for(QVector<Zombie*>::iterator it=grass[newzombie->x][newzombie->y]->zombielist.begin();
                    it!=grass[newzombie->x][newzombie->y]->zombielist.end();it++){
                    if((*it)==newzombie)
                    {
                        it=grass[newzombie->x][newzombie->y]->zombielist.erase(it);
                        break;
                    }
                }
            }
            else
            {
                for(QVector<Zombie*>::iterator it=zombielist.begin();
                    it!=zombielist.end();it++)
                {
                    if((*it)==newzombie)
                    {
                        it=zombielist.erase(it);
                        break;
                    }
                }
            }

            QTimer::singleShot(500,this,[=](){
                delete newzombie->label;
                delete newzombie->movie;
                delete newzombie->backbloodlabel;
                delete newzombie->bloodlabel;
                delete newzombie->coldbufflabel;
                delete newzombie->bloodbufflabel;
                delete newzombie;
            });
        });
    });
}

Widget::~Widget()
{
    GetMap getmap;
    getmap.writemap();
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPixmap pix;
    //主背景
    pix.load(":/resource/images/interface/mainbackground.jpg");

    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //植物种子栏和buff种子栏
    pix.load(":/resource/images/interface/SeedBank.png");

    painter.drawPixmap(10,10,pix.width()*1.5,pix.height()*1.5,pix);

    painter.drawPixmap(this->width()-pix.width()-10,10,pix.width(),pix.height(),pix);

    //铲子栏
    pix.load(":/resource/images/interface/ShovelBack.png");

    painter.drawPixmap(700,20,90,90,pix);


}

void Widget::mousePressEvent(QMouseEvent *event){
    if(event->button()==Qt::RightButton)
    {
        setCursor(Qt::ArrowCursor);
        selectplantnum=-1;
        selectbuffnum=-1;
    }
    else if(!islose && event->button()==Qt::LeftButton)
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
     //若草坪为空且能够放植物
     if(grass[i][j]->getiffree()&&grass[i][j]->getifput())
     {
         //如果是放植物
         if(selectplantnum!=-1)
         {
             QString plantname=seedname[selectplantnum-1];
             if(sunsum<sunneed[selectplantnum-1])
             {
                 setCursor(Qt::ArrowCursor);
                 selectplantnum=-1;
                 selectbuffnum=-1;
                 ifselectshovel=false;
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
                 selectbuffnum=-1;
                 ifselectshovel=false;
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
             selectbuffnum=-1;
             ifselectshovel=false;
         }
         else
         {
             setCursor(Qt::ArrowCursor);
             selectplantnum=-1;
             selectbuffnum=-1;
             ifselectshovel=false;
         }
     }
     //若草坪不为空，有植物在上面
     else if(!grass[i][j]->getiffree())
     {
         //如果选中了buff
         if(selectbuffnum!=-1)
         {
             QString buffname=seedname_buff[selectbuffnum-1];
             if(sunsum<sunneed_buff[selectbuffnum-1])
             {
                 setCursor(Qt::ArrowCursor);
                 selectplantnum=-1;
                 selectbuffnum=-1;
                 ifselectshovel=false;
                 return;
             }
             //注意狂暴可以和流血冰冻叠加
             //冰冻叠加只能同时存在一个
             if(buffname=="violent"){
                 //先判断是否已经拥有该种buff
                 if(grass[i][j]->plant->bufflist[0])
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     return;
                 }
                 //可以含有该buff
                 int fw=0;
                 if(grass[i][j]->plant->buffstate==0){
                     fw=0;
                     grass[i][j]->plant->buffstate=1;
                 }
                 else if(grass[i][j]->plant->buffstate==1){
                     fw=1;
                     grass[i][j]->plant->buffstate=3;
                 }
                 else if(grass[i][j]->plant->buffstate==2)
                 {
                     fw=0;
                     grass[i][j]->plant->buffstate=3;
                 }
                 else
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     return;
                 }
                 //说明有两个buff切换为超级
                 if(grass[i][j]->plant->buffstate==3) grass[i][j]->plant->changesuper();
                 //说明只有一个buff切换为狂暴
                 else grass[i][j]->plant->changeviolent();
                 qDebug()<<"you have show the violent buff";
                 Buff* buff=new Buff(this,i,j,1,fw);
                 buff->setParent(this);
                 buff->setFixedSize(20,20);
                 buff->move((grasscolpos[buff->y]+grasscolpos[buff->y-1])/2-buff->width()/2+fw*40,grassrowpos[buff->x-1]/3+grassrowpos[buff->x]*2/3);
                 buff->show();
                 grass[i][j]->plant->buffpoint[0]=buff;
                 //狂暴状态下攻击间隔变为原来一半
                 //如果为坚果则将生命值加400
                 grass[i][j]->plant->actcount/=2;
                 if(grass[i][j]->plant->bh==2) grass[i][j]->plant->hp+=400;
                 connect(buff,&Buff::die,[=](int num){
                     grass[i][j]->plant->bufflist[num-1]=false;
                     grass[i][j]->plant->buffpoint[num-1]=NULL;
                     if(buff->fw==0){
                         if(grass[i][j]->plant->buffstate==1)
                         {
                             grass[i][j]->plant->buffstate=0;
                             grass[i][j]->plant->changenormel();
                         }
                         else if(grass[i][j]->plant->buffstate==3)
                         {
                             grass[i][j]->plant->buffstate=2;
                             if(grass[i][j]->plant->bufflist[1]) grass[i][j]->plant->changecold();
                             else grass[i][j]->plant->changenormel();
                         }
                     }
                     else
                     {
                         if(grass[i][j]->plant->buffstate==2)
                         {
                             grass[i][j]->plant->buffstate=0;
                             grass[i][j]->plant->changenormel();
                         }
                         else if(grass[i][j]->plant->buffstate==3)
                         {
                             grass[i][j]->plant->buffstate=1;
                             if(grass[i][j]->plant->bufflist[1]) grass[i][j]->plant->changecold();
                             else grass[i][j]->plant->changenormel();
                         }
                     }
                     delete buff;
                     sunsum+=sunneed_buff[num-1]-25;
                     sunLabel->setText(QString::number(sunsum));
                     grass[i][j]->plant->actcount*=2;
                     //如果为坚果，则相当于呗一个攻击力为400的僵尸咬了一口
                     if(grass[i][j]->plant->bh==2){
                         Zombie* temp=new Zombie(this,1);
                         temp->setatk(400);
                         grass[i][j]->plant->hit(temp);
                         delete temp;
                         this->update();
                     }
                 });
                 grass[i][j]->plant->bufflist[0]=true;
             }
             else if(buffname=="cold"){
                 //注意仅当为可攻击角色才可以拥有冰冻，目前只有1即为豌豆射手
                 if(grass[i][j]->plant->bh!=1)
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     ifselectshovel=false;
                     return;
                 }
                 //先判断是否已经拥有该种buff
                 if(grass[i][j]->plant->bufflist[1] || grass[i][j]->plant->bufflist[2])
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     selectplantnum=-1;
                     ifselectshovel=false;
                     return;
                 }
                 //可以含有该buff
                 int fw=0;
                 if(grass[i][j]->plant->buffstate==0){
                     fw=0;
                     grass[i][j]->plant->buffstate=1;
                 }
                 else if(grass[i][j]->plant->buffstate==1){
                     fw=1;
                     grass[i][j]->plant->buffstate=3;
                 }
                 else if(grass[i][j]->plant->buffstate==2)
                 {
                     fw=0;
                     grass[i][j]->plant->buffstate=3;
                 }
                 else
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     return;
                 }
                 //说明有两个buff切换为超级
                 if(grass[i][j]->plant->buffstate==3) grass[i][j]->plant->changesuper();
                 //说明只有一个buff切换为冰冻
                 else grass[i][j]->plant->changecold();
                 qDebug()<<"you have show the cold buff";
                 Buff* buff=new Buff(this,i,j,2,fw);
                 buff->setParent(this);
                 buff->setFixedSize(20,20);
                 buff->move((grasscolpos[buff->y]+grasscolpos[buff->y-1])/2-buff->width()/2+fw*40,grassrowpos[buff->x-1]/3+grassrowpos[buff->x]*2/3);
                 buff->show();
                 grass[i][j]->plant->buffpoint[1]=buff;
                 connect(buff,&Buff::die,[=](int num){
                     grass[i][j]->plant->bufflist[num-1]=false;
                     grass[i][j]->plant->buffpoint[num-1]=NULL;
                     if(buff->fw==0){
                         if(grass[i][j]->plant->buffstate==1)
                         {
                             grass[i][j]->plant->buffstate=0;
                             grass[i][j]->plant->changenormel();
                         }
                         else if(grass[i][j]->plant->buffstate==3)
                         {
                             grass[i][j]->plant->buffstate=2;
                             grass[i][j]->plant->changeviolent();
                         }
                     }
                     else
                     {
                         if(grass[i][j]->plant->buffstate==2)
                         {
                             grass[i][j]->plant->buffstate=0;
                             grass[i][j]->plant->changenormel();
                         }
                         else if(grass[i][j]->plant->buffstate==3)
                         {
                             grass[i][j]->plant->buffstate=1;
                             grass[i][j]->plant->changeviolent();
                         }
                     }
                     delete buff;
                     sunsum+=sunneed_buff[num-1]-25;
                     sunLabel->setText(QString::number(sunsum));
                 });
                 grass[i][j]->plant->bufflist[1]=true;
             }
             else if(buffname=="blood"){
                 //注意仅当为可攻击角色才可以拥有冰冻，目前只有1即为豌豆射手
                 if(grass[i][j]->plant->bh!=1)
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     return;
                 }
                 //先判断是否已经拥有该种buff
                 if(grass[i][j]->plant->bufflist[2] || grass[i][j]->plant->bufflist[1])
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     return;
                 }
                 //可以含有该buff
                 int fw=0;
                 if(grass[i][j]->plant->buffstate==0){
                     fw=0;
                     grass[i][j]->plant->buffstate=1;
                 }
                 else if(grass[i][j]->plant->buffstate==1){
                     fw=1;
                     grass[i][j]->plant->buffstate=3;
                 }
                 else if(grass[i][j]->plant->buffstate==2)
                 {
                     fw=0;
                     grass[i][j]->plant->buffstate=3;
                 }
                 else
                 {
                     setCursor(Qt::ArrowCursor);
                     selectbuffnum=-1;
                     ifselectshovel=false;
                     selectplantnum=-1;
                     return;
                 }
                 //说明有两个buff切换为超级
                 if(grass[i][j]->plant->buffstate==3) grass[i][j]->plant->changesuper();
                 qDebug()<<"you have show the blood buff";
                 Buff* buff=new Buff(this,i,j,3,fw);
                 buff->setParent(this);
                 buff->setFixedSize(20,20);
                 buff->move((grasscolpos[buff->y]+grasscolpos[buff->y-1])/2-buff->width()/2+fw*40,grassrowpos[buff->x-1]/3+grassrowpos[buff->x]*2/3);
                 buff->show();
                 grass[i][j]->plant->buffpoint[2]=buff;
                 connect(buff,&Buff::die,[=](int num){
                     grass[i][j]->plant->bufflist[num-1]=false;
                     grass[i][j]->plant->buffpoint[num-1]=NULL;
                     if(buff->fw==0){
                         if(grass[i][j]->plant->buffstate==1)
                         {
                             grass[i][j]->plant->buffstate=0;
                             grass[i][j]->plant->changenormel();
                         }
                         else if(grass[i][j]->plant->buffstate==3)
                         {
                             grass[i][j]->plant->buffstate=2;
                             grass[i][j]->plant->changeviolent();
                         }
                     }
                     else
                     {
                         if(grass[i][j]->plant->buffstate==2)
                         {
                             grass[i][j]->plant->buffstate=0;
                             grass[i][j]->plant->changenormel();
                         }
                         else if(grass[i][j]->plant->buffstate==3)
                         {
                             grass[i][j]->plant->buffstate=1;
                             grass[i][j]->plant->changeviolent();
                         }
                     }
                     delete buff;
                     sunsum+=sunneed_buff[num-1]-25;
                     sunLabel->setText(QString::number(sunsum));
                 });
                 grass[i][j]->plant->bufflist[2]=true;
             }
             else
             {
                 setCursor(Qt::ArrowCursor);
                 selectplantnum=-1;
                 selectbuffnum=-1;
                 ifselectshovel=false;
                 return;
             }
             sunsum-=sunneed_buff[selectbuffnum-1];
             sunLabel->setText(QString::number(sunsum));
             setCursor(Qt::ArrowCursor);
             selectbuffnum=-1;
             ifselectshovel=false;
             selectplantnum=-1;
         }
         //为拆卸植物
         else if(ifselectshovel)
         {
             //删除植物空间
             delete grass[i][j]->plant->label;
             delete grass[i][j]->plant->movie;   //删除额外申请空间
             for(int k=0;k<5;k++)
             {
                 if(grass[i][j]->plant->buffpoint[k]!=NULL)
                 {
                     delete grass[i][j]->plant->buffpoint[k];
                 }
             }

             //更新草坪状态和其上的僵尸
             grass[i][j]->plant=NULL;
             grass[i][j]->setiffree(true);
             for(QVector<Zombie*>::iterator it=grass[i][j]->zombielist.begin();
                 it!=grass[i][j]->zombielist.end();it++)
             {
                 (*it)->setifatk(false);
                 (*it)->changewalk();
             }
             //初始化鼠标状态
             setCursor(Qt::ArrowCursor);
             selectplantnum=-1;
             selectbuffnum=-1;
             ifselectshovel=false;

         }
         else
         {
             setCursor(Qt::ArrowCursor);
             selectplantnum=-1;
             selectbuffnum=-1;
             ifselectshovel=false;
         }
     }
     //该草坪不允许放植物
     else
     {
         setCursor(Qt::ArrowCursor);
         selectplantnum=-1;
         selectbuffnum=-1;
         ifselectshovel=false;
     }
 }
