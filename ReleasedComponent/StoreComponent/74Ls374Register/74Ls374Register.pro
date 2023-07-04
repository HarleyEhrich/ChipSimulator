QT += gui
QT += widgets
QT += xml

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Register74LS374.cpp

HEADERS += \
    Register74LS374.h

DISTFILES += \
    Register74Ls374.json

#---------Import basic lib----------------------
unix|win32|macx{
    CONFIG(debug, debug|release){
        LIBS += -L$$PWD/../../../SDK/BasickSDK/debug/bin/ -lBasicSDK
        INCLUDEPATH += $$PWD/../../../SDK/BasickSDK/debug/include
        DEPENDPATH += $$PWD/../../../SDK/BasickSDK/debug/include
    }

    CONFIG(release, debug|release){
        LIBS += -L$$PWD/../../../SDK/BasickSDK/release/bin/ -lBasicSDK
        INCLUDEPATH += $$PWD/../../../SDK/BasickSDK/release/include
        DEPENDPATH += $$PWD/../../../SDK/BasickSDK/release/include
    }
}




#---------Import abstractconinterface lib----------------------
unix|win32|macx{
    CONFIG(debug, debug|release){
        LIBS += -L$$PWD/../../../SDK/AbstractConInterfaceSDK/debug/bin/ -lAbstractConInterface
        INCLUDEPATH += $$PWD/../../../SDK/AbstractConInterfaceSDK/debug/include
        DEPENDPATH += $$PWD/../../../SDK/AbstractConInterfaceSDK/debug/include
    }
    CONFIG(release, debug|release){
    LIBS += -L$$PWD/../../../SDK/AbstractConInterfaceSDK/release/bin/ -lAbstractConInterface
    INCLUDEPATH += $$PWD/../../../SDK/AbstractConInterfaceSDK/release/include
    DEPENDPATH += $$PWD/../../../SDK/AbstractConInterfaceSDK/release/include
    }
}

## Default rules for deployment.
#unix {
#    target.path = $$[QT_INSTALL_PLUGINS]/generic
#}

#---------------Eeport lib and head--------------------
config += debug_and_release

COPY_DEST = $$PWD/../../../ComponentPlugin/

SRC_HEAD_FILES = $$PWD/*.h
SRC_HEAD_FILES = $$replace(SRC_HEAD_FILES,/,\\)

win32|macx{
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
