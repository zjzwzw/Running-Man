#ifndef DARTS_H
#define DARTS_H
#include <QPixmap>


class darts
{
public:
    darts();
    //更新坐标
    void updatePosition();

public:
    //飞镖资源
    QPixmap mydarts;
    QPixmap dartspic[3];//三个不同状态的飞镖

    //位置
    int m_X;
    int m_Y;

    //飞镖矩形边框
    QRect m_Rect;

    //状态
    bool m_Free;

    //速度
    int m_Speed;
};

#endif // DARTS_H
