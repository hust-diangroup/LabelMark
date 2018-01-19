#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;
class fileoperation
{
private:


public:
    int VideoInfInput(QString name, int frame_counter, int objnum, QStringList str, QString quality, QString language, QString scene);
    void VideoFinalInfInput(QString name);
//    void GetOutputDir();
};





#endif // FILEINOUT_H
