#-------------------------------------------------
#
# Project created by QtCreator 2019-10-20T15:08:23
#
#-------------------------------------------------

QT       += core gui
QT       += core gui bluetooth
QT       += androidextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = one_smart_control_mobile
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        bluetooth/characteristicinfo.cpp \
        bluetooth/device.cpp \
        bluetooth/deviceinfo.cpp \
        bluetooth/serviceinfo.cpp \
        connectwidget.cpp \
        easyprotocol.cpp \
        flowchartwidget.cpp \
        gripperwidget.cpp \
        lightwidget.cpp \
        main.cpp \
        sliderwidget.cpp \
        smartcontroldata.cpp \
        smartcontrolmainwindow.cpp \
        timewidget.cpp \
        workingspace.cpp

HEADERS += \
        bluetooth/characteristicinfo.h \
        bluetooth/device.h \
        bluetooth/deviceinfo.h \
        bluetooth/serviceinfo.h \
        config.h \
        connectwidget.h \
        easyprotocol.h \
        flowchartwidget.h \
        gripperwidget.h \
        lightwidget.h \
        sliderwidget.h \
        smartcontroldata.h \
        smartcontrolmainwindow.h \
        timewidget.h \
        workingspace.h

FORMS += \
    smartcontrolmainwindow.ui

CONFIG += mobility
MOBILITY = 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,x86) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}

contains(ANDROID_TARGET_ARCH,x86_64) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
