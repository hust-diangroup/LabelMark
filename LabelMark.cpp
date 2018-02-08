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


void LabelMark::on_languageLine_returnPressed()
{
    ui->qualityLine->setFocus();
}

void LabelMark::on_sceneLine_returnPressed()
{
    ui->languageLine->setFocus();
}

void LabelMark::on_markLine_returnPressed()
{
    ui->sceneLine->setFocus();
}

void LabelMark::on_qualityLine_returnPressed()
{
    str = ui->markLine->text() + "," + ui->sceneLine->text() + "," + ui->languageLine->text() + ',' + ui->qualityLine->text();
    emit sendData(str);
    qDebug("test<<<%s", qPrintable( str ) );
    this->close();
}
