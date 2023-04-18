#ifndef AMTLGRAPHICSVIEW_H
#define AMTLGRAPHICSVIEW_H

#include <QDebug>
#include <QGraphicsEffect>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QList>
#include <QMouseEvent>
#include <QObject>
#include <QPaintEvent>
#include <QPoint>
#include <QPointF>
#include <QPushButton>
#include <QWidget>

#include "include/project_include.h"
#include "viewcontrollunit.h"

class AmtlGraphicsView : public QGraphicsView
{
    //__ Macro && Friend && Other__//
    Q_OBJECT



    //__ Construct && Destroy__//
public:
    AmtlGraphicsView(QWidget *parent = nullptr);
    virtual ~AmtlGraphicsView();


    //__ Signals && Slots __//
public slots:
    //水平对齐底部
    void alignBottom();

    //垂直对齐中间
    void alignCenter();

    //垂直对齐右侧
    void alignEnd();

    //水平对齐中间
    void alignMiddle();

    //垂直对齐左侧
    void alignStart();

    //水平对齐顶部
    void alignTop();


    //__ Class Functions __//
private:
    void init();

    void initViewControlWidget();

    bool isMoveAndSelect();

    void moveSceneCenterImpl(QPointF delta);

    bool moveItemToPos(QGraphicsItem* targetItem,const QPoint& scenePos);

    //水平对齐底部
    void alignBottomImpl();

    //垂直对齐中间
    void alignCenterImpl();

    //垂直对齐右侧
    void alignEndImpl();

    //水平对齐中间
    void alignMiddleImpl();

    //垂直对齐左侧
    void alignStartImpl();

    //水平对齐顶部
    void alignTopImpl();

    void setLockViewImpl(const bool& locked);

    void setModelImpl(const bool& model);

    void setZoomRatioImpl(const qreal& ratio);



    //__ Class Variable __//
private:
    ViewControllUnit* _cuniWidget =nullptr;

    bool _viewLoked=false;
    bool _moveAndSelectModel=true;

    bool _mousePreessed=false;
    QPoint _mousePressedDownPos;
    QPointF _centerScenePos;



    //__ Interface && Override __//
protected://QGraphicsView
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

protected://QWidget
    virtual void resizeEvent(QResizeEvent *event) override;

    //__ Static Varable && Functions __//



};

#endif // AMTLGRAPHICSVIEW_H


///* 整个滚动条区域样式 */
//QScrollBar:vertical {
//    background-color: #f8f9fa;
//width: 12px;/*将会设置到滑块的大小*/
//margin: 12px 0 12px 0;/*上下按钮可占据0-24这个上下范围*/
//}

///*-------------------------向上按钮区域------------------------------*/
//QScrollBar::sub-line:vertical {/* 向上按钮的背景区域 */
//    background-color: transparent;
//border: 1px solid transparent;
//height: 12px;
//    margin-up: 0px;
//    subcontrol-position: top;
//    subcontrol-origin: margin;
//}
//QScrollBar::up-arrow:vertical {/* 向上箭头样式 */
//    background-color: transparent;
//height: 8px;
//width: 8px;
//}
//QScrollBar::up-arrow:vertical:hover {/* 当鼠标放到向上箭头上的时候 */
//    border-image:url(:/triangle_up.png);
//}

///*-------------------------滑块上方区域------------------------------*/
//QScrollBar::sub-page:vertical {/* 滑块上面区域样式 */
//border: 1px solid transparent;
//    background-color: transparent;
//}
//QScrollBar::sub-line:vertical:hover {}/* 当鼠标放到向上区域的时候 */

///*-------------------------滑块区域------------------------------*/
//QScrollBar::handle:vertical {	/* 滑块区域样式 */
//    background-color: #dfe0e1;
//border: 1px transprent;
//    border-radius: 2px;
//    margin-left: 3px;
//    margin-right: 3px;
//}
//QScrollBar::handle:vertical:hover,
//                                QScrollBar::handle:vertical:pressed {/* 鼠标滑过滑块样式 */
//    background-color: #959596;
//    margin-left: 2px;
//    margin-right: 2px;
//    border-radius: 3px;

//    QScrollBar::up-arrow:vertical {/* 当鼠标放到向上箭头上的时候 */
//        border-image:url(:/triangle_up.png);
//    }

//}

///*-------------------------滑块下方区域------------------------------*/
///* 滑块下面区域样式 */
//QScrollBar::add-page:vertical {
//border: 1px solid transparent;
//    background-color: transparent;
//}

///* 当鼠标放到向下区域的时候 */
//QScrollBar::add-line:vertical:hover {}

///*-------------------------向下按钮区域------------------------------*/
//QScrollBar::add-line:vertical {/*下方的按钮的背景*/
//    background-color: transparent;
//border: 1px solid transparent;
//height: 12px;
//    margin-bottom: 0px;
//    subcontrol-position: bottom;
//    subcontrol-origin: margin;
//}
//QScrollBar::down-arrow:vertical {/* 向下箭头样式 */
//    background-color: transparent;
//height: 8px;
//width: 8px;
//}
//QScrollBar::down-arrow:vertical:hover {/* 当鼠标放到向下箭头上的时候 */
//    border-image:url(:/triangle_down.png);
//}



///**********************************************************************************/
///* 整个滚动条区域样式 */
//QScrollBar:horizontal {
//    background-color: #f8f9fa;
//height: 12px;/*将会设置到滑块的大小*/
//margin: 0 12px 0 12px;/*左右按钮可占据0-12这个范围*/
//}
//QScrollBar:horizontal:hover {
//    QScrollBar::up-arrow:vertical {/* 当鼠标放到向上箭头上的时候 */
//        border-image:url(:/triangle_left.png);
//    }
//    QScrollBar::down-arrow:horizontal {/* 当鼠标放到向下箭头上的时候 */
//        border-image:url(:/triangle_right.png);
//    }
//    QScrollBar::handle:horizontal {/* 鼠标滑过滑块样式 */
//        background-color: #959596;
//        margin-top: 2px;
//        margin-bottom: 2px;
//        border-radius: 3px;
//    }
//}
///*-------------------------向左按钮区域------------------------------*/
//QScrollBar::sub-line:horizontal {/* 向左按钮的背景区域 */
//    background-color: transparent;
//border: 1px solid transparent;
//width: 12px;
//    margin-left: 0px;
//    subcontrol-position: left;
//    subcontrol-origin: margin;
//}
//QScrollBar::up-arrow:horizontal {/* 向左箭头样式 */
//    background-color: transparent;
//height: 8px;
//width: 8px;
//}
//QScrollBar::up-arrow:vertical:hover {/* 当鼠标放到向左箭头上的时候 */
//    border-image:url(:/triangle_left.png);
//}
///*-------------------------滑块左侧区域------------------------------*/
//QScrollBar::sub-page:horizontal {/* 滑块左侧区域样式 */
//border: 1px solid transparent;
//    background-color: transparent;
//}
//QScrollBar::sub-line:vertical:hover {}/* 当鼠标放到左侧区域的时候 */
///*-------------------------滑块区域------------------------------*/
//QScrollBar::handle:horizontal {	/* 滑块区域样式 */
//    background-color: #dfe0e1;
//border: 1px transprent;
//    border-radius: 2px;
//    margin-top: 3px;
//    margin-bottom: 3px;
//}
//QScrollBar::handle:horizontal:hover,
//                                  QScrollBar::handle:horizontal:pressed {/* 鼠标滑过滑块样式 */
//    background-color: #959596;
//    margin-top: 2px;
//    margin-bottom: 2px;
//    border-radius: 3px;
//}
///*-------------------------滑块下方区域------------------------------*/
//QScrollBar::add-page:horizontal {/* 滑块下面区域样式 */
//border: 1px solid transparent;
//    background-color: transparent;
//}
//QScrollBar::add-line:vertical:hover {}/* 当鼠标放到向下区域的时候 */
///*-------------------------向右侧按钮区域------------------------------*/
//QScrollBar::add-line:horizontal {/*右侧的按钮的背景*/
//    background-color: transparent;
//border: 1px solid transparent;
//width: 12px;
//    margin-right: 0px;
//    subcontrol-position: right;
//    subcontrol-origin: margin;
//}
//QScrollBar::down-arrow:horizontal {/* 向下箭头样式 */
//    background-color: transparent;
//height: 8px;
//width: 8px;
//}
//QScrollBar::down-arrow:horizontal:hover {/* 当鼠标放到向下箭头上的时候 */
//    border-image:url(:/triangle_right.png);
//}
