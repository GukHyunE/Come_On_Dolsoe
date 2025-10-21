#ifndef NUMPAD_H
#define NUMPAD_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

namespace Ui {
class NumPad;
}

class NumPad : public QWidget
{
    Q_OBJECT

public:
    explicit NumPad(QWidget *parent = 0);
    ~NumPad();
    void setLineEdit(QLineEdit *line, bool isPasswordField);
    void setIsPasswordField(bool isPassword);
    Ui::NumPad *ui; // ui is public

private slots:
    void numpadHandler();
    void on_backButton_clicked();
    void on_enterButton_clicked();

private:
    void updatePasswordIndicators(int length);

    QLineEdit *m_outputLineEdit;
    bool m_isPasswordField;
    QList<QLabel*> m_pwIndicators;
    bool m_backButtonBlocked;
};

#endif // NUMPAD_H
