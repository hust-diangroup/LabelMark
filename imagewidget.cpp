// imagewidget.cpp
#include "imagewidget.h"
#include <QDir>
#include <QStringList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QDebug>


Mat img_original, img_drawing;
Point quad[100][4];
int pointNum = 0;
int quadNum = 0;
bool flags;
ImageWidget::ImageWidget(QWidget *parent, bool flag, QString dirname)
    : QWidget(parent),
      flag(flag),
      dirname(dirname)

{
    this->init();
}

ImageWidget::~ImageWidget(){}

void ImageWidget::init() {
    // 窗口基本设置
    this->setWindowTitle("Image Preview");
   // this->setMinimumSize(780, 600);
    m_showWidget.setWindowTitle("Image Show");
    m_showWidget.setAlignment(Qt::AlignCenter);

    const QSize IMAGE_SIZE(240, 160);
    const QSize ITEM_SIZE(240, 190);

    // 判断路径是否存在
    m_strPath = dirname;
    QDir dir(m_strPath);
    if (!dir.exists()) {
        return;
    }

    // 设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    if(flag){
        filters << "*.png" << "*.jpg";
    }else{
        filters << "*.avi"<<"*.mp4";//设置过滤类型                                       x
    }
    dir.setNameFilters(filters);
    m_imgList = dir.entryList();
    if (m_imgList.count() <= 0) {
        return;
    }

    // QListWidget基本设置
    m_listWidget = new QListWidget(this);
    m_listWidget->setIconSize(IMAGE_SIZE);
    m_listWidget->setResizeMode(QListView::Adjust);
    m_listWidget->setViewMode(QListView::IconMode);
    m_listWidget->setMovement(QListView::Static);
    m_listWidget->setSpacing(8);

    // 创建单元项
    for (int i = 0; i<m_imgList.count(); ++i) {
        QPixmap pixmap(m_strPath + "/" + m_imgList.at(i));
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(IMAGE_SIZE)), m_imgList.at(i));
        listWidgetItem->setSizeHint(ITEM_SIZE);
        m_listWidget->insertItem(i, listWidgetItem);
    }

    textEdit = new QTextEdit(this);
    textEdit->setObjectName(QStringLiteral("textEdit"));
    textEdit->setGeometry(QRect(300, 10, 150, 450));
    textEdit->setText("打标内容:");
    textEdit->setFocusPolicy(Qt::NoFocus);

    // 窗口布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_listWidget);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    // 信号与槽
    connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slot_itemClicked(QListWidgetItem*)));

    flags = flag;
}

// 最大化窗口显示图像
void ImageWidget::slot_itemClicked(QListWidgetItem * item) {
   // m_showWidget.setPixmap(QPixmap(m_strPath + "\\" + m_imgList.at(m_listWidget->row(item))));
    //m_showWidget.showMaximized();

    int counter = m_listWidget->row(item);
    QString name = m_strPath + "/" + m_imgList.at(counter);
    fileoperation fileout;

    VideoCapture capture(name.toStdString());
    capture >> img_original;

    QDomDocument FrameMessage;
//    QFileInfo FI(name+".xml");
//    if (FI.isFile())
//    {

//    }
    QString strHeader( "version=\"1.0\" encoding=\"us-ascii\"" );
    FrameMessage.appendChild( FrameMessage.createProcessingInstruction("xml", strHeader) );
    QDomElement MainFrameNode = FrameMessage.createElement("frames");
    FrameMessage.appendChild(MainFrameNode);

    if(flag){
        namedWindow("Picture");
        img_original = imread(name.toStdString());
        img_original.copyTo(img_drawing);
        imshow("Picture",img_original);
        setMouseCallback("Picture", onMouse, 0);
    }else{

        namedWindow("Video");
        img_original.copyTo(img_drawing);
        imshow("Video", img_original);
        setMouseCallback("Video", onMouse, 0);
    }


    while (1){

        int c = waitKey(0);
        if ((c & 255) == 27)
        {
            cout << "Exiting ...\n";
            memset(quad,0,400*sizeof(Point));         //clear all the variables
            quadNum = 0;
            pointNum = 0;
            str.clear();
            fileout.VideoFinalInfInput(FrameMessage, name);
            quality.clear();
            language.clear();
            scene.clear();
            if(flag){
                destroyWindow("Picture");
            }else{
                destroyWindow("Video");
            }

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


           if(!fileout.SetFrameMessage(FrameMessage, name, counter, quadNum, ImageWidget::str, ImageWidget::quality, ImageWidget::language, ImageWidget::scene))//write the xml
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
            ++counter;
            quadNum = 0;
            pointNum = 0;
            str.clear();
            if(flag){
                if(m_imgList.count() == counter){
                    destroyWindow("Picture");
                    return;
                }
                name = m_strPath + "\\" + m_imgList.at(counter);
                img_original = imread(name.toStdString());
                img_original.copyTo(img_drawing);
            }else{
                capture >> img_original;   //move to the next frame
            }
                        qDebug()<< "aaaa";
            if (img_original.empty()){

                fileout.VideoFinalInfInput(FrameMessage, name);
                if(flag){
                    destroyWindow("Video");
                }else{
                    destroyWindow("Picture");
                }
                return;
            }

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
            connect(widget, SIGNAL(sendData(QString)), this, SLOT(receiveDataSave(QString)));
            break;
        }

        if(flag){
            imshow("Picture", img_drawing);
        }else{
            imshow("Video", img_drawing);
        }

    }
}

void ImageWidget::receiveDataSave(QString data){
    QString showlist = this->textEdit->toPlainText() + '\n' + data;
    this->textEdit->setText(showlist);     //获取传递过来的数据
    str << data;
    quality = "low";
    language = "Chinese";
    scene = "Station";
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
        //cout<<"x = "<<x<<" y = "<<y<<endl;
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
    if (flags){
        imshow("Picture", img_drawing);
    }else{
        imshow("Video", img_drawing);
    }
    return;
}

int fileoperation::SetFrameMessage(QDomDocument FrameMessage, QString name, int frame_counter, int quadNum, QStringList str, QString quality, QString language, QString scene)
{

    if (str.count() != quadNum)
    {
        cout << "please ensure the number of Transcriptions is equal to the number of the quad" <<endl;
        return 0;
    }
//    QString postfix = ".txt";
//    QString txtname = name + postfix;
//    ofstream   ofresult(txtname.toStdString(), ios::app);
    QDomElement MainFrameNode = FrameMessage.documentElement();
    QDomElement FrameNode = FrameMessage.createElement("frame");
    FrameNode.setAttribute("ID", QString::number(frame_counter+1));
    for (int i = 0; i < quadNum ; i++)
    {
        QStringList XList,YList;
        XList  << QString::number(quad[i][0].x,10)
               << QString::number(quad[i][1].x,10)
               << QString::number(quad[i][2].x,10)
               << QString::number(quad[i][3].x,10);
        YList  << QString::number(quad[i][0].y,10)
               << QString::number(quad[i][1].y,10)
               << QString::number(quad[i][2].y,10)
               << QString::number(quad[i][3].y,10);
        QDomElement ObjectNode = FrameMessage.createElement("object");
        ObjectNode.setAttribute("Transcription", str[i]);
        ObjectNode.setAttribute("ID", i+1001);
        ObjectNode.setAttribute("Quality", quality);
        ObjectNode.setAttribute("Language", language);
        ObjectNode.setAttribute("Scene", scene);
        for(int j = 0; j < 4; ++j) {
            QDomElement attribNode = FrameMessage.createElement("Point");
            attribNode.setAttribute("x", XList.at(j));
            attribNode.setAttribute("y", YList.at(j));
            ObjectNode.appendChild(attribNode);
        }
        FrameNode.appendChild(ObjectNode);
    }
    MainFrameNode.appendChild(FrameNode);
    FrameMessage.appendChild(MainFrameNode);
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
//    ofresult.close();
    return 1;
}

void fileoperation::VideoFinalInfInput(QDomDocument FrameMessage, QString name)
{
    QString postfix = ".xml";
    QString txtname = name + postfix;
//    ofstream   ofresult(txtname.toStdString(), ios::app);
//    ofresult << "</frames>" << endl;
//    ofresult.close();
    QFile file(txtname);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QTextStream stream(&file);
    FrameMessage.save(stream, 4);
    file.close();
}

