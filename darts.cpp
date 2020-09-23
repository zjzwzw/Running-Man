#include "darts.h"
#include "config.h"
#include "hero2.h"
#include "hero.h"

darts::darts()
{
    //飞镖资源加载
    mydarts.load("://image/darts1.png");
    dartspic[0].load("://image/darts1.png");
    dartspic[1].load("://image/darts2.png");
    dartspic[2].load("://image/darts3.png");

    //飞镖状态初始化
    dart_Free = true;

    //飞镖速度初始化
    m_Speed = dartsSpeed;

    //飞镖矩形初始化
    dart_Rect.setWidth(mydarts.width());
    dart_Rect.setHeight(mydarts.height());
    dart_Rect.moveTo(dart_X,dart_Y);
}

void darts::updatePosition()
{
    //空闲状态，不计算坐标
    if(dart_Free)
    {
        return;
    }
    //飞镖向左飞
    dart_X -= m_Speed;
    dart_Rect.moveTo(dart_X,dart_Y);

    if(dart_X <= -mydarts.width())
        dart_Free = true; 
}






