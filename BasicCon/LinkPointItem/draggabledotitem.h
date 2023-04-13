#ifndef DRAGEABLEDOTITEM_H
#define DRAGEABLEDOTITEM_H

#include <QBrush>
#include <QGraphicsItem>
#include <QMenu>
#include <QObject>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QRectF>

#define NO_AUTO_ALGIN

namespace amtl {
    enum NEXTDRAGGABLEITEMDIREACTION{NO_DIREACTION,UP,DOWN,LEFT,RIGHT};
    enum SIG_TRANS_DIRECTION{NONE,PRE,NEXT,BOTH};

}

class DraggableDotItem : public QObject ,public QGraphicsItem
{

    Q_OBJECT

    //-----------------Construct&Destructor Function----------------//
public:
    explicit DraggableDotItem(QGraphicsItem *parent = nullptr);

    virtual ~DraggableDotItem();


    //-----------------Normal Class Function----------------//
public:
    bool visible() const;

    void setVisible(bool newVisible);

    bool itemCustomMove() const;

    void setItemCustomMove(bool itemCustomMove);

    bool waitLink() const;

    void setWaitLink(bool newWaitLink);

private:
    void init();

    //路径获取
    static const QPainterPath& getPainterPath(amtl::NEXTDRAGGABLEITEMDIREACTION oren);

    //创建对象--包含在该scene内
    inline DraggableDotItem* creatNewInstance();

    inline void creatItemAfter();

    void setNewPos(const QPointF& newPos, const QPointF& oldPos, amtl::SIG_TRANS_DIRECTION sigTransDir=amtl::SIG_TRANS_DIRECTION::BOTH);

    void setNextItem(DraggableDotItem* newItem);

    void setPreItem(DraggableDotItem* newItem);

    void calBoRec();


    //-----------------Signals----------------//
signals:
    void msg(QString msg);

    //要求view全部更新-sig
    void requestUpdateView();

    //请求点连接-sig
    void requestLink(DraggableDotItem* linkDot);

    void requestDelAllLink();

    //下一个item的位置变化-sig
    void nItemPostionChange(QPointF newPos,QPointF oldPos);

    //上一个item位置变化-sig
    void pItemPostionChange(QPointF newPos,QPointF oldPos);


    //-----------------Slot Function----------------//
public slots:
    //更新目前item与下一item的方向关系
    void updateDire();

    //获取该点的前item
    const DraggableDotItem* const getPreviousDraggableItem();

    //获取该店的后item
    const DraggableDotItem* const getNextDraggableItem();

    //在目前item的后面插入一个item
    bool sertDotItemAfter(DraggableDotItem* newItem);

    //删除item
    bool deleteThisItem();

    //item从item链中拿出
    bool takeOutItemFromChain();

    //后续item位置变化槽函数
    void nextItemPostionChange(QPointF newPos,QPointF oldPos);

    //前item位置变化槽函数
    void preItemPositionChange(QPointF newPos,QPointF oldPos);


    //-----------------Virtual Override Function----------------//
public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual QRectF boundingRect() const override;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;


private:
    //绘制笔刷信息
    static const QBrush _mainBodybrush;
    static const QPen _mainBodypen;
    static const QPen _linkLinePen;
    static const QPen _selectBorderPen;
    static const QPen _waitLinkBorderPen;


    //图元绘制大小信息
    //图元的宽/高
    static const qreal _dotWidthHeight;
    //图元负的一半宽/高
    static const qreal _negHalfDotWidthHeight;

    //目前图元与下一个绑定点的方向关系
    amtl::NEXTDRAGGABLEITEMDIREACTION _curDire;

    //目前图元目前绘制路径
    QPainterPath _curPPath;

    //目前图元边界信息
    QRectF _mainBodyBoudingRect;
    QRectF _boudingRect;

    //是否可见
    bool _visible;

    //节点是否可由点击移动
    bool _itemCustomMove;

    //鼠标是否按下，移动边线使用
    bool _mousePressed=false;

    bool _waitLink;

    /// \brief The point coordinates are used to describe the relative coordinates of the mouse click point from the origin of the primitive.
    /// \brief 该点坐标用于描述鼠标点击点距离图元原点的相对坐标
    QPointF _mpReleativeOri;

    //联系关系
    DraggableDotItem* _preItem=nullptr;
    DraggableDotItem* _nextItem=nullptr;
};

#endif // DRAGEABLEDOTITEM_H
