#ifndef ABSTRACTCONINTERFACE_H
#define ABSTRACTCONINTERFACE_H

#include "AbstractConInterface_global.h"

#include <QDateTime>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPixmap>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QDomNode>

namespace AMTL {
//    enum MSGTYPE{DEAFAULT,WARNING,ERROR};
}

class ABSTRACTCONINTERFACE_EXPORT AbstractConInterface : public QObject ,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

#define ComAbstractLabelName "AbstractComponet"
#define ComExtendLabelName "ExtendComponent"

public:
    /// \brief The global time tick type
    enum class TICK_TYPE{
        ZERO_HIGH,
        HIGH_ZERO
    };

public:
    explicit AbstractConInterface(long sceneID, QGraphicsItem *parent = nullptr);
    virtual ~AbstractConInterface(){;}

signals:
    //显示新的窗口
    void newPannelWidget(const QString& senderMsg, const QString& pannelTitle, QWidget* pannel);

    //Function which can be override by all kinds of plugin
public slots:


    //运行函数，使用run来统一管理控件状态的更新入口，对外界传递该函数来使该控件可被其它控件调用，每次调用必须根据此完成状态更新
    virtual void run()=0;

    //运行保存，读取机制，通过将控件状态转为文本，以供下次读取，注意到图元基本信息，诸如位置等应有Abstarct 接口完成，理论上不推荐自主实现，但是也可以自主实现
    virtual bool loadStatusFormText(const QString& text) = 0;
    virtual bool saveStatusToText(QString& text) = 0;


    //获取控件的设置控件组，主界面处理控件删除后设置控件的删除，不需要控件自行处理。
    virtual QVector<QWidget*> getSetWidgetsVec() = 0;

    //获取控件设置面板，控件每次需要创建示例，注意到不应当管理创建之后的控件生存周期的管理，主界面将会处理。
    virtual QWidget* getSettingPannel() = 0;


    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


    // Class function
public:
    long sceneId() const;
    void setSceneId(long newScenceId);

    void tick(TICK_TYPE tickType);

    /// \brief 创建接口，返回该实例
    /// \brief Creat a new instance, and return this new instance
    virtual AbstractConInterface* instance(long sceneID, QGraphicsItem *parent = nullptr) =0 ;

protected:
    bool loadFromXmlAbstractImpl(QXmlStreamReader* root);
    bool saveToXmlAbstractImpl(QXmlStreamWriter* root);

    virtual bool saveToXmlExtendImpl(QXmlStreamWriter* root);
    virtual bool loadFromXmlExtendImpl(QXmlStreamReader* root);


//    //从文本内加载控件信息
//    bool loadFromTextAbstarctImpl(const QString& abText);
//    //将文本信息加载到控件内
//    bool saveToTextAbstarctImpl(QString& abText);

private:
    //控件别名
    QString _conNickName;

    //控件设置
    long _sceneId=-1;

    bool _tickNew = false;

    TICK_TYPE _curTickType;


    //是否可移动--默认可移动
    bool _isMoveable=true;
    //鼠标处于按下状态
    bool _mousePressed=false;
    //鼠标点击事件发生点
    QPointF _mousePressedPoint;


public:
    static bool initial();
    static QString comId();
    static QString comName();
    static QString componentDesInfo();
    static QString comAuthor();
    static QString comCreatTimeStr();
    static QDateTime comCreatTime();
    static QString comImagePath();
    static QPixmap comImage();

protected:
    static void intialComponentInfo(
        const QString& cid,
        const QString& cName,
        const QString& cDesInfo,
        const QString& author,
        const QString& creatTime,
        const QString& cImagePath,
        const QString& timeFormat="yyyy-mm-dd");

protected:
    inline static bool __initial=false;//是否初始化，未初始化不允许加载入。

    inline static QString __comId;//component的唯一编号
    inline static QString __comName;//组件默认名称
    inline static QString __comDesInfo;

    inline static QString __comAuthor;//组件作者

    inline static QString __comCreatTimeStr;
    inline static QDateTime __comCreatTime;//组件创建时间

    inline static QString __comImagePath;
    inline static QPixmap __comImage;//组件图片
};

//    //注册设置按钮，提供按钮名称，以及对应的设置函数，注意到该函数仅能接收到点击事件产生的true，false，两个值
//    bool registerSetBtn(const QString& btnName,std::function<void(int)> setFunction, bool btndefaultValue=false);
//    bool registerSetValueBox(const QString& valueName, std::function<void(int)> setFunction, int defaultValue=0);


#define AbstractConInterface_iid "com.amtl.plugin.abstractconinterface"

Q_DECLARE_INTERFACE(AbstractConInterface, AbstractConInterface_iid)

#endif // ABSTRACTCONINTERFACE_H
