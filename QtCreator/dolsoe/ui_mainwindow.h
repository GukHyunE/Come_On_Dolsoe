/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *workingPage;
    QLabel *label;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *carryPB;
    QComboBox *naviCB;
    QPushButton *tempPB;
    QPushButton *endCB;
    QLabel *statusLabel;
    QPushButton *langKrPB;
    QPushButton *langEnPB;
    QWidget *gohomePage;
    QLabel *label_2;
    QLabel *label_3;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(50, 30, 601, 501));
        workingPage = new QWidget();
        workingPage->setObjectName(QString::fromUtf8("workingPage"));
        label = new QLabel(workingPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(130, 40, 351, 251));
        horizontalLayoutWidget = new QWidget(workingPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(120, 270, 376, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        carryPB = new QPushButton(horizontalLayoutWidget);
        carryPB->setObjectName(QString::fromUtf8("carryPB"));

        horizontalLayout->addWidget(carryPB);

        naviCB = new QComboBox(horizontalLayoutWidget);
        naviCB->setObjectName(QString::fromUtf8("naviCB"));

        horizontalLayout->addWidget(naviCB);

        tempPB = new QPushButton(horizontalLayoutWidget);
        tempPB->setObjectName(QString::fromUtf8("tempPB"));

        horizontalLayout->addWidget(tempPB);

        endCB = new QPushButton(horizontalLayoutWidget);
        endCB->setObjectName(QString::fromUtf8("endCB"));

        horizontalLayout->addWidget(endCB);

        statusLabel = new QLabel(workingPage);
        statusLabel->setObjectName(QString::fromUtf8("statusLabel"));
        statusLabel->setGeometry(QRect(40, 460, 351, 25));
        langKrPB = new QPushButton(workingPage);
        langKrPB->setObjectName(QString::fromUtf8("langKrPB"));
        langKrPB->setGeometry(QRect(410, 10, 89, 25));
        langEnPB = new QPushButton(workingPage);
        langEnPB->setObjectName(QString::fromUtf8("langEnPB"));
        langEnPB->setGeometry(QRect(510, 10, 89, 25));
        stackedWidget->addWidget(workingPage);
        gohomePage = new QWidget();
        gohomePage->setObjectName(QString::fromUtf8("gohomePage"));
        label_2 = new QLabel(gohomePage);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(170, 140, 301, 101));
        label_3 = new QLabel(gohomePage);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(220, 370, 141, 17));
        stackedWidget->addWidget(gohomePage);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "\353\260\224\355\224\204\354\260\215\353\212\224\353\217\214\354\207\240", nullptr));
        carryPB->setText(QApplication::translate("MainWindow", "\353\224\260\353\235\274\354\230\244\353\204\210\353\235\274", nullptr));
        tempPB->setText(QApplication::translate("MainWindow", "\354\240\225\354\247\200\355\225\230\352\261\260\353\235\274", nullptr));
        endCB->setText(QApplication::translate("MainWindow", "\354\242\205\353\243\214\355\225\230\352\261\260\353\235\274", nullptr));
        statusLabel->setText(QString());
        langKrPB->setText(QApplication::translate("MainWindow", "\355\225\234\352\265\255\354\226\264", nullptr));
        langEnPB->setText(QApplication::translate("MainWindow", "English", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\353\217\214\354\207\240 \354\247\221\352\260\200\353\212\224 \354\202\254\354\247\204", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\353\217\214\354\207\240 \355\207\264\352\267\274\355\225\264\354\234\240~~", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
