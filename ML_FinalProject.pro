#-------------------------------------------------
#
# Project created by QtCreator 2015-01-01T15:39:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ML_FinalProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    classifier.cpp \
    machine_learning.cpp \
    image_process.cpp

HEADERS  += mainwindow.h \
    classifier.h \
    machine_learning.h \
    image_process.h

INCLUDEPATH += C:\\opencv30b\\x64\\include \
                C:\\opencv30b\\x64\\include\\opencv \
                C:\\opencv30b\\x64\\include\\opencv2
#                C:\\qwt-6.1.1\\src \


LIBS += C:\\opencv30b\\x64\\lib\\opencv_world300.lib \
        C:\\opencv30b\\x64\\lib\\opencv_world300d.lib \
        C:\\opencv30b\\x64\\lib\\opencv_ts300.lib
#        C:\\qwt-6.1.1\\lib\\qwt.lib \

FORMS    += mainwindow.ui
