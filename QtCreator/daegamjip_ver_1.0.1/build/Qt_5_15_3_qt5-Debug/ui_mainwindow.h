/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
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
    QLabel *backgroundLabel;
    QLabel *titleLabel;
    QLabel *dolsoeLabel;
    QPushButton *wakeUpButton;
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
    QLabel *carryingLabel;
    QPushButton *pushButton_3;
    QWidget *finishPage;
    QLabel *goodbyeLabel;
    QPushButton *pushButton_2;
    QLabel *finishLabel;
    QWidget *noRobotPage;
    QVBoxLayout *verticalLayout_3;
    QLabel *namuLabel;
    QLabel *label_7;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1080, 1920);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_4 = new QVBoxLayout(centralwidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        stack = new QStackedWidget(centralwidget);
        stack->setObjectName(QString::fromUtf8("stack"));
        startPage = new QWidget();
        startPage->setObjectName(QString::fromUtf8("startPage"));
        backgroundLabel = new QLabel(startPage);
        backgroundLabel->setObjectName(QString::fromUtf8("backgroundLabel"));
        backgroundLabel->setGeometry(QRect(0, 0, 1080, 1920));
        backgroundLabel->setScaledContents(true);
        titleLabel = new QLabel(startPage);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 0, 1080, 1920));
        titleLabel->setScaledContents(false);
        dolsoeLabel = new QLabel(startPage);
        dolsoeLabel->setObjectName(QString::fromUtf8("dolsoeLabel"));
        dolsoeLabel->setGeometry(QRect(0, 0, 1080, 1920));
        dolsoeLabel->setScaledContents(false);
        wakeUpButton = new QPushButton(startPage);
        wakeUpButton->setObjectName(QString::fromUtf8("wakeUpButton"));
        wakeUpButton->setGeometry(QRect(440, 1270, 200, 50));
        stack->addWidget(startPage);
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        horizontalLayoutWidget = new QWidget(inputPage);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(180, 110, 401, 100));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(horizontalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(horizontalLayoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(horizontalLayoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        nameLE = new QLineEdit(horizontalLayoutWidget);
        nameLE->setObjectName(QString::fromUtf8("nameLE"));

        verticalLayout->addWidget(nameLE);

        countryCB = new QComboBox(horizontalLayoutWidget);
        countryCB->setObjectName(QString::fromUtf8("countryCB"));
        countryCB->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

        verticalLayout->addWidget(countryCB);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        countrynumLE = new QLineEdit(horizontalLayoutWidget);
        countrynumLE->setObjectName(QString::fromUtf8("countrynumLE"));
        countrynumLE->setReadOnly(true);

        horizontalLayout_3->addWidget(countrynumLE);

        numberLE = new QLineEdit(horizontalLayoutWidget);
        numberLE->setObjectName(QString::fromUtf8("numberLE"));

        horizontalLayout_3->addWidget(numberLE);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 7);

        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 7);
        back = new QPushButton(inputPage);
        back->setObjectName(QString::fromUtf8("back"));
        back->setGeometry(QRect(60, 430, 91, 25));
        next = new QPushButton(inputPage);
        next->setObjectName(QString::fromUtf8("next"));
        next->setEnabled(false);
        next->setGeometry(QRect(630, 430, 95, 25));
        horizontalLayoutWidget_2 = new QWidget(inputPage);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(180, 240, 401, 83));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_4 = new QLabel(horizontalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_5->addWidget(label_4);

        label_5 = new QLabel(horizontalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        label_6 = new QLabel(horizontalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_5->addWidget(label_6);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pwLE = new QLineEdit(horizontalLayoutWidget_2);
        pwLE->setObjectName(QString::fromUtf8("pwLE"));
        pwLE->setMaxLength(4);
        pwLE->setEchoMode(QLineEdit::EchoMode::Normal);

        verticalLayout_6->addWidget(pwLE);

        repwLE = new QLineEdit(horizontalLayoutWidget_2);
        repwLE->setObjectName(QString::fromUtf8("repwLE"));
        repwLE->setMaxLength(4);
        repwLE->setEchoMode(QLineEdit::EchoMode::Normal);

        verticalLayout_6->addWidget(repwLE);

        pwokLabel = new QLabel(horizontalLayoutWidget_2);
        pwokLabel->setObjectName(QString::fromUtf8("pwokLabel"));

        verticalLayout_6->addWidget(pwokLabel);


        horizontalLayout->addLayout(verticalLayout_6);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 7);
        privacyCheckBox = new QCheckBox(inputPage);
        privacyCheckBox->setObjectName(QString::fromUtf8("privacyCheckBox"));
        privacyCheckBox->setGeometry(QRect(270, 430, 231, 22));
        stack->addWidget(inputPage);
        cameraPage = new QWidget();
        cameraPage->setObjectName(QString::fromUtf8("cameraPage"));
        cameraLabel = new QLabel(cameraPage);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setGeometry(QRect(60, 20, 631, 411));
        QFont font;
        font.setPointSize(20);
        cameraLabel->setFont(font);
        pushButton = new QPushButton(cameraPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 490, 95, 25));
        stack->addWidget(cameraPage);
        letsgoPage = new QWidget();
        letsgoPage->setObjectName(QString::fromUtf8("letsgoPage"));
        carryingLabel = new QLabel(letsgoPage);
        carryingLabel->setObjectName(QString::fromUtf8("carryingLabel"));
        carryingLabel->setGeometry(QRect(240, 400, 600, 400));
        carryingLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/carrying.jpg")));
        carryingLabel->setScaledContents(true);
        pushButton_3 = new QPushButton(letsgoPage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(440, 820, 200, 50));
        stack->addWidget(letsgoPage);
        finishPage = new QWidget();
        finishPage->setObjectName(QString::fromUtf8("finishPage"));
        goodbyeLabel = new QLabel(finishPage);
        goodbyeLabel->setObjectName(QString::fromUtf8("goodbyeLabel"));
        goodbyeLabel->setGeometry(QRect(0, 0, 1080, 1920));
        goodbyeLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/goodbye.png")));
        goodbyeLabel->setScaledContents(true);
        pushButton_2 = new QPushButton(finishPage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(430, 1330, 200, 50));
        finishLabel = new QLabel(finishPage);
        finishLabel->setObjectName(QString::fromUtf8("finishLabel"));
        finishLabel->setGeometry(QRect(430, 1430, 200, 50));
        stack->addWidget(finishPage);
        noRobotPage = new QWidget();
        noRobotPage->setObjectName(QString::fromUtf8("noRobotPage"));
        verticalLayout_3 = new QVBoxLayout(noRobotPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        namuLabel = new QLabel(noRobotPage);
        namuLabel->setObjectName(QString::fromUtf8("namuLabel"));
        namuLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/namu.gif")));

        verticalLayout_3->addWidget(namuLabel);

        label_7 = new QLabel(noRobotPage);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QFont font1;
        font1.setPointSize(24);
        label_7->setFont(font1);

        verticalLayout_3->addWidget(label_7);

        stack->addWidget(noRobotPage);

        verticalLayout_4->addWidget(stack);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1080, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stack->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        backgroundLabel->setText(QString());
        titleLabel->setText(QString());
        dolsoeLabel->setText(QString());
        wakeUpButton->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240 \352\271\250\354\232\260\352\270\260", nullptr));
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
        carryingLabel->setText(QString());
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240\354\225\274 \352\260\200\354\236\220", nullptr));
        goodbyeLabel->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\354\264\210\352\270\260 \355\231\224\353\251\264", nullptr));
        finishLabel->setText(QCoreApplication::translate("MainWindow", "\354\246\220\352\261\260\354\232\264 \354\227\254\355\226\211 \353\220\230\354\204\270\354\232\224!", nullptr));
        namuLabel->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "\355\230\204\354\236\254 \354\202\254\354\232\251 \352\260\200\353\212\245\355\225\234 \353\241\234\353\264\207\354\235\264 \354\227\206\354\212\265\353\213\210\353\213\244.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
