QT += gui \
    widgets

TEMPLATE = lib
CONFIG += plugin

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    LinkPointItem/conlinkpointitem.cpp \
    LinkPointItem/draggabledotitem.cpp

HEADERS += \
    LinkPointItem/conlinkpointitem.h \
    LinkPointItem/draggabledotitem.h

DISTFILES += BasicCon.json \
    Json/ConLinkLine.json \
    Json/LinkPointItem/LinkPointItem.json


# Default rules for deployment.
unix {
    target.path = $$[QT_INSTALL_PLUGINS]/generic
}
!isEmpty(target.path): INSTALLS += target

unix|win32: LIBS += -L$$PWD/AbstractConInterface/lib/ -lAbstractConInterface

INCLUDEPATH += $$PWD/AbstractConInterface/include
DEPENDPATH += $$PWD/AbstractConInterface/include
