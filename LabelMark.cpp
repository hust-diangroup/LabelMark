#include "LabelMark.h"
#include "ui_LabelMark.h"

LabelMark::LabelMark(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelMark)
{
    ui->setupUi(this);
    this->setWindowTitle("LabelMark");
    qDebug("hehe<<<%s", qPrintable( str ) );
}

LabelMark::~LabelMark()
{

    delete ui;
}


void LabelMark::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Return){
        str = ui->lineEdit->text();
        emit sendData(ui->lineEdit->text());
        qDebug("test<<<%s", qPrintable( str ) );
        this->close();
    }

}
