QT       += core gui network network multimedia widgets multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 link_pkgconfig

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# OpenCV settings
QMAKE_CXXFLAGS += $$system(pkg-config --cflags opencv4)
LIBS += $$system(pkg-config --libs opencv4)
LIBS += -lyaml-cpp

# --- GPIO Settings for Raspberry Pi ---
# Force GPIO compilation for Raspberry Pi builds
DEFINES += RPI_BUILD
SOURCES += gpiohandler.cpp
HEADERS += gpiohandler.h
LIBS += -lgpiod
# ------------------------------------

# ROS2 Integration
ROS2_DISTRO = humble # Assuming humble, adjust if needed
ROS2_INSTALL_PATH = /opt/ros/$${ROS2_DISTRO}

INCLUDEPATH += $${ROS2_INSTALL_PATH}/include \
               $${ROS2_INSTALL_PATH}/include/rcl \
               $${ROS2_INSTALL_PATH}/include/rclcpp \
               $${ROS2_INSTALL_PATH}/include/rcutils \
               $${ROS2_INSTALL_PATH}/include/rmw \
               $${ROS2_INSTALL_PATH}/include/rcl_yaml_param_parser \
               $${ROS2_INSTALL_PATH}/include/rosidl_runtime_c \
               $${ROS2_INSTALL_PATH}/include/rosidl_typesupport_interface \
               $${ROS2_INSTALL_PATH}/include/rcpputils \
               $${ROS2_INSTALL_PATH}/include/builtin_interfaces \
               $${ROS2_INSTALL_PATH}/include/rosidl_runtime_cpp \
               $${ROS2_INSTALL_PATH}/include/tracetools \
               $${ROS2_INSTALL_PATH}/include/rcl_interfaces \
               $${ROS2_INSTALL_PATH}/include/libstatistics_collector \
               $${ROS2_INSTALL_PATH}/include/statistics_msgs \
               $${ROS2_INSTALL_PATH}/include/std_msgs
LIBS += -L$${ROS2_INSTALL_PATH}/lib -L/usr/lib/x86_64-linux-gnu/ -lrclcpp -lrcl -lrcutils -lrmw -ltracetools -lstd_msgs__rosidl_typesupport_cpp -lrosidl_typesupport_cpp -lfastrtps -lfastcdr -ltinyxml2 -lyaml-cpp

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