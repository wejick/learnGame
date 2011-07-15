/* 
copyright	: Gian Giovani 2011
Contact		: wejick@gmail.com
Blog		: wejick.wordpress.com
<<license>>
*/

#include <QtGui/QApplication>
#include "mainwin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWin w;
    w.show();

    return a.exec();
}
