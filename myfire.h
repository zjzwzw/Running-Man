#ifndef MYFIRE_H
#define MYFIRE_H
#include<QPixmap>


class myfire
{
public:
    myfire();


    void updatefirePos();//火球左更新图片
    void updatefirePosR();//火球右更新图片

    QPixmap fire;
    QPixmap fire_;

    //左火球和右火球位置
    int fire_X;
    int fire_Y;

    int fire_XR;
    int fire_YR;

    //左火球和右火球矩形框
    QRect fire_Rect;
    QRect fire_RectR;

    //是否空闲
    bool fire_Free;
    bool fire_FreeR;

    //火球速度
    int m_Speed;
};

#endif // MYFIRE_H
