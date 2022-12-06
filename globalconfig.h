#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include<QString>
#include<QPair>
#include<QDir>

extern int grassrow;
extern int grasscol;
extern int grassrowpos[6];
extern int grasscolpos[10];

extern int seedwidth;
extern int seedheight;
extern int seedstartx;
extern int seedstarty;

extern QString seedname[8];
extern int seednum;
extern int sunneed[8];

extern int plantheight;
extern int plantwidth;

extern int sunsum;

extern bool mapbool[6][10];

extern QDir qdir;

QPair<int,int> thegrass(int x,int y);

extern int seedwidth_buff;
extern int seedheight_buff;
extern int seedstartx_buff;
extern int seedstarty_buff;

extern QString seedname_buff[8];
extern int seednum_buff;
extern int sunneed_buff[8];
#endif // GLOBALCONFIG_H
