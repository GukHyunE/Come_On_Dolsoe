#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QMetaType>
#include <opencv2/core/mat.hpp>
#include "rclcpp/rclcpp.hpp"
#include <QTimer>

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QApplication a(argc, argv);

    QTranslator translator;
    if (translator.load("daegamjip_ko", ":/")) {
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();

    QTimer timer;
    QObject::connect(&timer, &QTimer::timeout, [&]() {
        rclcpp::spin_some(w.get_node());
    });
    timer.start(100); // Spin every 100ms

    return a.exec();
}
