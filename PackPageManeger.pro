#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T22:16:30
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PackPageManeger
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    controlerclass.cpp \
    settingsclass.cpp \
    FtpDownload.cpp

HEADERS  += dialog.h \
    controlerclass.h \
    settingsclass.h \
    FtpDownload.h

FORMS    += dialog.ui
