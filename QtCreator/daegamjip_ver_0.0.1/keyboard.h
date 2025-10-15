#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class Keyboard; }
QT_END_NAMESPACE

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = nullptr);
    ~Keyboard();
    void setLineEdit(QLineEdit *line);
    Ui::Keyboard *ui; // ui is public

private slots:
    void keyboardHandler();
    void on_shiftButton_toggled(bool checked);
    void on_langButton_toggled(bool checked);
    void on_backButton_clicked();
    void on_spaceButton_clicked();
    void on_enterButton_clicked();

private:
    void updateKeyLabels();
    void initializeMaps();
    void processKorean(const QChar& c);
    void commitComposition();
    QChar compose();

    QLineEdit *m_outputLineEdit;
    bool m_isKorean;
    bool m_isShift;

    // For Hangul composition
    int m_cho, m_jung, m_jong;
    bool m_isComposing;

    QMap<QPushButton*, QString> m_mapEngNormal;
    QMap<QPushButton*, QString> m_mapEngShift;
    QMap<QPushButton*, QString> m_mapKorNormal;
    QMap<QPushButton*, QString> m_mapKorShift;
    bool m_backButtonBlocked;
};

#endif // KEYBOARD_H