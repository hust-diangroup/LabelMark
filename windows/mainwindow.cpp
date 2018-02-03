#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    flag = ui->radioButton->isChecked();
    qDebug()<<flag;
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




void MainWindow::on_openDir_clicked()
{
    dirname = QFileDialog::getExistingDirectory(this,tr("action"),"",QFileDialog::ShowDirsOnly) ;
    QDir dir(dirname);//如果不加地址，则就在当前目录下遍历
    ui->dirName->setText(dirname);
    flag = ui->radioButton->isChecked();
    ImageWidget *w = new ImageWidget(ui->scrollArea, flag, dirname);
    connect(w, SIGNAL(sendToShow(QString)), this, SLOT(receiveData(QString)));
    ui->scrollArea->setWidget(w);
}
