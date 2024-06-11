QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../brick_game/snake/controller.cpp \
    main.cpp \
    mainmenu.cpp \
    ../../brick_game/snake/model.cpp \
    ../../brick_game/tetris/s21_tetris.c \
    view.cpp

HEADERS += \
    ../../brick_game/snake/controller.h \
    mainmenu.h \
    ../../brick_game/snake/model.h \
    ../../brick_game/tetris/s21_tetris.h \
    view.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainmenu.ui

RESOURCES += \
    images/resources.qrc

#DISTFILES += \
#    images/image.png \
#    images/menu.png

