/* 
copyright	: Gian Giovani 2011
Contact		: wejick@gmail.com
Blog		: wejick.wordpress.com

*/

#ifndef PONG_H
#define PONG_H

#include <QtGui/QWidget>
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

class Pong : public QWidget
{
    Q_OBJECT

public:
    Pong(QWidget *parent = 0);
    ~Pong();

private:
    int winSize;
    QRect paddle1;
    QRect paddle2;
    int kec_paddle;
    QRect bola;
    int kecx_bola;
    int kecy_bola;
    int width;
    int height;
    QPainter *g;
    QTimer *timer;
    int point;
    int life;
    int naik;

    void keyPressEvent(QKeyEvent *event);
    void updatePosisi();
    void doAi();
    void paintEvent(QPaintEvent *);
    void drawBack();

public slots:
    void draw();
};

#endif // PONG_H
