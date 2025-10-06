#include "numpad.h"
#include "ui_numpad.h"
#include <QPushButton>
#include <QTimer>

NumPad::NumPad(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NumPad),
    m_backButtonBlocked(false),
    m_password("")
{
    ui->setupUi(this);

    // The internal lineEdit is no longer used for logic, just a UI remnant.
    ui->lineEdit->setVisible(false);

    // Populate indicator list
    m_pwIndicators << ui->np_pw_indicator_1 << ui->np_pw_indicator_2 << ui->np_pw_indicator_3 << ui->np_pw_indicator_4;
    updatePasswordIndicators(0);

    // Connect all number buttons to numpadHandler
    const auto buttons = findChildren<QPushButton*>();
    for (QPushButton *button : buttons) {
        if (button->objectName().startsWith("Button")) {
            connect(button, &QPushButton::clicked, this, &NumPad::numpadHandler);
        }
    }
    connect(ui->backButton, &QPushButton::clicked, this, &NumPad::on_backButton_clicked);
    connect(ui->enterButton, &QPushButton::clicked, this, &NumPad::on_enterButton_clicked);
}

NumPad::~NumPad()
{
    delete ui;
}

void NumPad::clear()
{
    m_password.clear();
    updatePasswordIndicators(0);
}

void NumPad::acceptAndClose()
{
    accept();
}

void NumPad::numpadHandler()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;

    if (m_password.length() < 4) {
        m_password.append(button->text());
        updatePasswordIndicators(m_password.length());
    }
}

void NumPad::on_backButton_clicked()
{
    if (m_backButtonBlocked) return;
    m_backButtonBlocked = true;

    m_password.chop(1);
    updatePasswordIndicators(m_password.length());

    QTimer::singleShot(100, this, [this]() { m_backButtonBlocked = false; });
}

void NumPad::on_enterButton_clicked()
{
    emit passwordEntered(m_password);
}

void NumPad::updatePasswordIndicators(int length)
{
    for (int i = 0; i < m_pwIndicators.size(); ++i) {
        if (i < length) {
            m_pwIndicators[i]->setText("*");
            m_pwIndicators[i]->setStyleSheet("font-size: 18px; font-weight: bold; border: 1px solid black;");
        } else {
            m_pwIndicators[i]->setText("");
            m_pwIndicators[i]->setStyleSheet("border: 1px solid black;");
        }
    }
}
