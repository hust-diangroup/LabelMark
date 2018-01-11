/********************************************************************
    created:    2017/12/30
    file ext:   cpp
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
using namespace std;
using namespace cv;
namespace Ui {
class MainWindow;
}
/********************************************************************
    created:         2017/12/30
    name:            cpp
    author:          Yinhao
    description::    Create a MainWindow
                     //Choose video from documents
*********************************************************************/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString dirname;
    QString filename;
    QString str;
    ~MainWindow();
    void setDir();
private slots:
    void on_pushButton_clicked();
    //Get String from LabelMark
    void receiveData(QString data);

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};


void drawQuadri (Point * quad);
int isempty(Point * quad);
void onMouse(int event, int x, int y, int, void*);

#endif // MAINWINDOW_H
