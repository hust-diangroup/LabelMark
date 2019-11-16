#-------------------------------------------------
#
# Project created by QtCreator 2017-12-30T02:25:59
#
#-------------------------------------------------

QT       += core gui xml

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

INCLUDEPATH += C:\opencv\opencv\build\include \
                C:\opencv\opencv\build\include\opencv \
                C:\opencv\opencv\build\include\opencv2

LIBS += C:\opencv_mingw\bin\libopencv_core330.dll \
        C:\opencv_mingw\bin\libopencv_highgui330.dll \
        C:\opencv_mingw\bin\libopencv_imgcodecs330.dll \
        C:\opencv_mingw\bin\libopencv_imgproc330.dll \
        C:\opencv_mingw\bin\libopencv_videoio330.dll
