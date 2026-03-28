QT       += core gui sql printsupport serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += depend_includepath

SOURCES += \
    colordelegate.cpp \
    connection.cpp \
    distribution.cpp \
    main.cpp \
    mainwindow.cpp \
    pick_up.cpp

HEADERS += \
    colordelegate.h \
    connection.h \
    distribution.h \
    mainwindow.h \
    pick_up.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
