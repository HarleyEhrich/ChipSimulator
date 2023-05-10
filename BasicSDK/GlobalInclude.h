#ifndef GLOBAL_H
#define GLOBAL_H
#pragma once

#include <QColor>
#include <QPointF>
#include <QRect>

#include "BasicSDK_global.h"
#include "UniGraphicsItemObject.h"

#define DEBUGINFO Q_FUNC_INFO

#define MAKE_DEA_SHADOW_EFF(shadowPtr,target)           \
    shadowPtr=new QGraphicsDropShadowEffect(target);    \
    shadowPtr->setColor(Qt::gray);                      \
    shadowPtr->setOffset(0,0);                          \
    shadowPtr->setBlurRadius(8);                        \
    target->setGraphicsEffect(shadowPtr);               \
 \

#define RENDER_HINT_ANT(painterPtr) painterPtr->setRenderHint(QPainter::Antialiasing);

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
/// count with 8 times
#define ComponentMaxId 10000
class UniqueNumberGenerator : QObject
{
    //__ Macro && Friend && Other__//
    Q_OBJECT

    //__ Construct && Destroy__//
private:
    UniqueNumberGenerator(size_t maxIdNumber = 10000);
    ~UniqueNumberGenerator();

    //__ Class Functions __//
public:
    long operator()(long idStartOffset=0);

    long getNewId(long idStartOffset=0);

    long getNewIdForObj(QObject* obj, long id = -1);

private:
    long findUseableId(long idStartOffsets=0);

    bool setValue(size_t offsetBits, bool value);

    bool isTrue(size_t offsetBits, bool* ok =nullptr);


    //__ Class Variable __//
private:
    size_t _maxIndex;
    size_t _maxBits;
    size_t _lastUsedIdOffsetBits;
    char* _usedBitsMap;//80000个可用ID

    QMap<size_t,QWeakPointer<QObject>> _idToObjMap;

    //__ Static Varable && Functions __//
public:
    static bool TypeExits(const QString& typeName);
    static int GetTypeIdByName(const QString& typeName);
    static int RegisterType(const QString& typeName,size_t maxIdNumber);
    static UniqueNumberGenerator *Instance(int type = int(UniqueIDType::Component));

private:
    inline static int curTypeId =0;
    inline static QMap<int,QString> typeIdToNameMap;
    inline static QMap<QString,int> typeNameToIdMap;

    inline static QMap<int,UniqueNumberGenerator*> instanceMap;

};using UniGener = UniqueNumberGenerator;

}

#endif // GLOBAL_H
