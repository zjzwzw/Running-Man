#include "mainwindow.h"
#include <QApplication>
#include <QResource>
#include "home_page.h"
#include <QSound>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QResource::registerResource(res_PATH);

    home_page h;
    h.show();
    return a.exec();
}
