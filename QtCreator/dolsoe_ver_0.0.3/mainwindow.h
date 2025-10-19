#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QLabel>
#include <QMovie>
#include <QPixmap>
#include "homepage.h" // Include HomePage header
#include "numpad.h" // Include Numpad header

#include "rclcpp/rclcpp.hpp" // ROS2 Node
#include "std_msgs/msg/string.hpp" // ROS2 String message type

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum class NumpadReason {
    None,
    Start,
    Shutdown
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    rclcpp::Node::SharedPtr get_ros_node() const { return m_ros_node; }
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void connectToServer();
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onPasswordEntered(const QString &password);
    void updateTexts();
    void updateImageDisplay();
    void publishMp3Command(int track); // New slot for publishing MP3 commands

    void on_langKrPB_clicked();
    void on_langEnPB_clicked();
    void on_carryPB_clicked();
    void on_naviCB_activated(int index);
    void on_tempPB_clicked();
    void on_endCB_clicked();

private:
    Ui::MainWindow *ui;
    QTcpSocket *m_socket;
    QString m_assignedPassword;
    NumPad *m_numpad;
    NumpadReason m_numpadReason;
    QString m_currentLanguage;

    QLabel *m_imageDisplayLabel;
    QMovie *m_workingMovie;
    QPixmap m_restPixmap;
    bool m_isStopped;
    bool m_isBusy;

    HomePage *m_homePage;

    // ROS2 members
    rclcpp::Node::SharedPtr m_ros_node;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr m_ros_publisher;
};
#endif // MAINWINDOW_H
