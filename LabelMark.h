/********************************************************************
    created:    2017/12/30
    file ext:   cpp
    author:     Yinhao
    purpose:    Create a QWidget to make lables
*********************************************************************/
#ifndef LabelMark_H
#define LabelMark_H

#include <QWidget>
#include <QKeyEvent>


namespace Ui {
class LabelMark;
}

class LabelMark : public QWidget
{
    Q_OBJECT

public:
    explicit LabelMark(QWidget *parent = 0);
    void set(QString strs, QString scene, QString language, QString quality);
    ~LabelMark();
private:
    Ui::LabelMark *ui;
    void keyPressEvent(QKeyEvent * event);

private:
    QString str ;
    QString strs;
    QString scene;
    QString language;
    QString quality;
signals:
    //return QString to the main window
    void sendData(QString);
};

#endif // LabelMark_H
