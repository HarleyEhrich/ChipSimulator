#ifndef DRAGGABLELINE_H
#define DRAGGABLELINE_H

/**
*    @file:    draggableline.h
*    @brief:   数据连接点之间连接线
*    @author:  harley_ehrich@outlook.com
*    @date:    2023-02-23  14:45
*/

#include <QBrush>
#include <QGraphicsEffect>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QGraphicsObject>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>
#include <QGraphicsSceneDragDropEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QList>
#include <QMenu>
#include <QMessageBox>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QPolygon>
#include <QPushButton>
#include <QRectF>
#include <QStyle>
#include <QStyleOptionGraphicsItem>
#include <QWidgetAction>
#include <QtMath>

#include "GlobalInclude.h"

class BASICSDK_EXPORT UniLinkLine : public QObject , public QGraphicsItem
{
    Q_OBJECT

    friend class ConLinkPointItem;

signals:
    /// \brief [Sig] 连线该节点下一个节点发生变化
    void tellNextItemChanged();

    /// \brief [Sig] 连线该节点上一个节点发生变化
    void tellPreItemChanged();

    /// \brief [Sig] 告知连接点释放该链接
    void tellUnbind(UniLinkLine* targetLine);

    /// \brief [Sig] tellLineSelectStatusChange
    /// \param newStatus
    void tellLineSelectStatusChange(bool newStatus);

    /// \brief [sig]
    /// \param newStatus
    void tellLineVisiableChange(bool newStatus);

    /// \brief [Sig] 在line坐标发生位置变化前产生该信号
    /// \param oldPos 坐标变化前的旧坐标，scene坐标系
    /// \param newPos 坐标变化后的新坐标，scene坐标系
    void positionChange(QPointF oldPos,QPointF newPos);

    /// \brief [Sig] 坐标已经发生变化
    void positionHasChanged();


public slots:

    /// \brief [public slot]
    /// \param oldPos
    virtual void nextItemPosChange(QPointF oldPos,QPointF newPos);

    /// \brief [public slot] nextItemPosHasChanged
    virtual void nextItemPosHasChanged();

    /// \brief [public slot] lineSelectStatusChangeSlot
    /// \param newStatus
    virtual void lineSelectStatusChangeSlot(bool newStatus);

    /// \brief [public slot] lineVisiableChangeSlot
    /// \param newStatus
    virtual void lineVisiableChangeSlot(bool newStatus);

private slots:
    //Just tell the output connection point to unbind this link, this will do nothing
    void unBind();

    //Default reverse this visiable setting.
    void reverseLineVisiable();

    void reverseLineSelect();

    void addNodeAfterThisNode();

    void deleteThisNode();

public:
    explicit UniLinkLine(QGraphicsItem *parent = nullptr);
    virtual ~UniLinkLine();

    UniLinkLine *getNextItem() const;
    UniLinkLine *getPreItem() const;

    bool sertItemAfterThis(UniLinkLine *item);

private:
    void initial();

#ifdef QT_DEBUG
    void testInitial();
#endif

    //Some function for shape caculater, there need tun  of rewrite.
    inline QPolygon gnerateItemLineCllBoundingPoly(const QPointF &newPos);
    inline void gnerateItemPainterPath(const QPointF& newPos);
    inline void updateStatus();

//Line link funciton
    void setNextItem(UniLinkLine *newNextItem);//设置后向item
    void setPreItem(UniLinkLine *newPreItem);//设置前向item
    void linkNextItem(UniLinkLine *newItem);//连接两个点
    void takeThisNodeOutOfLine();

//
    inline void unbindImpl();

//Status function
    void addNodeAfterThisItemImpl();

    inline bool isThisItemDeleteableImpl();
    inline void deleteThisItemImpl();

    inline bool isLineVisibleImpl();
    inline void setLineVisibleImpl(bool visible);

    inline bool isSelectedLineAllItemImpl();
    inline void setLineSelectedAllImpl(bool selected);


private:
    bool _startEnd;//

    QPainterPath _shape;//形状
    QRectF _boudingRect;
    bool _doMove;

    UniLinkLine* _nextItem;//下一个连接点
    UniLinkLine* _preItem;//上一个连接点

    QGraphicsDropShadowEffect* _shadowEffect;//本体的阴影

    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual QPainterPath shape() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    virtual void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) override;
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    virtual void keyPressEvent(QKeyEvent *event) override;

    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;


    //public static function
public:
    static QList<UniLinkLine*> creatLineWithPoints(const QList<QPoint>& posVec);
    static QList<UniLinkLine*> creatLineWithText(const QStringList& list);
    static QStringList storeLineToText(UniLinkLine* lineHead);

    //private static function
private:
    static void initialSta();

private:
    inline static int __norLineWitdh;//连线常规宽度
    inline static int __activeLineWidth;//连线活动宽度
    inline static int __dotLineWidth;//连接点绘制的边缘宽度
    inline static int __dotWhSize;//连接节点的长宽
    inline static int __shadowBlurRadius;//阴影绘制宽度

    inline static QColor __norColor;//常规颜色
    inline static QColor __activeColor;//活动状态主颜色
    inline static QColor __dotActLineColor;//节点边界颜色
    inline static QColor __dotLineColor;//节点活动状态颜色
    inline static QColor __dotBodyColor;//节点主体颜色
    inline static QColor __shadowColor;//阴影颜色

    inline static QRectF __dotRect;//连接节点的rect
    inline static QRectF __dotRectCll;//节点的碰撞矩形

    //连线正常画笔笔刷
    inline static QPen __lineNorPen;//常规状态画笔
    inline static QBrush __lineNorBru;//常规状态画刷，这个稍微粗一点，用来作为底层
    inline static QPen __lineSelectPen;//活动状态辅助连线画笔
    inline static QBrush __lineSelectBrush;//互动状态辅助线画刷
    inline static QPen __dotActPen;//连接节点画笔
    inline static QPen __dotPen;//节点活动颜色
    inline static QBrush __dotBrush;//连接节点画刷

};

#endif // DRAGGABLELINE_H
