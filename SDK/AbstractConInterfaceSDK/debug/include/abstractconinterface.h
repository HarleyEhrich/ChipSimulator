#ifndef ABSTRACTCONINTERFACE_H
#define ABSTRACTCONINTERFACE_H


#include <QDateTime>
#include <QDomNode>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMap>
#include <QObject>
#include <QPixmap>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <QVector>
#include <QWidget>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>


#include "AbstractConInterface_global.h"

#include "UniGraphicsItemObject.h"
#include "UniConnectionPoint.h"


class ABSTRACTCONINTERFACE_EXPORT AbstractConInterface : public UniGraphicsItemObject
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

#define ComAbstractLabelName "AbstractComponet"
#define ComExtendLabelName "ExtendComponent"

public:
    /// \brief The global time tick type
    enum class TICK_TYPE{
        ZERO_HIGH,
        HIGH_ZERO,
        NO_TICK
    };

public:
    explicit AbstractConInterface(long sceneID, QGraphicsItem *parent = nullptr,QObject* parentObject=nullptr);
    explicit AbstractConInterface(long sceneID, const QString& conName,QGraphicsItem *parent = nullptr,QObject* parentObject=nullptr);
    virtual ~AbstractConInterface();

signals:
    //显示新的窗口
    void newPannelWidget(QWidget* pannel, const QString& senderMsg);//Maybe just show a widget with parent nullptr is ok.

    //Function which can be override by all kinds of plugin
public slots:
    //运行函数，使用run来统一管理控件状态的更新入口，对外界传递该函数来使该控件可被其它控件调用，每次调用必须根据此完成状态更新
    virtual void run()=0;

    //获取控件的设置控件组，主界面处理控件删除后设置控件的删除，不需要控件自行处理。
    virtual QVector<QWidget*> getSetWidgetsVec() = 0;

    //获取控件设置面板，控件每次需要创建示例，注意到不应当管理创建之后的控件生存周期的管理，主界面将会处理。
    virtual QWidget* getSettingPannel() = 0;


    //运行保存，读取机制，通过将控件状态转为文本，以供下次读取，注意到图元基本信息，诸如位置等由Abstarct 接口完成
    bool loadStatusFormXml(QXmlStreamReader* root);
    bool saveStatusToXml(QXmlStreamWriter* root);

    // Class function
public:
    long sceneId() const;
    void setSceneId(long newScenceId);

    virtual void preTick(TICK_TYPE tickType);

    void tick(TICK_TYPE tickType);

    virtual void postTick(TICK_TYPE tickType);

    /// \brief 创建接口，返回该实例
    /// \brief Creat a new instance, and return this new instance
    virtual AbstractConInterface* instance(long sceneID, QGraphicsItem *parent = nullptr) =0 ;

protected:
    bool loadFromXmlAbstractImpl(QXmlStreamReader* root);
    bool saveToXmlAbstractImpl(QXmlStreamWriter* root);

    virtual void customInit();

    virtual void gnerateItemPainterPath();

    virtual bool loadFromXmlExtendImpl(QXmlStreamReader * root);
    virtual bool saveToXmlExtendImpl(QXmlStreamWriter* root);


    virtual void connectionDataChangeImpl(UniConnectionPoint* changePtr,qsizetype changedIndex,int changeLen);


private:
    void init();

    int registerConnectionPoint(COOR_POS pos,
                                bool outputPoint,
                                QString pointName,
                                int dataBits,
                                int maxBindItemNumber);

protected:
    //Painter releate variable
    QPainterPath _itemPainterPath;
    QRectF _boudingRect;
    QGraphicsDropShadowEffect* _shadowEffect;

    //控件别名
    QString _comNickName;
    //控件设置
    long _sceneId;

    //Tick status
    bool _tickNew;
    TICK_TYPE _curTickType;

private:
    //ConnectionPoint
    QVector<UniConnectionPoint*> _connectPointVec;
    QMap<UniConnectionPoint*,QWeakPointer<const QBitArray>> _pointDataMap;




    //是否可移动--默认可移动
    bool _isMoveable=true;
    //鼠标处于按下状态
    bool _mousePressed=false;
    //鼠标点击事件发生点
    QPointF _mousePressedPoint;


public:
    // UniGraphicsItemObject interface
    virtual QPointF getRealItemCenterScenePos() override;
    virtual QRectF getRealBoudingRect() override;

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


public:
    static bool staInitial();
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

    static int registerConnectionPoint(AbstractConInterface* targetCom,COOR_POS pos,bool outputPoint,QString pointName,int dataBits =1,int maxBindItemNumber=1);

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


//    //从文本内加载控件信息
//    bool loadFromTextAbstarctImpl(const QString& abText);
//    //将文本信息加载到控件内
//    bool saveToTextAbstarctImpl(QString& abText);

//    //注册设置按钮，提供按钮名称，以及对应的设置函数，注意到该函数仅能接收到点击事件产生的true，false，两个值
//    bool registerSetBtn(const QString& btnName,std::function<void(int)> setFunction, bool btndefaultValue=false);
//    bool registerSetValueBox(const QString& valueName, std::function<void(int)> setFunction, int defaultValue=0);


#define AbstractConInterface_iid "com.amtl.plugin.abstractconinterface"

Q_DECLARE_INTERFACE(AbstractConInterface, AbstractConInterface_iid)

#endif // ABSTRACTCONINTERFACE_H
