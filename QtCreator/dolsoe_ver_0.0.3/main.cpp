#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include "rclcpp/rclcpp.hpp"
#include <QTimer>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QApplication a(argc, argv);

    QTranslator translator;
    // To switch to English, change "dolsoe_ko" to "dolsoe_en"
    if (translator.load("dolsoe_en", ":/")) {
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        rclcpp::spin_some(w.get_ros_node());
    });
    timer.start(100); // Spin every 100ms

    return a.exec();
}
