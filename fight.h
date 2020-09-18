#ifndef FIGHT_H
#define FIGHT_H

#include <QMainWindow>
#include <QTimer>
#include <QLCDNumber>
#include "config.h"
#include "map.h"
#include "hero.h"
#include "hero2.h"

class fight : public QMainWindow
{
    Q_OBJECT
public:
    explicit fight(QWidget *parent = nullptr);
    void initscene();//初始化游戏

    void playgame();//开始游戏

    void updateposition();//更新坐标函数

    void paintEvent(QPaintEvent *event);//画图事件

    void keyPressEvent(QKeyEvent *e);//键盘按压事件

    void keyReleaseEvent(QKeyEvent *e);//键盘释放事件

    void timerEvent(QTimerEvent *e);//控制移动时间事件

    void detection();//碰撞检测函数

    void changeDartPic();//改变图片函数

    int bleed1,bleed2 ;//血量

    int energy1,energy2 ;//能量



    map m_map;

    hero m_hero;

    hero2 m_hero2;

    QTimer m_Timer;

    QTimer picTimer;

    bool ispause;//是否暂停

    QPixmap pausepic;//暂停游戏

    int dartsInterval;


signals:

public slots:
};

#endif // FIGHT_H
