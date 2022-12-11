#include "peashooter.h"

void Peashooter::act(){

}

void Peashooter::mousePressEvent(QMouseEvent*){

}

void Peashooter::paintEvent(QPaintEvent *){

}

void Peashooter::changenormel(){
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

void Peashooter::changeviolent(){
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

void Peashooter::changecold(){
    QMovie* movie1;
    movie1=new QMovie(this->coldpix);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}

void Peashooter::changesuper(){
    QMovie* movie1;
    movie1=new QMovie(this->superpix);
    movie1->resized(QSize(50,50));
    movie1->start();
    label->setMovie(movie1);
    //label->show();
    delete movie;
    movie=movie1;
    parent->update();
}
