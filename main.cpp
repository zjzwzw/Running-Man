#include "mainwindow.h"
#include <QApplication>
#include "home_page.h"
#include <QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    home_page h;
    h.show();


    return a.exec();
}
