/********************************************************************************
** Form generated from reading UI file 'home_page.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_PAGE_H
#define UI_HOME_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_home_page
{
public:
    QWidget *centralwidget;
    QWidget *title;
    QWidget *widget;
    QPushButton *single;
    QPushButton *double_;
    QPushButton *fight;
    QMenuBar *menubar;

    void setupUi(QMainWindow *home_page)
    {
        if (home_page->objectName().isEmpty())
            home_page->setObjectName(QStringLiteral("home_page"));
        home_page->resize(970, 600);
        centralwidget = new QWidget(home_page);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        title = new QWidget(centralwidget);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(320, 90, 600, 140));
        title->setStyleSheet(QLatin1String("\n"
"border-image: url(:/image/title.png);"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(330, 230, 500, 241));
        single = new QPushButton(widget);
        single->setObjectName(QStringLiteral("single"));
        single->setGeometry(QRect(130, 0, 250, 75));
        double_ = new QPushButton(widget);
        double_->setObjectName(QStringLiteral("double_"));
        double_->setGeometry(QRect(130, 80, 250, 75));
        fight = new QPushButton(widget);
        fight->setObjectName(QStringLiteral("fight"));
        fight->setGeometry(QRect(130, 160, 250, 75));
        home_page->setCentralWidget(centralwidget);
        menubar = new QMenuBar(home_page);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 970, 26));
        home_page->setMenuBar(menubar);

        retranslateUi(home_page);

        QMetaObject::connectSlotsByName(home_page);
    } // setupUi

    void retranslateUi(QMainWindow *home_page)
    {
        home_page->setWindowTitle(QApplication::translate("home_page", "MainWindow", Q_NULLPTR));
        single->setText(QString());
        double_->setText(QString());
        fight->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class home_page: public Ui_home_page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_PAGE_H
