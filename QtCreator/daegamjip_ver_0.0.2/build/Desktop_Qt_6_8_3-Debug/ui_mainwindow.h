/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_4;
    QStackedWidget *stack;
    QWidget *startPage;
    QPushButton *startButton;
    QTextEdit *logo;
    QWidget *inputPage;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QVBoxLayout *verticalLayout;
    QLineEdit *nameLE;
    QComboBox *countryCB;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *countrynumLE;
    QLineEdit *numberLE;
    QPushButton *back;
    QPushButton *next;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *pwLE;
    QLineEdit *repwLE;
    QLabel *pwokLabel;
    QCheckBox *privacyCheckBox;
    QWidget *cameraPage;
    QLabel *cameraLabel;
    QPushButton *pushButton;
    QWidget *letsgoPage;
    QPushButton *pushButton_3;
    QWidget *finishPage;
    QLabel *finishLabel;
    QPushButton *pushButton_2;
    QWidget *noRobotPage;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(856, 744);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        stack = new QStackedWidget(centralwidget);
        stack->setObjectName("stack");
        startPage = new QWidget();
        startPage->setObjectName("startPage");
        startButton = new QPushButton(startPage);
        startButton->setObjectName("startButton");
        startButton->setGeometry(QRect(310, 370, 131, 30));
        logo = new QTextEdit(startPage);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(240, 140, 381, 71));
        stack->addWidget(startPage);
        inputPage = new QWidget();
        inputPage->setObjectName("inputPage");
        horizontalLayoutWidget = new QWidget(inputPage);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(180, 110, 401, 100));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        nameLE = new QLineEdit(horizontalLayoutWidget);
        nameLE->setObjectName("nameLE");
        nameLE->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        verticalLayout->addWidget(nameLE);

        countryCB = new QComboBox(horizontalLayoutWidget);
        countryCB->setObjectName("countryCB");
        countryCB->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        verticalLayout->addWidget(countryCB);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        countrynumLE = new QLineEdit(horizontalLayoutWidget);
        countrynumLE->setObjectName("countrynumLE");
        countrynumLE->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        countrynumLE->setReadOnly(true);

        horizontalLayout_3->addWidget(countrynumLE);

        numberLE = new QLineEdit(horizontalLayoutWidget);
        numberLE->setObjectName("numberLE");
        numberLE->setAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);

        horizontalLayout_3->addWidget(numberLE);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 7);

        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 7);
        back = new QPushButton(inputPage);
        back->setObjectName("back");
        back->setGeometry(QRect(60, 430, 91, 25));
        next = new QPushButton(inputPage);
        next->setObjectName("next");
        next->setEnabled(false);
        next->setGeometry(QRect(630, 430, 95, 25));
        horizontalLayoutWidget_2 = new QWidget(inputPage);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(180, 240, 401, 83));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName("verticalLayout_5");
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName("label_4");
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName("label_5");
        label_5->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName("label_6");

        verticalLayout_5->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName("verticalLayout_6");
        pwLE = new QLineEdit(horizontalLayoutWidget_2);
        pwLE->setObjectName("pwLE");
        pwLE->setMaxLength(4);
        pwLE->setEchoMode(QLineEdit::EchoMode::Password);
        pwLE->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(pwLE);

        repwLE = new QLineEdit(horizontalLayoutWidget_2);
        repwLE->setObjectName("repwLE");
        repwLE->setMaxLength(4);
        repwLE->setEchoMode(QLineEdit::EchoMode::Password);
        repwLE->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_6->addWidget(repwLE);

        pwokLabel = new QLabel(horizontalLayoutWidget_2);
        pwokLabel->setObjectName("pwokLabel");

        verticalLayout_6->addWidget(pwokLabel);


        horizontalLayout->addLayout(verticalLayout_6);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 7);
        privacyCheckBox = new QCheckBox(inputPage);
        privacyCheckBox->setObjectName("privacyCheckBox");
        privacyCheckBox->setGeometry(QRect(270, 430, 231, 22));
        stack->addWidget(inputPage);
        cameraPage = new QWidget();
        cameraPage->setObjectName("cameraPage");
        cameraLabel = new QLabel(cameraPage);
        cameraLabel->setObjectName("cameraLabel");
        cameraLabel->setGeometry(QRect(60, 20, 631, 411));
        QFont font;
        font.setPointSize(20);
        cameraLabel->setFont(font);
        cameraLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);
        pushButton = new QPushButton(cameraPage);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(340, 490, 95, 25));
        stack->addWidget(cameraPage);
        letsgoPage = new QWidget();
        letsgoPage->setObjectName("letsgoPage");
        pushButton_3 = new QPushButton(letsgoPage);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(270, 420, 161, 25));
        stack->addWidget(letsgoPage);
        finishPage = new QWidget();
        finishPage->setObjectName("finishPage");
        finishLabel = new QLabel(finishPage);
        finishLabel->setObjectName("finishLabel");
        finishLabel->setGeometry(QRect(280, 150, 251, 41));
        pushButton_2 = new QPushButton(finishPage);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(330, 430, 95, 25));
        stack->addWidget(finishPage);
        noRobotPage = new QWidget();
        noRobotPage->setObjectName("noRobotPage");
        verticalLayout_7 = new QVBoxLayout(noRobotPage);
        verticalLayout_7->setObjectName("verticalLayout_7");
        label_7 = new QLabel(noRobotPage);
        label_7->setObjectName("label_7");
        QFont font1;
        font1.setPointSize(24);
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_7->addWidget(label_7);

        stack->addWidget(noRobotPage);

        verticalLayout_4->addWidget(stack);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 856, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240 \352\271\250\354\232\260\352\270\260", nullptr));
        logo->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:26pt;\">\353\217\214\354\207\240\354\225\274, \354\235\264\353\246\254\354\230\244\353\204\210\353\235\274!</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\354\235\264\353\246\204", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\352\265\255\352\260\200", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\353\262\210\355\230\270", nullptr));
        back->setText(QCoreApplication::translate("MainWindow", "\354\235\264\354\240\204", nullptr));
        next->setText(QCoreApplication::translate("MainWindow", "\353\213\244\354\235\214", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240 \353\271\204\353\260\200\353\262\210\355\230\270", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\353\271\204\353\260\200\353\262\210\355\230\270 \354\236\254\354\236\205\353\240\245", nullptr));
        label_6->setText(QString());
        pwokLabel->setText(QString());
        privacyCheckBox->setText(QCoreApplication::translate("MainWindow", "\352\260\234\354\235\270\354\240\225\353\263\264 \354\262\230\353\246\254\353\260\251\354\271\250\354\227\220 \353\217\231\354\235\230\355\225\251\353\213\210\353\213\244.", nullptr));
        cameraLabel->setText(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\354\264\254\354\230\201 \354\213\234\354\236\221", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240\354\225\274 \352\260\200\354\236\220", nullptr));
        finishLabel->setText(QCoreApplication::translate("MainWindow", "\354\246\220\352\261\260\354\232\264 \354\227\254\355\226\211 \353\220\230\354\204\270\354\232\224!", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\354\264\210\352\270\260 \355\231\224\353\251\264", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\355\230\204\354\236\254 \354\202\254\354\232\251 \352\260\200\353\212\245\355\225\234 \353\241\234\353\264\207\354\235\264 \354\227\206\354\212\265\353\213\210\353\213\244.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
