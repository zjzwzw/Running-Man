#ifndef MAP_H
#define MAP_H
#include <QPixmap>


class map
{
public:
    map();

    void mapPosition();

    void mapPosition_();

    void mPosition();

    //地图图片对象
    QPixmap m_map1;
    QPixmap m_map2;

    QPixmap m_map1_;
    QPixmap m_map2_;

    QPixmap m1;
    QPixmap m2;

    //地图Y轴坐标
    int m_map1_posX;
    int m_map2_posX;

    int m_map1__posX;
    int m_map2__posX;

    int m1X;
    int m2X;

    //地图滚动幅度
    int m_scroll_speed;
};

#endif // MAP_H
