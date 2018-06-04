#-------------------------------------------------
#
# Project created by QtCreator 2018-04-24T17:09:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BentoNyan
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
win32 {
    win32-msvc* {
        LIBS     += opengl32.lib glu32.lib
        INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

        LIBS += -L$$(OPENCV_DIR)\lib \
            -lopencv_core2413 \
            -lopencv_highgui2413 \
            -lopencv_imgproc2413 \
            -lopencv_features2d2413 \
            -lopencv_calib3d2413

    } else {
        LIBS     += -lopengl32 -lglu32
        INCLUDEPATH +=$$(OPENCV_DIR)\..\..\include

        LIBS += -L$$(OPENCV_DIR)\lib \
            -lopencv_core2413 \
            -lopencv_highgui2413 \
            -lopencv_imgproc2413 \
            -lopencv_features2d2413 \
            -lopencv_calib3d2413

    }
}
macx {
    # The following define makes your compiler emit warnings if you use
    # any feature of Qt which has been marked as deprecated (the exact warnings
    # depend on your compiler). Please consult the documentation of the
    # deprecated API in order to know how to port your code away from it.
    DEFINES += QT_DEPRECATED_WARNINGS

    # You can also make your code fail to compile if you use deprecated APIs.
    # In order to do so, uncomment the following line.
    # You can also select to disable deprecated APIs only up to a certain version of Qt.
    #DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.13.4

    INCLUDEPATH +=/usr/local/include

    LIBS += -L/usr/local/lib \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_features2d \
        -lopencv_calib3d
}
unix {
    INCLUDEPATH +=$$(OPENCV_DIR)/include \
                /root/opencv/include/ \

    LIBS += -lGL
    LIBS += -lGLU
    #-L$$(OPENCV_DIR)/lib
    LIBS += -L/root/opencv/lib \
        -lopencv_core \
        -lopencv_highgui \
        -lopencv_imgproc \
        -lopencv_features2d \
        -lopencv_calib3d
}



SOURCES += \
        main.cpp \
        bento.cpp \
    imageprocessor.cpp

HEADERS += \
        bento.h \
    imageprocessor.h

FORMS += \
        bento.ui

RESOURCES += \
    sons.qrc
