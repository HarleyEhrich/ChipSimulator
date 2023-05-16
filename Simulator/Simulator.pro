QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ControlObj/ElecGraphicsControllor.cpp \
    ControlObj/PluginLoaderControllor.cpp \
    Log/LogHandler.cpp \
    Test/DevAssistance.cpp \
    Widgets/Containers/amtldrawerwidget.cpp \
    Widgets/FloatWidgets/ToastInfoWidget.cpp \
    Widgets/Graphics/amtlgraphicsscene.cpp \
    Widgets/Graphics/amtlgraphicsview.cpp \
    Widgets/Graphics/viewcontrollunit.cpp \
    Widgets/Multiplexed/circuitdiagram.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
<<<<<<< HEAD
    Include/project_include.h \
=======
    ControlObj/ElecGraphicsControllor.h \
    ControlObj/PluginLoaderControllor.h \
    Include/ProjectInclude.h \
>>>>>>> c344d8f (修改接口)
    Log/LogHandler.h \
    Test/DevAssistance.h \
    Widgets/Containers/amtldrawerwidget.h \
    Widgets/FloatWidgets/ToastInfoWidget.h \
    Widgets/Graphics/amtlgraphicsscene.h \
    Widgets/Graphics/amtlgraphicsview.h \
    Widgets/Graphics/viewcontrollunit.h \
    Widgets/Multiplexed/circuitdiagram.h \
    mainwindow.h

FORMS += \
    Widgets/FloatWidgets/ToastInfoWidget.ui \
    Widgets/Graphics/viewcontrollunit.ui \
    Widgets/Multiplexed/circuitdiagramui.ui \
    mainwindow.ui

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
        LIBS += -L$$PWD/../../SDK/BasickSDK/release/bin/ -lBasicSDK
        INCLUDEPATH += $$PWD/../../SDK/BasickSDK/release/include
        DEPENDPATH += $$PWD/../../SDK/BasickSDK/release/include
    }
}




##---------Import abstractconinterface lib----------------------
#unix|win32{
#    CONFIG(debug, debug|release){
#        LIBS += -L$$PWD/../SDK/AbstractConInterfaceSDK/debug/bin/ -AbstractConInterface
#        INCLUDEPATH += $$PWD/../SDK/AbstractConInterfaceSDK/debug/include
#        DEPENDPATH += $$PWD/../SDK/AbstractConInterfaceSDK/debug/include
#    }

#    CONFIG(release, debug|release){
#    LIBS += -L$$PWD/../SDK/AbstractConInterfaceSDK/release/bin/ -AbstractConInterface
#    INCLUDEPATH += $$PWD/../SDK/AbstractConInterfaceSDK/release/include
#    DEPENDPATH += $$PWD/../SDK/AbstractConInterfaceSDK/release/include
#    }
#}
