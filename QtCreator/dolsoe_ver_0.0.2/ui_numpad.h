/********************************************************************************
** Form generated from reading UI file 'numpad.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NUMPAD_H
#define UI_NUMPAD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NumPad
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *npPwIndicatorLayout;
    QLabel *np_pw_indicator_1;
    QLabel *np_pw_indicator_2;
    QLabel *np_pw_indicator_3;
    QLabel *np_pw_indicator_4;
    QGridLayout *gridLayout;
    QPushButton *Button1;
    QPushButton *Button2;
    QPushButton *Button3;
    QPushButton *Button4;
    QPushButton *Button5;
    QPushButton *Button6;
    QPushButton *Button7;
    QPushButton *Button8;
    QPushButton *Button9;
    QPushButton *backButton;
    QPushButton *Button0;
    QPushButton *enterButton;

    void setupUi(QWidget *NumPad)
    {
        if (NumPad->objectName().isEmpty())
            NumPad->setObjectName(QString::fromUtf8("NumPad"));
        NumPad->resize(272, 300);
        verticalLayout = new QVBoxLayout(NumPad);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit = new QLineEdit(NumPad);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setStyleSheet(QString::fromUtf8(""));
        lineEdit->setReadOnly(true);

        verticalLayout->addWidget(lineEdit);

        npPwIndicatorLayout = new QHBoxLayout();
        npPwIndicatorLayout->setSpacing(6);
        npPwIndicatorLayout->setObjectName(QString::fromUtf8("npPwIndicatorLayout"));
        np_pw_indicator_1 = new QLabel(NumPad);
        np_pw_indicator_1->setObjectName(QString::fromUtf8("np_pw_indicator_1"));
        np_pw_indicator_1->setMinimumSize(QSize(20, 20));
        np_pw_indicator_1->setMaximumSize(QSize(20, 20));
        np_pw_indicator_1->setAlignment(Qt::AlignmentFlag::AlignCenter);

        npPwIndicatorLayout->addWidget(np_pw_indicator_1);

        np_pw_indicator_2 = new QLabel(NumPad);
        np_pw_indicator_2->setObjectName(QString::fromUtf8("np_pw_indicator_2"));
        np_pw_indicator_2->setMinimumSize(QSize(20, 20));
        np_pw_indicator_2->setMaximumSize(QSize(20, 20));
        np_pw_indicator_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        npPwIndicatorLayout->addWidget(np_pw_indicator_2);

        np_pw_indicator_3 = new QLabel(NumPad);
        np_pw_indicator_3->setObjectName(QString::fromUtf8("np_pw_indicator_3"));
        np_pw_indicator_3->setMinimumSize(QSize(20, 20));
        np_pw_indicator_3->setMaximumSize(QSize(20, 20));
        np_pw_indicator_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        npPwIndicatorLayout->addWidget(np_pw_indicator_3);

        np_pw_indicator_4 = new QLabel(NumPad);
        np_pw_indicator_4->setObjectName(QString::fromUtf8("np_pw_indicator_4"));
        np_pw_indicator_4->setMinimumSize(QSize(20, 20));
        np_pw_indicator_4->setMaximumSize(QSize(20, 20));
        np_pw_indicator_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        npPwIndicatorLayout->addWidget(np_pw_indicator_4);


        verticalLayout->addLayout(npPwIndicatorLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        Button1 = new QPushButton(NumPad);
        Button1->setObjectName(QString::fromUtf8("Button1"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(Button1->sizePolicy().hasHeightForWidth());
        Button1->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button1, 0, 0, 1, 1);

        Button2 = new QPushButton(NumPad);
        Button2->setObjectName(QString::fromUtf8("Button2"));
        sizePolicy1.setHeightForWidth(Button2->sizePolicy().hasHeightForWidth());
        Button2->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button2, 0, 1, 1, 1);

        Button3 = new QPushButton(NumPad);
        Button3->setObjectName(QString::fromUtf8("Button3"));
        sizePolicy1.setHeightForWidth(Button3->sizePolicy().hasHeightForWidth());
        Button3->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button3, 0, 2, 1, 1);

        Button4 = new QPushButton(NumPad);
        Button4->setObjectName(QString::fromUtf8("Button4"));
        sizePolicy1.setHeightForWidth(Button4->sizePolicy().hasHeightForWidth());
        Button4->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button4, 1, 0, 1, 1);

        Button5 = new QPushButton(NumPad);
        Button5->setObjectName(QString::fromUtf8("Button5"));
        sizePolicy1.setHeightForWidth(Button5->sizePolicy().hasHeightForWidth());
        Button5->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button5, 1, 1, 1, 1);

        Button6 = new QPushButton(NumPad);
        Button6->setObjectName(QString::fromUtf8("Button6"));
        sizePolicy1.setHeightForWidth(Button6->sizePolicy().hasHeightForWidth());
        Button6->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button6, 1, 2, 1, 1);

        Button7 = new QPushButton(NumPad);
        Button7->setObjectName(QString::fromUtf8("Button7"));
        sizePolicy1.setHeightForWidth(Button7->sizePolicy().hasHeightForWidth());
        Button7->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button7, 2, 0, 1, 1);

        Button8 = new QPushButton(NumPad);
        Button8->setObjectName(QString::fromUtf8("Button8"));
        sizePolicy1.setHeightForWidth(Button8->sizePolicy().hasHeightForWidth());
        Button8->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button8, 2, 1, 1, 1);

        Button9 = new QPushButton(NumPad);
        Button9->setObjectName(QString::fromUtf8("Button9"));
        sizePolicy1.setHeightForWidth(Button9->sizePolicy().hasHeightForWidth());
        Button9->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button9, 2, 2, 1, 1);

        backButton = new QPushButton(NumPad);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        sizePolicy1.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(backButton, 3, 0, 1, 1);

        Button0 = new QPushButton(NumPad);
        Button0->setObjectName(QString::fromUtf8("Button0"));
        sizePolicy1.setHeightForWidth(Button0->sizePolicy().hasHeightForWidth());
        Button0->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(Button0, 3, 1, 1, 1);

        enterButton = new QPushButton(NumPad);
        enterButton->setObjectName(QString::fromUtf8("enterButton"));
        sizePolicy1.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(enterButton, 3, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(NumPad);

        QMetaObject::connectSlotsByName(NumPad);
    } // setupUi

    void retranslateUi(QWidget *NumPad)
    {
        NumPad->setWindowTitle(QApplication::translate("NumPad", "NumPad", nullptr));
        np_pw_indicator_1->setStyleSheet(QApplication::translate("NumPad", "border: 1px solid black;", nullptr));
        np_pw_indicator_1->setText(QString());
        np_pw_indicator_2->setStyleSheet(QApplication::translate("NumPad", "border: 1px solid black;", nullptr));
        np_pw_indicator_2->setText(QString());
        np_pw_indicator_3->setStyleSheet(QApplication::translate("NumPad", "border: 1px solid black;", nullptr));
        np_pw_indicator_3->setText(QString());
        np_pw_indicator_4->setStyleSheet(QApplication::translate("NumPad", "border: 1px solid black;", nullptr));
        np_pw_indicator_4->setText(QString());
        Button1->setText(QApplication::translate("NumPad", "1", nullptr));
        Button2->setText(QApplication::translate("NumPad", "2", nullptr));
        Button3->setText(QApplication::translate("NumPad", "3", nullptr));
        Button4->setText(QApplication::translate("NumPad", "4", nullptr));
        Button5->setText(QApplication::translate("NumPad", "5", nullptr));
        Button6->setText(QApplication::translate("NumPad", "6", nullptr));
        Button7->setText(QApplication::translate("NumPad", "7", nullptr));
        Button8->setText(QApplication::translate("NumPad", "8", nullptr));
        Button9->setText(QApplication::translate("NumPad", "9", nullptr));
        backButton->setText(QApplication::translate("NumPad", "\354\247\200\354\233\200", nullptr));
        Button0->setText(QApplication::translate("NumPad", "0", nullptr));
        enterButton->setText(QApplication::translate("NumPad", "\355\231\225\354\235\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NumPad: public Ui_NumPad {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NUMPAD_H
