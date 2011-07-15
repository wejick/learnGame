/* 
copyright	: Gian Giovani 2011
Contact		: wejick@gmail.com
Blog		: wejick.wordpress.com

*/

#include "pong.h"
#include "math.h"
#include <QApplication>
#include <iostream>

Pong::Pong(QWidget *parent)
    : QWidget(parent)
{
    //property widget
    {
        winSize=400;
        setMinimumSize(winSize,winSize);
        setMaximumSize(winSize,winSize);
        g = new QPainter();
        timer=new QTimer;
        setFocusPolicy(Qt::ClickFocus);
        setFocus();
    }
    //property game
    {
        width=winSize;
        height=winSize;
        //Paddle
        paddle1=QRect(0,height/2,10,50);
        paddle2=QRect(width-10,height/2,10,50);
        kec_paddle = 5;
        //bola
        bola=QRect((width/2)-15,height/2,15,15);
        kecx_bola = 3;
        kecy_bola = 5;
        //point
        point=0;
        life=3;
        //gerak
        naik=kec_paddle;
    }
    connect(timer,SIGNAL(timeout()),this,SLOT(draw()));
    timer->start(1000/30);
}
Pong::~Pong()
{

}

void Pong::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Up :
        if(paddle1.top()>=0)
        paddle1.moveBottom(paddle1.bottom()-kec_paddle);
        break;
    case Qt::Key_Down:
        if(paddle1.bottom()<=height)
        paddle1.moveBottom(paddle1.bottom()+kec_paddle);
        break;
    default :
        break;
    }
}

void Pong::doAi(){
    std::cout<<"ai start  ";
    if(bola.x()>width/2){
        if(paddle2.top()+5!=bola.y()){
            if(bola.top()<paddle2.top()+5) {
                if((0+kecx_bola)>0){
                    std::cout<<"naik"<<"\n";
                    paddle2.moveBottom(paddle2.bottom()-naik);
                }
            }
            if(bola.top()>paddle2.top()+10) {
                if((0+kecx_bola)>0){
                    std::cout<<"turun"<<"\n";
                    paddle2.moveBottom(paddle2.bottom()+naik);
                }
            }
        }
    }
}

void Pong::updatePosisi(){

    if((bola.x()+bola.width())>=width){ //bola memantul dari dinding kiri
        kecx_bola*=-1;
        //perlu diloncatkan biar gak stuck
        bola.moveRight((bola.x()+bola.width())+kecx_bola);
        bola.moveTop(bola.y()+kecy_bola);
    }
    if((bola.x()+bola.width())<=0+bola.width()) {
        life--;
        kecx_bola*=-1;
    }
    if(bola.y()<=0)
        kecy_bola*=-1;
    if(bola.y()>=height-bola.height())
        kecy_bola*=-1;
    //pantul paddle1
    if((bola.x())<=paddle1.width()){
        if(bola.y()>=paddle1.top() && (bola.y()<=paddle1.bottom())){
            point++;
            kecx_bola*=-1;
            //perlu diloncatkan biar gak stuck
            bola.moveRight((bola.x()+bola.width())+kecx_bola);
            bola.moveTop(bola.y()+kecy_bola);
            QApplication::beep();
        }
    }
    //pantul paddle2
    if((bola.x()+bola.width())>=width-paddle2.width()){
        if(bola.y()>=paddle2.top() && (bola.y()<=paddle2.bottom())){
            kecx_bola*=-1;
            //perlu diloncatkan biar gak stuck
            bola.moveRight((bola.x()+bola.width())+kecx_bola);
            bola.moveTop(bola.y()+kecy_bola);
            QApplication::beep();
        }
    }

    bola.moveRight((bola.x()+bola.width())+kecx_bola); //gerak bola sumbu x
    bola.moveTop(bola.y()+kecy_bola); //gerak bola sumbu y
}
void Pong::paintEvent(QPaintEvent *){
    g->begin(this);
    //bola
    drawBack();
    g->setBrush(Qt::red);
    g->fillRect(bola,Qt::red);
    g->drawRect(bola);    
    g->setBrush(Qt::blue);
    g->fillRect(paddle1,Qt::blue);
    g->drawRect(paddle1);
    g->fillRect(paddle2,Qt::blue);
    g->drawRect(paddle2);
    g->end();
}
void Pong::draw(){
    if(life<=0) {
        timer->stop();
    }
    doAi();
    updatePosisi();
    update();
}
void Pong::drawBack(){
    g->setBrush(Qt::black);
    g->drawLine(width/2,0,width/2,height);
    g->drawText(3,15,"Life : "+QByteArray::number(life));
    g->drawText(3,30,"Point : "+QByteArray::number(point));
}
