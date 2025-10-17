#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QMovie>
#include <QPixmap>
#include "homepage.h" // Include the new HomePage class

class NumPad; // Forward declaration

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    enum class NumpadReason {
        None,
        Start,
        Shutdown
    };

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_carryPB_clicked();
    void on_naviCB_activated(int index);
    void on_tempPB_clicked();
    void on_endCB_clicked();
    void onPasswordEntered(const QString &password);
    void on_langKrPB_clicked();
    void on_langEnPB_clicked();

    // Network slots
    void onConnected();
    void onReadyRead();
    void onDisconnected();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    void updateTexts();
    void connectToServer();
    void updateImageDisplay();
    Ui::MainWindow *ui;
    NumPad *m_numpad;
    NumpadReason m_numpadReason;
    QString m_currentLanguage;
    bool m_isStopped;

    // Network members
    QTcpSocket *m_socket;
    QString m_assignedPassword;

    // Image/GIF display members
    QLabel *m_imageDisplayLabel;
    QMovie *m_workingMovie;
    QPixmap m_restPixmap;
    bool m_isBusy;

    // Hone page members
    HomePage *m_homePage;
};
#endif // MAINWINDOW_H
