#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <QtXml/QDomDocument>

using namespace std;
class fileoperation
{
private:


public:
    int SetFrameMessage(QDomDocument FrameMessage, QString name, int frame_counter, int objnum, QStringList str, QString quality, QString language, QString scene);
    void VideoFinalInfInput(QDomDocument FrameMessage, QString name);
//    void GetOutputDir();
};





#endif // FILEINOUT_H
