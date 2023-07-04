#include "ReverseGate.h"


ReverseGate::ReverseGate():
    AbstractConInterface(){
    init();
}

ReverseGate::ReverseGate(long sceneID, QGraphicsItem *parent, QObject *parentObject):
    AbstractConInterface(sceneID, parent, parentObject){
    init();
}

void ReverseGate::run(){
    if(_inputCCPPoint.lock()->getDataValue(0)){
        _outPutCCPoint.lock()->setDataValue(QBitArray{1,false},0);
    }else{
        _outPutCCPoint.lock()->setDataValue(QBitArray{1,true},0);
    }
    update();
}

QFont ReverseGate::font() const{
    return _font;
}

void ReverseGate::init(){
    if(false == __intialSta){
        if(false == __intialSta){
            IntialStaticVariable();
            IntialComponentInfo(this,
                                "001",
                                "ReverseGate",
                                "非门，输出端的电平与输入端的电平相反",
                                "Bulid In",
                                "2023-05-01",
                                ""//todo image path not set
                                );
        }
    }


    _gateName = "1";

    int i = RegisterConnectionPoint(this,
                                    COOR_POS::LEFT,
                                    false,
                                    "I");

    int o = RegisterConnectionPoint(this,
                                    COOR_POS::RIGHT,
                                    true,
                                    "!O",
                                    1,10);

    _inputCCPPoint = getCCPointWPtrById(i);
    _outPutCCPoint = getCCPointWPtrById(o);

    _inputCCPPoint.lock()->setTextDirection(TextDriection::RIGHT);
    _outPutCCPoint.lock()->setTextDirection(TextDriection::LEFT);

    int halfCCPWidth = _inputCCPPoint.lock()->mainBodyWH()/2;
    _inputCCPPoint.lock()->setPos(-__mainBodySizeHalf.width()-halfCCPWidth-6,0);
    _outPutCCPoint.lock()->setPos(__mainBodySizeHalf.width()+halfCCPWidth+6,0);

    connect(this,&ReverseGate::tellComNickNameChange,this,&ReverseGate::updateStatus);
    updateStatus();
}

void ReverseGate::updateStatus(){
    gneratePos();
    gnerateItemPainterPathImpl();
}

void ReverseGate::gneratePos(){
    QFontMetrics fm{_font};
    _gateNamePos.setX(-fm.boundingRect(_gateName).width()/2);
    _gateNamePos.setY(-fm.boundingRect(_gateName).height()-4);
}

void ReverseGate::gnerateItemPainterPathImpl(){

    _itemPainterPath.clear();

    _itemPainterPath.addRect(-__mainBodySizeHalf.width(),-__mainBodySizeHalf.height(),__mainBodySize.width(),__mainBodySize.height());
    _itemPainterPath.addText(__textLBPos,font(),_comNickName);
    _itemPainterPath.addText(_gateNamePos,font(),_gateName);

    //Add the bouding rect
    for(auto&ccpItem : getCCPointVec()){
        QRectF ccPointRect = ccpItem->getRealBoudingRect();
        ccPointRect.moveCenter(
            mapFromScene(
                ccpItem->getRealItemCenterScenePos()
                )
            );

        _itemPainterPath.addRect(ccPointRect);
    }

    QRect bouding = _itemPainterPath.boundingRect().toRect();

    bouding.moveTopLeft({bouding.x() - 8,bouding.y() - 8});
    bouding.setHeight(bouding.height() + 16);
    bouding.setWidth(bouding.width() + 16);

    prepareGeometryChange();

    _boudingRect = bouding;

    update();
}

void ReverseGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    RENDER_HINT_ANT(painter);

    painter->setFont(font());
    painter->drawText(__textLBPos,_comNickName);
    painter->drawText(_gateNamePos,_gateName);

    painter->setPen(__mainBodyPen);
    painter->setBrush(__mainBodyBrush);
    painter->drawRoundedRect(-__mainBodySizeHalf.width(),
                             -__mainBodySizeHalf.height(),
                             __mainBodySize.width(),
                             __mainBodySize.height(),4,4);
//    painter->drawRect(-__mainBodySizeHalf.width(),-__mainBodySizeHalf.height(),__mainBodySize.width(),__mainBodySize.height());

    painter->restore();
}

AbstractConInterface *ReverseGate::instanceImpl(long sceneID, QGraphicsItem *parent){
    return new ReverseGate(sceneID,parent);
}

void ReverseGate::gnerateItemPainterPath(){
    gnerateItemPainterPathImpl();
}

bool ReverseGate::loadFromXmlExtendImpl(QXmlStreamReader *root){
    return true;
}

bool ReverseGate::saveToXmlExtendImpl(QXmlStreamWriter *root){
    return true;
}

void ReverseGate::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen){
    run();
}

void ReverseGate::IntialStaticVariable(){
    if(__intialSta) return ;

    __mainBodySize.setWidth(60);
    __mainBodySize.setHeight(90);

    __mainBodySizeHalf.setWidth(30);
    __mainBodySizeHalf.setHeight(45);

    __reverseFlagSize.setHeight(6);
    __reverseFlagSize.setWidth(6);

    __reverseFlagSizeHalf.setHeight(3);
    __reverseFlagSizeHalf.setWidth(3);


    __textLBPos.setX(-__mainBodySizeHalf.width());
    __textLBPos.setY(-__mainBodySizeHalf.height()-8);


    __mainBodyColor.setRgb(255, 255, 255);//Pure white

    __mainBodyPen.setColor(__mainBodyColor);
    __mainBodyPen.setWidth(0);
    __mainBodyBrush.setColor(__mainBodyColor);
    __mainBodyBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __intialSta = true;
}
