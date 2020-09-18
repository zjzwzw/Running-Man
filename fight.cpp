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

    initscene();
    this->startTimer(15);

    setFocusPolicy(Qt::StrongFocus);

    pausepic.load("://image/pause2.png");


    m_Timer.setInterval(GAME_RATE);

    //更新图片的计时器
    picTimer.setInterval(PIC_RATE);


    QSound *a = new QSound("://image/fightmusic.wav");
    a->play();

    QPushButton *home=new QPushButton(this);
    home->setGeometry(550,0,100,50);
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

}



void fight::initscene()
{
    setWindowTitle("Running man");

    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    bleed1=300;
    bleed2=300;
    energy1=300;
    energy2=300;
    ispause=false;

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
        changeDartPic();
    });

    //监听定时器的信号
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

}

void fight::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(m_map.m1X,0,m_map.m1);
    painter.drawPixmap(m_map.m2X,0,m_map.m2);


    painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.myHero);
    painter.drawPixmap(m_hero2.m_X,m_hero2.m_Y,m_hero2.myHero);

    //绘制暂停界面
    if(ispause==true)
        painter.drawPixmap(0,0,pausepic);



    if(((m_hero.D_judge&&m_hero.S_judge&&m_hero.isjump==false)||(m_hero.A_judge&&m_hero.S_judge&&m_hero.isjump==false))&&energy1>1)
           painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.mydash);

    if(m_hero.J_judge&&m_hero.D_judge)
           painter.drawPixmap(m_hero.m_X+75,m_hero.m_Y,m_hero.attack);
    else if(m_hero.J_judge&&m_hero.A_judge)
        painter.drawPixmap(m_hero.m_X-120,m_hero.m_Y,m_hero.attackL);
    else if(m_hero.J_judge)
        painter.drawPixmap(m_hero.m_X+75,m_hero.m_Y,m_hero.attack);



    if(((m_hero2.RIGHT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false)||(m_hero2.LEFT_judge&&m_hero2.DOWN_judge&&m_hero2.isjump==false))&&energy2>1)
            painter.drawPixmap(m_hero2.m_X,m_hero2.m_Y,m_hero2.mydash);

    if(m_hero2.L_judge&&m_hero2.RIGHT_judge)
            painter.drawPixmap(m_hero2.m_X+75,m_hero2.m_Y,m_hero2.attack);
    else if(m_hero2.L_judge&&m_hero2.LEFT_judge)
        painter.drawPixmap(m_hero2.m_X-120,m_hero2.m_Y,m_hero2.attackL);
    else if(m_hero2.L_judge)
        painter.drawPixmap(m_hero2.m_X+75,m_hero2.m_Y,m_hero2.attack);


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

    if(e->key()==Qt::Key_J&&energy1>19)
       {
        update();
        QSound::play("://image/attack.wav");
        m_hero.J_judge=true;
        energy1-=20;
       }
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

    if(e->key()==Qt::Key_L&&energy2>19)
       {
        update();
        QSound::play("://image/attack1.wav");
        m_hero2.L_judge=true;
        energy2-=20;
       }

}

void fight::keyReleaseEvent(QKeyEvent *e)
{
    if(e->key()==Qt::Key_D)

        m_hero.D_judge =false;

    else if(e->key()==Qt::Key_A)
        m_hero.A_judge =false;

    else if(e->key()==Qt::Key_S)
        m_hero.S_judge =false;

    if(e->key()==Qt::Key_J)
        m_hero.J_judge=false;
    if(e->key()==Qt::Key_Right)

        m_hero2.RIGHT_judge =false;

    else if(e->key()==Qt::Key_Left)
        m_hero2.LEFT_judge =false;

    else if(e->key()==Qt::Key_Down)
        m_hero2.DOWN_judge =false;

    if(e->key()==Qt::Key_L)
        m_hero2.L_judge=false;

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

    if(m_hero2.LEFT_judge)
    {
        m_hero2.m_X-=HERO_SPEED-5;
        if(m_hero2.m_X<0)
            m_hero2.m_X=0;
    }

    if(energy2<0)
        energy2=0;
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
               else
               {
               m_Timer.start();
               picTimer.start();
               bleed1=300;
               energy1=300;
               bleed2=300;
               energy2=300;
               }
             }



}

void fight::changeDartPic()
{
    m_hero.updatepic();
    if(m_hero.A_judge)
        m_hero.updateleftpic();
    if(m_hero.A_judge&&m_hero.isjump&&m_hero.status==true)
        m_hero.updateuppicL();
    else if(m_hero.A_judge&&m_hero.isjump&&m_hero.status==false)
        m_hero.updatedownpicL();


    if(m_hero.D_judge&&m_hero.isjump&&m_hero.status==true)
        m_hero.updateuppic();
    else if(m_hero.D_judge&&m_hero.isjump&&m_hero.status==false)
        m_hero.updatedownpic();

    if((m_hero.D_judge&&m_hero.S_judge&&m_hero.isjump==false)||(m_hero.A_judge&&m_hero.S_judge&&m_hero.isjump==false))
        m_hero.updatedash();

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
