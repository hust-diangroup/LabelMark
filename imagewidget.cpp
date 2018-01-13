// imagewidget.cpp
#include "imagewidget.h"
#include <QDir>
#include <QStringList>
#include <QListWidget>
#include <QVBoxLayout>
#include <QListWidgetItem>

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent){
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
    m_strPath = "C:\\Users\\Angelo\\Pictures";
    QDir dir(m_strPath);
    if (!dir.exists()) {
        return;
    }
    // 设置过滤器
    dir.setFilter(QDir::Files | QDir::NoSymLinks);
    QStringList filters;
    filters << "*.png" << "*.jpg";
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
        QPixmap pixmap(m_strPath + "\\" + m_imgList.at(i));
        QListWidgetItem *listWidgetItem = new QListWidgetItem(QIcon(pixmap.scaled(IMAGE_SIZE)), m_imgList.at(i));
        listWidgetItem->setSizeHint(ITEM_SIZE);
        m_listWidget->insertItem(i, listWidgetItem);
    }

    // 窗口布局
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_listWidget);
    mainLayout->setMargin(0);
    this->setLayout(mainLayout);

    // 信号与槽
    connect(m_listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(slot_itemClicked(QListWidgetItem*)));
}

// 最大化窗口显示图像
void ImageWidget::slot_itemClicked(QListWidgetItem * item) {
    m_showWidget.setPixmap(QPixmap(m_strPath + "\\" + m_imgList.at(m_listWidget->row(item))));
    m_showWidget.showMaximized();
}
