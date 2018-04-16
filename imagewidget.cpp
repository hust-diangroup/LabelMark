// imagewidget.cpp
#include "imagewidget.h"
#include <QDir>
#include <QStringList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QDebug>
#include <QTextCodec>


Mat img_original, img_drawing;
Point quad[100][4];
int pointNum = 0;
int quadNum = 0;
//int openwindow = 0;
//int maxwindow = 0;
QStringList *pstring = NULL;
QStringList *pscene = NULL;
QStringList *planguage = NULL;
QStringList *pquality = NULL;
int currentquad = -1;
int currentcontext = currentquad;
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
//    openwindow++;
//    maxwindow = openwindow;
    ClearAllVariable();
    int xxx;
    int counter = m_listWidget->row(item);
    int framecounter = 0;
    pstring = &str;
    pscene = &scene;
    planguage = &language;
    pquality = &quality;

//    QTextCodec *code = QTextCodec::codecForName("gbk");
//    std::string namestr = code->fromUnicode(m_strPath + "\\" + m_imgList.at(counter)).data();
//    QString name = QString::fromStdString(namestr);
    QString name = m_strPath + "/" + m_imgList.at(counter);
    QFileInfo file(name);
    if(!file.isFile())
    {
        return;
    }
    qDebug() << name;
    QString name_withoutsuffix = name;
    name_withoutsuffix.truncate(name_withoutsuffix.lastIndexOf("."));

    VideoCapture capture(name.toLocal8Bit().toStdString());
    capture >> img_original;

//    fileoperation fileout;
//   fileout.InitFrameMessage();
    InitFrameMessage();
    qDebug() << "Start!";
    if(flag){
        namedWindow("Picture", 0);
        img_original = imread(name.toLocal8Bit().toStdString());
        img_original.copyTo(img_drawing);
        int result = ReadPicQuad(name_withoutsuffix, &xxx);
        if ( !result )
        {
            ClearAllVariable();
            destroyWindow("Picture");
            return;
        }
//        destroyWindow("Picture");
//        namedWindow("Picture", 0);
        if(img_drawing.empty())
            return;
        imshow("Picture",img_drawing);
        setMouseCallback("Picture", onMouse, 0);
    }else{
//        fileout.ReadFile(name);
        ReadXmlFile(name_withoutsuffix);
        namedWindow("Video", 0);
        img_original.copyTo(img_drawing);
//        QObject::connect(&fileout,SIGNAL(senddata(QString)),this,SLOT(receiveDataSave(QString)));
//        fileout.ReadFramequad(img_drawing);
        ReadFramequad(img_drawing);
        imshow("Video", img_drawing);
        setMouseCallback("Video", onMouse, 0);
    }


    while (1){

        int c = waitKey(0);
        if ((c & 255) == 27)
        {
            cout << "Exiting ...\n";
//            qDebug() << quadNum;
//            qDebug() << c;
            if (quadNum)
            {
                if (flag){
                    PicInfInput(name_withoutsuffix, quadNum);
                }
                else{
                    SetFrameMessage(framecounter, quadNum);
                }
            }
            ClearAllVariable();
            if(flag){
//                openwindow--;
                destroyWindow("Picture");
            }else{
//                fileout.VideoFinalInfInput(name);
                VideoFinalInfInput(framecounter,name_withoutsuffix);
                destroyWindow("Video");
            }

            return;
        }
      //  qDebug() << c;
        switch ((char)c)
        {
        case 'n':
            //set down the statistics
            if (pointNum != 0)
            {
                cout << "No Transcription exists. If no label, please clear the points first." << endl;
                break;
            }

            if(flag)
            {
                if(!PicInfInput(name_withoutsuffix, quadNum))//write the pic
                {
                    cout << "Please check it again!" << endl;
                    break;
                }
            }
            else
            {
               if(!SetFrameMessage(framecounter, quadNum))//write the xml
               {
                   cout << "Please check it again!" << endl;
                   break;
               }
            }
            ++counter;
            ++framecounter;
            ClearAllVariable();

            if(flag){
                if(m_imgList.count() == counter){
                    qDebug() << "destroy!";
//                    openwindow--;
                    destroyWindow("Picture");
                    img_drawing.release();
                    return;
                }
                name = m_strPath + "/" + m_imgList.at(counter);
                name_withoutsuffix = name;
                name_withoutsuffix.truncate(name_withoutsuffix.lastIndexOf("."));
                img_original = imread(name.toLocal8Bit().toStdString());
                img_original.copyTo(img_drawing);
                int result = ReadPicQuad(name_withoutsuffix, &xxx);
                if ( !result )
                {
                    ClearAllVariable();
                    destroyWindow("Picture");
                    img_drawing.release();
                    return;
                }
            }else{
                capture >> img_original;   //move to the next frame
                img_original.copyTo(img_drawing);
//                QObject::connect(&fileout,SIGNAL(senddata(QString)),this,SLOT(receiveDataSave(QString)));
//               fileout.ReadFramequad(img_drawing);
                ReadFramequad(img_drawing);

            }

            if (img_original.empty()){
                if(flag){
                    destroyWindow("Picture");
                }else{
//                    fileout.VideoFinalInfInput(name);
                    VideoFinalInfInput(framecounter, name_withoutsuffix);
                    destroyWindow("Video");
                }
                return;
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
            quad[quadNum][pointNum].x=0;
            quad[quadNum][pointNum].y=0;
            img_original.copyTo(img_drawing);
            drawAllQuadri(0, str);                       //redraw the points and the lines on the image.
            for(int j = 0 ; j < pointNum; j++)
            {
                circle(img_drawing,cvPoint(quad[quadNum][j].x,quad[quadNum][j].y),1,Scalar(0, 255, 0),2,8,0);
            }
            break;
        case 'c':
            //clear the last quad array
            if (quadNum > 0 && pointNum == 0)       //clear the current quad
            {
                for(int tempquad = currentquad; tempquad < quadNum -1; tempquad++)  //use the next quad to replace the tempquad
                {
                    for(int pointSn = 0; pointSn < 4; pointSn++)
                    {
                        quad[tempquad][pointSn].x = quad[tempquad + 1][pointSn].x;
                        quad[tempquad][pointSn].y = quad[tempquad + 1][pointSn].y;
                    }
                }
                memset(quad[--quadNum],0,4*sizeof(Point));

                //remove the label from the content shown on ui
                str.removeAt(currentquad);
                scene.removeAt(currentquad);
                language.removeAt(currentquad);
                quality.removeAt(currentquad);
                showallcontext();
//                str.removeAt(currentquad);
//                QStringList contextlist = this->textEdit->toPlainText().split("\n");
//                contextlist.removeAt(currentquad + 1);
//                this->textEdit->setText(contextlist.join('\n'));
                //finish

                if(currentquad == quadNum)
                {
                    --currentquad;
                }
                img_original.copyTo(img_drawing);
                drawAllQuadri(0, str);    //redraw the points and the lines on the image.
            }
            else    //clear the points that haven't generate the quad yet
            {
                memset(quad[quadNum],0,4*sizeof(Point));
                img_original.copyTo(img_drawing);
                drawAllQuadri(0, str);
                pointNum = 0;
            }
            break;
        case 45://↓，change the value of currentquad to the former one
            if(currentquad > 0 && quadNum > 0)
            {
                currentquad--;
                drawAllQuadri(0, str);
                show = "打标内容:";
                show = show + "\n" + str[currentquad] + "," + scene[currentquad] + "," +language[currentquad] + "," + quality[currentquad];
                this->textEdit->setText(show);
            }
            break;
        case 61://↑，change the value of currentquad to the next one
            if(currentquad < quadNum - 1 && quadNum > 0)
            {
                currentquad++;
                drawAllQuadri(0, str);
                show = "打标内容:";
                show = show + "\n" + str[currentquad] + "," + scene[currentquad] + "," +language[currentquad] + "," + quality[currentquad];
                this->textEdit->setText(show);
            }
            break;
        case 112://indistinct label marking
            if ( currentquad > -1 )
            {
                str[currentquad] = "###";
                scene[currentquad] = "###";
                language[currentquad] = "###";
                quality[currentquad] = "###";
                show = "打标内容:";
                show = show + '\n'+ "###" + "," + "###"+ "," + "###"+ "," + "###";
                this->textEdit->setText(show);     //获取传递过来的数据
                drawAllQuadri(2, str);   //red for indistinct label
            }
            break;
        case 113:
            showallcontext();
            break;
        case 'x':
            if (currentquad > -1) //Only when currentquad is exist can we draw quad
            {
                LabelMark *widget = new LabelMark;
                widget->show();
                connect(widget, SIGNAL(sendData(QString)), this, SLOT(receiveDataSave(QString)));
            }
            else
            {
                qDebug() << "Please draw the quad first";
            }
            break;
        }

        if(flag){
//            destroyWindow("Picture");
//            namedWindow("Picture", 0);
            if(img_drawing.empty())
            {
                ClearAllVariable();
                return;
            }

            imshow("Picture", img_drawing);
        }else{
            imshow("Video", img_drawing);
        }

    }
}

void ImageWidget::receiveDataSave(QString data){
    QStringList datalist = data.split(',');
    str[currentquad] = datalist[0];
    scene[currentquad] = datalist[1];
    language[currentquad] = datalist[2];
    quality[currentquad] = datalist[3];
    show = "打标内容:";
    show = show + '\n' + data;
    this->textEdit->setText(show);     //获取传递过来的数据
}


void drawQuadri (Point * quadPoint, int blue, int green, int red) {
    for(int i = 0; i < 4; i++)
    {
        line(img_drawing,quadPoint[i],quadPoint[(i+1)%4],Scalar(blue, green, red),3,8,0);
    }
}

void drawAllQuadri (int currentquad_color, QStringList str)
{
    //this function only draws the quads that have already exist.
    //the rest points which haven't generate the quad won't be show in this function
    for (int i = 0 ; i < quadNum ; i++)   //redraw the rest of the quads
    {
        for(int j = 0 ; j < 4; j++)
        {
            circle(img_drawing,cvPoint(quad[i][j].x,quad[i][j].y),1,Scalar(0, 255, 0),2,8,0);
        }
        if (str[i] == "") //Transcriptions can be searched
        {
            drawQuadri(quad[i], 255, 255, 255); //white for the quad with no label
        }
        else
        {
            QString tmpstr = str[i];
            if(tmpstr.indexOf("#") == -1)
            {
                drawQuadri(quad[i], 0, 255, 0); //green for normal
            }
            else
            {
                drawQuadri(quad[i], 0, 0, 255); //red for indistinct
            }
        }
    }
    if (quadNum > 0)
    {
        for(int j = 0 ; j < 4; j++)
        {
            circle(img_drawing,cvPoint(quad[currentquad][j].x,quad[currentquad][j].y),1,Scalar(255, 0, 0),2,8,0);
        }
        switch(currentquad_color)
        {
            case 0:drawQuadri(quad[currentquad], 255, 0, 0); //blue
                   break;
            case 1:drawQuadri(quad[currentquad], 0, 255, 0); //green
                   break;
            case 2:drawQuadri(quad[currentquad], 0, 0, 255); //red
                   break;
        }
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
//        quad[quadNum][pointNum%4].x = x;
//        quad[quadNum][pointNum%4].y = y;
//        //cout<<"x = "<<x<<" y = "<<y<<endl;
//        pointNum++;

        break;
    case CV_EVENT_LBUTTONUP:
        //finish drawing the rect (use color green for finish)
        quad[quadNum][pointNum%4].x = x;
        quad[quadNum][pointNum%4].y = y;
        //cout<<"x = "<<x<<" y = "<<y<<endl;
        pointNum++;
        circle(img_drawing,cvPoint(x,y),1,Scalar(0, 0, 255),2,8,0);

        if(pointNum == 4)
        {
            pointNum = 0;
            cout<<"draw quadri line"<<endl;
            quadNum++;
            currentquad = quadNum - 1;
            (*pstring) << "";
            (*pscene) << "";
            (*planguage) << "";
            (*pquality) << "";
            drawAllQuadri(0, *pstring);

        }

        break;
    }
    if (flags){
//        destroyWindow("Picture");
//        namedWindow("Picture", 0);
        imshow("Picture", img_drawing);
    }else{
        imshow("Video", img_drawing);
    }
    return;
}

void ImageWidget::showallcontext()
{
    if(str.count() <= 0)
    {
        return;
    }
    showlist = "打标内容:";
    for(int i = 0; i< str.count(); i++)
    {
        if(str[i] == "")
        {
            showlist = showlist + "\n" + "(empty context)" + "," + scene[i] + "," +language[i] + "," + quality[i];
        }
        else
        {
            showlist = showlist + "\n" + str[i] + "," + scene[i] + "," +language[i] + "," + quality[i];
        }
    }
    this->textEdit->setText(showlist);
}

int ImageWidget::SetFrameMessage(int frame_counter, int quadNum)
{
    //set the message from quad and str to Frame
    if (str.count() != quadNum)
    {
        cout << "please ensure the number of Transcriptions is equal to the number of the quad" << endl;
        return 0;
    }
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
        ObjectNode.setAttribute("Quality", quality[i]);
        ObjectNode.setAttribute("Language", language[i]);
        ObjectNode.setAttribute("Scene", scene[i]);
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
    return 1;
}

void ImageWidget::VideoFinalInfInput(int counter, QString name)
{
    while ( !TmpFileFrameNode.isNull() )
    {
        counter++;
        QDomNode ObjectNode = TmpFileFrameNode.firstChild();
        while ( !ObjectNode.isNull() )
        {
            QString datashow = ObjectNode.toElement().attributeNode("Transcription").value()+","
                    + ObjectNode.toElement().attributeNode("Language").value()+","
                    + ObjectNode.toElement().attributeNode("Scene").value()+","
                    + ObjectNode.toElement().attributeNode("Quality").value();
            QStringList datashowlist = datashow.split(',');
            str << datashowlist[0];
            language << datashowlist[1];
            scene << datashowlist[2];
            quality << datashowlist[3];

            QDomNode PointNode = ObjectNode.firstChild();
            for (int i=0; i<4 ;i++)
            {
                QDomElement PointElement = PointNode.toElement();
                quad[quadNum][i].x = PointElement.attributeNode("x").value().toInt();
                quad[quadNum][i].y = PointElement.attributeNode("y").value().toInt();
                PointNode = PointNode.nextSibling();
            }
            quadNum++;
            ObjectNode = ObjectNode.nextSibling();
        }
        SetFrameMessage(counter, quadNum);
        ClearAllVariable();
        TmpFileFrameNode = TmpFileFrameNode.nextSibling();
    }

    //write to the file
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
    FrameMessage.clear();
    FileMessage.clear();
    file.close();
}

void ImageWidget::InitFrameMessage()
{
    //set the header and <frames> for the new FrameMessage
    QString strHeader( "version=\"1.0\" encoding=\"us-ascii\"" );
    FrameMessage.appendChild( FrameMessage.createProcessingInstruction("xml", strHeader) );
    QDomElement MainFrameNode = FrameMessage.createElement("frames");
    FrameMessage.appendChild( MainFrameNode );
}

void ImageWidget::ReadXmlFile(QString name)
{
    //if file already exist
    QFileInfo FI(name+".xml");
    if (FI.isFile())
    {
        QFile file(name+".xml");
        FileMessage.setContent(&file);
        FIleMainFrameNode = FileMessage.documentElement();
        TmpFileFrameNode = FIleMainFrameNode.firstChild();
    }
}

void ImageWidget::ReadFramequad(Mat img_drawing)
{
    showlist= "打标内容:";
    this->textEdit->setText(showlist);
    //Read the next Frame
    if ( !TmpFileFrameNode.isNull() )
    {
        QDomNode ObjectNode = TmpFileFrameNode.firstChild();
        while ( !ObjectNode.isNull() )
        {
            QString datashow = ObjectNode.toElement().attributeNode("Transcription").value()+","
                    + ObjectNode.toElement().attributeNode("Language").value()+","
                    + ObjectNode.toElement().attributeNode("Scene").value()+","
                    + ObjectNode.toElement().attributeNode("Quality").value();
            showlist = this->textEdit->toPlainText() + '\n' + datashow;
            this->textEdit->setText(showlist);     //获取传递过来的数据
            QStringList datashowlist = datashow.split(',');
            str << datashowlist[0];
            language << datashowlist[1];
            scene << datashowlist[2];
            quality << datashowlist[3];

            QDomNode PointNode = ObjectNode.firstChild();
            for (int i=0; i<4 ;i++)
            {
                QDomElement PointElement = PointNode.toElement();
                quad[quadNum][i].x = PointElement.attributeNode("x").value().toInt();
                quad[quadNum][i].y = PointElement.attributeNode("y").value().toInt();
                PointNode = PointNode.nextSibling();
            }
            quadNum++;
            ObjectNode = ObjectNode.nextSibling();
        }
        currentquad = quadNum - 1;
        drawAllQuadri(0, str);
    }
    TmpFileFrameNode = TmpFileFrameNode.nextSibling();
}

int ImageWidget::PicInfInput(QString name, int quadNum)
{
    if (str.count() != quadNum)
    {
        cout << "please ensure the number of Transcriptions is equal to the number of the quad"  << endl;
        return 0;
    }
    QFile file(name+".txt");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return 0;
    QTextStream stream(&file);
    for (int i=0; i<quadNum ; i++)  //write
    {
        QString tmpstr = str[i];
        if (tmpstr.isNull())
        {
            stream << quad[i][0].x << "," << quad[i][0].y << ","
                   << quad[i][1].x << "," << quad[i][1].y << ","
                   << quad[i][2].x << "," << quad[i][2].y << ","
                   << quad[i][3].x << "," << quad[i][3].y << "," << "" << "," << "" << "," << "" << "," << "" << "\r\n" ;
        }
        else
        {
            stream << quad[i][0].x << "," << quad[i][0].y << ","
                   << quad[i][1].x << "," << quad[i][1].y << ","
                   << quad[i][2].x << "," << quad[i][2].y << ","
                   << quad[i][3].x << "," << quad[i][3].y << "," << str[i] << "," << scene[i] << "," << language[i] << "," << quality[i] << "\r\n" ;
        }

    }
    stream << "row=" << img_drawing.rows << "," << "columns=" << img_drawing.cols;
    file.close();
    return 1;
}

int ImageWidget::ReadPicQuad(QString name, int* pcounter)
{
    showlist= "打标内容:";
    this->textEdit->setText(showlist);
    QFileInfo FI(name+".txt");
    if (FI.isFile())
    {
        QFile file(name+".txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug() << "The txt file is in wrong state, please ensure the txt file is readable.";
            return 0;
        }
        QTextStream in(&file);
        QString line = in.readLine();
        while (!line.isNull())
        {
            TxtStr << line;
            line = in.readLine();
        }
        file.close();
        for(int i=0; i<TxtStr.count()-1 ; i++)   //Get the n-1 lines. The nth line is the pixel statistic
        {
            QString tmpstr = TxtStr[i];
            QStringList PointandTrans = tmpstr.split(",");
            if (PointandTrans.count() < 9)
            {
                continue ;
                //return File_Error_Warning(name, pcounter);
            }
            else
            {
                if (!TxtlineToPointandtrans(i, PointandTrans))
                {
                    memset(quad[i], 0 , 8*sizeof(Point));
                    continue;
                    //return File_Error_Warning(name, pcounter);
                }
            }
            str << Transcrption;
            language << languagetranscription;
            scene << scenetranscription;
            quality << qualitytranscription;
            if (Transcrption == "")
            {
                Transcrption += "(empty context)";
            }
            showlist = this->textEdit->toPlainText() + '\n' + Transcrption + "," + scenetranscription + "," + languagetranscription + "," + qualitytranscription;
            this->textEdit->setText(showlist);     //获取传递过来的数据
            Transcrption.clear();
            quadNum++;
        }
        TxtStr.clear();
        currentquad = quadNum - 1;
        drawAllQuadri(0, str);
    }
    return 1;
}

void ImageWidget::ClearAllVariable()
{
    memset(quad,0,400*sizeof(Point));         //clear all the variables
    quadNum = 0;
    pointNum = 0;
    currentquad = -1;
    str.clear();
    quality.clear();
    language.clear();
    scene.clear();
}

int ImageWidget::File_Error_Warning(QString name, int *pcounter)
{
    QMessageBox msgBox(QMessageBox::Warning, "File error",		///--这里是设置消息框标题
            "The format of the content in the txt file of the picture is error\n Mark it again or switch to the next one?"); ///--这里是设置消息框显示的内容
    msgBox.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    msgBox.setButtonText(QMessageBox::Ok,QString("Mark it"));
    msgBox.setButtonText(QMessageBox::Cancel,QString("Next one"));
    if(msgBox.exec() == QMessageBox::Cancel)
    {
        (*pcounter)++;
        qDebug() << m_imgList.count() << " " << *pcounter;
        if(m_imgList.count() == *pcounter){
            return 0;
        }
        else{
            name = m_strPath + "/" + m_imgList.at(*pcounter);
            img_original = imread(name.toLocal8Bit().toStdString());
            img_original.copyTo(img_drawing);
            int result = ReadPicQuad(name, pcounter);
            return result;
        }
    }
    else
    {
        return 1;
    }
}
int ImageWidget::TxtlineToPointandtrans(int counter, QStringList PointandTrans)
{
    int j = 0;
    for (; j < 8; j++)
    {
        bool ok;
        if( j%2 == 0)
        {
            quad[counter][j/2].x = PointandTrans[j].toInt(&ok,10);
        }
        else
        {
            quad[counter][j/2].y = PointandTrans[j].toInt(&ok,10);
        }
        if(ok == false)   //error when transform the string to number
        {
            return 0;
        }
    }
//    for (; j < PointandTrans.count()-1 ; j++)  //in case there is "," in the transcription
//    {
//        Transcrption += (PointandTrans[j]+",");
//    }
//    Transcrption += PointandTrans[j];   //add the last one with no ","
    while (PointandTrans.count() < 12)
    {
        PointandTrans << "";
    }
    Transcrption = PointandTrans[j++];
    scenetranscription = PointandTrans[j++];
    languagetranscription = PointandTrans[j++];
    qualitytranscription = PointandTrans[j];
    return 1;
}
