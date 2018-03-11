/********************************************************************
    created:    2017/12/30
    file ext:   header
    author:     Yinhao
    purpose:    Create a MainWindow
                Using OpenCv to make a video into one frame
*********************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include "LabelMark.h"
#include "imagewidget.h"
#include "FileOperation.h"

using namespace std;
using namespace cv;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QString dirname;
    QString filename;
    QString quality;
    QString language;
    QString scene;
    QStringList str;
    bool flag;
    ~MainWindow();
    void setDir();
private slots:
    void on_pushButton_clicked();
    //Get String from LabelMark
    void receiveData(QString data);

    void on_pushButton_2_clicked();



    void on_openDir_clicked();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    bool start = false;
};



#endif // MAINWINDOW_H
