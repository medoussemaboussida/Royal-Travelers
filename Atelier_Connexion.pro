#-------------------------------------------------
#
# Project created by QtCreator 2018-10-26T21:45:23
#
#-------------------------------------------------

QT       += core gui sql
QT       += core gui
QT       += core gui charts
QT       += svg
QT       += printsupport
QT       += network
QT       +=serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = Atelier_Connexion
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
    arduino.cpp \
    chatboxdialog.cpp \
    client.cpp \
    dialog.cpp \
    employee.cpp \
    excel.cpp \
        main.cpp \
        mainwindow.cpp \
    connection.cpp \
    mission.cpp \
    qrcode.cpp \
    qrcodegeneratedemo.cpp \
    qrcodegenerateworker.cpp \
    qrwidget.cpp \
    stat_client.cpp \
    stat_mission.cpp \
    statistiques.cpp \
    widget.cpp

HEADERS += \
    arduino.h \
    chatboxdialog.h \
    client.h \
    dialog.h \
    employee.h \
    excel.h \
        mainwindow.h \
    connection.h \
    mission.h \
    qrcode.h \
    qrcodegenerateworker.h \
    qrwidget.h \
    stat_client.h \
    stat_mission.h \
    statistiques.h \
    widget.h

FORMS += \
        chatboxdialog.ui \
        dialog.ui \
        mainwindow.ui \
        statistiques.ui \
        widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
