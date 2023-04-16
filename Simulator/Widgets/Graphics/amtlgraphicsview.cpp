#include "amtlgraphicsview.h"

#include <QResizeEvent>



AmtlGraphicsView::AmtlGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->init();

}

AmtlGraphicsView::~AmtlGraphicsView()
{

}

void AmtlGraphicsView::init()
{
    this->setMouseTracking(true);

    _cuniWidget=new ViewControllUnit(this);

    connect(_cuniWidget,&ViewControllUnit::tellLockStatusChange,this,[=](bool locked){
        _viewLoked = locked;
    });

    connect(_cuniWidget,&ViewControllUnit::tellModelChange,this,[=](bool selectMoveModel){
        _moveAndSelectModel = selectMoveModel;
    });

    connect(_cuniWidget,&ViewControllUnit::tellZoom,this,[=](qreal factor){
        this->scale(factor,factor);
    });


    //目前开启状态，等待解决残影问题--已解决
//    setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);

}

void AmtlGraphicsView::moveCenterImpl(QPointF delta) {
    //如果是在缩放之后，调用的平移方法，那么平移量先要乘上缩放比，transform是view的变换矩阵，m11可以用为缩放比
    delta *= this->transform().m11();

    //修改锚点，调用缩放方法
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->centerOn(mapToScene(QPoint(this->viewport()->rect().width()/ 2 - delta.x(),
                                           this->viewport()->rect().height()/ 2 - delta.y())));
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

void AmtlGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(_mousePreessed){
        setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
        moveCenterImpl(mapToScene(event->pos()) - mapToScene(_mousePressedDownPos));
//        qDebug()<<"Center change"<<_centerScenePos - (event->pos() - _mousePressedDownPos);
        _mousePressedDownPos = event->pos();
    }else{
        QGraphicsView::mouseMoveEvent(event);
    }
}

void AmtlGraphicsView::mousePressEvent(QMouseEvent *event)
{
    if(_moveAndSelectModel){
        //Move and select
        if(event->button() != Qt::MiddleButton){
            //Pass this to the item
            QGraphicsView::mousePressEvent(event);
            return ;
        }
    }

    //Wait Move this view
    _mousePreessed = true;
    _mousePressedDownPos = event->pos();
    // 记录鼠标按下时的中心点坐标
    _centerScenePos = mapToScene(width()/2, height()/2);
}

void AmtlGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    _mousePreessed =false;
    QGraphicsView::mouseReleaseEvent(event);
}

void AmtlGraphicsView::resizeEvent(QResizeEvent *event)
{
    QGraphicsView::resizeEvent(event);
    _cuniWidget->move(event->size().width()/2-_cuniWidget->width()/2,10);//Make the control unit widget stay at the center of the view.
}
