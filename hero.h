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
    QPixmap upHero;
    QPixmap downHero;
    QPixmap upHeroL;
    QPixmap downHeroL;

    QPixmap attack;
    QPixmap attackL;

    QPixmap mydash;
    QPixmap dash[5];

    QPixmap myfire;
    QPixmap fire[4];

    QPixmap dazhao;
    QPixmap Dazhao[12];


    //大招火球坐标
    int x;
    int y;

    //英雄坐标
    int m_X;
    int m_Y;

    //英雄的矩形边框
    QRect m_Rect;

    //攻击矩形检测
    QRect attack_Rect;
    QRect attackL_Rect;

    //火球矩形检测
    QRect fire_Rect;

    void updatedazhaopic();//大招图片更新
    void updatefirepic();//更新火球图片
   void updatepic();//向右更新图片
   void updateleftpic();//向左更新图片
   void updateuppic();//向上右更新图片
   void updatedownpic();//向下右更新图片
   void updateuppicL();//向上左更新图片
   void updatedownpicL();//向上右更新图片
   void updatedash();//冲刺护盾图片更新

   bool isdead;


   //键盘哪个键被按下
   bool W_judge;
   bool A_judge;
   bool D_judge;
   bool S_judge;
   bool J_judge;
   bool K_judge;
   bool U_judge;
   bool isjump;//是否跳跃
   bool status;//0上，1下跳跃状态
};

#endif // HERO_H
