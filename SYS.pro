QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += \
    inc/
    src/
    ui/

SOURCES += \
    src/dialog.cpp \
    src/invoker.cpp \
    src/main.cpp \
    src/sys.cpp \
    src/vdf.cpp \

HEADERS += \
    inc/command.h \
    inc/dialog.h \
    inc/invoker.h \
    inc/sys.h \
    inc/vdf.h \

FORMS += \
    ui/dialog.ui \
    ui/sys.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
