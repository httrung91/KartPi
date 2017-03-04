TEMPLATE = app

QT += core qml quick

CONFIG += c++11

SOURCES += \
    ./source/main.cpp \
    source/kartrpi_engine.cpp \
    source/kartrpi_screencontroller.cpp \
    source/kartrpi_consolemodel.cpp \
    source/kartrpi_wiringpiwrapper.cpp \
    source/kartrpi_lasermodel.cpp \
    source/kartrpi_shieldmodel.cpp \
    source/kartrpi_bombmodel.cpp \
    source/kartrpi_speedmodel.cpp \
    source/kartrpi_timemodel.cpp \
    source/kartrpi_kartstatusmodel.cpp

RESOURCES += \
    qml/qml.qrc \
    res/res.qrc

linux-oe-g++: {
    DEFINES += TARGET_BUILD
    message("FOR RASPBERRY")\
    INCLUDEPATH +=  ${SDKTARGETSYSROOT}/usr/include
    LIBS += -L${SDKTARGETSYSROOT}/usr/lib -lwiringPi -lwiringPiDev
}
else:{
    message("FOR DESKTOP")
}



# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    source/kartrpi_engine.h \
    source/kartrpi_screencontroller.h \
    source/kartrpi_consolemodel.h \
    source/kartrpi_wiringpiwrapper.h \
    source/kartpi_commondefs.h \
    source/kartrpi_lasermodel.h \
    source/kartrpi_shieldmodel.h \
    source/kartrpi_bombmodel.h \
    source/kartrpi_speedmodel.h \
    source/kartrpi_timemodel.h \
    source/kartrpi_kartstatusmodel.h


