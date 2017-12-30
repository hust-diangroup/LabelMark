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
/********************************************************************
    created:      2017/12/30
    name:         LabelMark
    author:       Yinhao
    description:  Class for Label Mark
                  Return QString to the main window
*********************************************************************/
class LabelMark : public QWidget
{
    Q_OBJECT

public:
    explicit LabelMark(QWidget *parent = 0);
    ~LabelMark();
    void keyPressEvent(QKeyEvent * event);
private:
    Ui::LabelMark *ui;

private:
    QString str ;
signals:
    //return QString to the main window
    void sendData(QString);
};

#endif // LabelMark_H
