QT       += core gui network network multimedia widgets multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 link_pkgconfig

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# OpenCV settings
PKGCONFIG += opencv4
LIBS += -ltbb

FORMS    += mainwindow.ui keyboard.ui numpad.ui

RESOURCES += translations.qrc image.qrc

HEADERS += \
    mainwindow.h \
    camerawidget.h \
    keyboard.h \
    numpad.h \
    videoworker.h

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    camerawidget.cpp \
    keyboard.cpp \
    numpad.cpp \
    videoworker.cpp

TRANSLATIONS += \
    daegamjip_ko.ts \
    daegamjip_en.ts

# Default rules for deployment.
qnx: target.path = /tmp/${TARGET}/bin
else: unix:!android: target.path = /opt/${TARGET}/bin
!isEmpty(target.path): INSTALLS += target