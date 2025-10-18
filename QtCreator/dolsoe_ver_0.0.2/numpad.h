#ifndef NUMPAD_H
#define NUMPAD_H

#include <QDialog>
#include <QLabel>
#include <QList>

namespace Ui {
class NumPad;
}

class NumPad : public QDialog
{
    Q_OBJECT

public:
    explicit NumPad(QWidget *parent = 0);
    ~NumPad();
    void clear();

public slots:
    void acceptAndClose();
    void updateLanguage(const QString &language);

signals:
    void passwordEntered(const QString &password);

private slots:
    void numpadHandler();
    void on_backButton_clicked();
    void on_enterButton_clicked();

private:
    void updatePasswordIndicators(int length);
    Ui::NumPad *ui;
    QList<QLabel*> m_pwIndicators;
    bool m_backButtonBlocked;
    QString m_password;
};

#endif // NUMPAD_H