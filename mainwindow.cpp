#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "LabelMark.h"
Mat img_original, img_drawing;
Point quad [4];
int pointNum = 0;
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

void drawQuadri (Point * quad) {
    for(int i = 0; i < 4; i++)
    {
        line(img_drawing,quad[i],quad[(i+1)%4],Scalar(0,255,0),3,8,0);
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
        quad[pointNum%4].x = x;
        quad[pointNum%4].y = y;
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
            drawQuadri(quad);
        }

        break;
    }

    imshow("Video", img_drawing);
    return;
}

void MainWindow::on_pushButton_clicked()
{
    namedWindow("Video");
    ofstream outfile("1.txt");
    VideoCapture capture("C:\\Users\\Angelo\\Pictures\\test.avi");
    capture >> img_original;
    img_original.copyTo(img_drawing);
    imshow("Video", img_original);
    setMouseCallback("Video", onMouse, 0);
    int frame_counter = 0;
    while (1){
        int c = waitKey(0);
        if ((c & 255) == 27)
        {
            cout << "Exiting ...\n";
            break;
        }
        switch ((char)c)
        {
        case 'n':
            //read the next frame
            ++frame_counter;
            capture >> img_original;
            if (img_original.empty()){
                cout << "\nVideo Finished!" << endl;

            }

            img_original.copyTo(img_drawing);

            if (!isempty(quad))
            {
                drawQuadri(quad);

                outfile << frame_counter << " " << quad[0].x << " "<< quad[0].y << " "
                    << quad[1].x << " "<< quad[1].y << " "
                    << quad[2].x << " "<< quad[2].y << " "
                    << quad[3].x << " "<< quad[3].y << " "<<endl;
            }

            break;
        case 'z':
            //undo the latest labeling point
            if(pointNum == 0)
            {
                cout<<"if you want to clear the existent quad please press 'c'"<<endl;
                break;
            }
            pointNum--;
            quad[pointNum].x=0;
            quad[pointNum].y=0;
            img_original.copyTo(img_drawing);
            for(int i = 0 ; i < pointNum; i++)
            {
                circle(img_drawing,quad[i],1,Scalar(0, 255, 0),1,8,0);
            }

            break;
        case 'c':
            //clear quad array
            memset(quad,0,4*sizeof(Point));
            img_original.copyTo(img_drawing);
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
}
