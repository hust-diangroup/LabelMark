// imagewidget.h
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets/QWidget>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QtXml/QDomDocument>
#include <QLabel>
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "LabelMark.h"
//#include "FileOperation.h"
#include <QtWidgets/QTextEdit>
#include <QMessageBox>




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
    QStringList quality;
    QStringList language;
    QStringList scene;
    QString show;
    QString showlist;
    QStringList str;

    //视频文件操作
    int SetFrameMessage(int frame_counter, int quadNum);
    void showallcontext();
    void VideoFinalInfInput(int counter, QString name);
    void InitFrameMessage();
    void ReadXmlFile(QString name);
    void ReadFramequad(Mat img_drawing);

    //图片文件操作
    int PicInfInput(QString name, int objnum);
    int ReadPicQuad(QString name, int* pcounter);
    int TxtlineToPointandtrans(int counter, QStringList PointandTrans);

    //提示框设计
    int File_Error_Warning(QString name, int* pcounter);   //读取txt文件错误消息框,可以自行选择重新打标或者直接跳到下一张

private:
    void init();    // 初始化
    void ClearAllVariable();  //清除当前帧或者图片所有点以及标签

private slots:
    void slot_itemClicked(QListWidgetItem*);
    void receiveDataSave(QString data);
private:
    QStringList m_imgList;      // 文件目录下所有的图像文件名
    QListWidget *m_listWidget;  // 预览窗口
    QString m_strPath;          // 文件夹路径
    QLabel m_showWidget;        // 图像显示窗口
    QTextEdit *textEdit;

    //视频文件变量
    QDomDocument FrameMessage;
    QDomDocument FileMessage;
    QDomElement FIleMainFrameNode;
    QDomNode TmpFileFrameNode;

    //图片文件变量

    QStringList TxtStr;
    QString Transcrption;
    QString languagetranscription;
    QString qualitytranscription;
    QString scenetranscription;
signals:
    void sendToShow(QString);
};


void drawQuadri (Point * quad, int blue, int green, int red);
void drawAllQuadri (int currentquad_color, QStringList str);
int isempty(Point * quad);
void onMouse(int event, int x, int y, int, void*);


#endif // IMAGEWIDGET_H
