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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LabelMark
{
public:
    QLineEdit *lineEdit;

    void setupUi(QWidget *LabelMark)
    {
        if (LabelMark->objectName().isEmpty())
            LabelMark->setObjectName(QStringLiteral("LabelMark"));
        LabelMark->resize(392, 91);
        lineEdit = new QLineEdit(LabelMark);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(30, 30, 331, 21));

        retranslateUi(LabelMark);

        QMetaObject::connectSlotsByName(LabelMark);
    } // setupUi

    void retranslateUi(QWidget *LabelMark)
    {
        LabelMark->setWindowTitle(QApplication::translate("LabelMark", "Form", Q_NULLPTR));
        lineEdit->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class LabelMark: public Ui_LabelMark {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELMARK_H
