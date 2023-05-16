#ifndef UNICONNECTIONPOINT_H
#define UNICONNECTIONPOINT_H

/**
*    @file:    UniConnectionPoint.h
*    @brief:
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-04-13  01:11
*/


#include <QBitArray>
#include <QFontMetrics>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>
#include <QPainterPath>
#include <QString>
#include <QXmlStreamReader>

#include "GlobalInclude.h"
#include "UniLinkLine.h"

#define REQUEST_LINK true
#define UNREQUEST_LINK false

class UniConnectionPoint;

using TextDriection = AMTL::DIRECTION;
using COOR_POS = AMTL::DIRECTION;
using UniConnectionPointPtr = QWeakPointer<UniConnectionPoint>;

class BASICSDK_EXPORT UniConnectionPoint : public UniGraphicsItemObject /*public QObject, public QGraphicsItem*/
{
    Q_OBJECT

    friend class UniLinkLine;

public:
    explicit UniConnectionPoint();
    explicit UniConnectionPoint(int id,COOR_POS pos,bool outputPoint,QString pointName=tr("连接点"),int dataBits =1,int maxBindItemNumber=1, QGraphicsItem *parent = nullptr);
    virtual ~UniConnectionPoint();

//----self define slots and singals
signals:
    void toastInfo(QString infoTitle,
              QString info,
              bool autoHide=true,
              AMTL::ToastInfoPosition showPos = AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
              AMTL::ToastInfoType infoType = AMTL::ToastInfoType::TIP_DEFAULT);

//告知信息的信号--内部不准准绑定
    //通知scene准备链接或者取消链接
    void tellBindStatusChange(bool newStatus, UniConnectionPointPtr targetObj);

    //告知数据变化
    void tellDataChanged(UniConnectionPoint* changePtr,qsizetype changedIndex,int changeLen=1);//Just to remind thie father that the data been changed, please do something

    void tellHighResistanceStatusChange(bool newResistance);

    //告知名称变化了
    void tellPointNameChange(QString oldName, QString newName);

    //告知字体变了
    void tellTextFontChange(QFont oldFont,QFont newFont);

    //告知在父item的范围变化
    void tellSelfPosChange(COOR_POS oldSelfPos,COOR_POS newSelfPos);

    //告知文本位置变化
    void tellTextDirectionChange(TextDriection oldDir,TextDriection newDir);

//需要内部执行的信号，需要注意不要嵌套互相调用了
    //Path相关--需要重新生成
    void requestGenratePath();

public slots:
    virtual void linkLineItemPoschange(const QPointF& oldPos,const QPointF& newPos);

    virtual void linkLineItemPosHasChanged();

    virtual void linkLineRequestUnbind(UniLinkLine* targetLineHead);

//----nor function
public:
//Implement of get and set function
    //Data parts.Make sured the data can only be changed in setDataValue function
    //For father item quick access data
    QWeakPointer<const QBitArray> getDataPtr();
<<<<<<< HEAD
=======
    //快速获取数据值
    bool getDataValue(qsizetype index,bool* ok=nullptr);
>>>>>>> 6b02597 (修改基础库)
    //return the data changed bits number
    qsizetype setDataValue(const QBitArray& value, qsizetype indexStart=0);

    bool highResistance() const;
    void setHighResistance(bool newHighResistance);

    bool getLinkStautes() const;

    COOR_POS selfPos() const;
    void setSelfPos(COOR_POS newSelfPos);

    QString pointName() const;
    void setPointName(const QString &newPointName);

    QFont textFont() const;
    void setTextFont(const QFont &newTextFont);

    TextDriection textDirection() const;
    void setTextDirection(TextDriection newTextDirection);

    // Bind/Unbind connection and relate function
    inline bool isBindThisConnnectionPoint(UniConnectionPoint* target);
    inline int findBindConnectionPointIndex(UniConnectionPoint* target);
    inline int findBindConnectionPointIndexByLineHead(UniLinkLine* targetLineHead);

    // 绑定连接点
    bool bindConnectionPoint(UniConnectionPoint* targetConnectionPoint);

    // 解绑连接点
    bool unBindConnectionPoint(UniConnectionPoint* targetPoint);

    bool loadStatusFormXml(QXmlStreamReader* root);
    bool saveStatusToXml(QXmlStreamWriter* root);

    bool loadLinkStatusFormXml(QXmlStreamReader* root);
    bool saveLinkStatusToXml(QXmlStreamWriter* root);

protected:
    // 等待链接的状态
    void setBindStautes(bool newLinkStautes);

    //特殊节口，用于output向输入连接点传递数据变换
    qsizetype inputDataValue(QBitArray value, qsizetype indexStart=0);

    virtual QList<QPoint> gnerateLinePointList(UniConnectionPoint* target);


private:
    void innit();

    //For painterPath
    void gneratePainterPath();//重新生成形状
    void gnerateText();//重新生成相关文本--Will auto call gneratePainterPath();

    bool creatNewLine(const QList<QPoint>& pointList,UniLinkLine** lineHead, UniLinkLine** lineTail);
    inline bool deleteLine(UniLinkLine* lineHead, UniLinkLine* lineTail);

    // 绑定连接点
    inline bool bindConnectionPointImpl(UniConnectionPoint* targetConnectionPoint);
    // 解绑连接点
    inline bool unBindConnectionPointImpl(UniConnectionPoint* targetConnectionPoint);
    //Bind and unbind for input connection point
    inline bool bindConnctionPointInputImpl(UniConnectionPoint* targetConnectionPoint, UniLinkLine* lineHead, UniLinkLine* lineTail);
    inline bool unBindConnectionPointInputImpl(UniConnectionPoint* targetPoint);

    bool loadStatusFormXmlImpl(QXmlStreamReader* root);
    bool saveStatusToXmlImpl(QXmlStreamWriter* root);

    bool loadLinkStatusFormXmlImpl(QXmlStreamReader* root);
    bool saveLinkStatusToXmlImpl(QXmlStreamWriter* root);

//----nor var
private:
    QSharedPointer<UniConnectionPoint> _selfSharedPtr;

    //Identification info
    int _id=-1;//独一id，可以在没有名称的是否根据id查找--必须要设置，在后期json读取进入时需要这个
    COOR_POS _selfPos;//必须设置的位置
    bool _outputConnectionPoint;//是输出还是输入信号，只有输出和输入才能配对
    QString _pointName;//名称


    //Pair relate
    bool _linkStautes;

    //Data
    QVector<UniConnectionPoint*> _bindPointVec;    //Try to make the head and the tail will be earse and insert at the same time.
    QVector<UniLinkLine*> _lineHeadVec;//Store the link line item's head here.
    QVector<UniLinkLine*> _lineTailVec;//store the link line item's tail here.
    QSharedPointer<QBitArray> _dataPtrSelf;//Stored the data
    bool _highResistance;//高阻抗,自动传递到连接的点，默认是true

    //Settings here
    //Data setting
    int _dataBitsLen;//BitsArray only accept the same length array
    int _maxBindItemNumber;//-1 means no limit, default 1,and mind input point only can choose 1


    //Ui setting
    bool _showPointName;
    QFont _textFont;
    TextDriection _textDirection;//Defined where the text will be show

    //Some ui used var
    QGraphicsDropShadowEffect* _shadowEffect;//本体的阴影
    QPainterPath _itemPainterPath;//The item painter path
    QRectF _boudingRect;
    QPoint _finalTextBLPos;//最终显示的文本的左上角位置，相对于Item的positon
    QString _finalText;


//----Interface and override
    // UniGraphicsItemObject interface
public:
    virtual QPointF getRealItemCenterScenePos() override;
    virtual QRectF getRealBoudingRect() override;

public:
    // QGraphicsItem interface
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    virtual QPainterPath shape() const override;

protected:
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;


//----static var and function
<<<<<<< HEAD
private:
    void innitSta();

=======
public:
    static int mainBodyWH();
>>>>>>> 6b02597 (修改基础库)

private:

<<<<<<< HEAD
=======
private:
>>>>>>> 6b02597 (修改基础库)
    inline static bool __useLineToPointBind = true;

    inline static int __mainBodyWH;//主体长宽
    inline static int __centerCircleWH;//中心圆大小

    inline static int __uniLineWidth;//通用边界线粗细
    inline static int __mainBodyLineWidth;//正常边界线粗细
    inline static int  __centerCircleLineWidth;//中心圆绘制线粗细

    inline static QColor __uniNorColor;//普通颜色
    inline static QColor __uniActColor;//激活颜色
    inline static QColor __mainBodyColor;//主要主体颜色
    inline static QColor __mainBodyBorderColor;//主要主体边界颜色
    inline static QColor __centerCircleColor;//中心圆主体颜色
    inline static QColor __centerCircleBorderColor;//中心圆边界颜色
    inline static QColor __shadowColor;

    inline static QRectF __mainBodyRect;//整体圆
    inline static QRectF __mainBodyRectCll;//主体圆的碰撞区域
    inline static QRectF __centerCircleRect;//中心连接中的圆形

    inline static QPen __uniNorPen;//通用画笔
    inline static QBrush __uniNorBrush;//通用画刷
    inline static QPen __uniActPen;//通用激活状态画笔
    inline static QBrush __uniActBrush;//通用激活状态画刷
    inline static QPen __mainBodyPen;//主体画笔
    inline static QBrush __mainBodyBrush;//主体画刷
    inline static QPen __centerCirclePen;//画笔
    inline static QBrush __centerCircleBrush;//画刷
    inline static QPen __textPen;//画笔
    inline static QBrush __textBrush;//画刷
};



#endif // UNICONNECTIONPOINT_H
