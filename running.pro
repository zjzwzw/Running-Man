#-------------------------------------------------
#
# Project created by QtCreator 2020-09-08T09:07:40
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia



RESOURCES += \
      res.qrc

RC_ICONS = icon.ico
# 添加图标

CONFIG+=  resources_big
#  大资源文件

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = running
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    map.cpp \
    hero.cpp \
    darts.cpp \
    fight.cpp \
    hero2.cpp \
    home_page.cpp \
    myice.cpp \
    myfire.cpp

HEADERS += \
        mainwindow.h \
    config.h \
    map.h \
    hero.h \
    darts.h \
    fight.h \
    hero2.h \
    home_page.h \
    myice.h \
    myfire.h

FORMS += \
        mainwindow.ui \
    home_page.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
