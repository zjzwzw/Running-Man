#include "darts.h"
#include "config.h"

darts::darts()
{
    //飞镖资源加载
    dartspic[0].load("://image/darts1.png");
    dartspic[1].load("://image/darts2.png");
    dartspic[2].load("://image/darts3.png");

    mydarts.load("://image/darts1.png");



    //飞镖位置
    m_X = 0;
    m_Y = 0;

    //飞镖状态
    m_Free = true;

    //飞镖速度
    m_Speed = dartsSpeed;

    //飞镖矩形
    m_Rect.setWidth(mydarts.width());
    m_Rect.setHeight(mydarts.height());
    m_Rect.moveTo(m_X,m_Y);
}

void darts::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    m_X -= m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_X <= -mydarts.width())
    {
        m_Free = true;
    }
}







