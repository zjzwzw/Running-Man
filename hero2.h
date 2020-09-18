#ifndef HERO2_H
#define HERO2_H
#include <QPixmap>

class hero2
{
public:
    hero2();


    //英雄资源 对象
    QPixmap myHero;
    QPixmap rightHero[7];
    QPixmap leftHero[7];
    QPixmap upHero;
    QPixmap downHero;
    QPixmap upHeroL;
    QPixmap downHeroL;

    QPixmap attack;
    QPixmap attackL;

    QPixmap mydash;
    QPixmap dash[5];


    //英雄坐标
    int m_X;
    int m_Y;

    //英雄的矩形边框
    QRect m_Rect;

    //攻击矩形检测
    QRect attack_Rect;
    QRect attackL_Rect;

   void setPosition(int x, int y);

   void updatepic();//向右更新图片

   void updateleftpic();//向左更新图片

   void updateuppic();//向上右更新图片

   void updatedownpic();//向下右更新图片

   void updateuppicL();//向上左更新图片

   void updatedownpicL();//向上右更新图片

   void updatedash();

   bool isdead;

   //键盘哪个键被按下
   bool UP_judge;
   bool RIGHT_judge;
   bool LEFT_judge;
   bool DOWN_judge;
   bool L_judge;
   bool isjump;
   bool status;//0上，1下跳跃状态
};


#endif // HERO2_H
