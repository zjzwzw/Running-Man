#ifndef MYICE_H
#define MYICE_H
#include <QPixmap>


class myice
{
public:
    myice();

    void updateicePos();//冰柱左更新图片
    void updateicePosR();//冰柱右更新图片


    QPixmap ice;
    QPixmap ice_;

    //左冰柱和右冰柱位置
    int ice_X;
    int ice_Y;

    int ice_XR;
    int ice_YR;

    //左冰柱和右冰柱矩形框
    QRect ice_Rect;
    QRect ice_RectR;

    //是否空闲
    bool ice_Free;
    bool ice_FreeR;

    //冰柱速度
    int m_Speed;
};

#endif // MYICE_H
