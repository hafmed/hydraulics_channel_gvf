#-------------------------------------------------
# HAF 29-4-2020/5-9-2020
# on Qt 5.9.5 GCC 7.3.0; 64 bit Qt Creator 4.5.2 Ubuntu 18.4
# sudo apt install g++
# sudo apt install cmake
# sudo apt-get install libgl-dev
# sudo apt-get install qt5-default
# sudo apt install qtcreator
#------------Make *.AppImage----------------------
# in the directorie : compilation
#  Vider le repertoire compilation sauf *.desctop icon et linuxdeployqt-6-x86_64.AppImage
# chmod a+x linuxdeployqt-6-x86_64.AppImage
# ./linuxdeployqt-6-x86_64.AppImage hydraulics-channel-gvf -appimage -qmake=/home/hafmed/Qt5.12.8/5.12.8/gcc_64/bin/qmake
#-------------------------------------------------

QT       += core gui
CONFIG += c++17
VERSION = 4.2.10  #21-9-2020 -25-7-2021 -9-8-2021 -25-7-2022
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QMAKE_CXXFLAGS += -std=c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

android:DISTFILES += \
android-sources/AndroidManifest.xml \
android-sources/build.gradle

ANDROID_VERSION_CODE = 0644210

android:ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android-sources

TARGET = hydraulics-channel-gvf
TEMPLATE = app

SOURCES += main.cpp\
        hydraulics-channel-gvf.cpp \
        qcustomplot/qcustomplot.cpp

HEADERS  += hydraulics-channel-gvf.h \
        constants \
        qcustomplot/qcustomplot.h

FORMS    += hydraulics-channel-gvf.ui

TRANSLATIONS = translations/qt_en.ts

RESOURCES += \
    qtresource.qrc \
    translations.qrc

win32:RC_ICONS += icons\hydraulics-channel-gvf.ico

DISTFILES += \
    android-sources/AndroidManifest.xml \
    android-sources/build.gradle \
    android-sources/res/drawable-hdpi/icon.png \
    android-sources/res/drawable-ldpi/icon.png \
    android-sources/res/drawable-mdpi/icon.png \
    android-sources/res/drawable-xhdpi/icon.png \
    android-sources/res/drawable-xxhdpi/icon.png \
    android-sources/res/drawable-xxxhdpi/icon.png
