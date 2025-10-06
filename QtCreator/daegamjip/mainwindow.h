#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <QTranslator>
#include <QLabel>
#include <QList>
#include <QCamera>
#include <QCameraInfo>
#include <QVideoWidget>
#include <QPushButton>
#include <QTcpSocket>

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

private:
    Ui::MainWindow *ui;

    Keyboard *keyboard;
    NumPad *numpad;
    QMap<QString, QString> countryCodes;
    QTranslator *translator;
    QWidget *m_languageButtonWidget;

    QPushButton *tempPrevButton;
    QPushButton *tempNextButton;
    QPushButton *m_koreanButton; // Added for language button
    QPushButton *m_englishButton; // Added for language button

    QList<QLabel*> m_pwIndicators;
    QList<QLabel*> m_repwIndicators;

    QCamera *m_camera;
    QVideoWidget *m_videoWidget;

    QTimer *m_sequenceTimer;
    MainWindow::CameraSequenceState m_sequenceState;
    int m_stateCountdown;
    QTimer *m_finishPageTimer;
    int m_previousStackIndex;
    QTcpSocket *socket;


private slots:
    void on_startButton_clicked();
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
    void on_englishButton_clicked();
    void changeLanguage(const QString &language);
    void updatePasswordIndicators(int length, const QList<QLabel*>& indicators);
    void onCameraError(QCamera::Error error);
    void goToStartPage();
    void startCamera();
    void stopCamera();
    void onSocketReadyRead();


private:
    void resetCameraPage();
};
#endif // MAINWINDOW_H
