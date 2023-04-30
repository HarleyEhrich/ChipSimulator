#include "AmtlGraphicsView.h"

AmtlGraphicsView::AmtlGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    this->init();

}

AmtlGraphicsView::~AmtlGraphicsView()
{

}

void AmtlGraphicsView::alignBottom()
{
    alignBottomImpl();
}

void AmtlGraphicsView::alignCenter()
{
    alignCenterImpl();
}

void AmtlGraphicsView::alignEnd()
{
    alignEndImpl();
}

void AmtlGraphicsView::alignMiddle()
{
    alignMiddleImpl();
}

void AmtlGraphicsView::alignStart()
{
    alignStartImpl();
}

void AmtlGraphicsView::alignTop()
{
    alignTopImpl();
}

void AmtlGraphicsView::init()
{
    _box = new QFrame();
    _boxLay = new QHBoxLayout();
    _container = new QWidget();
    _containerLay = new QHBoxLayout();

    _box->setObjectName("elec_view_box");
    _box->setLayout(_boxLay);


    _boxLay->setObjectName("elec_view_box_lay");
    _boxLay->setContentsMargins(0,0,0,0);
    _boxLay->addWidget(_container);

    _container->setObjectName("elec_view_container");
    _container->setLayout(_containerLay);

    _containerLay->setObjectName("elec_view_container_lay");
    _containerLay->setContentsMargins(0,0,0,0);
    _containerLay->addWidget(this);

    this->setMouseTracking(true);

    initViewControlWidget();

    setObjectName("elec_view");

    setDragMode(QGraphicsView::RubberBandDrag);

    setCacheMode(QGraphicsView::CacheBackground);

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //目前开启状态，等待解决残影问题--已解决
    //setViewportUpdateMode(QGraphicsView::ViewportUpdateMode::FullViewportUpdate);

//    _box->setStyleSheet("#elec_view_box,elec_view_box_lay{"
//                        "   background-color: transparent;"
//                        "   border: 0px;"
//                        "}"
//                        "#elec_view_container,elec_view_container_lay{/*Page Container*/"
//                        "   background-color: transparent;"
//                        "   border: 0px solid transparent;"
//                        "   border-radius: 0px;"
//                        "}"
//                        "/*特例电路图的样式表*/"
//                        "#elec_view{"
//                        "   background-color: rgb(253, 253, 253);"
//                        "   border: 1px solid transparent;"
//                        "   border-radius: 6px;"
//                        "   padding: 4px;"
//                        "}");

}

void AmtlGraphicsView::initViewControlWidget()
{
    _cuniWidget=new ViewControlUnitWidget(this);

    connect(_cuniWidget,&ViewControlUnitWidget::tellAlignBottom,this,&AmtlGraphicsView::alignBottom);
    connect(_cuniWidget,&ViewControlUnitWidget::tellAlignCenter,this,&AmtlGraphicsView::alignCenter);
    connect(_cuniWidget,&ViewControlUnitWidget::tellAlignEnd,this,&AmtlGraphicsView::alignEnd);
    connect(_cuniWidget,&ViewControlUnitWidget::tellAlignMiddle,this,&AmtlGraphicsView::alignMiddle);
    connect(_cuniWidget,&ViewControlUnitWidget::tellAlignStart,this,&AmtlGraphicsView::alignStart);
    connect(_cuniWidget,&ViewControlUnitWidget::tellAlignTop,this,&AmtlGraphicsView::alignTop);
    connect(_cuniWidget,&ViewControlUnitWidget::tellLockStatusChange,this,[=](bool locked){

        setLockViewImpl(locked);
    });
    connect(_cuniWidget,&ViewControlUnitWidget::tellModelChange,this,[=](bool selectMoveModel){
        setModelImpl(selectMoveModel);
    });
    connect(_cuniWidget,&ViewControlUnitWidget::tellZoom,this,[=](qreal factor){
        setZoomRatioImpl(factor);
    });
}

bool AmtlGraphicsView::isMoveAndSelect(){
    return SELECT_MOVE_MODEL == _moveAndSelectModel;
}

void AmtlGraphicsView::moveSceneCenterImpl(QPointF delta) {
    //如果是在缩放之后，调用的平移方法，那么平移量先要乘上缩放比，transform是view的变换矩阵，m11可以用为缩放比
    delta *= this->transform().m11();

    //修改锚点，调用缩放方法
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->centerOn(mapToScene(QPoint(this->viewport()->rect().width()/ 2 - delta.x(),
                                           this->viewport()->rect().height()/ 2 - delta.y())));
    this->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
}

bool AmtlGraphicsView::moveItemToPos(QGraphicsItem *targetItem, const QPoint &scenePos/*scene cor pos*/)
{
    auto* targetPtr = targetItem;

    while(targetPtr!=nullptr
           && 0 == (targetPtr->flags() & QGraphicsItem::ItemIsMovable)){
        targetPtr = targetPtr->parentItem();
    }

    if(targetPtr){
        //获取到其相对值，再转为scene
        targetPtr->setPos(targetPtr->mapToParent(targetPtr->mapFromScene(scenePos))/*获取到最终移动的item在其父中的坐标*/
                          + targetPtr->scenePos()-targetItem->scenePos()/*消除item与其父item之间的位置偏移*/);
        return true;
    }

    return  false;
}

void AmtlGraphicsView::alignBottomImpl()
{
    //选中的item按照第一个的item的水平底部对齐
    QList<QGraphicsItem*> selectItems = scene()->selectedItems();
    if(selectItems.size() <=1 ) return ;

    UniGraphicsItemObject* ptr = dynamic_cast<UniGraphicsItemObject*>(selectItems[0]);
    QPoint newScenePos;
    int alignTargetItemBottomY;
    if(ptr){
        newScenePos = ptr->getRealItemCenterScenePos().toPoint();
        alignTargetItemBottomY = newScenePos.y() + ptr->getRealBoudingRect().height()/2;
    }else{
        newScenePos = selectItems[0]->scenePos().toPoint();
        alignTargetItemBottomY = newScenePos.y() + selectItems[0]->boundingRect().height()/2;
    }

    UniGraphicsItemObject* curPtr=nullptr;
    for(auto& selectItem : selectItems){
        if(Q_UNLIKELY(selectItem==nullptr)) continue;//This is just to erase the warning tip
        curPtr = dynamic_cast<UniGraphicsItemObject*>(selectItem);
        if(curPtr){
            newScenePos.setX(curPtr->getRealItemCenterScenePos().x());
            newScenePos.setY(alignTargetItemBottomY - curPtr->getRealBoudingRect().height()/2);
        }else{
            newScenePos.setX(selectItem->scenePos().x());
            newScenePos.setY(alignTargetItemBottomY - selectItem->boundingRect().height()/2);
        }

        if(moveItemToPos(selectItem,newScenePos)==false){
            qDebug()<<DEBUGINFO<<"During the alignment operation, the target item or its parent node cannot be moved, and the alignment fails.";
        }
    }
}

void AmtlGraphicsView::alignCenterImpl()
{
    //选中的item按照第一个的item的中间垂直对齐
    QList<QGraphicsItem*> selectItems = scene()->selectedItems();
    if(selectItems.size() <=1 ) return ;

    UniGraphicsItemObject* ptr = dynamic_cast<UniGraphicsItemObject*>(selectItems[0]);
    QPoint newScenePos;
    if(ptr){
        newScenePos = ptr->getRealItemCenterScenePos().toPoint();
    }else{
        newScenePos = selectItems[0]->scenePos().toPoint();
    }

    UniGraphicsItemObject* curPtr=nullptr;
    for(auto& selectItem : selectItems){
        if(Q_UNLIKELY(selectItem==nullptr)) continue;//This is just to erase the warning tip
        curPtr = dynamic_cast<UniGraphicsItemObject*>(selectItem);
        if(curPtr){
            newScenePos.setY(curPtr->getRealItemCenterScenePos().y());
        }else{
            newScenePos.setY(selectItem->scenePos().y());
        }

        if(moveItemToPos(selectItem,newScenePos)==false){
            qDebug()<<DEBUGINFO<<"During the alignment operation, the target item or its parent node cannot be moved, and the alignment fails.";
        }
    }
}

void AmtlGraphicsView::alignEndImpl()
{
    //选中的item按照第一个的item的右侧垂直对齐
    QList<QGraphicsItem*> selectItems = scene()->selectedItems();
    if(selectItems.size() <=1 ) return ;

    UniGraphicsItemObject* ptr = dynamic_cast<UniGraphicsItemObject*>(selectItems[0]);
    QPoint newScenePos;
    int alignTargetItemEndX;
    if(ptr){
        newScenePos = ptr->getRealItemCenterScenePos().toPoint();
        alignTargetItemEndX = newScenePos.x() + ptr->getRealBoudingRect().width()/2;
    }else{
        newScenePos = selectItems[0]->scenePos().toPoint();
        alignTargetItemEndX = newScenePos.x() + selectItems[0]->boundingRect().width()/2;
    }

    UniGraphicsItemObject* curPtr=nullptr;
    for(auto& selectItem : selectItems){
        if(Q_UNLIKELY(selectItem==nullptr)) continue;//This is just to erase the warning tip
        curPtr = dynamic_cast<UniGraphicsItemObject*>(selectItem);
        if(curPtr){
            newScenePos.setX(alignTargetItemEndX - curPtr->getRealBoudingRect().width() / 2);
            newScenePos.setY(curPtr->getRealItemCenterScenePos().y());
        }else{
            newScenePos.setX(alignTargetItemEndX - selectItem->boundingRect().width() / 2);
            newScenePos.setY(selectItem->scenePos().y());
        }

        if(moveItemToPos(selectItem,newScenePos)==false){
            qDebug()<<DEBUGINFO<<"During the alignment operation, the target item or its parent node cannot be moved, and the alignment fails.";
        }
    }
}

void AmtlGraphicsView::alignMiddleImpl()
{
    //选中的item按照第一个的item的水平中间对齐
    QList<QGraphicsItem*> selectItems = scene()->selectedItems();
    if(selectItems.size() <=1 ) return ;

    UniGraphicsItemObject* ptr = dynamic_cast<UniGraphicsItemObject*>(selectItems[0]);
    QPoint newScenePos;
    if(ptr){
        newScenePos = ptr->getRealItemCenterScenePos().toPoint();
    }else{
        newScenePos = selectItems[0]->scenePos().toPoint();
    }

    UniGraphicsItemObject* curPtr=nullptr;
    for(auto& selectItem : selectItems){
        if(Q_UNLIKELY(selectItem==nullptr)) continue;//This is just to erase the warning tip
        curPtr = dynamic_cast<UniGraphicsItemObject*>(selectItem);
        if(curPtr){
            newScenePos.setX(curPtr->getRealItemCenterScenePos().x());
        }else{
            newScenePos.setX(selectItem->scenePos().x());
        }

        if(moveItemToPos(selectItem,newScenePos)==false){
            qDebug()<<DEBUGINFO<<"During the alignment operation, the target item or its parent node cannot be moved, and the alignment fails.";
        }
    }
}

void AmtlGraphicsView::alignStartImpl()
{
    //选中的item按照第一个的item的左侧垂直对齐
    QList<QGraphicsItem*> selectItems = scene()->selectedItems();
    if(selectItems.size() <=1 ) return ;

    UniGraphicsItemObject* ptr = dynamic_cast<UniGraphicsItemObject*>(selectItems[0]);
    QPoint newScenePos;
    int alignTargetItemStartX;
    if(ptr){
        newScenePos = ptr->getRealItemCenterScenePos().toPoint();
        alignTargetItemStartX = newScenePos.x() - ptr->getRealBoudingRect().width()/2;
    }else{
        newScenePos = selectItems[0]->scenePos().toPoint();
        alignTargetItemStartX = newScenePos.x() - selectItems[0]->boundingRect().width()/2;
    }

    UniGraphicsItemObject* curPtr=nullptr;
    for(auto& selectItem : selectItems){
        if(Q_UNLIKELY(selectItem==nullptr)) continue;//This is just to erase the warning tip
        curPtr = dynamic_cast<UniGraphicsItemObject*>(selectItem);
        if(curPtr){
            newScenePos.setX(alignTargetItemStartX + curPtr->getRealBoudingRect().width() / 2);
            newScenePos.setY(curPtr->getRealItemCenterScenePos().y());
        }else{
            newScenePos.setX(alignTargetItemStartX + selectItem->boundingRect().width() / 2);
            newScenePos.setY(selectItem->scenePos().y());
        }

        if(moveItemToPos(selectItem,newScenePos)==false){
            qDebug()<<DEBUGINFO<<"During the alignment operation, the target item or its parent node cannot be moved, and the alignment fails.";
        }
    }
}

void AmtlGraphicsView::alignTopImpl()
{
    //选中的item按照第一个的item的水平上侧对齐
    QList<QGraphicsItem*> selectItems = scene()->selectedItems();
    if(selectItems.size() <=1 ) return ;

    UniGraphicsItemObject* ptr = dynamic_cast<UniGraphicsItemObject*>(selectItems[0]);
    QPoint newScenePos;
    int alignTargetItemTopY;
    if(ptr){
        newScenePos = ptr->getRealItemCenterScenePos().toPoint();
        alignTargetItemTopY = newScenePos.y() - ptr->getRealBoudingRect().height()/2;
    }else{
        newScenePos = selectItems[0]->scenePos().toPoint();
        alignTargetItemTopY = newScenePos.y() - selectItems[0]->boundingRect().height()/2;
    }

    UniGraphicsItemObject* curPtr=nullptr;
    for(auto& selectItem : selectItems){
        if(Q_UNLIKELY(selectItem==nullptr)) continue;//This is just to erase the warning tip
        curPtr = dynamic_cast<UniGraphicsItemObject*>(selectItem);
        if(curPtr){
            newScenePos.setX(curPtr->getRealItemCenterScenePos().x());
            newScenePos.setY(alignTargetItemTopY + curPtr->getRealBoudingRect().height()/2);
        }else{
            newScenePos.setX(selectItem->scenePos().x());
            newScenePos.setY(alignTargetItemTopY + selectItem->boundingRect().height()/2);
        }

        if(moveItemToPos(selectItem,newScenePos)==false){
            qDebug()<<DEBUGINFO<<"During the alignment operation, the target item or its parent node cannot be moved, and the alignment fails.";
        }
    }
}

void AmtlGraphicsView::setLockViewImpl(const bool &locked)
{
    if(locked) scene()->clearSelection();
    setInteractive(!locked);//Locked-interactive false
    _viewLoked = locked;
}

void AmtlGraphicsView::setModelImpl(const bool &model)
{

    _moveAndSelectModel = model;
}

void AmtlGraphicsView::setZoomRatioImpl(const qreal &ratio)
{
    this->scale(ratio,ratio);
}

void AmtlGraphicsView::mouseMoveEvent(QMouseEvent *event)
{
    if(_mousePreessed){
        moveSceneCenterImpl(mapToScene(event->pos()) - mapToScene(_mousePressedDownPos));
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
    //Make the control unit widget stay at the center of the view.
    _cuniWidget->move(event->size().width()/2-_cuniWidget->width()/2,10);
}
