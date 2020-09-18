#include "hero.h"
#include "config.h"

hero::hero()
{
    //添加资源

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

    upHero.load("://image/rise.png");
    downHero.load("://image/drop.png");

    upHeroL.load("://image/riseL.png");
    downHeroL.load("://image/dropL.png");

    attack.load("://image/attack.png");
    attackL.load("://image/attackL.png");

    dash[0].load("://image/dash1.png");
    dash[1].load("://image/dash2.png");
    dash[2].load("://image/dash3.png");
    dash[3].load("://image/dash4.png");
    dash[4].load("://image/dash5.png");

    fire[0].load("://image/fire1.png");
    fire[1].load("://image/fire2.png");
    fire[2].load("://image/fire3.png");
    fire[3].load("://image/fire4.png");

    //初始化坐标
    m_X = GAME_WIDTH * 0.1;
    m_Y = GAME_HEIGHT - 150;

    //矩形边框 碰撞检测用
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);

    attack_Rect.setWidth(attack.width());
    attack_Rect.setHeight(attack.height());


    attackL_Rect.setWidth(attackL.width());
    attackL_Rect.setHeight(attackL.height());


    fire_Rect.setWidth(myfire.width());
    fire_Rect.setHeight(myfire.height());



    D_judge =false;
    A_judge =false;
    W_judge =false;
    S_judge =false;
    J_judge =false;
    K_judge =false;
    isjump =false;
    status =true;


    //初始化间隔记录变量

}

void hero::updatefirepic()
{
    static int m=0;
    static int fireSpeed = 0;
    myfire=fire[m];
    fire_Rect.setWidth(myfire.width());
    fire_Rect.setHeight(myfire.height());
    fireSpeed+=15;
    x=fireSpeed-600;
    y=0;
    fire_Rect.moveTo(x,y);
    if(x>GAME_WIDTH)
    {
        x=-600;
        y=-10000;
        fire_Rect.moveTo(x,y);
        fireSpeed=0;
        K_judge=false;
    }

    m++;
    if(m>=4)
        m=0;
}

void hero::updatepic()
{
    static int m=0;
    myHero=rightHero[m];
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(J_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(J_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
    m++;
    if(m>=6)
        m=0;

}

void hero::updateleftpic()
{
    static int m=0;
    myHero=leftHero[m];
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(J_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(J_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
    m++;
    if(m>=6)
        m=0;
}

void hero::updateuppic()
{
    myHero=upHero;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(J_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(J_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero::updatedownpic()
{
    myHero=downHero;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(J_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(J_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero::updateuppicL()
{
    myHero=upHeroL;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(J_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(J_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero::updatedownpicL()
{
    myHero=downHeroL;
    m_Rect.setWidth(myHero.width());
    m_Rect.setHeight(myHero.height());
    m_Rect.moveTo(m_X,m_Y);
    if(J_judge)
    {
        attackL_Rect.moveTo(m_X-120,m_Y);
        attack_Rect.moveTo(m_X+75,m_Y);
    }
    else if(J_judge==false)
    {
        attackL_Rect.moveTo(-10000,-10000);
        attack_Rect.moveTo(-10000,-10000);
    }
}

void hero::updatedash()
{
    static int k=0;
    mydash=dash[k];
    k++;
    if(k>4)
        k=0;
}
















