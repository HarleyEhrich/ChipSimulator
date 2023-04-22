QT += gui
QT += widgets

TEMPLATE = lib
DEFINES += ABSTRACTCONINTERFACE_LIBRARY

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    abstractconinterface.cpp

HEADERS += \
    AbstractConInterface_global.h \
    abstractconinterface.h

RESOURCES += \
    resource/res.qrc

TRANSLATIONS += \
    AbstractConInterface_zh_CN.ts

#---------Import basic lib----------------------
unix|win32{
    CONFIG(debug, debug|release){
        LIBS += -L$$PWD/../SDK/BasickSDK/debug/bin/ -lBasicSDK
        INCLUDEPATH += $$PWD/../SDK/BasickSDK/debug/include
        DEPENDPATH += $$PWD/../SDK/BasickSDK/debug/include
    }

    CONFIG(release, debug|release){
        LIBS += -L$$PWD/../SDK/BasickSDK/release/bin/ -lBasicSDK
        INCLUDEPATH += $$PWD/../SDK/BasickSDK/release/include
        DEPENDPATH += $$PWD/../SDK/BasickSDK/release/include
    }
}



# Default rules for deployment.
unix {
    target.path = /usr/lib
}

#---------------Eeport lib and head--------------------
config += debug_and_release

COPY_DEST = $$PWD/../SDK/AbstractConInterfaceSDK

SRC_HEAD_FILES = $$PWD/*.h
SRC_HEAD_FILES = $$replace(SRC_HEAD_FILES,/,\\)

win32{
    CONFIG(debug, debug|release){
        #Header files copy dest dir
        COPY_HEAD_DIR = $${COPY_DEST}/debug/include/

        #Copy dll file to the sdk folder
        target.path = $${COPY_DEST}/debug/bin/
    }

    CONFIG(release, debug|release){
        COPY_HEAD_DIR = $${COPY_DEST}/release/include/
        #
        target.path = $${COPY_DEST}/release/bin/
    }


    COPY_HEAD_DIR = $$replace(COPY_HEAD_DIR,/,\\)
    #Copy command
    QMAKE_POST_LINK += xcopy $${SRC_HEAD_FILES} $${COPY_HEAD_DIR} /y /d
}

!isEmpty(target.path): INSTALLS += target



