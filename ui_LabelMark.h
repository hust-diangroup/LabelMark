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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LabelMark
{
public:
    QLineEdit *markLine;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;

    void setupUi(QWidget *LabelMark)
    {
        if (LabelMark->objectName().isEmpty())
            LabelMark->setObjectName(QStringLiteral("LabelMark"));
        LabelMark->resize(339, 172);
        markLine = new QLineEdit(LabelMark);
        markLine->setObjectName(QStringLiteral("markLine"));
        markLine->setGeometry(QRect(70, 10, 241, 21));
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
        comboBox = new QComboBox(LabelMark);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(70, 50, 171, 22));
        comboBox_2 = new QComboBox(LabelMark);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(70, 90, 171, 22));
        comboBox_3 = new QComboBox(LabelMark);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(70, 130, 171, 22));

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
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("LabelMark", "\346\234\272\345\234\272\347\201\253\350\275\246\347\253\231\347\255\211\347\253\231\345\217\260", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\350\210\236\345\217\260", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\347\220\203\345\234\272", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\344\271\241\346\235\221", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\345\257\272\345\272\231\346\225\231\345\240\202\345\256\253\346\256\277", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\351\244\220\345\216\205\351\243\237\345\240\202", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\345\222\226\345\225\241\345\216\205\351\205\222\345\220\247", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\345\225\206\345\234\272\350\266\205\345\270\202", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\345\224\256\347\245\250\345\244\204", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\345\215\232\347\211\251\351\246\206", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\350\241\227\351\201\223", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\346\225\231\345\256\244", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\345\205\266\345\256\203", Q_NULLPTR)
        );
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("LabelMark", "\344\270\255\346\226\207", Q_NULLPTR)
         << QApplication::translate("LabelMark", "English", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\347\273\264\345\220\276\345\260\224\350\257\255", Q_NULLPTR)
        );
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("LabelMark", "\351\253\230", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\344\270\255", Q_NULLPTR)
         << QApplication::translate("LabelMark", "\344\275\216", Q_NULLPTR)
        );
    } // retranslateUi

};

namespace Ui {
    class LabelMark: public Ui_LabelMark {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LABELMARK_H
