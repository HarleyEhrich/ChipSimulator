#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#include <QColor>
#include <QMap>
#include <QMultiMap>
#include <QObject>
#include <QPointF>
#include <QRect>
#include <QSharedPointer>
#include <QVector>
#include <QWeakPointer>
#include <QWidget>

#include "BasicSDK_global.h"

#ifdef QT_DEBUG
    #define DEBUGINFO <<Q_FUNC_INFO<<__LINE__
#elif
    #define DEBUGINFO
#endif

#define MAKE_DEA_SHADOW_EFF(shadowPtr,target)           \
    shadowPtr=new QGraphicsDropShadowEffect(target);    \
    shadowPtr->setColor(Qt::gray);                      \
    shadowPtr->setOffset(0,0);                          \
    shadowPtr->setBlurRadius(8);                        \
    target->setGraphicsEffect(shadowPtr);


#define RENDER_HINT_ANT(painterPtr) painterPtr->setRenderHint(QPainter::Antialiasing);


#define MAKE_AUTO_PTR(classname)  \
    using classname##Ptr = QWeakPointer<classname>;   \
    using classname##SPtr = QSharedPointer<classname>;

#define CHECK_READ_END(xmlReader) \
    if(xmlReader.atEnd()){\
        qFatal(tr("Xml file end with no end elements.").toLatin1().data()); \
        return false;   \
    }


MAKE_AUTO_PTR(QWidget);
MAKE_AUTO_PTR(QObject);

namespace AMTL {//Enum

enum class DIRECTION{
    ABOVE,
    BELOW,
    LEFT,
    RIGHT
};

enum class ToastInfoPosition{
    TIP_LEFT_TOP,
    TIP_LEFT_BOTTOM,
    TIP_RIGHT_TOP,
    TIP_RIGHT_BOTTOM,
    TIP_MID_TOP,
    TIP_MID_BOTTOM
};

enum class ToastInfoType{
    TIP_DEFAULT,//默认类型
    TIP_INFORMATION,//信息: 就普通的信息
    TIP_TIP,//提示类消息:给用户提示用的信息
    TIP_WARNING,//警告信息: 出现了问题，但是已经内部解决了
    TIP_ERROR//错误信息: 可能会导致系统崩溃的信息
};

enum class UniqueIDType{
    Component,
    UserDefined,
    Default//默认的编号
};


}


namespace AMTL {


const QPoint ZERO_POINT{0,0};
const QPointF ZERO_POINTF{0.f,0.f};

namespace COLOR{
//Color
const QColor SHADOW_COLOR{66, 80, 102};

//主体颜色
const QColor MAIN_COLOR{237, 237, 235};//奶白色
const QColor MAIN_COLOR_DARK{0,0,0};//纯黑色

//强调色
const QColor NOTIFY_COLOR{22, 133, 169};//石青-#1685a9
//TODO 暗夜模式未定强调颜色
const QColor NOTIFY_COLOR_DARK{22, 133, 169};//石青-#1685a9

}

}

namespace AMTL {//function


}

namespace AMTL{//class

}

#endif // GLOBAL_H
