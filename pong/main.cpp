/* 
copyright	: Gian Giovani 2011
Contact		: wejick@gmail.com
Blog		: wejick.wordpress.com

*/

#include <QtGui/QApplication>
#include <pong.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Pong game;
    game.show();
    return a.exec();
}
