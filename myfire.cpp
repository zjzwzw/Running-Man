#include "myfire.h"
#include "config.h"

myfire::myfire()
{
    //添加资源
    fire.load("://image/fire1_.png");
    fire_.load("://image/fire2_.png");

    //火球是否空闲
    fire_Free=true;
    fire_FreeR=true;

    m_Speed = dartsSpeed;

    //矩形检测设定
    fire_Rect.setWidth(fire.width());
    fire_Rect.setHeight(fire.height());
    fire_Rect.moveTo(fire_X,fire_Y);

    fire_RectR.setWidth(fire_.width());
    fire_RectR.setHeight(fire_.height());
    fire_RectR.moveTo(fire_XR,fire_YR);

}

void myfire::updatefirePos()
{
    if(fire_Free)
    {
        return;
    }
    fire_X -= m_Speed+70;
    fire_Rect.moveTo(fire_X,fire_Y);

    if(fire_X <= -fire.width()||fire_X>GAME_WIDTH)
    {
        fire_Free = true;
    }
}

void myfire::updatefirePosR()
{
    if(fire_FreeR)
    {
        return;
    }
    fire_XR += m_Speed+70;
    fire_RectR.moveTo(fire_XR,fire_YR);

    if(fire_XR <= -fire.width()||fire_XR>GAME_WIDTH)
    {
        fire_FreeR = true;
    }
}
