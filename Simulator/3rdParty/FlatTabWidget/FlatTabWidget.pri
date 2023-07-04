SOURCES += \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetAnimation.cpp \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInAnimator.cpp \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInDecorator.cpp \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideAnimator.cpp \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideDecorator.cpp \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.cpp \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverDecorator.cpp \
    $$PWD/TabPagesWidget.cpp \
    $$PWD/customtabbar.cpp \
    $$PWD/tabitem.cpp \
    $$PWD/tabpagegenerator.cpp

HEADERS += \
    $$PWD/3rdparty/AbstractAnimator.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetAnimation.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetAnimationPrivate.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInAnimator.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetFadeIn/StackedWidgetFadeInDecorator.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideAnimator.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlide/StackedWidgetSlideDecorator.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverAnimator.h \
    $$PWD/3rdparty/StackedWidgetAnimation/StackedWidgetSlideOver/StackedWidgetSlideOverDecorator.h \
    $$PWD/3rdparty/WAF.h \
    $$PWD/TabPagesWidget.h \
    $$PWD/customtabbar.h \
    $$PWD/tabitem.h \
    $$PWD/tabpagegenerator.h

FORMS += \
    $$PWD/TabPagesWidget.ui \
    $$PWD/tabitem.ui

INCLUDEPATH += $$PWD

RESOURCES += \
    $$PWD/resources/widget_icon.qrc
