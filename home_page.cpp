#include "home_page.h"
#include "ui_home_page.h"
#include "mainwindow.h"
#include "fight.h"
#include <QPainter>
#include <QSound>
#include <QLabel>
#include <QMouseEvent>

home_page::home_page(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::home_page)
{
   ui->setupUi(this);

   QSound *m = new QSound("://image/music1.wav");
   m->play();

   setWindowTitle("Running man");
   setFixedSize(GAME_WIDTH,GAME_HEIGHT);

   ui->single->setStyleSheet("QPushButton{border-image:url(://image/b1.png)}"
                       "QPushButton:hover{border-image:url(://image/b1_.png)}"
                       "QPushButton:pressed{border-image:url(://image/b1.png)}");
   ui->double_->setStyleSheet("QPushButton{border-image:url(://image/b2.png)}"
                       "QPushButton:hover{border-image:url(://image/b2_.png)}"
                       "QPushButton:pressed{border-image:url(://image/b2.png)}");
   ui->fight->setStyleSheet("QPushButton{border-image:url(://image/b3.png)}"
                       "QPushButton:hover{border-image:url(://image/b3_.png)}"
                       "QPushButton:pressed{border-image:url(://image/b3.png)}");

   ui->title->move(300,-140);
   ui->widget->move(350,GAME_HEIGHT);

   t.setInterval(GAME_RATE);
   t.start();
   connect(&t , &QTimer::timeout,[=](){

        static int y=-140;
        static int y1=GAME_HEIGHT;
        y1-=2;
        y+=2;
        ui->title->move(300,y);
        ui->widget->move(350,y1);
        if(y>100&&y1<300)
            t.stop();
   });





   m_Timer.setInterval(GAME_RATE);

   m_Timer.start();


   connect(&m_Timer , &QTimer::timeout,[=](){


       m_map.mapPosition();

       update();

   });


   connect(ui->single,&QPushButton::clicked,[=]()
   {
      MainWindow *w=new MainWindow;
      w->show();
      w->people=1;
      this->close();
      m->stop();
   });
   connect(ui->double_,&QPushButton::clicked,[=]()
   {
      MainWindow *w=new MainWindow;
      w->show();
      w->people=2;
      this->close();
      m->stop();
   });
   connect(ui->fight,&QPushButton::clicked,[=]()
   {
      fight *w=new fight;
      w->show();
      this->close();
      m->stop();
   });
}

home_page::~home_page()
{
    delete ui;
}

void home_page::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(m_map.m_map1_posX,0,m_map.m_map1);
    painter.drawPixmap(m_map.m_map2_posX,0,m_map.m_map2);


}

void home_page::mousePressEvent(QMouseEvent *e)
{

    //加速出现
    if(e->buttons()==Qt::LeftButton)
    {
        t.setInterval(1);
    }


}
