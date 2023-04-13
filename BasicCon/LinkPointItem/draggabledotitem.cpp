#include "draggabledotitem.h"

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QStyleOptionGraphicsItem>


//笔刷定义
const QBrush DraggableDotItem::_mainBodybrush{QColor{22, 133, 169}};
const QPen DraggableDotItem::_mainBodypen{QColor{255,255,255}};
const QPen DraggableDotItem::_linkLinePen{Qt::black};
const QPen DraggableDotItem::_selectBorderPen{Qt::DashDotLine};
const QPen DraggableDotItem::_waitLinkBorderPen{QColor{252, 85, 49}};

const qreal DraggableDotItem::_dotWidthHeight=64.0;//16
const qreal DraggableDotItem::_negHalfDotWidthHeight=-32.0;


DraggableDotItem::DraggableDotItem(QGraphicsItem *parent)
    : QGraphicsItem(parent),
      _curDire(amtl::NEXTDRAGGABLEITEMDIREACTION::NO_DIREACTION),
      _curPPath(DraggableDotItem::getPainterPath(_curDire)),
      _mainBodyBoudingRect(_negHalfDotWidthHeight,_negHalfDotWidthHeight,_dotWidthHeight,_dotWidthHeight),
      _boudingRect(_negHalfDotWidthHeight,_negHalfDotWidthHeight,_dotWidthHeight,_dotWidthHeight),
      _visible(true),
      _itemCustomMove(true),
      _mousePressed(false),
      _waitLink(false),
      _mpReleativeOri(),
      _nextItem(nullptr),
      _preItem(nullptr)
{
    this->init();
}


DraggableDotItem::~DraggableDotItem()
{

}



bool DraggableDotItem::visible() const
{
    return _visible;
}

void DraggableDotItem::setVisible(bool newVisible)
{
    _visible = newVisible;
}

bool DraggableDotItem::itemCustomMove() const
{
    return _itemCustomMove;
}

void DraggableDotItem::setItemCustomMove(bool itemCustomMove)
{
    _itemCustomMove = itemCustomMove;
}

bool DraggableDotItem::waitLink() const
{
    return _waitLink;
}

void DraggableDotItem::setWaitLink(bool newWaitLink)
{
    _waitLink = newWaitLink;
}



void DraggableDotItem::init()
{
    this->setFlags(ItemIsSelectable | ItemIsMovable | ItemSendsGeometryChanges );
}

const QPainterPath &DraggableDotItem::getPainterPath(amtl::NEXTDRAGGABLEITEMDIREACTION dire)
{
    static bool isPathInit=false;

    static QPainterPath _noOrenPath;
    static QPainterPath _upOrenPath;
    static QPainterPath _downOrenPath;
    static QPainterPath _leftOrenPath;
    static QPainterPath _rightOrenPath;

    if(isPathInit==false){
        //正常的为一个圆形，坐标起始点为图元一半大小的左上角点，圆的大小为图元的大小。
        _noOrenPath.addEllipse(DraggableDotItem::_negHalfDotWidthHeight,\
                               DraggableDotItem::_negHalfDotWidthHeight,\
                               DraggableDotItem::_dotWidthHeight,\
                               DraggableDotItem::_dotWidthHeight);
        _noOrenPath.closeSubpath();


        //上开口，下一个图元的scene中y的值小于目前图元scene的y的值，两者x值相同
        _upOrenPath.moveTo(-DraggableDotItem::_negHalfDotWidthHeight,0);
        _upOrenPath.arcTo(DraggableDotItem::_negHalfDotWidthHeight,\
                          DraggableDotItem::_negHalfDotWidthHeight,\
                          DraggableDotItem::_dotWidthHeight,\
                          DraggableDotItem::_dotWidthHeight,\
                          0,
                          -180);
        _upOrenPath.lineTo(0, DraggableDotItem::_negHalfDotWidthHeight);
        _upOrenPath.lineTo(-DraggableDotItem::_negHalfDotWidthHeight,0);

        _upOrenPath.closeSubpath();

        //下开口，下一个图元的scene中y的值大于目前图元scene的y的值，两者x值相同
        _downOrenPath.moveTo(-DraggableDotItem::_negHalfDotWidthHeight,0);
        _downOrenPath.arcTo(DraggableDotItem::_negHalfDotWidthHeight,\
                            DraggableDotItem::_negHalfDotWidthHeight,\
                            DraggableDotItem::_dotWidthHeight,\
                            DraggableDotItem::_dotWidthHeight,\
                            0,
                            180);
        _downOrenPath.lineTo(0, -DraggableDotItem::_negHalfDotWidthHeight);
        _downOrenPath.lineTo(-DraggableDotItem::_negHalfDotWidthHeight,0);
        _downOrenPath.closeSubpath();

        //左开口
        _leftOrenPath.moveTo(0, DraggableDotItem::_negHalfDotWidthHeight);
        _leftOrenPath.arcTo(DraggableDotItem::_negHalfDotWidthHeight,\
                            DraggableDotItem::_negHalfDotWidthHeight,\
                            DraggableDotItem::_dotWidthHeight,\
                            DraggableDotItem::_dotWidthHeight,\
                            90,
                            -180);
        _leftOrenPath.lineTo(DraggableDotItem::_negHalfDotWidthHeight,0);
        _leftOrenPath.lineTo(0, DraggableDotItem::_negHalfDotWidthHeight);
        _leftOrenPath.closeSubpath();

        //右开口
        _rightOrenPath.moveTo(0, DraggableDotItem::_negHalfDotWidthHeight);
        _rightOrenPath.arcTo(DraggableDotItem::_negHalfDotWidthHeight,\
                             DraggableDotItem::_negHalfDotWidthHeight,\
                             DraggableDotItem::_dotWidthHeight,\
                             DraggableDotItem::_dotWidthHeight,\
                             90,
                             180);
        _rightOrenPath.lineTo(-DraggableDotItem::_negHalfDotWidthHeight,0);
        _rightOrenPath.lineTo(0, DraggableDotItem::_negHalfDotWidthHeight);
        _rightOrenPath.closeSubpath();

        isPathInit=true;
    }

    switch (dire){
    case amtl::UP:{
        return _upOrenPath;
    }
    case amtl::DOWN:{
        return _downOrenPath;
    }
    case amtl::LEFT:{
        return _leftOrenPath;
    }
    case amtl::RIGHT:{
        return _rightOrenPath;
    }
    default:
        return _noOrenPath;
    }
}

DraggableDotItem *DraggableDotItem::creatNewInstance()
{
    //Creat new item instance
    auto newItem=new DraggableDotItem();
    //Add item to this scene
    this->scene()->addItem(newItem);
    return newItem;
}

void DraggableDotItem::creatItemAfter()
{
    auto newPos=this->scenePos();
    switch (_curDire){
    case amtl::NEXTDRAGGABLEITEMDIREACTION::NO_DIREACTION:{
        //Default show at this item right 8 size position
        newPos.setX(newPos.x()+_dotWidthHeight*8);
        break;
    }
    case amtl::NEXTDRAGGABLEITEMDIREACTION::UP      :
    case amtl::NEXTDRAGGABLEITEMDIREACTION::DOWN    :
    case amtl::NEXTDRAGGABLEITEMDIREACTION::LEFT    :
    case amtl::NEXTDRAGGABLEITEMDIREACTION::RIGHT   :{
        newPos.setX((this->_nextItem->scenePos().x()-this->scenePos().x())/2+newPos.x());
        newPos.setY((this->_nextItem->scenePos().y()-this->scenePos().y())/2+newPos.y());
    }
    }
    auto newItem=this->creatNewInstance();
    newItem->setNewPos(newPos,newItem->scenePos());
    this->sertDotItemAfter(newItem);
}

void DraggableDotItem::setNewPos(const QPointF &newPos, const QPointF &oldPos, amtl::SIG_TRANS_DIRECTION sigTransDir)
{
    if(newPos==oldPos){
        return ;
    }

    this->setPos(newPos);

    this->updateDire();
    this->calBoRec();

    this->update();

    switch (sigTransDir){
    case amtl::SIG_TRANS_DIRECTION::NONE : {
        break;
    }
    case amtl::SIG_TRANS_DIRECTION::PRE : {
        qDebug()<<"DraggableDotItem::setNewPos: pre";

        emit nItemPostionChange(newPos, oldPos);//Make sure pre item can update link line
        break;
    }
    case amtl::SIG_TRANS_DIRECTION::NEXT : {
        qDebug()<<"DraggableDotItem::setNewPos: next";

        emit pItemPostionChange(newPos, oldPos);
        break;
    }
    case amtl::SIG_TRANS_DIRECTION::BOTH : {
        qDebug()<<"DraggableDotItem::setNewPos: both"<<receivers(SIGNAL(nItemPostionChange(QPointF,QPointF)));
        emit nItemPostionChange(newPos, oldPos);//Make sure pre item can update link line


        qDebug()<<"DraggableDotItem::setNewPos: both"<<receivers(SIGNAL(pItemPostionChange(QPointF,QPointF)));
        emit pItemPostionChange(newPos, oldPos);


        break;
    }
    }
}

void DraggableDotItem::setNextItem(DraggableDotItem *newItem)
{
    if(newItem==this->_nextItem){
        return ;
    }
    if(this->_nextItem!=nullptr){
        //断开下一连接点的信号链接
        disconnect(_nextItem,&DraggableDotItem::nItemPostionChange,this,&DraggableDotItem::nextItemPostionChange);
    }
    this->_nextItem=newItem;
    if(newItem!=nullptr){
        //链接上新的信号
        connect(newItem,&DraggableDotItem::nItemPostionChange,this,&DraggableDotItem::nextItemPostionChange);
    }
    this->updateDire();
    this->calBoRec();//重新计算边界
    this->update();
}

void DraggableDotItem::setPreItem(DraggableDotItem *newItem)
{
    if(newItem==this->_preItem){
        return ;
    }
    if(this->_preItem!=nullptr){
        disconnect(this->_preItem,&DraggableDotItem::pItemPostionChange,this,&DraggableDotItem::preItemPositionChange);
    }
    this->_preItem=newItem;
    if(newItem!=nullptr){
        connect(newItem,&DraggableDotItem::pItemPostionChange,this,&DraggableDotItem::preItemPositionChange);
    }

}

void DraggableDotItem::calBoRec()
{
    _boudingRect=_mainBodyBoudingRect;

    if(this->_nextItem==nullptr){
        return ;
    }

    _boudingRect.setWidth(abs(this->_nextItem->scenePos().x()-this->scenePos().x())+_dotWidthHeight);
    _boudingRect.setHeight(abs(this->_nextItem->scenePos().y()-this->scenePos().y())+_dotWidthHeight);

    switch (this->_curDire) {
    case amtl::NEXTDRAGGABLEITEMDIREACTION::NO_DIREACTION:{
        //This should be something i will quiet not happy to see.
        //Means my direction set got a bug.

#ifdef QT_DEBUG
        qDebug()<<"DraggableDotItem::calBoRec : [Error] May got a bug here.";
#endif
        //Make a log
        emit msg("[Error] May got a bug here. From: DraggableDotItem::calBoRec()");
        break;
    }
    case amtl::NEXTDRAGGABLEITEMDIREACTION::UP :{
        _boudingRect.moveBottomLeft(_mainBodyBoudingRect.bottomLeft());
        break;
    }
    case amtl::NEXTDRAGGABLEITEMDIREACTION::DOWN :{
        _boudingRect.moveTopRight(_mainBodyBoudingRect.topRight());
        break;
    }
    case amtl::NEXTDRAGGABLEITEMDIREACTION::LEFT :{
        _boudingRect.moveBottomRight(_mainBodyBoudingRect.bottomRight());
        break;
    }
    case amtl::NEXTDRAGGABLEITEMDIREACTION::RIGHT :{
        _boudingRect.moveTo(_mainBodyBoudingRect.topLeft());
        break;
    }
    }
}



void DraggableDotItem::updateDire()
{
    if(this->_nextItem==nullptr){
        this->_curDire=amtl::NEXTDRAGGABLEITEMDIREACTION::NO_DIREACTION;
    }else{

        if(this->scenePos().x() <= this->_nextItem->scenePos().x()){
            if(this->scenePos().y() <= this->_nextItem->scenePos().y()){
                //Right
                this->_curDire=amtl::NEXTDRAGGABLEITEMDIREACTION::RIGHT;
            }else{
                //Up
                this->_curDire=amtl::NEXTDRAGGABLEITEMDIREACTION::UP;
            }
        }else{
            if(this->scenePos().y() <= this->_nextItem->scenePos().y()){
                //Down
                this->_curDire=amtl::NEXTDRAGGABLEITEMDIREACTION::DOWN;
            }else{
                //Left
                this->_curDire=amtl::NEXTDRAGGABLEITEMDIREACTION::LEFT;
            }
        }
    }

    //Get new path
    this->_curPPath=this->getPainterPath(this->_curDire);

}

const DraggableDotItem * const DraggableDotItem::getPreviousDraggableItem()
{
    return this->_preItem;
}

const DraggableDotItem * const DraggableDotItem::getNextDraggableItem()
{
    return this->_nextItem;
}

bool DraggableDotItem::sertDotItemAfter(DraggableDotItem *newItem)
{
    this->blockSignals(true);

    if(newItem && (newItem->_preItem!=nullptr || newItem->_nextItem!=nullptr )){
        //Shall not pass a already linkred dot item in.
        return false;
    }

    auto oldItem=this->_nextItem;

    if(oldItem!=nullptr) {
        oldItem->setPreItem(newItem);
    }

    this->setNextItem(newItem);

    if(newItem!=nullptr) {
        newItem->setPreItem(this);
        newItem->setNextItem(oldItem);
    }

    this->blockSignals(false);
}

bool DraggableDotItem::deleteThisItem()
{
    this->takeOutItemFromChain();
    this->deleteLater();
    return true;
}

bool DraggableDotItem::takeOutItemFromChain()
{
    this->blockSignals(true);

    if(_preItem!=nullptr) {
        this->_preItem->setNextItem(this->_nextItem);
    }

    if(_nextItem!=nullptr) {
        this->_nextItem->setPreItem(this->_preItem);
    }

    this->blockSignals(false);

    return true;
}

void DraggableDotItem::nextItemPostionChange(QPointF newPos,QPointF oldPos)
{
    this->updateDire();//避免因为界限处变方向产生问题
    this->calBoRec();
    this->update();
}

void DraggableDotItem::preItemPositionChange(QPointF newPos, QPointF oldPos)
{
    this->updateDire();//避免因为界限处变方向产生问题
    this->calBoRec();
    this->update();
}



void DraggableDotItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(_visible==false){
        //不可视模式，忽略绘制
        return ;
    }

    //TODO 选中效果展示，颜色调整
    painter->save();

    //抗锯齿
    painter->setRenderHint(QPainter::Antialiasing);

    //    painter->setPen(this->_selectBorderPen);
    //    painter->drawRect(this->_boudingRect);

    //选中了就画框
    if(this->isSelected()==true){
        painter->setPen(this->_selectBorderPen);
        painter->drawRect(this->_mainBodyBoudingRect);
    }

    if(_waitLink){
        painter->setPen(this->_waitLinkBorderPen);
        painter->drawRect(this->_mainBodyBoudingRect);
    }

    //与下一点的连接线
    if(this->_nextItem!=nullptr){
        painter->setPen(_linkLinePen);
        painter->drawLine(mapFromScene(this->scenePos()),mapFromScene(this->_nextItem->scenePos()));
    }

    painter->setBrush(this->_mainBodybrush);
    painter->setPen(this->_mainBodypen);

    painter->drawPath(this->_curPPath);

    painter->restore();
}

QRectF DraggableDotItem::boundingRect() const
{
    return _boudingRect;
}

void DraggableDotItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(_mainBodyBoudingRect.contains(event->pos())){//处于图元可点击点
            //清除scene中其它item选中模式为假，包含所有的控件，保证在选中线点时，只能有点被选中
            this->scene()->clearSelection();
            //设置选中模式
            this->setSelected(true);
            this->_mousePressed=true;
            this->_mpReleativeOri=this->scenePos()-event->scenePos();
        }else{
            //Un Process this event
            event->ignore();
        }
    }else if(event->button()==Qt::RightButton){
        if(this->_nextItem!=nullptr && this->_preItem!=nullptr){
            emit msg(tr("节点不能重复连接"));
        }else{
            if(_waitLink){
                _waitLink=false;
            }else{
                _waitLink=true;
            }
            emit requestLink(this);
        }

        this->scene()->clearSelection();
        //设置选中模式
        this->setSelected(true);
        this->update();

    }else{
        QGraphicsItem::mousePressEvent(event);
    }
}

void DraggableDotItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->_mousePressed && _itemCustomMove==true){
        auto newPos=event->scenePos()+this->_mpReleativeOri;
        auto oldPos=this->scenePos();
        this->setNewPos(newPos,oldPos);
    }

    //Default set event accept
}

void DraggableDotItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->_mousePressed=false;
    this->update();
    //不允许点多选
    this->setSelected(false);
}

void DraggableDotItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        //左键双击添加点
        this->creatItemAfter();
    }else if(event->button()==Qt::RightButton){
        if(this->_itemCustomMove==false){
            //删除整条链--由上层处理
            emit requestDelAllLink();
        }else{
            //右键双击删除点
            auto oldPre=_preItem;
            this->deleteThisItem();

            if(oldPre!=nullptr) {
                //Make sure preitem can update it's view
                oldPre->update();
            }
        }

    }else{
        QGraphicsItem::mouseDoubleClickEvent(event);
    }
}



//QVariant DraggableDotItem::itemChange(GraphicsItemChange change, const QVariant &value)
//{
//    if(change==QGraphicsItem::ItemPositionChange){
//        //位置变化
//        //        qDebug()<<"DraggableDotItem::itemChange : item position change "<<value.value<QPointF>();
//    }
//    return value;
//}
