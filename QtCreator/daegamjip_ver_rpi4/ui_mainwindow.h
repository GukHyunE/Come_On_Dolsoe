/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
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
#include <QtWidgets/QSpacerItem>
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
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_8;
    QVBoxLayout *verticalLayout_7;
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
    QLabel *label_8;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *pwLE;
    QLineEdit *repwLE;
    QLabel *pwokLabel;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *back;
    QLabel *label_9;
    QCheckBox *privacyCheckBox;
    QLabel *label_10;
    QPushButton *next;
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
    QSpacerItem *verticalSpacer_2;
    QLabel *namuLabel;
    QLabel *label_7;
    QSpacerItem *verticalSpacer;
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
        wakeUpButton->setGeometry(QRect(480, 1150, 81, 31));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(wakeUpButton->sizePolicy().hasHeightForWidth());
        wakeUpButton->setSizePolicy(sizePolicy);
        stack->addWidget(startPage);
        inputPage = new QWidget();
        inputPage->setObjectName(QString::fromUtf8("inputPage"));
        verticalLayoutWidget_2 = new QWidget(inputPage);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(230, 560, 601, 261));
        verticalLayout_8 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(0, 0, 0, 0);
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(verticalLayoutWidget_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        nameLE = new QLineEdit(verticalLayoutWidget_2);
        nameLE->setObjectName(QString::fromUtf8("nameLE"));

        verticalLayout->addWidget(nameLE);

        countryCB = new QComboBox(verticalLayoutWidget_2);
        countryCB->setObjectName(QString::fromUtf8("countryCB"));
        countryCB->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        verticalLayout->addWidget(countryCB);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        countrynumLE = new QLineEdit(verticalLayoutWidget_2);
        countrynumLE->setObjectName(QString::fromUtf8("countrynumLE"));
        countrynumLE->setReadOnly(true);

        horizontalLayout_3->addWidget(countrynumLE);

        numberLE = new QLineEdit(verticalLayoutWidget_2);
        numberLE->setObjectName(QString::fromUtf8("numberLE"));

        horizontalLayout_3->addWidget(numberLE);

        horizontalLayout_3->setStretch(0, 3);
        horizontalLayout_3->setStretch(1, 7);

        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout);

        horizontalLayout_2->setStretch(0, 3);
        horizontalLayout_2->setStretch(1, 7);

        verticalLayout_7->addLayout(horizontalLayout_2);

        label_8 = new QLabel(verticalLayoutWidget_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_7->addWidget(label_8);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_4 = new QLabel(verticalLayoutWidget_2);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_5->addWidget(label_4);

        label_5 = new QLabel(verticalLayoutWidget_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_5->addWidget(label_5);

        label_6 = new QLabel(verticalLayoutWidget_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_5->addWidget(label_6);

        verticalLayout_5->setStretch(0, 4);
        verticalLayout_5->setStretch(1, 4);
        verticalLayout_5->setStretch(2, 1);

        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        pwLE = new QLineEdit(verticalLayoutWidget_2);
        pwLE->setObjectName(QString::fromUtf8("pwLE"));
        pwLE->setMaxLength(4);
        pwLE->setEchoMode(QLineEdit::Normal);

        verticalLayout_6->addWidget(pwLE);

        repwLE = new QLineEdit(verticalLayoutWidget_2);
        repwLE->setObjectName(QString::fromUtf8("repwLE"));
        repwLE->setMaxLength(4);
        repwLE->setEchoMode(QLineEdit::Normal);

        verticalLayout_6->addWidget(repwLE);

        pwokLabel = new QLabel(verticalLayoutWidget_2);
        pwokLabel->setObjectName(QString::fromUtf8("pwokLabel"));

        verticalLayout_6->addWidget(pwokLabel);

        verticalLayout_6->setStretch(0, 4);
        verticalLayout_6->setStretch(1, 4);
        verticalLayout_6->setStretch(2, 1);

        horizontalLayout->addLayout(verticalLayout_6);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 7);

        verticalLayout_7->addLayout(horizontalLayout);

        verticalLayout_7->setStretch(0, 4);
        verticalLayout_7->setStretch(1, 1);

        verticalLayout_8->addLayout(verticalLayout_7);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        back = new QPushButton(verticalLayoutWidget_2);
        back->setObjectName(QString::fromUtf8("back"));

        horizontalLayout_4->addWidget(back);

        label_9 = new QLabel(verticalLayoutWidget_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        privacyCheckBox = new QCheckBox(verticalLayoutWidget_2);
        privacyCheckBox->setObjectName(QString::fromUtf8("privacyCheckBox"));

        horizontalLayout_4->addWidget(privacyCheckBox);

        label_10 = new QLabel(verticalLayoutWidget_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_4->addWidget(label_10);

        next = new QPushButton(verticalLayoutWidget_2);
        next->setObjectName(QString::fromUtf8("next"));
        next->setEnabled(false);

        horizontalLayout_4->addWidget(next);


        verticalLayout_8->addLayout(horizontalLayout_4);

        stack->addWidget(inputPage);
        cameraPage = new QWidget();
        cameraPage->setObjectName(QString::fromUtf8("cameraPage"));
        cameraLabel = new QLabel(cameraPage);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setGeometry(QRect(60, 20, 631, 411));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy1);
        QFont font;
        cameraLabel->setFont(font);
        pushButton = new QPushButton(cameraPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(340, 490, 200, 50));
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
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
        sizePolicy1.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy1);
        finishLabel = new QLabel(finishPage);
        finishLabel->setObjectName(QString::fromUtf8("finishLabel"));
        finishLabel->setGeometry(QRect(340, 1430, 400, 100));
        stack->addWidget(finishPage);
        noRobotPage = new QWidget();
        noRobotPage->setObjectName(QString::fromUtf8("noRobotPage"));
        verticalLayout_3 = new QVBoxLayout(noRobotPage);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        namuLabel = new QLabel(noRobotPage);
        namuLabel->setObjectName(QString::fromUtf8("namuLabel"));
        namuLabel->setPixmap(QPixmap(QString::fromUtf8(":/images/namu.gif")));
        namuLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(namuLabel);

        label_7 = new QLabel(noRobotPage);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_7);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

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
        label_8->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240 \353\271\204\353\260\200\353\262\210\355\230\270", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\353\271\204\353\260\200\353\262\210\355\230\270 \354\236\254\354\236\205\353\240\245", nullptr));
        label_6->setText(QString());
        pwokLabel->setText(QString());
        back->setText(QCoreApplication::translate("MainWindow", "\354\235\264\354\240\204", nullptr));
        label_9->setText(QString());
        privacyCheckBox->setText(QCoreApplication::translate("MainWindow", "\352\260\234\354\235\270\354\240\225\353\263\264 \354\262\230\353\246\254\353\260\251\354\271\250\354\227\220 \353\217\231\354\235\230\355\225\251\353\213\210\353\213\244.", nullptr));
        label_10->setText(QString());
        next->setText(QCoreApplication::translate("MainWindow", "\353\213\244\354\235\214", nullptr));
        cameraLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px;", nullptr));
        cameraLabel->setText(QString());
        pushButton->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px;", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\354\264\254\354\230\201 \354\213\234\354\236\221", nullptr));
        carryingLabel->setText(QString());
        pushButton_3->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px;", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\353\217\214\354\207\240\354\225\274 \352\260\200\354\236\220", nullptr));
        goodbyeLabel->setText(QString());
        pushButton_2->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px;", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\354\264\210\352\270\260 \355\231\224\353\251\264", nullptr));
        finishLabel->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px;", nullptr));
        finishLabel->setText(QCoreApplication::translate("MainWindow", "\354\246\220\352\261\260\354\232\264 \354\227\254\355\226\211 \353\220\230\354\204\270\354\232\224!", nullptr));
        namuLabel->setText(QString());
        label_7->setStyleSheet(QCoreApplication::translate("MainWindow", "font-size: 36px;", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\355\230\204\354\236\254 \354\202\254\354\232\251 \352\260\200\353\212\245\355\225\234 \353\241\234\353\264\207\354\235\264 \354\227\206\354\212\265\353\213\210\353\213\244.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
