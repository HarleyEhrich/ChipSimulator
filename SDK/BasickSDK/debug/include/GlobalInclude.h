#ifndef GLOBAL_H
#define GLOBAL_H

#include <QColor>
#include <QPointF>
#include <QTime>
#include <QDateTime>

#include "BasicSDK_global.h"
#include "UniGraphicsItemObject.h"

#ifdef QT_DEBUG
#define DEBUGINFO qPrintable(QDateTime::currentDateTime().toString("[ yy/MM/dd hh:mm:ss ]("))<<QT_MESSAGELOG_FILE<<":"<<QT_MESSAGELOG_LINE<<"@"<<QT_MESSAGELOG_FUNC<<"):"
#else

#define DEBUGINFO ""

#endif
namespace AMTL {

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

//Const and static var
const QPoint ZERO_POINT{0,0};
const QPointF ZERO_POINTF{0.f,0.f};

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


#endif // GLOBAL_H
