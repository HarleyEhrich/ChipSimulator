#include "UniLinkLine.h"

using AMTL::ZERO_POINT;
using AMTL::ZERO_POINTF;

//------------------------------------------------------------------------


//均为scene坐标
void UniLinkLine::nextItemPosChange(QPointF oldPos, QPointF newPos)
{
    Q_UNUSED(oldPos)
    Q_UNUSED(newPos)
}

void UniLinkLine::nextItemPosHasChanged()
{
    //更新
    updateStatus();
}

void UniLinkLine::lineSelectStatusChangeSlot(bool newStatus)
{
   setLineSelectedAllImpl(newStatus);
}

void UniLinkLine::lineVisiableChangeSlot(bool newStatus)
{
    setLineVisibleImpl(newStatus);
}


//Private slots for item self use, will not be called by the other item.
void UniLinkLine::unBind()
{
    unbindImpl();
}

void UniLinkLine::reverseLineVisiable()
{
    setLineVisibleImpl(!isLineVisibleImpl());
}

void UniLinkLine::reverseLineSelect()
{
    setLineSelectedAllImpl(!isSelectedLineAllItemImpl());
}

void UniLinkLine::addNodeAfterThisNode()
{
    addNodeAfterThisItemImpl();
}

void UniLinkLine::deleteThisNode()
{
    deleteThisItemImpl();
}


//------------------------------------------------------------------------


UniLinkLine::UniLinkLine(QGraphicsItem *parent)
    : UniGraphicsItemObject(nullptr,parent)
    ,_startEnd(true)
    ,_nextItem(nullptr)
    ,_preItem(nullptr)
    ,_shadowEffect(nullptr)
{
    this->initial();
}

UniLinkLine::~UniLinkLine(){
    //delete all the resource;
    _shadowEffect->deleteLater();
}

UniLinkLine *UniLinkLine::getNextItem() const
{
    return _nextItem;
}

UniLinkLine *UniLinkLine::getPreItem() const
{
    return _preItem;
}

bool UniLinkLine::sertItemAfterThis(UniLinkLine *item)
{
    //插入不允许传入空指针
    if(item==nullptr) return false;

    //link允许断开链接，也即可以传入一个空的指针来完成链路的断开--Bullshit, look what you write above you can't pass a nullptr to unlink this line, it's not allowed;
    linkNextItem(item);
    return true;
}


//------------------------------------------------------------------------


void UniLinkLine::initial(){
    //初始化画笔--全局实例
    this->initialSta();

    this->setFlags(ItemSendsGeometryChanges | ItemIsSelectable | ItemIsMovable | ItemIsFocusable);
    //initial shape and basic info
    updateStatus();

    //make sure this is above main widget
//    this->setZValue(AMTL::LINK_LINE_ZVALUE);

    _shadowEffect=new QGraphicsDropShadowEffect(this);
    _shadowEffect->setColor(__shadowColor);
    _shadowEffect->setOffset(0,0);
    _shadowEffect->setBlurRadius(__shadowBlurRadius);
    this->setGraphicsEffect(_shadowEffect);

}

//newPos为item内坐标
QPolygon UniLinkLine::gnerateItemLineCllBoundingPoly(const QPointF &newPos){
    QPolygon resPoly;

    QLineF line{mapFromParent(pos()),newPos};
    double offset = __norLineWitdh*3;
    double sinAlpha = qSin(line.angle()/180*M_PI), cosAlpha=qCos(line.angle()/180*M_PI);
    int sinOffset=sinAlpha*offset,cosOffset=cosAlpha*offset;
    int targetPointOffset = (newPos == ZERO_POINTF) ? 0 : 4;

    resPoly << QPoint{-sinOffset,-cosOffset};
    resPoly << QPoint{(int)newPos.x()-targetPointOffset*cosOffset-sinOffset,
                      (int)newPos.y()+targetPointOffset*sinOffset-cosOffset};
    resPoly << QPoint{(int)newPos.x()-targetPointOffset*cosOffset+sinOffset,
                      (int)newPos.y()+targetPointOffset*sinOffset+cosOffset};
    resPoly << QPoint{sinOffset,cosOffset};

    return resPoly;
}

//newPos为item内坐标
void UniLinkLine::gnerateItemPainterPath(const QPointF &newPos)
{
    //NOTE 注意到貌似这个会大大增加整个图元的绘制CPU占用率
    prepareGeometryChange();//Make sure the bouding rect will be right

    _shape.clear();
    _shape.addEllipse(__dotRect);
    _shape.addRect(__dotRectCll);//扩大一点命中范围
    _shape.moveTo(ZERO_POINTF);
    _shape.lineTo(newPos);
    _shape.moveTo(ZERO_POINTF);
    _shape.addPolygon(gnerateItemLineCllBoundingPoly(newPos));
    _shape.closeSubpath();

    //Expand this border make sure every thing can be coverd.
    _boudingRect = _shape.boundingRect();
    _boudingRect.moveTopLeft({_boudingRect.x()-6,_boudingRect.y()-8});
    _boudingRect.setHeight(_boudingRect.height()+16);
    _boudingRect.setWidth(_boudingRect.width()+12);
}

void UniLinkLine::updateStatus()
{
    if(this->_nextItem!=nullptr && this->_preItem!=nullptr){
        //当且仅当前后均有连线时才不是头
        this->_startEnd=false;
        gnerateItemPainterPath(mapFromScene(_nextItem->scenePos()));
    }else{
        this->_startEnd=true;
        if(isLineVisibleImpl()){
            //起始/末尾节点，并且线路可见，如果起始节点输入下一节点的位置映射到该节点的位置，否则为0
            gnerateItemPainterPath(_nextItem==nullptr ? ZERO_POINTF : mapFromScene(_nextItem->scenePos()));
        }else{
            gnerateItemPainterPath(ZERO_POINTF);
        }

    }

    this->update();
}

void UniLinkLine::setNextItem(UniLinkLine *newNextItem)
{
    if (_nextItem == newNextItem)
        return;

    auto oldItem=_nextItem;
    if(oldItem!=nullptr){
        //disconnect this to old item
        disconnect(oldItem,&UniLinkLine::positionChange,this,&UniLinkLine::nextItemPosChange);
        disconnect(oldItem,&UniLinkLine::positionHasChanged,this,&UniLinkLine::nextItemPosHasChanged);
//        disconnect(oldItem,&UniLinkLine::tellLineSelectStatusChange,this,&UniLinkLine::lineSelectStatusChangeSlot);
        disconnect(oldItem,&UniLinkLine::tellLineVisiableChange,this,&UniLinkLine::lineVisiableChangeSlot);
    }

    if(newNextItem!=nullptr){
        //connect this
        connect(newNextItem,&UniLinkLine::positionChange,this,&UniLinkLine::nextItemPosChange);
        connect(newNextItem,&UniLinkLine::positionHasChanged,this,&UniLinkLine::nextItemPosHasChanged);
//        connect(newNextItem,&UniLinkLine::tellLineSelectStatusChange,this,&UniLinkLine::lineSelectStatusChangeSlot);
        connect(newNextItem,&UniLinkLine::tellLineVisiableChange,this,&UniLinkLine::lineVisiableChangeSlot);
    }

    _nextItem = newNextItem;

    emit tellNextItemChanged();
}

void UniLinkLine::setPreItem(UniLinkLine *newPreItem)
{
    if (_preItem == newPreItem)
        return;

    auto oldItem=_preItem;
    if(oldItem!=nullptr){
//        disconnect(oldItem,&UniLinkLine::tellLineSelectStatusChange,this,&UniLinkLine::lineSelectStatusChangeSlot);
        disconnect(oldItem,&UniLinkLine::tellLineVisiableChange,this,&UniLinkLine::lineVisiableChangeSlot);
    }

    if(newPreItem!=nullptr){
        //connect this
//        connect(newPreItem,&UniLinkLine::tellLineSelectStatusChange,this,&UniLinkLine::lineSelectStatusChangeSlot);
        connect(newPreItem,&UniLinkLine::tellLineVisiableChange,this,&UniLinkLine::lineVisiableChangeSlot);
    }

    _preItem = newPreItem;

    emit tellPreItemChanged();
}

void UniLinkLine::linkNextItem(UniLinkLine *newItem)
{
    auto oldNextItem=_nextItem;
    this->setNextItem(newItem);
    if(newItem!=nullptr){
        newItem->setPreItem(this);
        newItem->setNextItem(oldNextItem);
        newItem->updateStatus();
    }

    if(oldNextItem!=nullptr){
        oldNextItem->setPreItem(newItem);
    }

    updateStatus();
}

//Only allow to delete not head and tail node
void UniLinkLine::takeThisNodeOutOfLine()
{
    UniLinkLine* curPreItem = _preItem;
    UniLinkLine* curNextItem=_nextItem;

    if(curPreItem==nullptr || curNextItem==nullptr){
        qWarning()<<"This node can't be take from this line, cause it's a line head or tail.";
        return;
    }

    this->setNextItem(nullptr);
    this->setPreItem(nullptr);

    curPreItem->setNextItem(curNextItem);
    curNextItem->setPreItem(curPreItem);

    curPreItem->updateStatus();
    curNextItem->updateStatus();
}

void UniLinkLine::unbindImpl()
{
    UniLinkLine* ptr = this;
    while(ptr->_preItem) ptr =ptr->_preItem;

    //Remid only line head emit this message will be recived by the point
    emit ptr->tellUnbind(ptr);//Notfy the control connection point to unbind this link
}

void UniLinkLine::addNodeAfterThisItemImpl(){
    UniLinkLine* sertItem;
    if(_nextItem == nullptr){
        if(Q_LIKELY(_preItem)){
            _preItem->addNodeAfterThisNode();
        }else{
            qFatal("There is an independent connection line node and no operation can be performed on it.");
            assert("There is an independent connection line node and no operation can be performed on it，Why would there got a sigle point line????");
        }

        return ;
    }

    sertItem  = new UniLinkLine();
    sertItem->setPos(
        mapToParent(
            mapFromScene(
                (_nextItem->scenePos().x()-scenePos().x())/2 + scenePos().x(),
                (_nextItem->scenePos().y()-scenePos().y())/2 + scenePos().y()
                )
            )
        );

    scene()->addItem(sertItem);
    sertItemAfterThis(sertItem);

    UniLinkLine* ptr = sertItem;
    while(ptr->_nextItem){
        ptr->stackBefore(ptr->_nextItem);
        ptr = ptr->_nextItem;
    }

    updateStatus();
}

bool UniLinkLine::isThisItemDeleteableImpl()
{
    int count=1;
    UniLinkLine* forwardPtr=_preItem,*backwardPtr=_nextItem;

    while(count <3 && (forwardPtr || backwardPtr)){
        if(forwardPtr){
            ++count;
            forwardPtr = forwardPtr->_preItem;
        }
        if(backwardPtr){
            ++count;
            backwardPtr = backwardPtr->_nextItem;
        }
    }

    return count==3;
}

void UniLinkLine::deleteThisItemImpl()
{
    if(Q_UNLIKELY(!isThisItemDeleteableImpl())){
        //todo emit a sig tell the connection point to delete this link
        unBind();
        return;
    }

    if(_startEnd==true){
        //Move this to next item or pre item
        if(_nextItem){
            setPos(mapToParent(mapFromScene(_nextItem->scenePos())));
            _nextItem->deleteThisNode();
        }else{
            setPos(mapToParent(mapFromScene(_preItem->scenePos())));
            _preItem->deleteThisNode();
        }
        this->updateStatus();
    }else{
        //将目前节点从连接线内去除，如果是最后一个，则删除数据点连接
        takeThisNodeOutOfLine();
        deleteLater();
    }
}

bool UniLinkLine::isLineVisibleImpl()
{
    if(_startEnd){
        if(_nextItem){
            return _nextItem->isVisible();
        }
        if(_preItem){
            return _preItem->isVisible();
        }
    }


    return isVisible();
}

void UniLinkLine::setLineVisibleImpl(bool visible)
{
    if(isLineVisibleImpl() == visible) return ;

    UniLinkLine* ptrPre = _preItem;
    UniLinkLine* ptrNext = _nextItem;

    while(ptrPre){
        ptrPre->setVisible(visible);
        ptrPre->updateStatus();
        ptrPre = ptrPre->_preItem;
    }

    while(ptrNext){
        ptrNext->setVisible(visible);
        ptrNext->updateStatus();
        ptrNext = ptrNext->_nextItem;
    }

    updateStatus();

    emit tellLineVisiableChange(visible);
}

//Only when all line node is all selected will return true
bool UniLinkLine::isSelectedLineAllItemImpl()
{
    if(isSelected()==false) return false;

    UniLinkLine* ptrPre = _preItem;
    UniLinkLine* ptrNext = _nextItem;

    while(ptrPre){
        if(ptrPre->isSelected()==false) return false;
        ptrPre = ptrPre->_preItem;
    }

    while(ptrNext){
        if(ptrNext->isSelected()==false) return false;
        ptrNext = ptrNext->_nextItem;
    }

    return true;
}

void UniLinkLine::setLineSelectedAllImpl(bool selected)
{
    //This means this line is been seletc all
    if(isSelectedLineAllItemImpl() == selected) return ;

    UniLinkLine* ptrPre = _preItem;
    UniLinkLine* ptrNext = _nextItem;

    while(ptrPre){
        ptrPre->setSelected(selected);
        ptrPre->update();
        ptrPre = ptrPre->_preItem;
    }

    while(ptrNext){
        ptrNext->setSelected(selected);
        ptrNext->update();//No shape change, no need to update shape.
        ptrNext = ptrNext->_nextItem;
    }

    emit tellLineSelectStatusChange(selected);
}


//------------------------------------------------------------------------
QPointF UniLinkLine::getRealItemCenterScenePos()
{
    return mapToScene(AMTL::ZERO_POINTF);
}

QRectF UniLinkLine::getRealBoudingRect()
{
    return __dotRect;
}

QRectF UniLinkLine::boundingRect() const
{
    return _boudingRect;
}

QPainterPath UniLinkLine::shape() const
{
    return _shape;
}

void UniLinkLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(_startEnd==false && isVisible() == false){
        //仅当不绘制线路被设置且不为头尾节点时不绘制线路
        return ;
    }

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);//抗锯齿

#ifdef QT_DEBUG
//    painter->setPen(Qt::green);
//    painter->drawRect(_boudingRect);
//    painter->setPen(Qt::blue);
//    painter->drawRect(_shape.boundingRect());
//    painter->drawPath(_shape);
#endif

    if(this->_nextItem!=nullptr && this->_nextItem->isVisible()){//连接线
        painter->setPen(UniLinkLine::__lineNorPen);
        painter->setBrush(UniLinkLine::__lineNorBru);
        painter->drawLine(ZERO_POINT,mapFromScene(_nextItem->pos()));

        if(isSelected()){//active line assit signal
            painter->setPen(__lineSelectPen);
            painter->setBrush(__lineSelectBrush);
            painter->drawLine(ZERO_POINT,mapFromScene(_nextItem->pos()));
        }
    }

    if(isSelected()==true ){//选中圆形绘制
        painter->setPen(__dotActPen);
    }else{
        painter->setPen(__dotPen);
    }
    painter->setBrush(__dotBrush);
    painter->drawEllipse(__dotRect);

    painter->restore();
}

void UniLinkLine::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsView* view= qobject_cast<QGraphicsView*>(event->widget()->parentWidget());
    if(view == nullptr){
        qWarning()<<"The graphics view component does not exist and the context menu cannot be generated.";
        return;
    }

    //Make sure the item will be setected
    if(isSelected()==false){
        setSelected(true);
        this->update();
    }


    QMenu* menu=new QMenu(view);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(menu);
    QAction* unbindAct = new QAction(menu);
    QAction* changeLineVisableAct = new QAction(menu);
    QAction* selectAllLineAct = new QAction(menu);
    QAction* addItemNodeAfterThisAct = new QAction(menu);


    unbindAct->setText(tr("取消端点链接[Ctrl Del]"));
    unbindAct->setToolTip(tr("将该连接线所链接的两个数据点之间链接删除"));

    if(isLineVisibleImpl()){
        changeLineVisableAct->setText(tr("隐藏连线"));
    }else{
        changeLineVisableAct->setText(tr("显示连线"));
    }
    changeLineVisableAct->setToolTip(tr("改变连接线之间的可视性"));

    addItemNodeAfterThisAct->setText(tr("添加节点 "));
    addItemNodeAfterThisAct->setToolTip(tr("在该节点之后添加一个节点 [双击]"));
    selectAllLineAct->setText(tr("选择全线"));
    selectAllLineAct->setToolTip(tr("将整条连接线全部选中 [Right Button+ Ctrl]"));

    shadow->setOffset(0, 0);
    shadow->setColor(QColor(68, 68, 68));
    shadow->setBlurRadius(10);
    menu->setToolTipsVisible(true);
    menu->setToolTipDuration(2000);
    menu->setWindowFlags(menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground,true);
    menu->setGraphicsEffect(shadow);
    menu->setStyleSheet("QMenu{color:black;background-color:white; border-radius:4px;padding:6px;margin:8px;}"
                        "QMenu::item:text{ padding-left:8px;padding-right:8px; padding-top: 8px; padding-bottom: 8px;}"
                        "QMenu::item:selected{ color:#ffffff;background-color: #ea5455; border-radius:4px;}"
                        "QMenu::separator{height:1px;background:#bbbbbb;margin:5px;margin-left:10px;margin-right:10px;}");

    menu->addAction(unbindAct);
    menu->addSeparator();
    menu->addAction(changeLineVisableAct);
    menu->addAction(selectAllLineAct);
    menu->addAction(addItemNodeAfterThisAct);

    connect(menu,&QMenu::aboutToHide,menu,&QMenu::deleteLater);

    connect(unbindAct,&QAction::triggered,this,&UniLinkLine::unBind);
    connect(changeLineVisableAct,&QAction::triggered,this,&UniLinkLine::reverseLineVisiable);
    connect(selectAllLineAct,&QAction::triggered,this,&UniLinkLine::reverseLineSelect);
    connect(addItemNodeAfterThisAct,&QAction::triggered,this,&UniLinkLine::addNodeAfterThisNode);

    if(isThisItemDeleteableImpl()){
        QAction* deleteThisLineNodeAct = new QAction(menu);
        deleteThisLineNodeAct->setText(tr("删除该点 [Del]"));
        deleteThisLineNodeAct->setToolTip(tr("将该节点从连接线上删除，注意，如果少于2个点将会删除链接"));
        menu->addAction(deleteThisLineNodeAct);
        connect(deleteThisLineNodeAct,&QAction::triggered,this,&UniLinkLine::deleteThisNode);
    }

    //Bug will out put UpdateLayeredWindowIndirect failed for ptDst=(868, 552), size=(123x121), dirty=(143x141 -10, -10) (参数错误。)
    menu->exec(QCursor::pos());
}

QVariant UniLinkLine::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change==GraphicsItemChange::ItemPositionChange){
        //value == new position for this item
        //notify pre item this postion is change
        emit positionChange(scenePos(),mapToScene(mapFromParent(value.value<QPointF>())));

    }

    if(change == GraphicsItemChange::ItemPositionHasChanged){
        emit positionHasChanged();
        updateStatus();//由于本身变化，在更新形状时需要这个节点的坐标，在此处更新。
    }

    if(change == GraphicsItemChange::ItemVisibleChange){
        //Make sure the head will always display.
        if(value.toBool() == false && _startEnd){
            return {true};
        }
    }

    return value;
}

void UniLinkLine::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace){
        if(!isSelectedLineAllItemImpl() && event->modifiers() != Qt::ControlModifier)deleteThisItemImpl();
        else unbindImpl();
    }

    QGraphicsItem::keyPressEvent(event);
}

void UniLinkLine::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton && (flags() & ItemIsSelectable)){
        //双击添加点
        addNodeAfterThisItemImpl();
    }
    QGraphicsItem::mouseDoubleClickEvent(event);
}

void UniLinkLine::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(_doMove){
        QGraphicsItem::mouseMoveEvent(event);
    }else{
        //redispatch this event to another item in the bouding rect area
        event->ignore();
    }
}

void UniLinkLine::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::RightButton && (flags() & ItemIsSelectable)){
        bool hideAllLine = (event->modifiers() & Qt::ShiftModifier) != 0;
        if(hideAllLine){
            setLineVisibleImpl(!isLineVisibleImpl());
        }

        bool selectAll = (event->modifiers() & Qt::ControlModifier) != 0;
        if(selectAll){
            //右键直接选中全部线
            //select all line or cancel all line
            setLineSelectedAllImpl(!isSelectedLineAllItemImpl());
        }
    }

    if(event->modifiers() & Qt::ShiftModifier && event->button() == Qt::LeftButton){
        event->setModifiers(Qt::ControlModifier | event->modifiers());//将shift转为CTRL，保证shift的使用
    }

    QGraphicsItem::mousePressEvent(event);

    if(__dotRectCll.contains(event->pos())){
        _doMove=true;
    }else{
        _doMove=false;
    }

    if(!_shape.contains(event->pos()) && isSelected()){
        setSelected(false);
        this->update();
    }
}

void UniLinkLine::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier && event->button() == Qt::LeftButton){
        event->setModifiers(Qt::ControlModifier | event->modifiers());//将shift转为CTRL，保证shift的使用
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

//Pass the scene pos
QList<UniLinkLine *> UniLinkLine::creatLineWithPoints(const QList<QPoint> &posVec)
{
    QList<UniLinkLine *> res;

    if(posVec.size()<=0){
        return res;
    }

    UniLinkLine* header=new UniLinkLine();
    auto curItem=header;

    auto iter=posVec.begin();
    header->setPos(*iter);//Here must be in the scene, got no parent
    res.append(header);
    ++iter;

    while(iter!=posVec.end()){
        UniLinkLine* newItem=new UniLinkLine();
        newItem->setPos(*iter);
        curItem->sertItemAfterThis(newItem);
        curItem=newItem;
        ++iter;
    }

    res.append(curItem);

    return res;
}

QList<UniLinkLine *> UniLinkLine::creatLineWithText(const QStringList &list)
{
    QList<QPoint> points;
//    bool ok;
    for(auto item=list.begin();item!=list.end();item++){
        QPoint t;
        t.setX((*item).toInt());
        ++item;
        t.setY((*item).toInt());

        points.append(t);
    }
    return creatLineWithPoints(points);
}

QStringList UniLinkLine::storeLineToText(UniLinkLine *lineHead)
{
    QStringList res;
    auto tptr=lineHead;
    while(tptr!=nullptr){
        res << QString::number(tptr->scenePos().toPoint().x())<<QString::number(tptr->scenePos().toPoint().y());
        tptr=tptr->_nextItem;
    }
    return res;
}

//------------------------------------------------------------------------


void UniLinkLine::initialSta()
{
    static bool painterInitial=false;//画笔数据是否初始化

    if(painterInitial==true) return;

    __norLineWitdh=2;
    __activeLineWidth=2;
    __dotLineWidth=2;
    __dotWhSize=10;//节点的大小
    __shadowBlurRadius=6;

    __norColor.setRgb(66, 80, 102);
    __activeColor=Qt::white;

    __dotLineColor.setRgb(22, 133, 169);
    __dotActLineColor.setRgb(255,255,255);
    __dotBodyColor.setRgb(22, 133, 169);

    __shadowColor=__norColor;

    //dot rect
    __dotRect.setTopLeft(QPointF{(qreal)(-__dotWhSize /2),(qreal)(-__dotWhSize/2)});
    __dotRect.setWidth(__dotWhSize);
    __dotRect.setHeight(__dotWhSize);

    __dotRectCll.setTopLeft({-(qreal)__dotWhSize,-(qreal)__dotWhSize});
    __dotRectCll.setWidth(__dotWhSize*2);
    __dotRectCll.setHeight(__dotWhSize*2);

    //连线画笔
    __lineNorPen.setColor(__norColor);
    __lineNorPen.setWidth(__norLineWitdh);
    __lineNorPen.setCapStyle(Qt::PenCapStyle::RoundCap);
    __lineNorPen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);

    __lineNorBru.setStyle(Qt::BrushStyle::SolidPattern);
    __lineNorBru.setColor(UniLinkLine::__norColor);

    //选中后辅助线
    __lineSelectPen.setColor(__activeColor);
    __lineSelectPen.setWidth(__activeLineWidth);
    __lineSelectPen.setStyle(Qt::PenStyle::DashLine);
    __lineSelectPen.setCapStyle(Qt::PenCapStyle::RoundCap);
    __lineSelectPen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);

    __lineSelectBrush.setStyle(Qt::BrushStyle::SolidPattern);
    __lineSelectBrush.setColor(__activeColor);

    //dot
    __dotActPen.setColor(__dotActLineColor);
    __dotActPen.setWidth(__dotLineWidth);
    __dotActPen.setCapStyle(Qt::PenCapStyle::RoundCap);
    __dotActPen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);

    __dotPen.setColor(__dotLineColor);
    __dotPen.setWidth(__dotLineWidth);
    __dotPen.setCapStyle(Qt::PenCapStyle::RoundCap);
    __dotPen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);

    __dotBrush.setStyle(Qt::BrushStyle::SolidPattern);
    __dotBrush.setColor(__dotBodyColor);

    painterInitial=true;
}


//是否初始化
//bool UniLinkLine::__painterInitial=false;
//int type
//int UniLinkLine::__norLineWitdh;
//int UniLinkLine::__activeLineWidth;
//int UniLinkLine::__dotLineWidth;
//int UniLinkLine::__dotWhSize;
//int UniLinkLine::__shadowBlurRadius;
////color
//QColor UniLinkLine::__norColor;
//QColor UniLinkLine::__activeColor;
//QColor UniLinkLine::__dotActLineColor;
//QColor UniLinkLine::__dotLineColor;
//QColor UniLinkLine::__dotBodyColor;
//QColor UniLinkLine::__shadowColor;
//QPen UniLinkLine::__lineNorPen;
//QBrush UniLinkLine::__lineNorBru;//这个稍微粗一点，用来遮住
//QPen UniLinkLine::__lineSelectPen;
//QBrush UniLinkLine::__lineSelectBrush;
//QRectF UniLinkLine::__dotRect;
//QRectF UniLinkLine::__dotRectCll;
//QPen UniLinkLine::__dotActPen;
//QPen UniLinkLine::__dotPen;
//QBrush UniLinkLine::__dotBrush;



