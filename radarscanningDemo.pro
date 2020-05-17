QT += core widgets


CONFIG += c++11

TARGET = radarscanningDemo
CONFIG -= console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    RadarScanning.cpp

HEADERS += \
    RadarScanning.h

RESOURCES += \
    res.qrc
