#include "hero.h"
#include "config.h"

hero::hero()
{
    //加载飞机图片资源

    rightHero[0].load("://image/1.png");
    rightHero[1].load("://image/2.png");
    rightHero[2].load("://image/3.png");
    rightHero[3].load("://image/4.png");
    rightHero[4].load("://image/5.png");
    rightHero[5].load("://image/6.png");
    rightHero[6].load("://image/7.png");

    leftHero[0].load("://image/1L.png");
    leftHero[1].load("://image/2L.png");
    leftHero[2].load("://image/3L.png");
    leftHero[3].load("://image/4L.png");
    leftHero[4].load("://image/5L.png");
    leftHero[5].load("://image/6L.png");
    leftHero[6].load("://image/7L.png");

    //初始化坐标
    m_X = GAME_WIDTH * 0.1;
    m_Y = GAME_HEIGHT - 150;

    //矩形边框 碰撞检测用
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);

    D_judge =false;
    A_judge =false;
    W_judge =false;
    S_judge =false;
    isjump =false;
    status =true;

    //初始化间隔记录变量

}

void hero::setPosition(int x, int y)
{
    m_X = x;
    m_Y = y;
    m_Rect.moveTo(m_X,m_Y);
}

void hero::updatepic()
{
    static int m=0;
    myHero=rightHero[m];
    m++;
    if(m>=6)
        m=0;

}

void hero::updateleftpic()
{
    static int m=0;
    myHero=leftHero[m];
    m++;
    if(m>=6)
        m=0;
}
















