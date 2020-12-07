#-------------------------------------------------
#
# Project created by QtCreator 2020-12-07T20:54:38
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGL_Texture
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    openglwidget.cpp

HEADERS  += mainwindow.h \
    openglwidget.h

FORMS    += mainwindow.ui

LIBS += -lopengl32
