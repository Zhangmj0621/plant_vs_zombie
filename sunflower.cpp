#include "sunflower.h"

void SunFlower::act(){

}

void SunFlower::mousePressEvent(QMouseEvent*){

}

void SunFlower::paintEvent(QPaintEvent *){

}

void SunFlower::changelight(){
    QMovie* movie1=new QMovie(this->lightmovie);
    movie1->resized(QSize(200,200));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}

void SunFlower::changegeneral(){
    QMovie* movie1=new QMovie(this->plantmovie);
    movie1->resized(QSize(200,200));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
}
