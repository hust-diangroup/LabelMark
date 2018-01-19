#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LabelMark.h"
#include "imagewidget.h"
#include "FileOperation.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{


}
void MainWindow::receiveData(QString data)
{
    QString showlist = ui->textEdit->toPlainText() + '\n' + data;
    ui->textEdit->setText(showlist);     //获取传递过来的数据
    str << data;
    quality = "low";
    language = "Chinese";
    scene = "Station";
}

void MainWindow::setDir(){
    dirname = QFileDialog::getExistingDirectory(this,tr("action"),"",QFileDialog::ShowDirsOnly) ;
    qDebug()<<dirname;
    QDir dir(dirname);//如果不加地址，则就在当前目录下遍历
    QStringList filters;
    filters << "*.jpg"<<"*.png";//设置过滤类型
    dir.setNameFilters(filters);//设置文件名的过滤
    QFileInfoList list = dir.entryInfoList();
    if(list.length()!=0)
        for (int i = 0; i < list.size(); ++i)
        {
            qDebug() << list.at(i).fileName();
        }
    else
    {
        qDebug()<<"no file";
    }
}

void MainWindow::on_pushButton_2_clicked()
{

}

int fileoperation::VideoInfInput(QString name, int frame_counter, int quadNum, QStringList str, QString quality, QString language, QString scene)
{

    if (str.count() != quadNum)
    {
        cout << "please ensure the number of Transcriptions is equal to the number of the quad" <<endl;
        return 0;
    }
    QString postfix = ".txt";
    QString txtname = name + postfix;
    ofstream   ofresult(txtname.toStdString(), ios::app);
//    if (frame_counter == 0)
//    {
//        ofresult << "<?xml version=\"1.0\" encoding=\"us-ascii\"?>" << endl;
//        ofresult << "<frames>" << endl;
//    }
//    if (isempty(quad[0]))
//    {
//        ofresult << "  <frame ID=\"" << frame_counter+1 << "\">" << endl;
//        ofresult << "  </frame>" << endl;
//    }
//    else
//    {
//        ofresult << "  <frame ID=\"" << frame_counter+1 << "\">" << endl;
//        for (int i = 0 ; i < quadNum ; i++)
//        {
//            ofresult << "    <object Transcription=\"" << qPrintable(str[i]) << "\" ID=\"" << i+1001 << "\" Quality=\"" << qPrintable(quality) <<"\" Language=\""<< qPrintable(language) <<"\" Scene=\" "<< qPrintable(scene) << "\">" << endl;
//            ofresult << "      <Point x=\""<< quad[i][0].x << "\" y=\"" << quad[i][0].y << "\" />" << endl;
//            ofresult << "      <Point x=\""<< quad[i][1].x << "\" y=\"" << quad[i][1].y << "\" />" << endl;
//            ofresult << "      <Point x=\""<< quad[i][2].x << "\" y=\"" << quad[i][2].y << "\" />" << endl;
//            ofresult << "      <Point x=\""<< quad[i][3].x << "\" y=\"" << quad[i][3].y << "\" />" << endl;
//            ofresult << "    </object>" << endl;
//        }
//        ofresult << "  </frame>" << endl;
//    }
    ofresult.close();
    return 1;
}

void fileoperation::VideoFinalInfInput(QString name)
{
    QString postfix = ".txt";
    QString txtname = name + postfix;
    ofstream   ofresult(txtname.toStdString(), ios::app);
    ofresult << "</frames>" << endl;
    ofresult.close();
}
void MainWindow::on_pushButton_3_clicked()
{
    QString name;
    dirname = QFileDialog::getExistingDirectory(this,tr("action"),"",QFileDialog::ShowDirsOnly) ;
    qDebug()<<dirname;
    QDir dir(dirname);//如果不加地址，则就在当前目录下遍历
    ImageWidget *w = new ImageWidget(ui->scrollArea, dirname);
    ui->scrollArea->setWidget(w);
}

