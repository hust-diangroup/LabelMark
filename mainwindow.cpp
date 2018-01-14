#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LabelMark.h"
#include "imagewidget.h"
#include "FileOperation.h"
Mat img_original, img_drawing;
Point quad[100][4];
int pointNum = 0;
int quadNum = 0;
enum buttonlabel{
    video,
    picture
};
buttonlabel flag = video;
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

void drawQuadri (Point * quadPoint) {
    for(int i = 0; i < 4; i++)
    {
        line(img_drawing,quadPoint[i],quadPoint[(i+1)%4],Scalar(0,255,0),3,8,0);
    }
}


int isempty(Point * quad)
{
    for (int i = 0 ; i < 4; i++)
    {
        if (quad[i].x !=0 || quad[i].y !=0 )
        {
            return 0;
        }
    }
    return 1;
}
void onMouse(int event, int x, int y, int, void*)
{


    switch (event)
    {
    case CV_EVENT_LBUTTONDOWN:
        quad[quadNum][pointNum%4].x = x;
        quad[quadNum][pointNum%4].y = y;
        cout<<"x = "<<x<<" y = "<<y<<endl;
        pointNum++;

        break;
    case CV_EVENT_LBUTTONUP:
        //finish drawing the rect (use color green for finish)

        circle(img_drawing,cvPoint(x,y),1,Scalar(0, 255, 0),2,8,0);

        if(pointNum == 4)
        {
            pointNum = 0;

            cout<<"draw quadri line"<<endl;
            drawQuadri(quad[quadNum++]);

        }

        break;
    }
    if (flag == picture)
    {
        imshow("Picture", img_drawing);
    }
    else if (flag == video)
    {
        imshow("Video", img_drawing);
    }
    return;
}
void MainWindow::on_pushButton_clicked()
{
    QString name;
    dirname = QFileDialog::getExistingDirectory(this,tr("action"),"",QFileDialog::ShowDirsOnly) ;
    qDebug()<<dirname;
    QDir dir(dirname);//如果不加地址，则就在当前目录下遍历
    QStringList filters;
    filters << "*.avi"<<"*.mp4";//设置过滤类型
    dir.setNameFilters(filters);//设置文件名的过滤
    QFileInfoList list = dir.entryInfoList();
    int frame_counter = 0;
    flag = video;
    if(list.length() == 0){

    }
    else{
        filename = list.at(frame_counter).fileName();
        qDebug()<<filename;
        name = dirname + "/" + filename;
        qDebug()<<name;
    }

    namedWindow("Video");
    fileoperation fileout;
    VideoCapture capture(name.toStdString());
    capture >> img_original;
    img_original.copyTo(img_drawing);
    imshow("Video", img_original);
    setMouseCallback("Video", onMouse, 0);

    while (1){
        int c = waitKey(0);
        if ((c & 255) == 27)
        {
            cout << "Exiting ...\n";
            memset(quad,0,400*sizeof(Point));         //clear all the variables
            quadNum = 0;
            pointNum = 0;
            str.clear();
            quality.clear();
            language.clear();
            scene.clear();
            destroyWindow("Video");
            return;
        }
        switch ((char)c)
        {
        case 'n':
            //set down the statistics
            if (pointNum != 0)
            {
                cout << "No Transcription exists. If no label, please clear the points first." << endl;
                break;
            }


           if(!fileout.VideoInfInput(name, frame_counter, quadNum, MainWindow::str, MainWindow::quality, MainWindow::language, MainWindow::scene))//write the xml
           {
               cout << "Please check it again!" << endl;
               break;
           }
            for (int i = 0; i<quadNum ; i++)    //clear the quad
            {
                for (int j = 0; j<4 ; j++)
                {
                    quad[i][j].x = 0;
                    quad[i][j].y = 0;
                }
            }
            ++frame_counter;
            quadNum = 0;
            pointNum = 0;
            str.clear();

            capture >> img_original;   //move to the next frame
            if (img_original.empty()){
                cout << "\nVideo Finished!" << endl;
                fileout.VideoFinalInfInput(name);
                destroyWindow("Video");
                return;
            }

            img_original.copyTo(img_drawing);
//                s = MainWindow::str;
//                qDebug("in file<<<%s", qPrintable( s ) );
//                outfile << quad[0].x << ","<< quad[0].y << ","
//                    << quad[1].x << ","<< quad[1].y << ","
//                    << quad[2].x << ","<< quad[2].y << ","
//                    << quad[3].x << ","<< quad[3].y << "," << qPrintable( s ) <<endl;

            break;
        case 'z':
            //undo the latest labeling point
            if(pointNum == 0)
            {
                cout<<"if you want to clear the existent quad please press 'c'"<<endl;
                break;
            }
            pointNum--;
            quad[quadNum][pointNum].x=0;
            quad[quadNum][pointNum].y=0;
            img_original.copyTo(img_drawing);
            for (int i = 0 ; i < quadNum ; i++)     //redraw the points and the lines on the image.
            {
                for(int j = 0 ; j < 4; j++)
                {
                    circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
                }
                drawQuadri(quad[i]);
            }
            for(int j = 0 ; j < pointNum; j++)
            {
                circle(img_drawing,cvPoint(quad[quadNum][j].x,quad[quadNum][j].y),1,Scalar(0, 255, 0),2,8,0);
            }
            break;
        case 'c':
            //clear the last quad array
            if (quadNum > 0 && pointNum == 0)       //clear the last quad
            {
                memset(quad[--quadNum],0,4*sizeof(Point));
                img_original.copyTo(img_drawing);
                for (int i = 0 ; i < quadNum ; i++)   //redraw the rest of the quads
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
                    }
                    drawQuadri(quad[i]);
                }
            }
            else    //clear the points with no line
            {
                memset(quad[quadNum],0,4*sizeof(Point));
                img_original.copyTo(img_drawing);
                for (int i = 0 ; i < quadNum ; i++)
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
                    }
                    drawQuadri(quad[i]);
                }
                pointNum = 0;
            }
            break;
        case 'x':
            LabelMark *widget = new LabelMark;
            widget->show();
            connect(widget, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
            break;
        }
        imshow("Video", img_drawing);
    }


}
void MainWindow::receiveData(QString data)
{
    ui->textEdit->setText(data);     //获取传递过来的数据
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
    QString name;
    dirname = QFileDialog::getExistingDirectory(this,tr("action"),"",QFileDialog::ShowDirsOnly) ;
    qDebug()<<dirname;
    QDir dir(dirname);//如果不加地址，则就在当前目录下遍历
    QStringList filters;
    filters << "*.jpg"<<"*.png";//设置过滤类型
    dir.setNameFilters(filters);//设置文件名的过滤
    QFileInfoList list = dir.entryInfoList();

    int pic_counter = 0;
    flag = picture;
    if(list.length() == 0){

    }
    else{
        filename = list.at(pic_counter).fileName();
        qDebug()<<filename;
        name = dirname + "/" + filename;
        qDebug()<<name;
    }

    namedWindow("Picture");
    ofstream outfile( "test.txt");
    img_original = imread(name.toStdString());
    img_original.copyTo(img_drawing);
    imshow("Picture",img_original);
    setMouseCallback("Picture", onMouse, 0);
    qDebug()<<"first";



    while (1){
        int c = waitKey(0);
        if ((c & 255) == 27)
        {
            cout << "Exiting ...\n";
            memset(quad,0,400*sizeof(Point));
            quadNum = 0;
            pointNum = 0;
            str.clear();
            quality.clear();
            language.clear();
            scene.clear();
            destroyWindow("Picture");
            return;
        }
        switch ((char)c)
        {
        case 'n':
            //read the next frame
            if (pointNum != 0)
            {
                cout << "No Transcription exists. If no label, please clear the points first." << endl;
                break;
            }
            if(str.count() != quadNum)
            {
                cout << "please ensure the number of Transcriptions is equal to the number of the quad" << endl;
                break;
            }
            if (!str.isEmpty())
            {
                for (int indexnum = 0 ; indexnum < quadNum ; indexnum++)
                {
                    outfile << name.toStdString() << " " << quad[indexnum][0].x << ","<< quad[indexnum][0].y << ","
                        << quad[indexnum][1].x << ","<< quad[indexnum][1].y << ","
                        << quad[indexnum][2].x << ","<< quad[indexnum][2].y << ","
                        << quad[indexnum][3].x << ","<< quad[indexnum][3].y << "," << qPrintable(str[indexnum]) <<endl;
                }
            }
            ++pic_counter;
            for (int i = 0; i<quadNum ; i++)  //clear the variables
            {
                for (int j = 0; j<4 ; j++)
                {
                    quad[i][j].x = 0;
                    quad[i][j].y = 0;
                }
            }
            quadNum = 0;
            pointNum = 0;
            str.clear();

            if (pic_counter >= list.length()){
                cout << "\nPicture Finished!" << endl;
                destroyWindow("Picture");
                return;
            }
            filename = list.at(pic_counter).fileName();
            name = dirname + "/" + filename;
            qDebug()<<name;
            img_original = imread(name.toStdString());
            img_original.copyTo(img_drawing);
            break;
        case 'z':
            //undo the latest labeling point
            if(pointNum == 0)
            {
                cout<<"if you want to clear the existent quad please press 'c'"<<endl;
                break;
            }
            pointNum--;
            quad[quadNum][pointNum].x=0;
            quad[quadNum][pointNum].y=0;
            img_original.copyTo(img_drawing);
            for (int i = 0 ; i < quadNum ; i++)
            {
                for(int j = 0 ; j < 4; j++)
                {
                    circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
                }
                drawQuadri(quad[i]);
            }
            for(int j = 0 ; j < pointNum; j++)
            {
                circle(img_drawing,cvPoint(quad[quadNum][j].x,quad[quadNum][j].y),1,Scalar(0, 255, 0),2,8,0);
            }

            break;
        case 'c':
            //clear quad array
            if (quadNum > 0 && pointNum == 0)       //clear the last quad
            {
                memset(quad[--quadNum],0,4*sizeof(Point));
                img_original.copyTo(img_drawing);
                for (int i = 0 ; i < quadNum ; i++)   //redraw the rest of the quads
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
                    }
                    drawQuadri(quad[i]);
                }
            }
            else    //clear the points with no line
            {
                memset(quad[quadNum],0,4*sizeof(Point));
                img_original.copyTo(img_drawing);
                for (int i = 0 ; i < quadNum ; i++)
                {
                    for(int j = 0 ; j < 4; j++)
                    {
                        circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
                    }
                    drawQuadri(quad[i]);
                }
                pointNum = 0;
            }
            break;
        case 'x':
            LabelMark *widget = new LabelMark;
            widget->show();
            connect(widget, SIGNAL(sendData(QString)), this, SLOT(receiveData(QString)));
            break;
        }
        imshow("Picture", img_drawing);
    }
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
    if (frame_counter == 0)
    {
        ofresult << "<?xml version=\"1.0\" encoding=\"us-ascii\"?>" << endl;
        ofresult << "<frames>" << endl;
    }
    if (isempty(quad[0]))
    {
        ofresult << "  <frame ID=\"" << frame_counter+1 << "\">" << endl;
        ofresult << "  </frame>" << endl;
    }
    else
    {
        ofresult << "  <frame ID=\"" << frame_counter+1 << "\">" << endl;
        for (int i = 0 ; i < quadNum ; i++)
        {
            ofresult << "    <object Transcription=\"" << qPrintable(str[i]) << "\" ID=\"" << i+1001 << "\" Quality=\"" << qPrintable(quality) <<"\" Language=\""<< qPrintable(language) <<"\" Scene=\" "<< qPrintable(scene) << "\">" << endl;
            ofresult << "      <Point x=\""<< quad[i][0].x << "\" y=\"" << quad[i][0].y << "\" />" << endl;
            ofresult << "      <Point x=\""<< quad[i][1].x << "\" y=\"" << quad[i][1].y << "\" />" << endl;
            ofresult << "      <Point x=\""<< quad[i][2].x << "\" y=\"" << quad[i][2].y << "\" />" << endl;
            ofresult << "      <Point x=\""<< quad[i][3].x << "\" y=\"" << quad[i][3].y << "\" />" << endl;
            ofresult << "    </object>" << endl;
        }
        ofresult << "  </frame>" << endl;
    }
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
    ImageWidget *w = new ImageWidget(ui->scrollArea);
    ui->scrollArea->setWidget(w);
}

