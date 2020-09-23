#include "fight.h"
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include "config.h"
#include <QMessageBox>
#include <QFont>
#include <QSound>
#include <QPushButton>
#include "home_page.h"

fight::fight(QWidget *parent) :
    QMainWindow(parent)

{
    //初始化场景
    initscene();
    //事件时间开始
    this->startTimer(EVENT_RATE);
    //键盘事件按键不相互影响
    setFocusPolicy(Qt::StrongFocus);
    //暂停图片加载
    pausepic.load("://image/pause2.png");
    //场景变化定时器
    m_Timer.setInterval(GAME_RATE);
    //更新图片的定时器
    picTimer.setInterval(PIC_RATE);
    //游戏界面音乐播放
    QSound *a = new QSound("://image/fightmusic.wav");
    a->play();
    //返回按键
    QPushButton *home=new QPushButton(this);
    home->setGeometry(550,0,100,50);
    home->setStyleSheet("QPushButton{border-image:url(://image/back.png)}"
                        "QPushButton:hover{border-image:url(://image/back_.png)}"
                        "QPushButton:pressed{border-image:url(://image/back.png)}");
    connect(home,&QPushButton::clicked,[=]()
    {
       //删除子对象
       this->deleteLater();
       home_page *h=new home_page;
       h->show();
       a->stop();
    });
}
void fight::initscene()
{    
    //标题设置
    setWindowTitle("Running man");
    //窗口大小初始化
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //英雄血量与能量初始化
    bleed1=300;
    bleed2=300;
    energy1=300;
    energy2=300;
    ispause=false;
    //开始游戏
    playgame();
    //飞镖发射间隔
    dartsInterval = 0;
    //随机数种子
    srand((unsigned int)time(0));
}

void fight::playgame()
{
    m_Timer.start();
    picTimer.start();
    connect(&picTimer,&QTimer::timeout,[=]()
    {
        //动态图片处理更新
        changeDartPic();
    });
    //场景变化
    connect(&m_Timer , &QTimer::timeout,[=](){

        if(energy1<300)
            energy1+=1;
        if(energy2<300)
            energy2+=1;
        updateposition();
        update();
        detection();
    });
}

void fight::updateposition()
{
    m_map.mPosition();

    for(int i = 0 ; i< DARTS_num;i++)
        //更新冰柱位置
       if(ice[i].ice_Free == false)
          ice[i].updateicePos();

        for(int i = 0 ; i< DARTS_num;i++)   
            //更新向右冰柱位置
           if(ice_[i].ice_FreeR == false)
              ice_[i].updateicePosR();       

        for(int i = 0 ; i< DARTS_num;i++)
      //更新火球位置
            if(fire[i].fire_Free == false)
           fire[i].updatefirePos();

        for(int i = 0 ; i< DARTS_num;i++)
            //更新向右火球位置
           if(fire_[i].fire_FreeR == false)
              fire_[i].updatefirePosR();

}

void fight::iceShow()
{
    dartsInterval++;
    if(dartsInterval < 5)
    {
        return;
    }

    dartsInterval = 0;

    if(m_hero2.LEFT_judge)
    for(int i = 0 ; i< DARTS_num;i++)
    {
        if(ice[i].ice_Free)
        {
            QSound::play("://image/iceshoot.wav");
            //空闲状态改为false
            ice[i].ice_Free = false;

            //设置坐标
            ice[i].ice_X = m_hero2.m_X;
            ice[i].ice_Y = (rand() % 100)+m_hero2.m_Y;
            break;
        }
    }
    else
    for(int i = 0 ; i< DARTS_num;i++)
    {
        if(ice_[i].ice_FreeR)
        {
            QSound::play("://image/iceshoot.wav");
            //空闲状态改为false
            ice_[i].ice_FreeR = false;

            //设置坐标
            ice_[i].ice_XR = m_hero2.m_X;
            ice_[i].ice_YR = (rand() % 100)+m_hero2.m_Y;
            break;
        }
    }

}

void fight::fireShow()
{
    dartsInterval++;
    if(dartsInterval < 5)
    {
        return;
    }

    dartsInterval = 0;

    if(m_hero.A_judge)
    for(int i = 0 ; i< DARTS_num;i++)
    {
        if(fire[i].fire_Free)
        {
            QSound::play("://image/fireshoot.wav");
            //空闲状态改为false
            fire[i].fire_Free = false;

            //设置坐标
            fire[i].fire_X = m_hero.m_X;
            fire[i].fire_Y = (rand() % 100)+m_hero.m_Y;
            break;
        }
    }
    else
    for(int i = 0 ; i< DARTS_num;i++)
    {
        if(fire_[i].fire_FreeR)
        {
            QSound::play("://image/fireshoot.wav");
            //空闲状态改为false
            fire_[i].fire_FreeR = false;

            //设置坐标
            fire_[i].fire_XR = m_hero.m_X;
            fire_[i].fire_YR = (rand() % 100)+m_hero.m_Y;
            break;
        }
    }
}

void fight::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(m_map.m1X,0,m_map.m1);
    painter.drawPixmap(m_map.m2X,0,m_map.m2);

    //绘制英雄
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.myHero);
    painter.drawPixmap(m_hero2.m_X,m_hero2.m_Y,m_hero2.myHero);

    //绘制暂停界面
    if(ispause==true)
        painter.drawPixmap(0,0,pausepic);

    //绘制冰柱
    for(int i = 0 ; i< DARTS_num;i++)    
        if(ice[i].ice_Free == false)
            painter.drawPixmap(ice[i].ice_X,ice[i].ice_Y,ice[i].ice);     

    for(int i = 0 ; i< DARTS_num;i++)
        if(ice_[i].ice_FreeR == false)
            painter.drawPixmap(ice_[i].ice_XR,ice_[i].ice_YR,ice_[i].ice_);


    //绘制火球
    for(int i = 0 ; i< DARTS_num;i++) 
        if(fire[i].fire_Free == false)    
            painter.drawPixmap(fire[i].fire_X,fire[i].fire_Y,fire[i].fire);

    for(int i = 0 ; i< DARTS_num;i++)
        if(fire_[i].fire_FreeR == false)
            painter.drawPixmap(fire_[i].fire_XR,fire_[i].fire_YR,fire_[i].fire_);


    //绘制p1冲刺
    if(((m_hero.D_judge&&m_hero.S_judge&&m_hero.isjump==false)||(m_hero.A_judge&&m_hero.S_judge&&m_hero.isjump==false))&&energy1>1)
           painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.mydash);
    //绘制p1普攻
    if(m_hero.J_judge&&m_hero.D_judge)
           painter.drawPixmap(m_hero.m_X+75,m_hero.m_Y,m_hero.attack);
    else if(m_hero.J_judge&&m_hero.A_judge)
        painter.drawPixmap(m_hero.m_X-120,m_hero.m_Y,m_hero.attackL);
    else if(m_hero.J_judge)
        painter.drawPixmap(m_hero.m_X+75,m_hero.m_Y,m_hero.attack);
    //绘制p1大招
    if(m_hero.U_judge)
        painter.drawPixmap(m_hero.m_X-55,m_hero.m_Y-35,m_hero.dazhao);


    //绘制p2冲刺
    if(((m_hero2.RIGHT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false)||(m_hero2.LEFT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false))&&energy2>1)
            painter.drawPixmap(m_hero2.m_X,m_hero2.m_Y,m_hero2.mydash);
    //绘制p2普攻
    if(m_hero2.L_judge&&m_hero2.RIGHT_judge)
            painter.drawPixmap(m_hero2.m_X+75,m_hero2.m_Y,m_hero2.attack);
    else if(m_hero2.L_judge&&m_hero2.LEFT_judge)
        painter.drawPixmap(m_hero2.m_X-120,m_hero2.m_Y,m_hero2.attackL);
    else if(m_hero2.L_judge)
        painter.drawPixmap(m_hero2.m_X+75,m_hero2.m_Y,m_hero2.attack);
    //绘制p2大招
    if(m_hero2.O_judge)
        painter.drawPixmap(m_hero2.m_X-55,m_hero2.m_Y-35,m_hero2.dazhao);


    //画血条
    painter.setPen(QPen(Qt::red,25));
    painter.drawLine(100,20,bleed1+100,20);
    painter.drawLine(1100-bleed2,20,1100,20);
    QFont font("宋体",20,QFont::Bold,true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(0,30,"HP");
    //画蓝条
    painter.setPen(QPen(Qt::blue,25));
    painter.drawLine(100,70,energy1+100,70);
    painter.drawLine(1100-energy2,70,1100,70);
    painter.setPen(Qt::black);
    painter.drawText(0,80,"MP");

}

void fight::keyPressEvent(QKeyEvent *e)
{

    //暂停
    if(e->key()==Qt::Key_P)
    {
        if(ispause==false)
        {
            ispause=true;
            m_Timer.stop();
            picTimer.stop();
            update();
        }
        else if (ispause==true)
        {
            ispause=false;
            m_Timer.start();
            picTimer.start();
             update();
        }
    }
    //p1移动与跳跃
    if(e->key()==Qt::Key_D)
        m_hero.D_judge =true;
    else if(e->key()==Qt::Key_A)
        m_hero.A_judge =true;
    else if(e->key()==Qt::Key_S)
        m_hero.S_judge =true;
    else if(e->key()==Qt::Key_W&&m_hero.isjump==false)
    {
        m_hero.isjump=true;
        m_hero.W_judge=true;
    }
    //p1普攻
    if(e->key()==Qt::Key_J&&energy1>19)
       {
        update();
        QSound::play("://image/attack.wav");
        m_hero.J_judge=true;
        energy1-=20;
       }
    //p1大招
    if(e->key()==Qt::Key_U)
    {
        m_hero.U_judge=true;
    }

    //p2移动
    if(e->key()==Qt::Key_Right)
        m_hero2.RIGHT_judge =true;
    else if(e->key()==Qt::Key_Left)
        m_hero2.LEFT_judge =true;
    else if(e->key()==Qt::Key_Down)
        m_hero2.DOWN_judge =true;
    else if(e->key()==Qt::Key_Up&&m_hero2.isjump==false)
    {
        m_hero2.isjump=true;
        m_hero2.UP_judge=true;
    }
    //p2普攻
    if(e->key()==Qt::Key_L&&energy2>19)
       {
        update();
        QSound::play("://image/attack1.wav");
        m_hero2.L_judge=true;
        energy2-=20;
       }
    //p2大招
    if(e->key()==Qt::Key_O)
    {
        m_hero2.O_judge=true;
    }

}

void fight::keyReleaseEvent(QKeyEvent *e)
{
    //p1
    if(e->key()==Qt::Key_D)
        m_hero.D_judge =false;
    else if(e->key()==Qt::Key_A)
        m_hero.A_judge =false;
    else if(e->key()==Qt::Key_S)
        m_hero.S_judge =false;
    if(e->key()==Qt::Key_J)
        m_hero.J_judge=false;
    if(e->key()==Qt::Key_U)
        m_hero.U_judge=false;

    //p2
    if(e->key()==Qt::Key_Right)
        m_hero2.RIGHT_judge =false;
    else if(e->key()==Qt::Key_Left)
        m_hero2.LEFT_judge =false;
    else if(e->key()==Qt::Key_Down)
        m_hero2.DOWN_judge =false;
    if(e->key()==Qt::Key_L)
        m_hero2.L_judge=false;
    if(e->key()==Qt::Key_O)
        m_hero2.O_judge=false;

}

void fight::timerEvent(QTimerEvent *e)
{
    if(energy1<0)
        energy1=0;
    if(m_hero.A_judge)
    {
        m_hero.m_X-=HERO_SPEED-5;
        if(m_hero.m_X<0)
            m_hero.m_X=0;
    }
    if(m_hero.D_judge)
    {
        m_hero.m_X+=HERO_SPEED-10;
        if(m_hero.m_X>GAME_WIDTH-70)
            m_hero.m_X=GAME_WIDTH-70;
    }
    if(m_hero.S_judge)
    {
        m_hero.m_Y+=HERO_SPEED+30;
        if(m_hero.m_Y>GAME_HEIGHT-150)
            m_hero.m_Y=GAME_HEIGHT-150;
    }



    if(energy2<0)
        energy2=0;
    if(m_hero2.LEFT_judge)
    {
        m_hero2.m_X-=HERO_SPEED-5;
        if(m_hero2.m_X<0)
            m_hero2.m_X=0;
    }
    if(m_hero2.RIGHT_judge)
    {
        m_hero2.m_X+=HERO_SPEED-10;
        if(m_hero2.m_X>GAME_WIDTH-70)
            m_hero2.m_X=GAME_WIDTH-70;
    }
    if(m_hero2.DOWN_judge)
    {
        m_hero2.m_Y+=HERO_SPEED+30;
        if(m_hero2.m_Y>GAME_HEIGHT-150)
            m_hero2.m_Y=GAME_HEIGHT-150;
    }

    //冲刺状态
    if(m_hero.S_judge&&m_hero.D_judge&&energy1>3)
    {
        m_hero.m_X+=HERO_SPEED-5;
        if(m_hero.m_Y>GAME_HEIGHT-150)
            m_hero.m_Y=GAME_HEIGHT-150;
        if(m_hero.m_X>GAME_WIDTH-70)
            m_hero.m_X=GAME_WIDTH-70;
        energy1-=2;
    }

    if(m_hero2.DOWN_judge&&m_hero2.RIGHT_judge&&energy2>3)
    {
        m_hero2.m_X+=HERO_SPEED-5;
        if(m_hero2.m_Y>GAME_HEIGHT-150)
            m_hero2.m_Y=GAME_HEIGHT-150;
        if(m_hero2.m_X>GAME_WIDTH-70)
            m_hero2.m_X=GAME_WIDTH-70;
        energy2-=2;
    }
    if(m_hero.S_judge&&m_hero.A_judge&&energy1>3)
    {
        m_hero.m_X-=HERO_SPEED;
        if(m_hero.m_Y>GAME_HEIGHT-150)
            m_hero.m_Y=GAME_HEIGHT-150;
        if(m_hero.m_X<0)
            m_hero.m_X=0;
        energy1-=2;
    }
    if(m_hero2.DOWN_judge&&m_hero2.LEFT_judge&&energy2>3)
    {
        m_hero2.m_X-=HERO_SPEED;
        if(m_hero2.m_Y>GAME_HEIGHT-150)
            m_hero2.m_Y=GAME_HEIGHT-150;
        if(m_hero2.m_X<0)
            m_hero2.m_X=0;
        energy2-=2;
    }


    //跳跃
    if(m_hero.isjump==true)
    {
        if(m_hero.status==true)
        {
            //模拟重力系统
            static int t=0;
            t++;
           if(t>=20&&m_hero.status==true)
            {
               t=0;
               m_hero.status=false;
           }
        if(m_hero.status==true)
        {
            if(t>=0&&t<10)
            m_hero.m_Y-=HERO_SPEED;
            else if (t>=10&&t<20)
                m_hero.m_Y-=HERO_SPEED-10;
        }
        }

        else if(m_hero.status==false&&m_hero.m_Y<=GAME_HEIGHT-300)
            m_hero.m_Y+=HERO_SPEED-10;
        else if(m_hero.status==false&&m_hero.m_Y>GAME_HEIGHT-300)
            m_hero.m_Y+=HERO_SPEED;

        //回到地面
        if(m_hero.m_Y>GAME_HEIGHT-150&&m_hero.status==false)
        {
            m_hero.m_Y=GAME_HEIGHT-150;
            m_hero.isjump=false;
            m_hero.status=true;
        }
    }

    if(m_hero2.isjump==true)
    {
        if(m_hero2.status==true)
        {
            //模拟重力系统
            static int t=0;
            t++;
           if(t>=20&&m_hero2.status==true)
            {
               t=0;
               m_hero2.status=false;
           }
        if(m_hero2.status==true)
        {
            if(t>=0&&t<10)
            m_hero2.m_Y-=HERO_SPEED;
            else if (t>=10&&t<20)
                m_hero2.m_Y-=HERO_SPEED-10;
        }
        }
        else if(m_hero2.status==false&&m_hero2.m_Y<=GAME_HEIGHT-300)
            m_hero2.m_Y+=HERO_SPEED-10;
        else if(m_hero2.status==false&&m_hero2.m_Y>GAME_HEIGHT-300)
            m_hero2.m_Y+=HERO_SPEED;

        //回到地面
        if(m_hero2.m_Y>GAME_HEIGHT-150&&m_hero2.status==false)
        {
            m_hero2.m_Y=GAME_HEIGHT-150;
            m_hero2.isjump=false;
            m_hero2.status=true;
        }

    }

}
void fight::detection()
{
    if(bleed1<0)
        bleed1=0;
    if(bleed2<0)
        bleed2=0;

    for(int i = 0 ;i < DARTS_num;i++)
    {
        if(ice[i].ice_Free)  
            continue;

        if(ice[i].ice_Rect.intersects(m_hero.m_Rect))
        {
            //冲刺状态不受到伤害
            if(((m_hero.S_judge&&m_hero.D_judge)||(m_hero.S_judge&&m_hero.A_judge))&&energy1>3)
        {
            ice[i].ice_Free = true;
            QSound::play("://image/icebroke.wav");
            continue;
        }
            else
            {
                ice[i].ice_Free=true;
                bleed1-=30;
                QSound::play("://image/hurt1.wav");
                continue;
            }
        }


     }
    for(int i = 0 ;i < DARTS_num;i++)
    {
        if(ice_[i].ice_FreeR)
            continue;

        if(ice_[i].ice_RectR.intersects(m_hero.m_Rect))
        {
            //冲刺状态不受到伤害
            if(((m_hero.S_judge&&m_hero.D_judge)||(m_hero.S_judge&&m_hero.A_judge))&&energy1>3)
        {
            ice_[i].ice_FreeR = true;
            QSound::play("://image/icebroke.wav");
            continue;
        }
            else
            {
                ice_[i].ice_FreeR=true;
                bleed1-=30;
                QSound::play("://image/hurt1.wav");
                continue;
            }
        }

     }

    for(int i = 0 ;i < DARTS_num;i++)
    {
        if(fire[i].fire_Free)
            continue;

        if(fire[i].fire_Rect.intersects(m_hero2.m_Rect))
        {
            //冲刺状态不受到伤害
            if(((m_hero2.DOWN_judge&&m_hero2.RIGHT_judge)||(m_hero2.DOWN_judge&&m_hero2.LEFT_judge))&&energy2>3)
        {
            fire[i].fire_Free = true;
            QSound::play("://image/fireburning.wav");
            continue;
        }
            else
            {
                fire[i].fire_Free=true;
                bleed2-=30;
                QSound::play("://image/hurt1.wav");
                continue;
            }
        }


     }
    for(int i = 0 ;i < DARTS_num;i++)
    {
        if(fire_[i].fire_FreeR)    
                 continue;

        if(fire_[i].fire_RectR.intersects(m_hero2.m_Rect))
        {
            //冲刺状态不受到伤害
            if(((m_hero2.DOWN_judge&&m_hero2.RIGHT_judge)||(m_hero2.DOWN_judge&&m_hero2.LEFT_judge))&&energy2>3)
        {
            fire_[i].fire_FreeR = true;
            QSound::play("://image/fireburning.wav");
            continue;
        }
            else
            {
                fire_[i].fire_FreeR=true;
                bleed2-=30;
                QSound::play("://image/hurt.wav");
                continue;
            }
        }

     }

       if(m_hero2.attack_Rect.intersects(m_hero.m_Rect)||m_hero2.attackL_Rect.intersects(m_hero.m_Rect))
       {
           QSound::play("://image/hurt1.wav");

           if(((m_hero.S_judge&&m_hero.D_judge)||(m_hero.S_judge&&m_hero.A_judge))&&energy1>3)
           {
              bleed1-=0;
           }
           else if(bleed1>0)
           {
               bleed1-=10;
           }
       }
       if(m_hero.attack_Rect.intersects(m_hero2.m_Rect)||m_hero.attackL_Rect.intersects(m_hero2.m_Rect))
       {
           QSound::play("://image/hurt.wav");

           if(((m_hero2.DOWN_judge&&m_hero2.RIGHT_judge)||(m_hero2.DOWN_judge&&m_hero2.LEFT_judge))&&energy1>3)
           {
               bleed2-=0;
           }
           else if(bleed2>0)
           {
               bleed2-=10;
           }
       }

           if(bleed1<=0||bleed2<=0)
           {
               if(bleed1<=0)
               QSound::play("://image/die.wav");
               else if(bleed2<=0)
               QSound::play("://image/die1.wav");
               m_Timer.stop();
               picTimer.stop();

               QPushButton *retry=new QPushButton("是");
               QPushButton *close=new QPushButton("否");
               QMessageBox *box = new QMessageBox;

               box->setWindowTitle("游戏结束");
               box->setText("重新来过？");
               box->addButton(retry,QMessageBox::AcceptRole);//枚举类型
               box->addButton(close,QMessageBox::RejectRole);
               box->show();
               box->exec();//等待用户操作

               if(box->clickedButton()==close)
               {
                  this->close();
               }

               //重新开始游戏
               else
               {
               m_Timer.start();
               picTimer.start();

               bleed1=300;
               energy1=300;
               bleed2=300;
               energy2=300;

               m_hero.D_judge =false;
               m_hero.A_judge =false;
               m_hero.W_judge =false;
               m_hero.S_judge =false;
               m_hero.J_judge =false;
               m_hero.U_judge =false;

               m_hero2.UP_judge =false;
               m_hero2.RIGHT_judge =false;
               m_hero2.LEFT_judge =false;
               m_hero2.DOWN_judge =false;
               m_hero2.L_judge =false;
               m_hero2.O_judge =false;

               }
             }



}

void fight::changeDartPic()
{
    //p1移动图片更新
    m_hero.updatepic();
    if(m_hero.A_judge)
        m_hero.updateleftpic();
    if(m_hero.A_judge&&m_hero.isjump&&m_hero.status==true)
        m_hero.updateuppicL();
    else if(m_hero.A_judge&&m_hero.isjump&&m_hero.status==false)
        m_hero.updatedownpicL();

    //p1跳跃图片更新
    if(m_hero.D_judge&&m_hero.isjump&&m_hero.status==true)
        m_hero.updateuppic();
    else if(m_hero.D_judge&&m_hero.isjump&&m_hero.status==false)
        m_hero.updatedownpic();

    //p1冲刺图片更新
    if((m_hero.D_judge&&m_hero.S_judge&&m_hero.isjump==false)||(m_hero.A_judge&&m_hero.S_judge&&m_hero.isjump==false))
        m_hero.updatedash();
    //p1大招图片更新
    if(m_hero.U_judge&&energy1>4)
       {
        fireShow();
        m_hero.updatedazhaopic();
        energy1-=5;
       }

    //p2移动图片更新
    m_hero2.updatepic();
    if(m_hero2.LEFT_judge)
        m_hero2.updateleftpic();
    if(m_hero2.LEFT_judge&&m_hero2.isjump&&m_hero2.status==true)
        m_hero2.updateuppicL();
    else if(m_hero2.LEFT_judge&&m_hero2.isjump&&m_hero2.status==false)
        m_hero2.updatedownpicL();

    //p2跳跃图片更新
    if(m_hero2.RIGHT_judge&&m_hero2.isjump&&m_hero2.status==true)
        m_hero2.updateuppic();
    else if(m_hero2.RIGHT_judge&&m_hero2.isjump&&m_hero2.status==false)
        m_hero2.updatedownpic();

    //p2冲刺图片更新
    if((m_hero2.RIGHT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false)||(m_hero2.LEFT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false))
        m_hero2.updatedash();
    //p2大招图片更新
    if(m_hero2.O_judge&&energy2>4)
       {
        iceShow();
        m_hero2.updatedazhaopic();
        energy2-=5;
       }

}
