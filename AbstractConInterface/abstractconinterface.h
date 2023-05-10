#ifndef ABSTRACTCONINTERFACE_H
#define ABSTRACTCONINTERFACE_H

#include <QDateTime>
#include <QGraphicsDropShadowEffect>
#include <QGraphicsItem>
#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
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

#include "AbstractConInterface_global.h"

#include "UniGraphicsItemObject.h"
#include "UniConnectionPoint.h"


#define ComAbstractLabelName "AbstractComponet"
#define ComExtendLabelName "ExtendComponent"

class AbstractConInterface;
using AbstractConInterfacePtr = QWeakPointer<AbstractConInterface>;

struct ABSTRACTCONINTERFACE_EXPORT ComponentWidget{
    AbstractConInterface* _widgetComponentPtr;
    QSharedPointer<QWidget> _widgetSPtr;
    bool _pannelFloat;
    bool _manualReleaseWidget;
};

struct ABSTRACTCONINTERFACE_EXPORT ComponentInfoStruct{
    QString comId;//component的唯一编号
    QString comName;//组件默认名称

    QString comDesInfo;//组件的描述信息
    QString comAuthor;//组件作者

    QString comCreatTimeStr;//时间字符串
    QString comCreatTimeFormat;
    QDateTime comCreatTime;//组件创建时间

    QString comImagePath;//组件图片
    QPixmap* comImage;//组件图片

public:
    ComponentInfoStruct(){
        comCreatTimeFormat = "yy-mm-dd";
    }

    ComponentInfoStruct(const ComponentInfoStruct& other){
        *this= other;
    }

    ComponentInfoStruct& operator=(const ComponentInfoStruct& other){
        comId = other.comId;//component的唯一编号
        comName = other.comName;//组件默认名称

        comDesInfo = other.comDesInfo;//组件的描述信息
        comAuthor = other.comAuthor;//组件作者

        comCreatTimeStr = other.comCreatTimeStr;//时间字符串
        comCreatTimeFormat = other.comCreatTimeFormat;
        comCreatTime = other.comCreatTime;//组件创建时间

        comImagePath = other.comImagePath;//组件图片
        comImage = new QPixmap(*other.comImage);//组件图片

        return *this;
    }
};


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
    explicit AbstractConInterface(const ComponentInfoStruct& cInfo);

    explicit AbstractConInterface(long sceneID, QGraphicsItem *parent = nullptr,QObject* parentObject=nullptr);

    virtual ~AbstractConInterface();




//-----------------------------------CSS--------------------------------------//
// Class Siganls & Slots
signals:
    //通知该控件的连接点数目发生变化
    void tellConnectionPointsNumChange(int startIndex, int len = 1, bool add = true);

    void tellComNickNameChange(QString newName);

    void tellTextFontChange();

public slots:
    //序列化、反序列化，通过将控件状态转为XML，以供下次读取，注意到图元基本信息，诸如位置等由Abstarct 接口完成
    bool loadStatusFormXml(QXmlStreamReader* root);
    bool saveStatusToXml(QXmlStreamWriter* root);

    //运行函数，使用run来统一管理控件状态的更新入口，对外界传递该函数来使该控件可被其它控件调用，每次调用必须根据此完成状态更新
    virtual void run()=0;




//-----------------------------------CFN--------------------------------------//
// Class function
public:
    /// \brief 创建接口，返回该实例
    /// \brief Creat a new instance, and return this new instance
    AbstractConInterface* instance(long sceneID, QGraphicsItem *parent = nullptr);

    //获取组件的信息
    bool isComInfoInitial();
    ComponentInfoStruct getComInfo();
    const QSharedPointer<const ComponentInfoStruct> getComInfoSPtr();

    //获取该控件的场景ID
    long getSceneId() const;

    QString comNickName() const;
    void setComNickName(const QString &newComNickName);

    QFont textFont() const;
    void setTextFont(const QFont &newTextFont);

    //获取数据ptr
    inline const QWeakPointer<const QBitArray> &getDataWPtr(UniConnectionPoint* uni);

    //通过id来获取数据连接点
    UniConnectionPointPtr getCCPointWPtrById(int id);
    //获取全部的数据连接点
    const QVector<UniConnectionPointSPtr>& getCCPointVec() const;

    //获取该控件所有的设置相关Widget
    const QVector<ComponentWidget>& getComponentWidgtes();

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

    virtual void connectionDataChangeImpl(UniConnectionPoint* changePtr,qsizetype changedIndex,int changeLen);

private:
    void initial();

    void intialComponentInfoImpl(const ComponentInfoStruct& cInfo);
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

    ComponentWidget *registerComWidgetImpl(
        QSharedPointer<QWidget> widget,
        bool pannel,
        bool manualReleaseWidget);




//-----------------------------------Var--------------------------------------//
protected:
    //Info
    QSharedPointer<ComponentInfoStruct> _comInfoSPtr;

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
    //ConnectionPoint
    QVector<UniConnectionPointSPtr> _connectPointVec;
    QMap<UniConnectionPoint*,QWeakPointer<const QBitArray>> _pointDataMap;
    QVector<ComponentWidget> _comWidgetVec;


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

#define AbstractConInterface_iid "com.amtl.plugin.abstractconinterface"

Q_DECLARE_INTERFACE(AbstractConInterface, AbstractConInterface_iid)

#endif // ABSTRACTCONINTERFACE_H
