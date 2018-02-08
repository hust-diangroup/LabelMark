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
    ~LabelMark();
private:
    Ui::LabelMark *ui;

private:
    QString str ;
signals:
    //return QString to the main window
    void sendData(QString);
private slots:
    void on_languageLine_returnPressed();
    void on_sceneLine_returnPressed();
    void on_markLine_returnPressed();
    void on_qualityLine_returnPressed();
};

#endif // LabelMark_H
