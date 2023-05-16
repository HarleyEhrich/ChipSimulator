QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ControlObj/ElecGraphicsControllor.cpp \
    ControlObj/PluginLoaderController.cpp \
    Log/LogHandler.cpp \
    Pages/InfoPages/AmtlInfoWidget.cpp \
    Widgets/FloatWidgets/ToastInfoWidget.cpp \
    Widgets/Graphics/MultiplexedScendaryWidget/ViewControlUnitWidget.cpp \
    Widgets/Graphics/AmtlGraphicsScene.cpp \
    Widgets/Graphics/AmtlGraphicsView.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ControlObj/ElecGraphicsControllor.h \
    ControlObj/PluginLoaderController.h \
    Include/ProjectInclude.h \
    Log/LogHandler.h \
    Pages/InfoPages/AmtlInfoWidget.h \
    Widgets/FloatWidgets/ToastInfoWidget.h \
    Widgets/Graphics/MultiplexedScendaryWidget/ViewControlUnitWidget.h \
    Widgets/Graphics/AmtlGraphicsScene.h \
    Widgets/Graphics/AmtlGraphicsView.h \
    mainwindow.h

FORMS += \
    Widgets/FloatWidgets/ToastInfoWidget.ui \
    Widgets/Graphics/MultiplexedScendaryWidget/ViewControlUnitWidget.ui \
    mainwindow.ui

RESOURCES += \
    Resource/icon.qrc \
    Resource/main_window_icon/mainwindow_icon.qrc \
    Resource/widget_icon/widget_icon.qrc


include(3rdParty/FlatTabWidget/FlatTabWidget.pri)

UI_DIR = $${OUT_PWD}/Ui/



# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

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




#---------Import abstractconinterface lib----------------------
unix|win32{
    CONFIG(debug, debug|release){
        LIBS += -L$$PWD/../SDK/AbstractConInterfaceSDK/debug/bin/ -lAbstractConInterface
        INCLUDEPATH += $$PWD/../SDK/AbstractConInterfaceSDK/debug/include
        DEPENDPATH += $$PWD/../SDK/AbstractConInterfaceSDK/debug/include
    }
    CONFIG(release, debug|release){
    LIBS += -L$$PWD/../SDK/AbstractConInterfaceSDK/release/bin/ -lAbstractConInterface
    INCLUDEPATH += $$PWD/../SDK/AbstractConInterfaceSDK/release/include
    DEPENDPATH += $$PWD/../SDK/AbstractConInterfaceSDK/release/include
    }
}

DISTFILES += \
    3rdParty/FlatTabWidget/3rdparty/LICENSE \
    3rdParty/FlatTabWidget/3rdparty/README.md \
    3rdParty/FlatTabWidget/FlatTabWidget.pri \
    3rdParty/FlatTabWidget/LICENSE \
    3rdParty/FlatTabWidget/README.md \
    Widgets/MultiplexedScendaryWidget/在此文件夹写入一下可以重复使用的界面文件.txt

