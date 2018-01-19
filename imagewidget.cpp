// imagewidget.cpp
#include "imagewidget.h"
#include <QDir>
#include <QStringList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include "LabelMark.h"
Mat img_original, img_drawing;
Point quad[100][4];
int pointNum = 0;
int quadNum = 0;

enum buttonlabel{
    video,
    picture
};
buttonlabel flag = video;
void drawQuadri (Point * quad);
int isempty(Point * quad);
void onMouse(int event, int x, int y, int, void*);
ImageWidget::ImageWidget(QWidget *parent, QString filename)
    : QWidget(parent),m_strPath(filename){
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
    QDir dir(m_strPath);
    if (!dir.exists()) {
        return;
    }
    // 设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.png" << "*.jpg";
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
        QPixmap pixmap(m_strPath + "\\" + m_imgList.at(i));
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(IMAGE_SIZE)), m_imgList.at(i));
        listWidgetItem->setSizeHint(ITEM_SIZE);
        m_listWidget->insertItem(i, listWidgetItem);
    }

    // 窗口布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_listWidget);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    // 信号与槽
    connect(m_listWidget, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(slot_itemClicked(QListWidgetItem*)));
}

// 最大化窗口显示图像
void ImageWidget::slot_itemClicked(QListWidgetItem * item) {
    m_showWidget.setPixmap(QPixmap(m_strPath + "\\" + m_imgList.at(m_listWidget->row(item))));
    m_showWidget.showMaximized();
        int pic_counter = m_listWidget->row(item);
    QString filename =  m_strPath + "\\" + m_imgList.at(pic_counter);

    flag = picture;
    namedWindow("Picture");
    ofstream outfile( "test.txt");
    img_original = imread(filename.toStdString());
    img_original.copyTo(img_drawing);
    imshow("Picture",img_original);
    setMouseCallback("Picture", onMouse, 0);
    //qDebug()<<"first";



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
                    outfile << filename.toStdString() << " " << quad[indexnum][0].x << ","<< quad[indexnum][0].y << ","
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

            if (pic_counter >= m_listWidget->row(item)){
                cout << "\nPicture Finished!" << endl;
                destroyWindow("Picture");
                return;
            }
            filename =  m_strPath + "\\" + m_imgList.at(pic_counter);
            //qDebug()<<name;
            img_original = imread(filename.toStdString());
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
