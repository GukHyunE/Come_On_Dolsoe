#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QMetaType>
#include <opencv2/core/mat.hpp>

int main(int argc, char *argv[])
{
    qRegisterMetaType<cv::Mat>("cv::Mat");
    QApplication a(argc, argv);

    QTranslator translator;
    if (translator.load("daegamjip_ko", ":/")) {
        a.installTranslator(&translator);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
