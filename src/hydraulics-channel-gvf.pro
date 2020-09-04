#-------------------------------------------------
# HAF 29-4-2020/17-7-2020
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
VERSION = 1.9.0  #30-8-2020
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

QMAKE_CXXFLAGS += -std=c++17

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = hydraulics-channel-gvf
TEMPLATE = app

SOURCES += main.cpp\
        hydraulics-channel-gvf.cpp \
    qcustomplot/qcustomplot.cpp

HEADERS  += hydraulics-channel-gvf.h \
    qcustomplot/qcustomplot.h

FORMS    += hydraulics-channel-gvf.ui

RESOURCES += \
    qtresource.qrc

win32:RC_ICONS += icons\hydraulics-channel-gvf.ico

