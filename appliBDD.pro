#-------------------------------------------------
#
# Project created by QtCreator 2017-02-27T08:51:48
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = appliBDD
TEMPLATE = app


SOURCES += main.cpp\
    dlgConnexion.cpp \
    mainwindow.cpp \
    dialogabout.cpp

HEADERS  += \
    dlgConnexion.h \
    mainwindow.h \
    dialogabout.h

FORMS    += \
    dlgConnexion.ui \
    mainwindow.ui \
    dialogabout.ui


TRANSLATIONS += appliBDD_fr_FR.ts\
            appliBDD_es.ts\
            appliBDD_it.ts

RESOURCES += \
    ressources.qrc

