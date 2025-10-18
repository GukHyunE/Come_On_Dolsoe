/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created by: Qt User Interface Compiler version 6.8.3
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
            Keyboard->setObjectName("Keyboard");
        Keyboard->resize(874, 300);
        verticalLayout = new QVBoxLayout(Keyboard);
        verticalLayout->setObjectName("verticalLayout");
        lineEdit = new QLineEdit(Keyboard);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        row1 = new QHBoxLayout();
        row1->setObjectName("row1");
        Buttonq = new QPushButton(Keyboard);
        Buttonq->setObjectName("Buttonq");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Buttonq->sizePolicy().hasHeightForWidth());
        Buttonq->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonq);

        Buttonw = new QPushButton(Keyboard);
        Buttonw->setObjectName("Buttonw");
        sizePolicy.setHeightForWidth(Buttonw->sizePolicy().hasHeightForWidth());
        Buttonw->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonw);

        Buttone = new QPushButton(Keyboard);
        Buttone->setObjectName("Buttone");
        sizePolicy.setHeightForWidth(Buttone->sizePolicy().hasHeightForWidth());
        Buttone->setSizePolicy(sizePolicy);

        row1->addWidget(Buttone);

        Buttonr = new QPushButton(Keyboard);
        Buttonr->setObjectName("Buttonr");
        sizePolicy.setHeightForWidth(Buttonr->sizePolicy().hasHeightForWidth());
        Buttonr->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonr);

        Buttont = new QPushButton(Keyboard);
        Buttont->setObjectName("Buttont");
        sizePolicy.setHeightForWidth(Buttont->sizePolicy().hasHeightForWidth());
        Buttont->setSizePolicy(sizePolicy);

        row1->addWidget(Buttont);

        Buttony = new QPushButton(Keyboard);
        Buttony->setObjectName("Buttony");
        sizePolicy.setHeightForWidth(Buttony->sizePolicy().hasHeightForWidth());
        Buttony->setSizePolicy(sizePolicy);

        row1->addWidget(Buttony);

        Buttonu = new QPushButton(Keyboard);
        Buttonu->setObjectName("Buttonu");
        sizePolicy.setHeightForWidth(Buttonu->sizePolicy().hasHeightForWidth());
        Buttonu->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonu);

        Buttoni = new QPushButton(Keyboard);
        Buttoni->setObjectName("Buttoni");
        sizePolicy.setHeightForWidth(Buttoni->sizePolicy().hasHeightForWidth());
        Buttoni->setSizePolicy(sizePolicy);

        row1->addWidget(Buttoni);

        Buttono = new QPushButton(Keyboard);
        Buttono->setObjectName("Buttono");
        sizePolicy.setHeightForWidth(Buttono->sizePolicy().hasHeightForWidth());
        Buttono->setSizePolicy(sizePolicy);

        row1->addWidget(Buttono);

        Buttonp = new QPushButton(Keyboard);
        Buttonp->setObjectName("Buttonp");
        sizePolicy.setHeightForWidth(Buttonp->sizePolicy().hasHeightForWidth());
        Buttonp->setSizePolicy(sizePolicy);

        row1->addWidget(Buttonp);


        verticalLayout->addLayout(row1);

        row2 = new QHBoxLayout();
        row2->setObjectName("row2");
        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        row2->addItem(horizontalSpacer);

        Buttona = new QPushButton(Keyboard);
        Buttona->setObjectName("Buttona");
        sizePolicy.setHeightForWidth(Buttona->sizePolicy().hasHeightForWidth());
        Buttona->setSizePolicy(sizePolicy);

        row2->addWidget(Buttona);

        Buttons = new QPushButton(Keyboard);
        Buttons->setObjectName("Buttons");
        sizePolicy.setHeightForWidth(Buttons->sizePolicy().hasHeightForWidth());
        Buttons->setSizePolicy(sizePolicy);

        row2->addWidget(Buttons);

        Buttond = new QPushButton(Keyboard);
        Buttond->setObjectName("Buttond");
        sizePolicy.setHeightForWidth(Buttond->sizePolicy().hasHeightForWidth());
        Buttond->setSizePolicy(sizePolicy);

        row2->addWidget(Buttond);

        Buttonf = new QPushButton(Keyboard);
        Buttonf->setObjectName("Buttonf");
        sizePolicy.setHeightForWidth(Buttonf->sizePolicy().hasHeightForWidth());
        Buttonf->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonf);

        Buttong = new QPushButton(Keyboard);
        Buttong->setObjectName("Buttong");
        sizePolicy.setHeightForWidth(Buttong->sizePolicy().hasHeightForWidth());
        Buttong->setSizePolicy(sizePolicy);

        row2->addWidget(Buttong);

        Buttonh = new QPushButton(Keyboard);
        Buttonh->setObjectName("Buttonh");
        sizePolicy.setHeightForWidth(Buttonh->sizePolicy().hasHeightForWidth());
        Buttonh->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonh);

        Buttonj = new QPushButton(Keyboard);
        Buttonj->setObjectName("Buttonj");
        sizePolicy.setHeightForWidth(Buttonj->sizePolicy().hasHeightForWidth());
        Buttonj->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonj);

        Buttonk = new QPushButton(Keyboard);
        Buttonk->setObjectName("Buttonk");
        sizePolicy.setHeightForWidth(Buttonk->sizePolicy().hasHeightForWidth());
        Buttonk->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonk);

        Buttonl = new QPushButton(Keyboard);
        Buttonl->setObjectName("Buttonl");
        sizePolicy.setHeightForWidth(Buttonl->sizePolicy().hasHeightForWidth());
        Buttonl->setSizePolicy(sizePolicy);

        row2->addWidget(Buttonl);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        row2->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(row2);

        row3 = new QHBoxLayout();
        row3->setObjectName("row3");
        shiftButton = new QPushButton(Keyboard);
        shiftButton->setObjectName("shiftButton");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(shiftButton->sizePolicy().hasHeightForWidth());
        shiftButton->setSizePolicy(sizePolicy1);
        shiftButton->setCheckable(true);

        row3->addWidget(shiftButton);

        Buttonz = new QPushButton(Keyboard);
        Buttonz->setObjectName("Buttonz");
        sizePolicy.setHeightForWidth(Buttonz->sizePolicy().hasHeightForWidth());
        Buttonz->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonz);

        Buttonx = new QPushButton(Keyboard);
        Buttonx->setObjectName("Buttonx");
        sizePolicy.setHeightForWidth(Buttonx->sizePolicy().hasHeightForWidth());
        Buttonx->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonx);

        Buttonc = new QPushButton(Keyboard);
        Buttonc->setObjectName("Buttonc");
        sizePolicy.setHeightForWidth(Buttonc->sizePolicy().hasHeightForWidth());
        Buttonc->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonc);

        Buttonv = new QPushButton(Keyboard);
        Buttonv->setObjectName("Buttonv");
        sizePolicy.setHeightForWidth(Buttonv->sizePolicy().hasHeightForWidth());
        Buttonv->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonv);

        Buttonb = new QPushButton(Keyboard);
        Buttonb->setObjectName("Buttonb");
        sizePolicy.setHeightForWidth(Buttonb->sizePolicy().hasHeightForWidth());
        Buttonb->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonb);

        Buttonn = new QPushButton(Keyboard);
        Buttonn->setObjectName("Buttonn");
        sizePolicy.setHeightForWidth(Buttonn->sizePolicy().hasHeightForWidth());
        Buttonn->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonn);

        Buttonm = new QPushButton(Keyboard);
        Buttonm->setObjectName("Buttonm");
        sizePolicy.setHeightForWidth(Buttonm->sizePolicy().hasHeightForWidth());
        Buttonm->setSizePolicy(sizePolicy);

        row3->addWidget(Buttonm);

        backButton = new QPushButton(Keyboard);
        backButton->setObjectName("backButton");
        sizePolicy1.setHeightForWidth(backButton->sizePolicy().hasHeightForWidth());
        backButton->setSizePolicy(sizePolicy1);

        row3->addWidget(backButton);


        verticalLayout->addLayout(row3);

        row4 = new QHBoxLayout();
        row4->setObjectName("row4");
        langButton = new QPushButton(Keyboard);
        langButton->setObjectName("langButton");
        sizePolicy1.setHeightForWidth(langButton->sizePolicy().hasHeightForWidth());
        langButton->setSizePolicy(sizePolicy1);
        langButton->setCheckable(true);

        row4->addWidget(langButton);

        spaceButton = new QPushButton(Keyboard);
        spaceButton->setObjectName("spaceButton");
        sizePolicy.setHeightForWidth(spaceButton->sizePolicy().hasHeightForWidth());
        spaceButton->setSizePolicy(sizePolicy);

        row4->addWidget(spaceButton);

        enterButton = new QPushButton(Keyboard);
        enterButton->setObjectName("enterButton");
        sizePolicy1.setHeightForWidth(enterButton->sizePolicy().hasHeightForWidth());
        enterButton->setSizePolicy(sizePolicy1);

        row4->addWidget(enterButton);


        verticalLayout->addLayout(row4);


        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        Keyboard->setWindowTitle(QCoreApplication::translate("Keyboard", "Keyboard", nullptr));
        Buttonq->setText(QCoreApplication::translate("Keyboard", "q", nullptr));
        Buttonw->setText(QCoreApplication::translate("Keyboard", "w", nullptr));
        Buttone->setText(QCoreApplication::translate("Keyboard", "e", nullptr));
        Buttonr->setText(QCoreApplication::translate("Keyboard", "r", nullptr));
        Buttont->setText(QCoreApplication::translate("Keyboard", "t", nullptr));
        Buttony->setText(QCoreApplication::translate("Keyboard", "y", nullptr));
        Buttonu->setText(QCoreApplication::translate("Keyboard", "u", nullptr));
        Buttoni->setText(QCoreApplication::translate("Keyboard", "i", nullptr));
        Buttono->setText(QCoreApplication::translate("Keyboard", "o", nullptr));
        Buttonp->setText(QCoreApplication::translate("Keyboard", "p", nullptr));
        Buttona->setText(QCoreApplication::translate("Keyboard", "a", nullptr));
        Buttons->setText(QCoreApplication::translate("Keyboard", "s", nullptr));
        Buttond->setText(QCoreApplication::translate("Keyboard", "d", nullptr));
        Buttonf->setText(QCoreApplication::translate("Keyboard", "f", nullptr));
        Buttong->setText(QCoreApplication::translate("Keyboard", "g", nullptr));
        Buttonh->setText(QCoreApplication::translate("Keyboard", "h", nullptr));
        Buttonj->setText(QCoreApplication::translate("Keyboard", "j", nullptr));
        Buttonk->setText(QCoreApplication::translate("Keyboard", "k", nullptr));
        Buttonl->setText(QCoreApplication::translate("Keyboard", "l", nullptr));
        shiftButton->setText(QCoreApplication::translate("Keyboard", "Shift", nullptr));
        Buttonz->setText(QCoreApplication::translate("Keyboard", "z", nullptr));
        Buttonx->setText(QCoreApplication::translate("Keyboard", "x", nullptr));
        Buttonc->setText(QCoreApplication::translate("Keyboard", "c", nullptr));
        Buttonv->setText(QCoreApplication::translate("Keyboard", "v", nullptr));
        Buttonb->setText(QCoreApplication::translate("Keyboard", "b", nullptr));
        Buttonn->setText(QCoreApplication::translate("Keyboard", "n", nullptr));
        Buttonm->setText(QCoreApplication::translate("Keyboard", "m", nullptr));
        backButton->setText(QCoreApplication::translate("Keyboard", "\354\247\200\354\233\200", nullptr));
        langButton->setText(QCoreApplication::translate("Keyboard", "\355\225\234/\354\230\201", nullptr));
        spaceButton->setText(QCoreApplication::translate("Keyboard", "Space", nullptr));
        enterButton->setText(QCoreApplication::translate("Keyboard", "\355\231\225\354\235\270", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
