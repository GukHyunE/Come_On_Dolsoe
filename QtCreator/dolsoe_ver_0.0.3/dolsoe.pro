QT       += core gui network network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    numpad.cpp \
    homepage.cpp

HEADERS += \
    mainwindow.h \
    numpad.h \
    homepage.h

FORMS += \
    mainwindow.ui \
    numpad.ui

RESOURCES += \
    translations.qrc \
    image.qrc

TRANSLATIONS += \
    dolsoe_ko.ts \
    dolsoe_en.ts

QMAKE_DIR_IMAGE = ../image

# ROS2 Integration
# Replace <ROS2_DISTRO> with your ROS2 distribution (e.g., foxy, humble)
# Replace <ROS2_INSTALL_PATH> if it's not /opt/ros/<ROS2_DISTRO>
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
LIBS += -L$${ROS2_INSTALL_PATH}/lib -lrclcpp -lrcl -ltracetools -lrmw -lrcutils -lstd_msgs__rosidl_typesupport_cpp

# If you have custom ROS2 messages, you might need to add their include paths
# INCLUDEPATH += /path/to/your/ros2_ws/install/your_package/include

# For C++17 or newer, which ROS2 typically requires
CONFIG += c++17

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
