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
using namespace std;
using namespace cv;

class QStringList;
class QListWidget;
class QListWidgetItem;

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent, QString filename);
    ~ImageWidget();
    QString m_strPath;          // 文件夹路径
    QString quality;
    QString language;
    QString scene;
    QStringList str;
private:
    void init();    // 初始化

private slots:
    void slot_itemClicked(QListWidgetItem*);

private:
    QStringList m_imgList;      // 文件目录下所有的图像文件名
    QListWidget *m_listWidget;  // 预览窗口

    QLabel m_showWidget;        // 图像显示窗口
};



#endif // IMAGEWIDGET_H
