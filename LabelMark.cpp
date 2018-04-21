#include "LabelMark.h"
#include "ui_LabelMark.h"


extern int index[3];
LabelMark::LabelMark(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LabelMark)
{
    ui->setupUi(this);
    this->setWindowTitle("LabelMark");
    ui->comboBox->setCurrentIndex(index[0]);
    ui->comboBox_2->setCurrentIndex(index[1]);
    ui->comboBox_3->setCurrentIndex(index[2]);
    qDebug("hehe<<<%s", qPrintable( str ) );

}

LabelMark::~LabelMark()
{

    delete ui;
}


void LabelMark::keyPressEvent(QKeyEvent * event){

    if ( event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return){
        str = ui->markLine->text() + "," + ui->comboBox->currentText() + "," + ui->comboBox_2->currentText() + ',' + ui->comboBox_3->currentText();
        index[0] = ui->comboBox->currentIndex();
        index[1] = ui->comboBox_2->currentIndex();
        index[2] = ui->comboBox_3->currentIndex();
        emit sendData(str);
        qDebug("test<<<%s", qPrintable( str ) );
        this->close();
    }



}
