QT       += core gui multimedia


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    crator.cpp \
    getmap.cpp \
    globalconfig.cpp \
    grass.cpp \
    main.cpp \
    pea.cpp \
    peashooter.cpp \
    plant.cpp \
    plantseed.cpp \
    sun.cpp \
    sunflower.cpp \
    wallnut.cpp \
    widget.cpp \
    zombie.cpp

HEADERS += \
    bullet.h \
    crator.h \
    getmap.h \
    globalconfig.h \
    grass.h \
    pea.h \
    peashooter.h \
    plant.h \
    plantseed.h \
    sun.h \
    sunflower.h \
    wallnut.h \
    widget.h \
    zombie.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
