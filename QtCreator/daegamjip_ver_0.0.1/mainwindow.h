#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTranslator>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QTcpSocket>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QThread>
#include <QTimer>

#include "videoworker.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Keyboard;
class NumPad;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum CameraSequenceState {
        Idle,
        InitialCountdown,
        Shooting,
        Turning,
        Recognizing
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(QObject *obj, QEvent *event);
    void resizeEvent(QResizeEvent* event) override;

private:
    Ui::MainWindow *ui;

    Keyboard *keyboard;
    NumPad *numpad;
    QMap<QString, QString> countryCodes;
    QTranslator *translator;
    QWidget *m_languageButtonWidget;

    QPushButton *tempPrevButton;
    QPushButton *tempNextButton;
    QPushButton *m_koreanButton;

    QList<QLabel*> m_pwIndicators;
    QList<QLabel*> m_repwIndicators;

    // Video members (OpenCV Worker Thread)
    QLabel* m_videoLabel;
    QThread* m_videoThread = nullptr;
    VideoWorker* m_videoWorker = nullptr;

    QTimer *m_sequenceTimer;
    MainWindow::CameraSequenceState m_sequenceState;
    int m_stateCountdown;
    QTimer *m_finishPageTimer;
    int m_previousStackIndex;
    QTcpSocket *socket;

    enum Language { KOREAN, ENGLISH };
    Language m_currentLanguage;
    QPropertyAnimation *m_titleAnimation;
    QGraphicsOpacityEffect *m_titleOpacityEffect;
    bool m_isTempNavigation = false;
    bool m_processFrame = true;

private slots:
    void on_next_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void updateCountdown();
    void on_back_clicked();
    void on_tempPrevButton_clicked();
    void on_tempNextButton_clicked();
    void onStackPageChanged(int index);
    void on_countryCB_currentIndexChanged(int index);
    void handlePasswordChanged();
    void checkFormCompleteness();
    void on_koreanButton_clicked();
    void changeLanguage(const QString &language);
    void updatePasswordIndicators(int length, const QList<QLabel*>& indicators);
    void goToStartPage();
    void onSocketReadyRead();

    void on_wakeUpButton_clicked();
    void startTitleAnimation();
    void showDolsoeAndButton();

    void updateFrame(const cv::Mat &frame);

private:
    void resetCameraPage();
};
#endif // MAINWINDOW_H