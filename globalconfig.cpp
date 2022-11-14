#include "globalconfig.h"

//草地配置
int grassrow=5;
int grasscol=9;
int grassrowpos[6]={95,269,414,578,704,860};
int grasscolpos[10]={340,460,561,685,790,908,1021,1126,1237,1358};

//卡片槽配置
int seedwidth=70;
int seedheight=100;
int seedstartx=130;
int seedstarty=17;
QString seedname[8]={"SunFlower","Peashooter","WallNut","Repeater","IceShooter","","",""};;
int seednum=3;
int sunneed[8]={50,100,50,0,0,0,0,0};

//植物配置
int plantheight=120;
int plantwidth=90;
int sunsum=5000;

//获取草编号
QPair<int,int> thegrass(int x,int y){
    int g_r,g_c;    //第几行第几列
    if(340<=x&&x<=460) g_c=1;
    else if(460<x&&x<=561) g_c=2;
    else if(561<x&&x<=685) g_c=3;
    else if(685<x&&x<=790) g_c=4;
    else if(790<x&&x<=908) g_c=5;
    else if(908<x&&x<=1021) g_c=6;
    else if(1021<x&&x<=1126) g_c=7;
    else if(1126<x&&x<=1237) g_c=8;
    else if(1237<x&&x<=1358) g_c=9;
    else g_c=-1;

    if(95<=y&&y<=269) g_r=1;
    else if(269<y&&y<=414) g_r=2;
    else if(414<y&&y<=578) g_r=3;
    else if(578<y&&y<=704) g_r=4;
    else if(704<y&&y<=860) g_r=5;
    else g_r=-1;

    return QPair<int,int>(g_r,g_c);
}
