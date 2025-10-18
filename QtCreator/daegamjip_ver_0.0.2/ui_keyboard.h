/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keyboard
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *row1;
    QPushButton *Buttonq;
    QPushButton *Buttonw;
    QPushButton *Buttone;
    QPushButton *Buttonr;
    QPushButton *Buttont;
    QPushButton *Buttony;
    QPushButton *Buttonu;
    QPushButton *Buttoni;
    QPushButton *Buttono;
    QPushButton *Buttonp;
    QHBoxLayout *row2;
    QSpacerItem *horizontalSpacer;
    QPushButton *Buttona;
    QPushButton *Buttons;
    QPushButton *Buttond;
    QPushButton *Buttonf;
    QPushButton *Buttong;
    QPushButton *Buttonh;
    QPushButton *Buttonj;
    QPushButton *Buttonk;
    QPushButton *Buttonl;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *row3;
    QPushButton *shiftButton;
    QPushButton *Buttonz;
    QPushButton *Buttonx;
    QPushButton *Buttonc;
    QPushButton *Buttonv;
    QPushButton *Buttonb;
    QPushButton *Buttonn;
    QPushButton *Buttonm;
    QPushButton *backButton;
    QHBoxLayout *row4;
    QPushButton *langButton;
    QPushButton *spaceButton;
    QPushButton *enterButton;

    void setupUi(QWidget *Keyboard)
    {
        if (Keyboard->objectName().isEmpty())
            Keyboard->setObjectName(QString::fromUtf8("Keyboard"));
        Keyboard->resize(874, 300);
        verticalLayout = new QVBoxLayout(Keyboard);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lineEdit = new QLineEdit(Keyboard);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        row1 = new QHBoxLayout();
        row1->setObjectName(QString::fromUtf8("row1"));
        Buttonq = new QPushButton(Keyboard);
        Buttonq->setObjectName(QString::fromUtf8("Buttonq"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Buttonq->sizePolicy().hasHeightForWidth());
        Buttonq->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonq);

        Buttonw = new QPushButton(Keyboard);
        Buttonw->setObjectName(QString::fromUtf8("Buttonw"));
        sizePolicy.setHeightForWidth(Buttonw->sizePolicy().hasHeightForWidth());
        Buttonw->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonw);

        Buttone = new QPushButton(Keyboard);
        Buttone->setObjectName(QString::fromUtf8("Buttone"));
        sizePolicy.setHeightForWidth(Buttone->sizePolicy().hasHeightForWidth());
        Buttone->setSizePolicy(sizePolicy);

        row1->addWidget(Buttone);

        Buttonr = new QPushButton(Keyboard);
        Buttonr->setObjectName(QString::fromUtf8("Buttonr"));
        sizePolicy.setHeightForWidth(Buttonr->sizePolicy().hasHeightForWidth());
        Buttonr->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonr);

        Buttont = new QPushButton(Keyboard);
        Buttont->setObjectName(QString::fromUtf8("Buttont"));
        sizePolicy.setHeightForWidth(Buttont->sizePolicy().hasHeightForWidth());
        Buttont->setSizePolicy(sizePolicy);

        row1->addWidget(Buttont);

        Buttony = new QPushButton(Keyboard);
        Buttony->setObjectName(QString::fromUtf8("Buttony"));
        sizePolicy.setHeightForWidth(Buttony->sizePolicy().hasHeightForWidth());
        Buttony->setSizePolicy(sizePolicy);

        row1->addWidget(Buttony);

        Buttonu = new QPushButton(Keyboard);
        Buttonu->setObjectName(QString::fromUtf8("Buttonu"));
        sizePolicy.setHeightForWidth(Buttonu->sizePolicy().hasHeightForWidth());
        Buttonu->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonu);

        Buttoni = new QPushButton(Keyboard);
        Buttoni->setObjectName(QString::fromUtf8("Buttoni"));
        sizePolicy.setHeightForWidth(Buttoni->sizePolicy().hasHeightForWidth());
        Buttoni->setSizePolicy(sizePolicy);

        row1->addWidget(Buttoni);

        Buttono = new QPushButton(Keyboard);
        Buttono->setObjectName(QString::fromUtf8("Buttono"));
        sizePolicy.setHeightForWidth(Buttono->sizePolicy().hasHeightForWidth());
        Buttono->setSizePolicy(sizePolicy);

        row1->addWidget(Buttono);

        Buttonp = new QPushButton(Keyboard);
        Buttonp->setObjectName(QString::fromUtf8("Buttonp"));
        sizePolicy.setHeightForWidth(Buttonp->sizePolicy().hasHeightForWidth());
        Buttonp->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonp);


        verticalLayout->addLayout(row1);

        row2 = new QHBoxLayout();
        row2->setObjectName(QString::fromUtf8("row2"));
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Minimum);

        row2->addItem(horizontalSpacer);

        Buttona = new QPushButton(Keyboard);
        Buttona->setObjectName(QString::fromUtf8("Buttona"));
        sizePolicy.setHeightForWidth(Buttona->sizePolicy().hasHeightForWidth());
        Buttona->setSizePolicy(sizePolicy);

        row2->addWidget(Buttona);

        Buttons = new QPushButton(Keyboard);
        Buttons->setObjectName(QString::fromUtf8("Buttons"));
        sizePolicy.setHeightForWidth(Buttons->sizePolicy().hasHeightForWidth());
        Buttons->setSizePolicy(sizePolicy);

        row2->addWidget(Buttons);

        Buttond = new QPushButton(Keyboard);
        Buttond->setObjectName(QString::fromUtf8("Buttond"));
        sizePolicy.setHeightForWidth(Buttond->sizePolicy().hasHeightForWidth());
        Buttond->setSizePolicy(sizePolicy);

        row2->addWidget(Buttond);

        Buttonf = new QPushButton(Keyboard);
        Buttonf->setObjectName(QString::fromUtf8("Buttonf"));
        sizePolicy.setHeightForWidth(Buttonf->sizePolicy().hasHeightForWidth());
        Buttonf->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonf);

        Buttong = new QPushButton(Keyboard);
        Buttong->setObjectName(QString::fromUtf8("Buttong"));
        sizePolicy.setHeightForWidth(Buttong->sizePolicy().hasHeightForWidth());
        Buttong->setSizePolicy(sizePolicy);

        row2->addWidget(Buttong);

        Buttonh = new QPushButton(Keyboard);
        Buttonh->setObjectName(QString::fromUtf8("Buttonh"));
        sizePolicy.setHeightForWidth(Buttonh->sizePolicy().hasHeightForWidth());
        Buttonh->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonh);

        Buttonj = new QPushButton(Keyboard);
        Buttonj->setObjectName(QString::fromUtf8("Buttonj"));
        sizePolicy.setHeightForWidth(Buttonj->sizePolicy().hasHeightForWidth());
        Buttonj->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonj);

        Buttonk = new QPushButton(Keyboard);
        Buttonk->setObjectName(QString::fromUtf8("Buttonk"));
        sizePolicy.setHeightForWidth(Buttonk->sizePolicy().hasHeightForWidth());
        Buttonk->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonk);

        Buttonl = new QPushButton(Keyboard);
        Buttonl->setObjectName(QString::fromUtf8("Buttonl"));
        sizePolicy.setHeightForWidth(Buttonl->sizePolicy().hasHeightForWidth());
        Buttonl->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonl);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Minimum);

        row2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(row2);

        row3 = new QHBoxLayout();
        row3->setObjectName(QString::fromUtf8("row3"));
        shiftButton = new QPushButton(Keyboard);
        shiftButton->setObjectName(QString::fromUtf8("shiftButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(shiftButton->sizePolicy().hasHeightForWidth());
        shiftButton->setSizePolicy(sizePolicy1);
        shiftButton->setCheckable(true);

        row3->addWidget(shiftButton);

        Buttonz = new QPushButton(Keyboard);
        Buttonz->setObjectName(QString::fromUtf8("Buttonz"));
        sizePolicy.setHeightForWidth(Buttonz->sizePolicy().hasHeightForWidth());
        Buttonz->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonz);

        Buttonx = new QPushButton(Keyboard);
        Buttonx->setObjectName(QString::fromUtf8("Buttonx"));
        sizePolicy.setHeightForWidth(Buttonx->sizePolicy().hasHeightForWidth());
        Buttonx->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonx);

        Buttonc = new QPushButton(Keyboard);
        Buttonc->setObjectName(QString::fromUtf8("Buttonc"));
        sizePolicy.setHeightForWidth(Buttonc->sizePolicy().hasHeightForWidth());
        Buttonc->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonc);

        Buttonv = new QPushButton(Keyboard);
        Buttonv->setObjectName(QString::fromUtf8("Buttonv"));
        sizePolicy.setHeightForWidth(Buttonv->sizePolicy().hasHeightForWidth());
        Buttonv->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonv);

        Buttonb = new QPushButton(Keyboard);
        Buttonb->setObjectName(QString::fromUtf8("Buttonb"));
        sizePolicy.setHeightForWidth(Buttonb->sizePolicy().hasHeightForWidth());
        Buttonb->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonb);

        Buttonn = new QPushButton(Keyboard);
        Buttonn->setObjectName(QString::fromUtf8("Buttonn"));
        sizePolicy.setHeightForWidth(Buttonn->sizePolicy().hasHeightForWidth());
        Buttonn->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonn);

        Buttonm = new QPushButton(Keyboard);
        Buttonm->setObjectName(QString::fromUtf8("Buttonm"));
        sizePolicy.setHeightForWidth(Buttonm->sizePolicy().hasHeightForWidth());
        Buttonm->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonm);

        backButton = new QPushButton(Keyboard);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        sizePolicy1.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy1);

        row3->addWidget(backButton);


        verticalLayout->addLayout(row3);

        row4 = new QHBoxLayout();
        row4->setObjectName(QString::fromUtf8("row4"));
        langButton = new QPushButton(Keyboard);
        langButton->setObjectName(QString::fromUtf8("langButton"));
        sizePolicy1.setHeightForWidth(langButton->sizePolicy().hasHeightForWidth());
        langButton->setSizePolicy(sizePolicy1);
        langButton->setCheckable(true);

        row4->addWidget(langButton);

        spaceButton = new QPushButton(Keyboard);
        spaceButton->setObjectName(QString::fromUtf8("spaceButton"));
        sizePolicy.setHeightForWidth(spaceButton->sizePolicy().hasHeightForWidth());
        spaceButton->setSizePolicy(sizePolicy);

        row4->addWidget(spaceButton);

        enterButton = new QPushButton(Keyboard);
        enterButton->setObjectName(QString::fromUtf8("enterButton"));
        sizePolicy1.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy1);

        row4->addWidget(enterButton);


        verticalLayout->addLayout(row4);


        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        Keyboard->setWindowTitle(QApplication::translate("Keyboard", "Keyboard", nullptr));
        Buttonq->setText(QApplication::translate("Keyboard", "q", nullptr));
        Buttonw->setText(QApplication::translate("Keyboard", "w", nullptr));
        Buttone->setText(QApplication::translate("Keyboard", "e", nullptr));
        Buttonr->setText(QApplication::translate("Keyboard", "r", nullptr));
        Buttont->setText(QApplication::translate("Keyboard", "t", nullptr));
        Buttony->setText(QApplication::translate("Keyboard", "y", nullptr));
        Buttonu->setText(QApplication::translate("Keyboard", "u", nullptr));
        Buttoni->setText(QApplication::translate("Keyboard", "i", nullptr));
        Buttono->setText(QApplication::translate("Keyboard", "o", nullptr));
        Buttonp->setText(QApplication::translate("Keyboard", "p", nullptr));
        Buttona->setText(QApplication::translate("Keyboard", "a", nullptr));
        Buttons->setText(QApplication::translate("Keyboard", "s", nullptr));
        Buttond->setText(QApplication::translate("Keyboard", "d", nullptr));
        Buttonf->setText(QApplication::translate("Keyboard", "f", nullptr));
        Buttong->setText(QApplication::translate("Keyboard", "g", nullptr));
        Buttonh->setText(QApplication::translate("Keyboard", "h", nullptr));
        Buttonj->setText(QApplication::translate("Keyboard", "j", nullptr));
        Buttonk->setText(QApplication::translate("Keyboard", "k", nullptr));
        Buttonl->setText(QApplication::translate("Keyboard", "l", nullptr));
        shiftButton->setText(QApplication::translate("Keyboard", "Shift", nullptr));
        Buttonz->setText(QApplication::translate("Keyboard", "z", nullptr));
        Buttonx->setText(QApplication::translate("Keyboard", "x", nullptr));
        Buttonc->setText(QApplication::translate("Keyboard", "c", nullptr));
        Buttonv->setText(QApplication::translate("Keyboard", "v", nullptr));
        Buttonb->setText(QApplication::translate("Keyboard", "b", nullptr));
        Buttonn->setText(QApplication::translate("Keyboard", "n", nullptr));
        Buttonm->setText(QApplication::translate("Keyboard", "m", nullptr));
        backButton->setText(QApplication::translate("Keyboard", "\354\247\200\354\233\200", nullptr));
        langButton->setText(QApplication::translate("Keyboard", "\355\225\234/\354\230\201", nullptr));
        spaceButton->setText(QApplication::translate("Keyboard", "Space", nullptr));
        enterButton->setText(QApplication::translate("Keyboard", "\355\231\225\354\235\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
