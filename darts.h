#ifndef DARTS_H
#define DARTS_H
#include <QPixmap>


class darts
{
public:
    darts();

    void updatePosition();//更新坐标

public:

    //飞镖资源
    QPixmap mydarts;
    QPixmap dartspic[3];//三个不同状态的飞镖

    //位置
    int dart_X;
    int dart_Y;

    //飞镖矩形边框
    QRect dart_Rect;

    //状态
    bool dart_Free;

    //速度
    int m_Speed;
};

#endif // DARTS_H
