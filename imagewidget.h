// imagewidget.h
#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QtWidgets/QWidget>
#include <QLabel>

class QStringList;
class QListWidget;
class QListWidgetItem;

class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = 0);
    ~ImageWidget();

private:
    void init();    // 初始化

private slots:
    void slot_itemClicked(QListWidgetItem*);

private:
    QStringList m_imgList;      // 文件目录下所有的图像文件名
    QListWidget *m_listWidget;  // 预览窗口
    QString m_strPath;          // 文件夹路径
    QLabel m_showWidget;        // 图像显示窗口

};

#endif // IMAGEWIDGET_H
