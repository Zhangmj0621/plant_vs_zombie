#include "widget.h"
#include"globalconfig.h"
#include<getmap.h>
#include<QDebug>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qdir.setPath(a.applicationDirPath());
    GetMap getmap;
    getmap.readmap();
    for(int i=1;i<=5;i++)
        for(int j=1;j<=9;j++)
        {
            if(mapbool[i][j]==false) qDebug()<<0;
            else qDebug()<<1;
        }
    Widget w;
    w.show();
    return a.exec();
}
