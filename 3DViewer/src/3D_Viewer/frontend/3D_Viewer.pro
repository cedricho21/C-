unix {
QT       += core gui opengl
}
macx {
QT       += core gui openglwidgets opengl
}
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(../3rdparty/QtGifImage/src/gifimage/qtgifimage.pri)

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../backend/model.cc \
    glview.cpp \
    main.cpp \
    mainwindow.cpp \

HEADERS += \
    ../backend/model.h \
    ../backend/controller.h \
    glview.h \
    mainwindow.h \

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
