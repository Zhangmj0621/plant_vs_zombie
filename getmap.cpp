#include "getmap.h"
#include<fstream>
#include"globalconfig.h"
#include<iostream>
using namespace std;

GetMap::GetMap()
{

}

void GetMap::readmap(){
    fstream io_file(qdir.absoluteFilePath("map.txt").toStdString(),ios::in|ios::out);
    int temp;
    for(int i=1;i<=5;i++)
        for(int j=1;j<=9;j++)
        {
            io_file>>temp;
            if(temp==0) mapbool[i][j]=false;
            else mapbool[i][j]=true;
        }
    io_file.close();
}

void GetMap::writemap(){
    fstream io_file(qdir.absoluteFilePath("map.txt").toStdString(),ios::in|ios::out);
    for(int i=1;i<=5;i++)
        for(int j=1;j<=9;j++)
        {
            if(j!=9) io_file<<mapbool[i][j]<<" ";
            else io_file<<mapbool[i][j]<<endl;
        }
    io_file.close();
}
