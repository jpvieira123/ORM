#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T13:51:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EasterDate
TEMPLATE = app

INCLUDEPATH += ../../src

QMAKE_LFLAGS += -Wl,-rpath=./ \
    -Wl,-rpath=../../src

SOURCES += main.cpp\
        mainwindow.cpp \
        easter.cpp

HEADERS  += mainwindow.h \
            easter.h

FORMS    += mainwindow.ui

LIBS     += -L../../src \
            -lqtorm

win32:QMAKE_LFLAGS += --enable-auto-import

target.path = $${PREFIX}/bin
INSTALLS += target
