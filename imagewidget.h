// imagewidget.h
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets/QWidget>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LabelMark.h"
#include "FileOperation.h"
#include <QtWidgets/QTextEdit>
using namespace std;
using namespace cv;
class QStringList;
class QListWidget;
class QListWidgetItem;

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent, bool flag, QString dirname);
    ~ImageWidget();
    bool flag;

    QString dirname;
    QString quality;
    QString language;
    QString scene;
    QString showdata;
    QStringList str;

private:
    void init();    // 初始化

private slots:
    void slot_itemClicked(QListWidgetItem*);
    void receiveDataSave(QString data);
private:
    QStringList m_imgList;      // 文件目录下所有的图像文件名
    QListWidget *m_listWidget;  // 预览窗口
    QString m_strPath;          // 文件夹路径
    QLabel m_showWidget;        // 图像显示窗口
    QTextEdit *textEdit;
signals:
    void sendToShow(QString);
};

void drawQuadri (Point * quad);
int isempty(Point * quad);
void onMouse(int event, int x, int y, int, void*);


#endif // IMAGEWIDGET_H
