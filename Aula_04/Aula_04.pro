#-------------------------------------------------
#
# Project created by QtCreator 2016-09-22T21:48:14
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Aula_04
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

win32 {
    INCLUDEPATH += "C:\\Program Files (x86)\\OpenCv\\build\\include" \

    CONFIG(debug,debug|release) {
        LIBS += -L"C:\\Program Files (x86)\\OpenCv\\build\\x86\\vc12\\lib" \
            -lopencv_core2410d \
            -lopencv_highgui2410d \
            -lopencv_imgproc2410d \
            -lopencv_features2d2410d \
            -lopencv_calib3d2410d \
-lopencv_nonfree2410d \
-lopencv_flann2410d
    }

    CONFIG(release,debug|release) {
        DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT
        LIBS += -L"C:\\Program Files (x86)\\OpenCv\\build\\x86\\vc12\\lib" \
            -lopencv_core2410 \
            -lopencv_highgui2410 \
            -lopencv_imgproc2410 \
            -lopencv_features2d2410 \
            -lopencv_calib3d2410 \
-lopencv_nonfree2410 \
-lopencv_flann2410

    }
}
