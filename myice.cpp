#include "myice.h"
#include "config.h"

myice::myice()
{
    //资源加载
    ice.load("://image/ice1.png");
    ice_.load("://image/ice2.png");

    //冰柱是否空闲
    ice_Free=true;
    ice_FreeR=true;

    m_Speed = dartsSpeed;

    ice_Rect.setWidth(ice.width());
    ice_Rect.setHeight(ice.height());
    ice_Rect.moveTo(ice_X,ice_Y);

    ice_RectR.setWidth(ice_.width());
    ice_RectR.setHeight(ice_.height());
    ice_RectR.moveTo(ice_XR,ice_YR);
}

void myice::updateicePos()
{
    if(ice_Free)
    {
        return;
    }

    ice_X -= m_Speed+70;
    ice_Rect.moveTo(ice_X,ice_Y);

    if(ice_X <= -ice.width()||ice_X>GAME_WIDTH)
    {
        ice_Free = true;
    }
}

void myice::updateicePosR()
{
    if(ice_FreeR)
    {
        return;
    }

    ice_XR += m_Speed+70;
    ice_RectR.moveTo(ice_XR,ice_YR);

    if(ice_XR <= -ice.width()||ice_XR>GAME_WIDTH)
    {
        ice_FreeR = true;
    }
}
