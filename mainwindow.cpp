#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include "config.h"
#include <QMessageBox>
#include <QFont>
#include <QSound>
#include <QPushButton>
#include "home_page.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //暂停图片资源加载
    pausepic.load("://image/pause.png");
    pausepic_.load("://image/pause2.png");
    //初始化场景
    initscene();
    //事件时间开始
    this->startTimer(EVENT_RATE);
    //游戏界面音乐播放
    QSound *a = new QSound("://image/music1.wav");
    a->play();
    //设置返回按钮有关
    QPushButton *home=new QPushButton(this);
    home->setGeometry(900,0,100,50);
    home->setStyleSheet("QPushButton{border-image:url(://image/back.png)}"
                        "QPushButton:hover{border-image:url(://image/back_.png)}"
                        "QPushButton:pressed{border-image:url(://image/back.png)}");
    connect(home,&QPushButton::clicked,[=]()
    {
       this->deleteLater();
       home_page *h=new home_page;
       h->show();
       a->stop();

    });
    //键盘不相互影响
    setFocusPolicy(Qt::StrongFocus);

    //游戏帧率
    m_Timer.setInterval(GAME_RATE);
    //更新图片的计时器
    picTimer.setInterval(PIC_RATE);

    //计时表
    gameTimer.setInterval(CLOCK_RATE);
    m_LCD.setParent(this);
    m_LCD.setFixedSize(200,50);
    m_LCD.setDigitCount(4);
    m_LCD.setMode(QLCDNumber::Dec);
    m_LCD.move(1000,0);
    m_LCD.show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initscene()
{
    //题目
    setWindowTitle("Running man");
    //大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //初始化数据
    ispause =false;
    bleed=500;
    energy=500;
    bleed_=500;
    energy_=500;
    m_hero.isdead=false;
    m_hero2.isdead=false;
    gametype=0;
    t=0;

    //开始游戏
    playgame();

    //飞镖发射间隔
    dartsInterval = 0;

    //随机数种子
    srand((unsigned int)time(NULL));

}

void MainWindow::playgame()
{
    m_Timer.start();
    picTimer.start();
    gameTimer.start();

    //游戏阶段定时器
    connect(&gameTimer,&QTimer::timeout,[=]()
    {
        t++;
        m_LCD.display(t);
        if(t>30&&gametype==0)
            {
            m_Timer.setInterval(20);
            gametype=1;
        }
        else if(t>60&&gametype==1)
            {
            m_Timer.setInterval(10);
            gametype=2;
        }

    });

    //动态图片更新定时器
    connect(&picTimer,&QTimer::timeout,[=]()
    {
        changeDartPic();
    });

    //场景更新定时器
    connect(&m_Timer , &QTimer::timeout,[=](){

        if(energy<500&&gametype==0)
            energy+=1;
        else if (energy<500&&gametype==1)
            energy+=0.5;
        else if(energy<500&&gametype==2)
            energy+=0.3;

        if(energy_<500&&gametype==0)
            energy_+=1;
        else if(energy_<500&&gametype==1)
            energy_+=0.5;
        else if(energy_<500&&gametype==2)
                energy_+=0.3;

        //飞镖出现
        dartsShow();
        //飞镖，地图位置更新
        updateposition();
        //重绘
        update();
        detection();

    });
}

void MainWindow::updateposition()
{
    if(people==1)
    m_map.mapPosition();
    else if(people==2)
    m_map.mapPosition_();

    //飞镖坐标计算
    for(int i = 0 ; i< DARTS_num;i++)
    {
        //非空闲飞镖 更新坐标
       if(m_darts[i].dart_Free == false)
       {
          m_darts[i].updatePosition();
       }
    }

}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //绘制地图
    if(people==1)
    {
    painter.drawPixmap(m_map.m_map1_posX,0,m_map.m_map1);
    painter.drawPixmap(m_map.m_map2_posX,0,m_map.m_map2);
    }
    if(people==2)
    {
    painter.drawPixmap(m_map.m_map1__posX,0,m_map.m_map1_);
    painter.drawPixmap(m_map.m_map2__posX,0,m_map.m_map2_);
    }

    //绘制英雄
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.myHero);


    //绘制冲刺
    if(((m_hero.D_judge&&m_hero.S_judge&&m_hero.isjump==false)||(m_hero.A_judge&&m_hero.S_judge&&m_hero.isjump==false))&&energy>1)
    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.mydash);

    //绘制普通攻击
    if(m_hero.J_judge&&m_hero.D_judge)
    painter.drawPixmap(m_hero.m_X+75,m_hero.m_Y,m_hero.attack);
    else if(m_hero.J_judge&&m_hero.A_judge)
        painter.drawPixmap(m_hero.m_X-120,m_hero.m_Y,m_hero.attackL);
    else if(m_hero.J_judge)
        painter.drawPixmap(m_hero.m_X+75,m_hero.m_Y,m_hero.attack);

    //绘制大招火球
    painter.drawPixmap(m_hero.x,m_hero.y,m_hero.myfire);

    //绘制暂停界面
    if(ispause==true&&people==1)
        painter.drawPixmap(0,100,pausepic);
    else if(ispause==true&&people==2)
        painter.drawPixmap(0,100,pausepic_);

    //绘制飞镖
    for(int i = 0 ; i< DARTS_num;i++)
    {
        if(m_darts[i].dart_Free == false)
        {

            //更新飞镖图片，待优化
            static int m=0;
            m_darts[i].mydarts=m_darts[i].dartspic[m];
            m++;
            painter.drawPixmap(m_darts[i].dart_X,m_darts[i].dart_Y,m_darts[i].mydarts);
            if(m>=3)
            {
                m=0;
            }
        }
    }


    if(people==2)
     painter.drawPixmap(m_hero2.m_X,m_hero2.m_Y,m_hero2.myHero);


    if(people==2)
    {
    if(((m_hero2.LEFT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false)||(m_hero2.RIGHT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false))&&energy>1)
    painter.drawPixmap(m_hero2.m_X,m_hero2.m_Y,m_hero2.mydash);

    if(m_hero2.RIGHT_judge&&m_hero2.L_judge)
    painter.drawPixmap(m_hero2.m_X+75,m_hero2.m_Y,m_hero2.attack);
    else if(m_hero2.L_judge&&m_hero2.LEFT_judge)
        painter.drawPixmap(m_hero2.m_X-120,m_hero2.m_Y,m_hero2.attackL);
    else if(m_hero2.L_judge)
        painter.drawPixmap(m_hero2.m_X+75,m_hero2.m_Y,m_hero2.attack);
    }

    //画血条
    if(people==1)
    {
    painter.setPen(QPen(Qt::red,25));
    painter.drawLine(100,20,bleed+100,20);
    QFont font("宋体",20,QFont::Bold,true);
    font.setLetterSpacing(QFont::AbsoluteSpacing,5);
    painter.setFont(font);
    painter.setPen(Qt::black);
    painter.drawText(20,30,"HP");

    //画蓝条
    painter.setPen(QPen(Qt::blue,25));
    painter.drawLine(100,70,energy+100,70);
    painter.setPen(Qt::black);
    painter.drawText(20,80,"MP");

    }


    else if(people==2)
    {
        //p1血条
        painter.setPen(QPen(Qt::red,20));
        painter.drawLine(100,15,bleed+100,15);
        QFont font("宋体",15,QFont::Bold,true);
        font.setLetterSpacing(QFont::AbsoluteSpacing,5);
        painter.setFont(font);
        painter.setPen(Qt::black);
        painter.drawText(20,30,"P1");
        //p1蓝条
        painter.setPen(QPen(Qt::blue,20));
        painter.drawLine(100,40,energy+100,40);

        //p2血条
        painter.setPen(QPen(Qt::red,20));
        painter.drawLine(100,70,bleed_+100,70);
        QFont font1("宋体",15,QFont::Bold,true);
        font.setLetterSpacing(QFont::AbsoluteSpacing,5);
        painter.setFont(font);
        painter.setPen(Qt::black);
        painter.drawText(20,90,"P2");
        //p2蓝条
        painter.setPen(QPen(Qt::blue,20));
        painter.drawLine(100,95,energy_+100,95);

    }

}

void MainWindow::keyPressEvent(QKeyEvent *e)
{

    if(e->key()==Qt::Key_P)
    {
        if(ispause==false)
        {
            ispause=true;
            m_Timer.stop();
            gameTimer.stop();
            picTimer.stop();
            update();
        }
        else if (ispause==true)
        {
            ispause=false;
            m_Timer.start();
            gameTimer.start();
            picTimer.start();
             update();
        }
    }

    //p1有关按键
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

    if(e->key()==Qt::Key_J&&energy>99)
       {
        update();
        QSound::play("://image/attack.wav");
        m_hero.J_judge=true;
        energy-=100;
       }
    if(e->key()==Qt::Key_K&&energy>499)
    {
        m_hero.K_judge=true;
        QSound::play("://image/fire.wav");
        energy-=500;

    }

    //p2有关按键
    if(people==2)
    {

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

    if(e->key()==Qt::Key_L&&energy_>99)
       {
        update();
        QSound::play("://image/attack1.wav");
        m_hero2.L_judge=true;
        energy_-=100;
       }
    }

}

void MainWindow::keyReleaseEvent(QKeyEvent *e)
{

    if(e->key()==Qt::Key_D)
        m_hero.D_judge =false;
    else if(e->key()==Qt::Key_A)
        m_hero.A_judge =false;
    else if(e->key()==Qt::Key_S)
        m_hero.S_judge =false;
    if(e->key()==Qt::Key_J)
        m_hero.J_judge=false;

    if(people==2)
    {
    if(e->key()==Qt::Key_Left)
        m_hero2.LEFT_judge =false;
    else if(e->key()==Qt::Key_Right)
        m_hero2.RIGHT_judge =false;
    else if(e->key()==Qt::Key_Down)
        m_hero2.DOWN_judge =false;
    if(e->key()==Qt::Key_L)
        m_hero2.L_judge=false;
    }

}

void MainWindow::timerEvent(QTimerEvent *e)
{
    if(energy<0)
        energy=0;
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



    if(people==2)
    {
        if(energy_<0)
            energy_=0;
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
    }



    //冲刺状态
    if(m_hero.S_judge&&m_hero.D_judge&&energy>3)
    {
        m_hero.m_X+=HERO_SPEED-5;
        if(m_hero.m_Y>GAME_HEIGHT-150)
            m_hero.m_Y=GAME_HEIGHT-150;
        if(m_hero.m_X>GAME_WIDTH-70)
            m_hero.m_X=GAME_WIDTH-70;
        energy -=4;

    }
    if(m_hero2.DOWN_judge&&m_hero2.RIGHT_judge&&energy_>3&&people==2)
    {
        m_hero2.m_X+=HERO_SPEED-5;
        if(m_hero2.m_Y>GAME_HEIGHT-150)
            m_hero2.m_Y=GAME_HEIGHT-150;
        if(m_hero2.m_X>GAME_WIDTH-70)
            m_hero2.m_X=GAME_WIDTH-70;
        energy_ -=4;
    }
    if(m_hero.S_judge&&m_hero.A_judge&&energy>3)
    {
        m_hero.m_X-=HERO_SPEED;
        if(m_hero.m_Y>GAME_HEIGHT-150)
            m_hero.m_Y=GAME_HEIGHT-150;
        if(m_hero.m_X<0)
            m_hero.m_X=0;
        energy -=4;
    }
    if(m_hero2.DOWN_judge&&m_hero2.LEFT_judge&&energy_>3&&people==2)
    {
        m_hero2.m_X-=HERO_SPEED;
        if(m_hero2.m_Y>GAME_HEIGHT-150)
            m_hero2.m_Y=GAME_HEIGHT-150;
        if(m_hero2.m_X<0)
            m_hero2.m_X=0;
        energy_ -=4;
    }


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

    if(m_hero2.isjump==true&&people==2)
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

void MainWindow::dartsShow()
{
    //累加出场间隔，每用20次定时器触发一次飞镖出现
    dartsInterval++;
    if(dartsInterval < 20)
    {
        return;
    }

    dartsInterval = 0;

    for(int i = 0 ; i< DARTS_num;i++)
    {
        if(m_darts[i].dart_Free)
        {
            QSound::play("://image/dm.wav");
            //空闲状态改为false
            m_darts[i].dart_Free = false;

            //设置坐标
            m_darts[i].dart_X = GAME_WIDTH;
            m_darts[i].dart_Y = rand() % (GAME_HEIGHT- m_darts[i].dart_Rect.height()-50);
            break;
        }
    }
}

void MainWindow::detection()
{
    if(bleed<0)
        bleed=0;
    //遍历所有非空闲的飞镖
    for(int i = 0 ;i < DARTS_num;i++)
    {
        if(m_darts[i].dart_Free)
            continue;

        //大招火球碰撞检测
        if(m_darts[i].dart_Rect.intersects(m_hero.fire_Rect))
        {
            m_darts[i].dart_Free=true;
            QSound::play("://image/collision.wav");
            continue;
        }

        //普通攻击碰撞检测
        if(m_darts[i].dart_Rect.intersects(m_hero.attack_Rect)||m_darts[i].dart_Rect.intersects(m_hero.attackL_Rect))
        {
            m_darts[i].dart_Free = true;
            QSound::play("://image/collision.wav");
            continue;
        }
        if((m_darts[i].dart_Rect.intersects(m_hero2.attack_Rect)||m_darts[i].dart_Rect.intersects(m_hero2.attackL_Rect))&&people==2)
        {
            m_darts[i].dart_Free = true;
            QSound::play("://image/collision.wav");
            continue;
        }

        //英雄碰撞检测
       if(m_darts[i].dart_Rect.intersects(m_hero.m_Rect)||(m_darts[i].dart_Rect.intersects(m_hero2.m_Rect)&&people==2))
       {
               if(((m_hero.S_judge&&m_hero.D_judge)||(m_hero.S_judge&&m_hero.A_judge))&&energy>3)
           {
               m_darts[i].dart_Free = true;
               QSound::play("://image/collision.wav");
               continue;
           }

           if(((m_hero2.DOWN_judge&&m_hero2.RIGHT_judge)||(m_hero2.DOWN_judge&&m_hero2.LEFT_judge))&&energy_>3)
           {
               m_darts[i].dart_Free = true;
               QSound::play("://image/collision.wav");
               continue;
           }

           else if(bleed>0&&m_darts[i].dart_Rect.intersects(m_hero.m_Rect))
           {
               QSound::play("://image/hurt1.wav");
               bleed-=50;
               m_darts[i].dart_Free = true;
           }
           else if(bleed_>0&&m_darts[i].dart_Rect.intersects(m_hero2.m_Rect))
           {
               QSound::play("://image/hurt.wav");
               bleed_-=50;
               m_darts[i].dart_Free = true;
           }

           if(bleed<=0&&m_hero.isdead==false)
           {
               m_hero.isdead=true;
               QSound::play("://image/die.wav");
               energy=500;
               //单英雄死后移出场景外
               m_hero.m_X=-10000;
               m_hero.m_Y=-10000;
               update();
           }
           if(bleed_<=0&&m_hero2.isdead==false)
           {
               m_hero2.isdead=true;
               QSound::play("://image/die1.wav");
               energy_=500;
               //单英雄死后移出场景外
               m_hero2.m_X=-10000;
               m_hero2.m_Y=-10000;
               update();
           }

           //死亡
           if((bleed<=0&&bleed_<=0&&people==2)||(bleed<=0&&people==1))
           {
               m_hero.isdead=true;
               m_hero2.isdead=true;
               m_Timer.stop();
               picTimer.stop();
               gameTimer.stop();
               m_LCD.display(0);

               QPushButton *retry=new QPushButton("是");
               QPushButton *close=new QPushButton("否");
               QMessageBox *box = new QMessageBox;

               box->setWindowTitle("游戏结束");
               QString::number(t);
               box->setText("你坚持了"+QString::number(t)+"秒，重新来过？");
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
                //重置定时器
               m_Timer.setInterval(GAME_RATE);
               picTimer.setInterval(PIC_RATE);
               gameTimer.setInterval(CLOCK_RATE);
               m_Timer.start();
               picTimer.start();
               gameTimer.start();

               bleed=500;
               energy=500;
               bleed_=500;
               energy_=500;

               m_hero2.UP_judge =false;
               m_hero2.RIGHT_judge =false;
               m_hero2.LEFT_judge =false;
               m_hero2.DOWN_judge =false;
               m_hero2.L_judge =false;
               m_hero2.O_judge =false;

               m_hero.isdead=false;
               m_hero2.isdead=false;

               m_hero.m_X = GAME_WIDTH * 0.6;
               m_hero.m_Y = GAME_HEIGHT - 150;
               m_hero2.m_X = GAME_WIDTH * 0.6;
               m_hero2.m_Y = GAME_HEIGHT - 150;
               t=0;
               gametype=0;
           }
       }

    }
}
    }

void MainWindow::changeDartPic()
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

    //p1大招火球图片更新
    if(m_hero.K_judge)
         m_hero.updatefirepic();



    //p2有关更新
    if(people==2)
    {
    m_hero2.updatepic();
    if(m_hero2.LEFT_judge)
        m_hero2.updateleftpic();
    if(m_hero2.LEFT_judge&&m_hero2.isjump&&m_hero2.status==true)
        m_hero2.updateuppicL();
    else if(m_hero2.LEFT_judge&&m_hero2.isjump&&m_hero2.status==false)
        m_hero2.updatedownpicL();

    if(m_hero2.RIGHT_judge&&m_hero2.isjump&&m_hero2.status==true)
        m_hero2.updateuppic();
    else if(m_hero2.RIGHT_judge&&m_hero2.isjump&&m_hero2.status==false)
        m_hero2.updatedownpic();

    if((m_hero2.RIGHT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false)||(m_hero2.LEFT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false))
        m_hero2.updatedash();
    }

}



















