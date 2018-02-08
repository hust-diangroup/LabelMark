/********************************************************************************
** Form generated from reading UI file 'LabelMark.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LABELMARK_H
#define UI_LABELMARK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LabelMark
{
public:
    QLineEdit *markLine;
    QLineEdit *sceneLine;
    QLineEdit *languageLine;
    QLineEdit *qualityLine;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;

    void setupUi(QWidget *LabelMark)
    {
        if (LabelMark->objectName().isEmpty())
            LabelMark->setObjectName(QStringLiteral("LabelMark"));
        LabelMark->resize(339, 172);
        markLine = new QLineEdit(LabelMark);
        markLine->setObjectName(QStringLiteral("markLine"));
        markLine->setGeometry(QRect(70, 10, 241, 21));
        sceneLine = new QLineEdit(LabelMark);
        sceneLine->setObjectName(QStringLiteral("sceneLine"));
        sceneLine->setGeometry(QRect(70, 50, 241, 20));
        languageLine = new QLineEdit(LabelMark);
        languageLine->setObjectName(QStringLiteral("languageLine"));
        languageLine->setGeometry(QRect(70, 90, 241, 20));
        qualityLine = new QLineEdit(LabelMark);
        qualityLine->setObjectName(QStringLiteral("qualityLine"));
        qualityLine->setGeometry(QRect(70, 130, 241, 20));
        label_4 = new QLabel(LabelMark);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(20, 10, 31, 21));
        label_5 = new QLabel(LabelMark);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(20, 50, 31, 21));
        label_6 = new QLabel(LabelMark);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 90, 31, 21));
        label_7 = new QLabel(LabelMark);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(20, 130, 31, 21));

        retranslateUi(LabelMark);

        QMetaObject::connectSlotsByName(LabelMark);
    } // setupUi

    void retranslateUi(QWidget *LabelMark)
    {
        LabelMark->setWindowTitle(QApplication::translate("LabelMark", "Form", Q_NULLPTR));
        markLine->setText(QString());
        label_4->setText(QApplication::translate("LabelMark", "\346\240\207\346\263\250", Q_NULLPTR));
        label_5->setText(QApplication::translate("LabelMark", "\345\234\272\346\231\257", Q_NULLPTR));
        label_6->setText(QApplication::translate("LabelMark", "\350\257\255\350\250\200", Q_NULLPTR));
        label_7->setText(QApplication::translate("LabelMark", "\350\264\250\351\207\217", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LabelMark: public Ui_LabelMark {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELMARK_H
