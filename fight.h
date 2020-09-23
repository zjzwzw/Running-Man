#ifndef FIGHT_H
#define FIGHT_H

#include <QMainWindow>
#include <QTimer>
#include <QLCDNumber>
#include "config.h"
#include "map.h"
#include "hero.h"
#include "hero2.h"
#include "myfire.h"
#include "myice.h"

class fight : public QMainWindow
{
    Q_OBJECT
public:
    explicit fight(QWidget *parent = nullptr);
    void initscene();//初始化游戏
    void playgame();//开始游戏
    void updateposition();//更新坐标函数
    void iceShow();//冰柱出现
    void fireShow();//火球出现
    void paintEvent(QPaintEvent *event);//画图事件
    void keyPressEvent(QKeyEvent *e);//键盘按压事件
    void keyReleaseEvent(QKeyEvent *e);//键盘释放事件
    void timerEvent(QTimerEvent *e);//控制移动时间事件
    void detection();//碰撞检测函数
    void changeDartPic();//改变图片函数

    int bleed1,bleed2 ;//血量
    int energy1,energy2 ;//能量

    //地图对象
    map m_map;

    //英雄对象
    hero m_hero;
    hero2 m_hero2;

    //冰柱对象数组
    myice ice[DARTS_num];
    myice ice_[DARTS_num];

    //火球对象数组
    myfire fire[DARTS_num];
    myfire fire_[DARTS_num];

    QTimer m_Timer;//背景定时器
    QTimer picTimer;//英雄更新定时器

    bool ispause;//是否暂停
    QPixmap pausepic;//暂停游戏
    int dartsInterval;


signals:

public slots:
};

#endif // FIGHT_H
