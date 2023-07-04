#include "OrReverseGate.h"


OrReverseGate::OrReverseGate():
    AbstractConInterface(){
    init();
}

OrReverseGate::OrReverseGate(long sceneID, QGraphicsItem *parent, QObject *parentObject):
    AbstractConInterface(sceneID, parent, parentObject){
    init();
}

void OrReverseGate::run(){
    runImpl();
    update();
}

QFont OrReverseGate::font() const{
    return _font;
}

void OrReverseGate::init(){
    if(false == __intialSta){
        IntialStaticVariable();
        IntialComponentInfo(this,
                            "001",
                            "OrReverseGate",
                            "或非门，端口经过或后再经过非运算的结果为输出端的电平",
                            "Bulid In",
                            "2023-05-01",
                            ""//todo image path not set
                            );
    }


    _gateName = ">=1";

    int input1 = RegisterConnectionPoint(this,
                                         COOR_POS::LEFT,
                                         false,
                                         "I1");
    int input2 = RegisterConnectionPoint(this,
                                         COOR_POS::LEFT,
                                         false,
                                         "I2");
    int output = RegisterConnectionPoint(this,
                                         COOR_POS::RIGHT,
                                         true,
                                         "!O",
                                         1,10);

    _input1 = getCCPointWPtrById(input1);
    _input2 = getCCPointWPtrById(input2);
    _output = getCCPointWPtrById(output);

    _input1.lock()->setTextDirection(TextDriection::RIGHT);
    _input2.lock()->setTextDirection(TextDriection::RIGHT);
    _output.lock()->setTextDirection(TextDriection::LEFT);

    _input1.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6 ,-__mainBodySizeHalf.height()/2);
    _input2.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6 ,__mainBodySizeHalf.height()/2);
    _output.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6 ,0);

    runImpl();

    connect(this,&OrReverseGate::tellComNickNameChange,this,&OrReverseGate::updateStatus);
    updateStatus();
}

void OrReverseGate::runImpl(){
    _output.lock()->setDataValue(QBitArray{1,(_input1.lock()->getDataValue(0) && _input2.lock()->getDataValue(0))},0);
}

void OrReverseGate::updateStatus(){
    gneratePos();
    gnerateItemPainterPathImpl();
}

void OrReverseGate::gneratePos(){
    QFontMetrics fm{_font};
    _gateNamePos.setX(-fm.boundingRect(_gateName).width()/2);
    _gateNamePos.setY(-fm.boundingRect(_gateName).height()-4);
}

void OrReverseGate::gnerateItemPainterPathImpl(){
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

void OrReverseGate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
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

AbstractConInterface *OrReverseGate::instanceImpl(long sceneID, QGraphicsItem *parent){
    return new OrReverseGate(sceneID,parent);
}

void OrReverseGate::gnerateItemPainterPath(){
    gnerateItemPainterPathImpl();
}

bool OrReverseGate::loadFromXmlExtendImpl(QXmlStreamReader *root){
    Q_UNUSED(root);
    return true;
}

bool OrReverseGate::saveToXmlExtendImpl(QXmlStreamWriter *root){
    Q_UNUSED(root);
    return true;
}

void OrReverseGate::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen){
    Q_UNUSED(changePtr);
    Q_UNUSED(changedIndex);
    Q_UNUSED(changeLen);

    run();
}

void OrReverseGate::IntialStaticVariable(){
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
