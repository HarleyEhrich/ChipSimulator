#ifndef ABSTRACTCONINTERFACE_H
#define ABSTRACTCONINTERFACE_H

#include <QDateTime>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
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


#include <GlobalInclude.h>
#include <UniGraphicsItemObject.h>
#include <UniLinkLine.h>
#include <UniConnectionPoint.h>

#include "AbstractConInterface_global.h"


/*
//Component
<ComponetXmlLabel>
    <ComponentExtendXmlLabel>
        //Some data usr stored
    </ComponentExtendXmlLabel>
    <ComponentCCPointXmlLabel>
        //Start store universal connection points status data

        <UniCCPointXmlLabel>//Start A universal connection point
            <UniCCPointDataXmlLabel>
                <UniCCPointBDataXmlLabel />
            </UniCCPointDataXmlLabel>
        </UniCCPointXmlLabel>

    </ComponentCCPointXmlLabel>
</ComponetXmlLabel>


//Line
<ComponentLinkXmlLabel>
    <UniCCPointLineXmlLabel>
        //line points text
    </UniCCPointLineXmlLabel>
</ComponentLinkXmlLabel>
*/

#define ComponetXmlLabel "Component"
#define ComponentExtendXmlLabel "ComponentExtend"
#define ComponentCCPointXmlLabel "CCPointsStatus"


#define ComponentLinkXmlLabel "FromComponent"

class AbstractConInterface;

struct ABSTRACTCONINTERFACE_EXPORT ComponentSettingWidgetInfoStruct{
    AbstractConInterface* _componentptr;
    QWidgetSPtr _widgetSPtr;

    bool _pannelFloat;//浮动面板？
    bool _manualReleaseWidget;//手动释放内存-都不管，直接释放掉智能指针就好了，在组件销毁时将会去掉这个面板全部的内容。
};
MAKE_AUTO_PTR(ComponentSettingWidgetInfoStruct);

struct ABSTRACTCONINTERFACE_EXPORT ComponentBasicInfoStruct{
    QString comId;//component的唯一编号
    QString comName;//组件默认名称

    QString comDesInfo;//组件的描述信息
    QString comAuthor;//组件作者

    QString comCreatTimeStr;//时间字符串
    QString comCreatTimeFormat;
    QDateTime comCreatTime;//组件创建时间

    QString comImagePath;//组件图片
    QPixmap* comImage;//组件图片--Will auto copy pixmap data rather is pointer

public:
    ComponentBasicInfoStruct();

    ComponentBasicInfoStruct(const ComponentBasicInfoStruct& other);

    ComponentBasicInfoStruct &operator=(const ComponentBasicInfoStruct& other);
};
MAKE_AUTO_PTR(ComponentBasicInfoStruct);


/// \brief The global time tick type
enum class TICK_TYPE{
    ZERO_HIGH,
    HIGH_ZERO,
    NO_TICK
};


class ABSTRACTCONINTERFACE_EXPORT AbstractConInterface : public UniGraphicsItemObject
{
    Q_OBJECT

public:
    //This is the root component construct
    explicit AbstractConInterface();
    explicit AbstractConInterface(const ComponentBasicInfoStruct& cInfo);
    explicit AbstractConInterface(long sceneID, QGraphicsItem *parent = nullptr,QObject* parentObject=nullptr);

    virtual ~AbstractConInterface();


//-----------------------------------CSS--------------------------------------//
// Class Siganls & Slots
signals:
    //通知该控件的连接点数目发生变化
    void tellConnectionPointsNumChange(int startIndex, int len = 1, bool add = true);

    void tellComNickNameChange(QString newName);

    void tellTextFontChange();

    void tellCCPointBindStatusChanged(bool newStatus, UniConnectionPointPtr target);

    void tellComAboutDestroy(long comId,AbstractConInterface* com);

public slots:
    void connectionDataChange(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen);
    void connectionBindStatusChange(bool newStatus, UniConnectionPoint* target);

    //序列化、反序列化，通过将控件状态转为XML，以供下次读取，注意到图元基本信息，诸如位置等由Abstarct 接口完成
    bool loadStatusFormXml(QXmlStreamReader* root);
    bool saveStatusToXml(QXmlStreamWriter* root);
    bool loadLinkFormXml(AbstractConInterface* targetCom,const QString& lineText,long toPointId,long fromPointId);
    bool saveLinkToXml(QXmlStreamWriter* root);

    //运行函数，使用run来统一管理控件状态的更新入口，对外界传递该函数来使该控件可被其它控件调用，每次调用必须根据此完成状态更新
    virtual void run()=0;


//-----------------------------------CFN--------------------------------------//
// Class function
public:
    /// \brief 创建接口，返回该实例
    /// \brief Creat a new instance, and return this new instance,
    /// \brief this will auto copy the basick info data pointer
    AbstractConInterface* instance(long sceneID, QGraphicsItem *parent = nullptr);

    //获取组件的信息
    bool isComInfoInitial();//If not initialed it will not allowed to use this component
    ComponentBasicInfoStruct getComInfo();//Get the copy of the component data
    const QSharedPointer<const ComponentBasicInfoStruct> getComInfoSPtr();//Get the component basic info shared ptr

    //获取该控件的场景ID
    long getSceneId() const;

    QString comNickName() const;//Nickname
    void setComNickName(const QString &newComNickName);

    QFont textFont() const;
    void setTextFont(const QFont &newTextFont);

    //获取数据ptr
    inline const QWeakPointer<const QBitArray> &getDataWPtr(UniConnectionPoint* uni);
    //通过id来获取数据连接点
    UniConnectionPointPtr getCCPointWPtrById(int id);
    //获取全部的数据连接点--Mainly used for make connect with the scene pair part sig-slot;
    const QVector<UniConnectionPointSPtr>& getCCPointVec() const;

    //获取该控件所有的设置相关Widget--This will auto delete, but need make sure when this component instance destroy main programe will take destroy the setting part too;
    const QVector<ComponentSettingWidgetInfoStruct>& getComponentWidgtes();

    //时序tick
    virtual void preTick(TICK_TYPE tickType);
    void tick(TICK_TYPE tickType);
    virtual void postTick(TICK_TYPE tickType);

protected:
    virtual void gnerateItemPainterPath() = 0;

    virtual AbstractConInterface* instanceImpl(long sceneID, QGraphicsItem *parent = nullptr) =0;

    QRect generateTextBouding(const QString& text);

    void setSceneId(long newScenceId);

    bool loadFromXmlAbstractImpl(QXmlStreamReader* root);
    bool saveToXmlAbstractImpl(QXmlStreamWriter* root);

    virtual bool loadFromXmlExtendImpl(QXmlStreamReader * root);
    virtual bool saveToXmlExtendImpl(QXmlStreamWriter* root);
    bool loadLinkFormXmlImpl(AbstractConInterface* targetCom,const QString& lineText,long toPointId,long fromPointId);
    bool saveLinkToXmlImpl(QXmlStreamWriter* root);

    virtual void connectionDataChangeImpl(UniConnectionPoint* changePtr,qsizetype changedIndex,int changeLen);

private:
    void initial();

    void intialComponentInfoImpl(const ComponentBasicInfoStruct& cInfo);
    void intialComponentInfoImpl(
        const QString& cid,
        const QString& cName,
        const QString& cDesInfo,
        const QString& author,
        const QString& creatTime,
        const QString& cImagePath,
        const QString& timeFormat);

    int registerConnectionPointImpl(COOR_POS pos,
                                bool outputPoint,
                                QString pointName,
                                int dataBits,
                                int maxBindItemNumber);

    bool unRegisterConnectionPointImpl(int size);

    ComponentSettingWidgetInfoStruct *registerComWidgetImpl(
        QSharedPointer<QWidget> widget,
        bool pannel,
        bool manualReleaseWidget);


//-----------------------------------Var--------------------------------------//
public:


protected:
    //Info
    QSharedPointer<ComponentBasicInfoStruct> _comInfoSPtr;

    //Painter releate variable
    QPainterPath _itemPainterPath;
    QRectF _boudingRect;
    QGraphicsDropShadowEffect* _shadowEffect;

    //控件别名
    QString _comNickName;
    QFont _textFont;

    //控件设置
    long _sceneId;

    //Tick status
    bool _tickNew;
    TICK_TYPE _curTickType;

private:
    //ConnectionPoint--!!
    QVector<UniConnectionPointSPtr> _connectPointVec;//连接点结合-find with id, id ==it's index

    QMap<UniConnectionPoint*,QWeakPointer<const QBitArray>> _pointDataMap;//数据快速指针Cache

    //内含一个智能指针保证了其设定使用的widget盒子不会被删除
    QVector<ComponentSettingWidgetInfoStruct> _comSettingInfoVec;//组件设定控件集合

//-----------------------------------ITF--------------------------------------//
//Interface override
public:
    // UniGraphicsItemObject interface
    virtual QPointF getRealItemCenterScenePos() override;
    virtual QRectF getRealBoudingRect() override;

    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;


protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


    //--------------static function and variable-----------------
protected:
    static void IntialComponentInfo(
        AbstractConInterface* targetCom,
        const QString& cid,
        const QString& cName,
        const QString& cDesInfo,
        const QString& author,
        const QString& creatTime,
        const QString& cImagePath,
        const QString& timeFormat="yyyy-mm-dd");

    static int RegisterConnectionPoint(
        AbstractConInterface* targetCom,
        COOR_POS pos,
        bool outputPoint,
        QString pointName,
        int dataBits =1,
        int maxBindItemNumber=1);


    static bool UnRegisterConnectionPoint(
        AbstractConInterface* target,
        int size);

    static bool RegisterComWidget(
        AbstractConInterface* targetCom,
        QSharedPointer<QWidget> widget,
        bool pannel,
        bool manualReleaseWidget
        );
};

MAKE_AUTO_PTR(AbstractConInterface);

#define AbstractConInterface_iid "com.amtl.plugin.abstractconinterface"

Q_DECLARE_INTERFACE(AbstractConInterface, AbstractConInterface_iid)

#endif // ABSTRACTCONINTERFACE_H
