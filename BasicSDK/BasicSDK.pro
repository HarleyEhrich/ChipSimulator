QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
DEFINES += BASICSDK_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    UniConnectionPoint.cpp \
    UniLinkLine.cpp

HEADERS += \
    BasicSDKInclude.h \
    BasicSDK_global.h \
    GlobalInclude.h \
    UniConnectionPoint.h \
    UniLinkLine.h

RESOURCES +=


# Default rules for deployment.
unix {
    target.path = /usr/lib
}


config += debug_and_release

COPY_DEST = $$PWD/../SDK/BasickSDK

SRC_HEAD_FILES = $$PWD/*.h
SRC_HEAD_FILES = $$replace(SRC_HEAD_FILES,/,\\)

win32{
    CONFIG(debug, debug|release){
        COPY_HEAD_DIR = $${COPY_DEST}/debug/include/

        #copy dll fill
        target.path = $${COPY_DEST}/debug/bin/
    }

    CONFIG(release, debug|release){
        COPY_HEAD_DIR = $${COPY_DEST}/release/include/
        #
        target.path = $${COPY_DEST}/release/bin/
    }


    COPY_HEAD_DIR = $$replace(COPY_HEAD_DIR,/,\\)
    QMAKE_POST_LINK += xcopy $${SRC_HEAD_FILES} $${COPY_HEAD_DIR} /y /d
}

!isEmpty(target.path): INSTALLS += target


