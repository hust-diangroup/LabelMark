#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "opencv2/opencv.hpp"
#include <QtXml/QDomDocument>

using namespace std;
using namespace cv;
class fileoperation
{

private:
    QDomDocument FrameMessage;
    QDomDocument FileMessage;
    QDomElement FIleMainFrameNode;
    QDomNode TmpFileFrameNode;


public:
    int SetFrameMessage(int frame_counter, int objnum, QStringList str, QString quality, QStringList language, QString scene);
    void VideoFinalInfInput(QString name);
    void InitFrameMessage();
    void ReadFile(QString name);
    void ReadFramequad(Mat img_drawing);
//    void GetOutputDir();

//signals:
//    void senddata(QString);


};





#endif // FILEINOUT_H
