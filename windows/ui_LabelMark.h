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
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *LabelMark)
    {
        if (LabelMark->objectName().isEmpty())
            LabelMark->setObjectName(QStringLiteral("LabelMark"));
        LabelMark->resize(339, 128);
        markLine = new QLineEdit(LabelMark);
        markLine->setObjectName(QStringLiteral("markLine"));
        markLine->setGeometry(QRect(70, 10, 241, 21));
        sceneLine = new QLineEdit(LabelMark);
        sceneLine->setObjectName(QStringLiteral("sceneLine"));
        sceneLine->setGeometry(QRect(70, 50, 241, 20));
        languageLine = new QLineEdit(LabelMark);
        languageLine->setObjectName(QStringLiteral("languageLine"));
        languageLine->setGeometry(QRect(70, 90, 241, 20));
        label = new QLabel(LabelMark);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(30, 90, 31, 21));
        label_2 = new QLabel(LabelMark);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(30, 50, 31, 21));
        label_3 = new QLabel(LabelMark);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 10, 31, 21));

        retranslateUi(LabelMark);

        QMetaObject::connectSlotsByName(LabelMark);
    } // setupUi

    void retranslateUi(QWidget *LabelMark)
    {
        LabelMark->setWindowTitle(QApplication::translate("LabelMark", "Form", Q_NULLPTR));
        markLine->setText(QString());
        label->setText(QApplication::translate("LabelMark", "\350\257\255\350\250\200", Q_NULLPTR));
        label_2->setText(QApplication::translate("LabelMark", "\345\234\272\346\231\257", Q_NULLPTR));
        label_3->setText(QApplication::translate("LabelMark", "\346\240\207\346\263\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LabelMark: public Ui_LabelMark {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELMARK_H
