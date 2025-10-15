#include "numpad.h"
#include "ui_numpad.h"
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QTimer>

NumPad::NumPad(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NumPad),
    m_outputLineEdit(nullptr),
    m_isPasswordField(false),
    m_backButtonBlocked(false)
{
    ui->setupUi(this);

    // Populate indicator list and set initial state
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

void NumPad::setLineEdit(QLineEdit *line, bool isPasswordField)
{
    m_outputLineEdit = line;
    if (m_outputLineEdit) {
        // Set echo mode and visibility for the Numpad's internal QLineEdit (ui->lineEdit)
        if (isPasswordField) {
            ui->lineEdit->setEchoMode(QLineEdit::Password);
            ui->lineEdit->setVisible(false); // Hide the internal QLineEdit for passwords
        } else {
            ui->lineEdit->setEchoMode(QLineEdit::Normal);
            ui->lineEdit->setVisible(true); // Show the internal QLineEdit for phone numbers
        }

        // Set the Numpad's internal flag and update indicators
        setIsPasswordField(isPasswordField);
        updatePasswordIndicators(m_outputLineEdit->text().length());
        ui->lineEdit->setText(m_outputLineEdit->text()); // Synchronize internal QLineEdit
    }
}

void NumPad::setIsPasswordField(bool isPassword)
{
    m_isPasswordField = isPassword;
    for (QLabel* indicator : m_pwIndicators) {
        indicator->setVisible(isPassword);
    }
}

void NumPad::numpadHandler()
{
    if (!m_outputLineEdit) return;
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    QString digit = button->text();

    m_outputLineEdit->insert(digit);
    ui->lineEdit->setText(m_outputLineEdit->text()); // Re-add this line

    if (m_isPasswordField) {
        updatePasswordIndicators(m_outputLineEdit->text().length());
    }
}

void NumPad::on_backButton_clicked()
{
    if (m_backButtonBlocked) return; // Prevent re-entry

    m_backButtonBlocked = true; // Block further entries

    if (!m_outputLineEdit) {
        // Unblock after a short delay even if m_outputLineEdit is null
        QTimer::singleShot(100, this, [this]() { m_backButtonBlocked = false; });
        return;
    }

    QString currentText = m_outputLineEdit->text();
    if (!currentText.isEmpty()) {
        currentText.chop(1);
        m_outputLineEdit->setText(currentText);
    }
    ui->lineEdit->setText(m_outputLineEdit->text()); // Re-add this line

    if (m_isPasswordField) {
        updatePasswordIndicators(m_outputLineEdit->text().length());
    }

    // Unblock after a short delay
    QTimer::singleShot(100, this, [this]() { m_backButtonBlocked = false; });
}

void NumPad::on_enterButton_clicked()
{
    close();
}

void NumPad::updatePasswordIndicators(int length)
{
    for (int i = 0; i < m_pwIndicators.size(); ++i) {
        if (i < length) {
            m_pwIndicators[i]->setText("*");
        } else {
            m_pwIndicators[i]->setText("");
        }
    }
}