QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += resource_big

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bomb.cpp \
    bullet.cpp \
    enemy_n.cpp \
    gameview.cpp \
    main.cpp \
    mainscene.cpp \
    map.cpp \
    menuscene.cpp \
    player_plane.cpp

HEADERS += \
    bomb.h \
    bullet.h \
    config.h \
    enemy_n.h \
    enums.h \
    gameview.h \
    mainscene.h \
    map.h \
    menuscene.h \
    player_plane.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
