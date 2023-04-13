#include "amtlgraphicsview.h"



AmtlGraphicsView::AmtlGraphicsView(QWidget *parent)
    : QGraphicsView(parent),
      _zoomInBtn(nullptr),
      _zoomOutBtn(nullptr),
      _scaleRatio(1.0)
{
    this->initial();
    this->setMouseTracking(true);
}


void AmtlGraphicsView::initial()
{

    ViewControllUnit* cuni=new ViewControllUnit(this);
    cuni->move(10,10);

    connect(cuni,&ViewControllUnit::zoom,this,[=](qreal factor){
        this->scale(factor,factor);
    });

    //目前开启状态，等待解决残影问题
//    setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);

//    QGraphicsDropShadowEffect* effect=new QGraphicsDropShadowEffect(this);
//    effect->setBlurRadius(4);
//    effect->setOffset(0,0);
//    this->setGraphicsEffect(effect);

}


void AmtlGraphicsView::mousePressEvent(QMouseEvent *event)
{

//    qDebug()<<"AmtlGraphicsView::mousePressEvent"<<"Mouse Pressed"<<event;

    QGraphicsView::mousePressEvent(event);
}

void AmtlGraphicsView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void AmtlGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}
