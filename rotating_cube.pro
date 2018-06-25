QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += opengl
TARGET = rotating_cube
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    geometry.cpp

HEADERS  += mainwindow.h \
    geometry.h

RESOURCES += \
    shaders.qrc
