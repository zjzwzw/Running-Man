#ifndef HOME_PAGE_H
#define HOME_PAGE_H

#include <QMainWindow>
#include "map.h"
#include <QTimer>
#include <QSound>

namespace Ui {
class home_page;
}

class home_page : public QMainWindow
{
    Q_OBJECT

public:
    explicit home_page(QWidget *parent = nullptr);
    ~home_page();


    map m_map;//地图对象

    QTimer m_Timer;//背景定时器

    QTimer t;//控件移动定时器

    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);

private:
    Ui::home_page *ui;
};

#endif // HOME_PAGE_H
