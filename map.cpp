#include "map.h"
#include "config.h"

map::map()
{
    //初始化加载地图对象
    m_map1.load(MAP_PATH);
    m_map2.load(MAP_PATH);

    m_map1_.load(MAP_PATH_);
    m_map2_.load(MAP_PATH_);

    m1.load(MAP_PATH_1);
    m2.load(MAP_PATH_1);

    //设置坐标
    m_map1_posX = GAME_WIDTH;
    m_map2_posX = 0;

    m_map1__posX = GAME_WIDTH;
    m_map2__posX = 0;

    m1X = GAME_WIDTH;
    m2X = 0;

    //设置滚动速度
    m_scroll_speed = MAP_SCROLL_SPEED;
}

void map::mapPosition()
{
    //处理第一张图片滚动
    m_map1_posX -= m_scroll_speed;
    if(m_map1_posX <= 0)
    {
        m_map1_posX = GAME_WIDTH;
    }

    //处理第二张图片滚动
    m_map2_posX -= m_scroll_speed;
    if(m_map2_posX <= -GAME_WIDTH)
    {
        m_map2_posX = 0;
    }
}

void map::mapPosition_()
{
    m_map1__posX -= m_scroll_speed;
    if(m_map1__posX <= 0)
    {
        m_map1__posX = GAME_WIDTH;
    }

    //处理第二张图片滚动
    m_map2__posX -= m_scroll_speed;
    if(m_map2__posX <= -GAME_WIDTH)
    {
        m_map2__posX = 0;
    }
}

void map::mPosition()
{
    m1X -= m_scroll_speed;
    if(m1X <= 0)
    {
        m1X = GAME_WIDTH;
    }

    //处理第二张图片滚动
    m2X -= m_scroll_speed;
    if(m2X <= -GAME_WIDTH)
    {
        m2X = 0;
    }
}
