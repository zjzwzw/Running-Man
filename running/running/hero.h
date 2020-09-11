#ifndef HERO_H
#define HERO_H
#include <QPixmap>


class hero
{
public:
    hero();


    //英雄资源 对象
    QPixmap myHero;
    QPixmap rightHero[7];
    QPixmap leftHero[7];

    //英雄坐标
    int m_X;
    int m_Y;

    //英雄的矩形边框
    QRect m_Rect;

   void setPosition(int x, int y);

   void updatepic();//向右更新图片

   void updateleftpic();//向左更新图片

   //键盘哪个键被按下
   bool W_judge;
   bool A_judge;
   bool D_judge;
   bool S_judge;
   bool isjump;
   bool status;//0上，1下跳跃状态
};

#endif // HERO_H
