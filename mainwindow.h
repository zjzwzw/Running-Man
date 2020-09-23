#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLCDNumber>
#include "config.h"
#include "map.h"
#include "hero.h"
#include "darts.h"
#include "hero2.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initscene();//初始化游戏
    void playgame();//开始游戏
    void updateposition();//更新坐标函数
    void paintEvent(QPaintEvent *event);//画图事件
    void keyPressEvent(QKeyEvent *e);//键盘按压事件
    void keyReleaseEvent(QKeyEvent *e);//键盘释放事件
    void timerEvent(QTimerEvent *e);//控制移动时间事件
    void dartsShow();//飞镖出现函数
    void detection();//碰撞检测函数
    void changeDartPic();//改变图片函数

    int bleed ;//血量
    double energy ;//能量
    int bleed_;//p2血量
    double energy_;//p2能量

    int t;//游戏时间
    int gametype;//游戏阶段
    int people;//游戏人数

    map m_map;//地图对象
    hero m_hero;//英雄对象
    hero2 m_hero2;//p2对象

    QTimer m_Timer;//背景定时器
    QTimer picTimer;//图片更新定时器
    QTimer gameTimer;//计时定时器

    QLCDNumber m_LCD;//计时器

    darts m_darts[DARTS_num];//飞镖对象数组
    int dartsInterval;//飞镖出现间隔

    bool ispause;//是否暂停
    QPixmap pausepic;//暂停游戏图片
    QPixmap pausepic_;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
