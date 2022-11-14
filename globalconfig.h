#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include<QString>
#include<QPair>

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

QPair<int,int> thegrass(int x,int y);
#endif // GLOBALCONFIG_H
