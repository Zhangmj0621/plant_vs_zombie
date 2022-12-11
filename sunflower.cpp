#include "sunflower.h"

void SunFlower::act(){

}

void SunFlower::mousePressEvent(QMouseEvent*){

}

void SunFlower::paintEvent(QPaintEvent *){

}

void SunFlower::changelight(){
    QMovie* movie1;
    if(!bufflist[0]) movie1=new QMovie(this->lightmovie);
    else movie1=new QMovie(this->violentlightmovie);
    movie1->resized(QSize(200,200));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}

void SunFlower::changegeneral(){
    QMovie* movie1;
    if(!bufflist[0]) movie1=new QMovie(this->plantmovie);
    else movie1=new QMovie(this->violentpix);
    movie1->resized(QSize(200,200));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}

void SunFlower::changenormel(){
    QMovie* movie1;
    movie1=new QMovie(this->plantmovie);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}

void SunFlower::changeviolent(){
    QMovie* movie1;
    movie1=new QMovie(this->violentpix);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}
