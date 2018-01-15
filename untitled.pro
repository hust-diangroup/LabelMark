#-------------------------------------------------
#
# Project created by QtCreator 2017-12-30T02:25:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    LabelMark.cpp \
    imagewidget.cpp

HEADERS  += mainwindow.h \
    LabelMark.h \
    imagewidget.h \
    FileOperation.h

FORMS    += mainwindow.ui \
    LabelMark.ui \
    imagewidget.ui

INCLUDEPATH += C:\Users\Angelo\Desktop\install\include
INCLUDEPATH+=C:\Users\Angelo\Desktop\install\include\opencv
INCLUDEPATH+=C:\Users\Angelo\Desktop\install\include\opencv2

LIBS += -L C:\Users\Angelo\Desktop\install\x86\mingw\bin\libopencv_*.dll
LIBS += -L C:\Users\Angelo\Desktop\install\x86\mingw\lib\libopencv_*.a
