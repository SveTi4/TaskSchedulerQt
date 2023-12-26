QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    authregdialog.cpp \
    edititemdialog.cpp \
    helpdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    loadingscreen.cpp \
    addtaskdialog.cpp

HEADERS += \
    authregdialog.h \
    edititemdialog.h \
    helpdialog.h \
    mainwindow.h \
    addtaskdialog.h \
    loadingscreen.h

FORMS += \
    authregdialog.ui \
    edititemdialog.ui \
    helpdialog.ui \
    mainwindow.ui \
    addtaskdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
