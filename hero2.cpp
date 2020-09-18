#include "hero2.h"
#include "config.h"

hero2::hero2()
{
    //加载资源

    rightHero[0].load("://image/1_2.png");
    rightHero[1].load("://image/2_2.png");
    rightHero[2].load("://image/3_2.png");
    rightHero[3].load("://image/4_2.png");
    rightHero[4].load("://image/5_2.png");
    rightHero[5].load("://image/6_2.png");
    rightHero[6].load("://image/7_2.png");

    leftHero[0].load("://image/1L_2.png");
    leftHero[1].load("://image/2L_2.png");
    leftHero[2].load("://image/3L_2.png");
    leftHero[3].load("://image/4L_2.png");
    leftHero[4].load("://image/5L_2.png");
    leftHero[5].load("://image/6L_2.png");
    leftHero[6].load("://image/7L_2.png");

    upHero.load("://image/rise_2.png");
    downHero.load("://image/drop_2.png");

    upHeroL.load("://image/riseL_2.png");
    downHeroL.load("://image/dropL_2.png");

    attack.load("://image/attack2.png");
    attackL.load("://image/attack2L.png");

    dash[0].load("://image/dash1.png");
    dash[1].load("://image/dash2.png");
    dash[2].load("://image/dash3.png");
    dash[3].load("://image/dash4.png");
    dash[4].load("://image/dash5.png");


    //初始化坐标
    m_X = GAME_WIDTH * 0.6;
    m_Y = GAME_HEIGHT - 150;

    //矩形边框 碰撞检测用
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);

    attack_Rect.setWidth(attack.width());
    attack_Rect.setHeight(attack.height());


    attackL_Rect.setWidth(attackL.width());
    attackL_Rect.setHeight(attackL.height());



    UP_judge =false;
    RIGHT_judge =false;
    LEFT_judge =false;
    DOWN_judge =false;
    L_judge =false;
    isjump =false;
    status =true;

    //初始化间隔记录变量

}



void hero2::updatepic()
{
    static int m=0;
    myHero=rightHero[m];
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(L_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(L_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
    m++;
    if(m>=6)
        m=0;

}

void hero2::updateleftpic()
{
    static int m=0;
    myHero=leftHero[m];
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(L_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(L_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
    m++;
    if(m>=6)
        m=0;
}

void hero2::updateuppic()
{
    myHero=upHero;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(L_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(L_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero2::updatedownpic()
{
    myHero=downHero;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(L_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(L_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero2::updateuppicL()
{
    myHero=upHeroL;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(L_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(L_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero2::updatedownpicL()
{
    myHero=downHeroL;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(L_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(L_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero2::updatedash()
{
    static int k=0;
    mydash=dash[k];
    k++;
    if(k>4)
        k=0;
}





