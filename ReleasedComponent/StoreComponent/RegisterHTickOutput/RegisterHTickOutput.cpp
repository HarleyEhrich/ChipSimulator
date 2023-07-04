#include "RegisterHTickOutput.h"


RegisterHTickOutput::RegisterHTickOutput():
    AbstractConInterface(){
    init();
}

RegisterHTickOutput::RegisterHTickOutput(long sceneID, QGraphicsItem *parent, QObject *parentObject):
    AbstractConInterface(sceneID, parent, parentObject){
    init();
}

void RegisterHTickOutput::run(){
    runImpl();
    update();
}

QFont RegisterHTickOutput::font() const{
    return _font;
}

void RegisterHTickOutput::init(){
    if(false == __intialSta){
        IntialStaticVariable();
        IntialComponentInfo(this,
                            "001",
                            "RegisterHTickOutput",
                            "",
                            "Bulid In",
                            "2023-05-01",
                            ""//todo image path not set
                            );
    }


    _comName = "";


    int startY = -__mainBodySizeHalf.height()+ UniConnectionPoint::mainBodyWH()/2 +4;
    int spcerInY = (__mainBodySize.height() - 8 - UniConnectionPoint::mainBodyWH()) / 8;

    int inputId;
    int outputId;
    UniConnectionPointPtr inputPtr,outputPtr;
    for(int i=0;i<8;++i){
        inputId = RegisterConnectionPoint(this,
                                          COOR_POS::LEFT,
                                          false,
                                          "A"+QString::number(i));
        outputId = RegisterConnectionPoint(this,
                                           COOR_POS::RIGHT,
                                           true,
                                           "D"+QString::number(i),
                                           1,10);

        inputPtr = getCCPointWPtrById(inputId);
        outputPtr = getCCPointWPtrById(outputId);

        inputPtr.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6,startY);
        outputPtr.lock()->setPos(__mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6,startY);

        inputPtr.lock()->setTextDirection(TextDriection::RIGHT);
        outputPtr.lock()->setTextDirection(TextDriection::LEFT);

        _inputVec.push_back(inputPtr);
        _outputVec.push_back(outputPtr);

        startY+=spcerInY;

    }

    _recvData = getCCPointWPtrById(
        RegisterConnectionPoint(this,
                                COOR_POS::LEFT,
                                false,
                                "Input")
        );

    _outData = getCCPointWPtrById(
        RegisterConnectionPoint(this,
                                COOR_POS::RIGHT,
                                false,
                                "Output")
        );


    _recvData.lock()->setPos(-__mainBodySizeHalf.width() - UniConnectionPoint::mainBodyWH() + 6,
                             __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH() - 4);
    _outData.lock()->setPos( __mainBodySizeHalf.width() + UniConnectionPoint::mainBodyWH() - 6,
                            __mainBodySizeHalf.height() - UniConnectionPoint::mainBodyWH() - 4);

    _recvData.lock()->setTextDirection(TextDriection::RIGHT);
    _outData.lock()->setTextDirection(TextDriection::LEFT);

    runImpl();

    connect(this,&RegisterHTickOutput::tellComNickNameChange,this,&RegisterHTickOutput::updateStatus);
    updateStatus();
}

void RegisterHTickOutput::runImpl(){

    if(!_tickNew){
        return ;
    }
    if(_curTickType != TICK_TYPE::HIGH_ZERO){

        if(_lastHighResistance != true){
            for(int i =0;i<8;++i){
                _outputVec[i].lock()->setHighResistance(_lastHighResistance);
            }
            _lastHighResistance = true;
        }

        return ;
    }

    if(_recvData.lock()->getDataValue(0)){
        //Reciver data to the register
        for(int i =0;i<8;++i){
            _outputVec[i].lock()->setDataValue(
                QBitArray{1,_inputVec[i].lock()->getDataValue(0)},0
                );
        }
    }

    if(_outData.lock()->getDataValue(0)){
        for(int i =0;i<8;++i){
            _outputVec[i].lock()->setHighResistance(false);
        }
        _lastHighResistance = false;
    }



}

void RegisterHTickOutput::updateStatus(){
    gneratePos();
    gnerateItemPainterPathImpl();
}

void RegisterHTickOutput::gneratePos(){
    QFontMetrics fm{_font};
    _comNameLBPos.setX(-fm.boundingRect(_comName).width()/2);
    _comNameLBPos.setY(-fm.boundingRect(_comName).height()-4);
}

void RegisterHTickOutput::gnerateItemPainterPathImpl(){
    _itemPainterPath.clear();

    _itemPainterPath.addRect(-__mainBodySizeHalf.width(),-__mainBodySizeHalf.height(),__mainBodySize.width(),__mainBodySize.height());
    _itemPainterPath.addText(__textLBPos,font(),_comNickName);
    _itemPainterPath.addText(_comNameLBPos,font(),_comName);


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

void RegisterHTickOutput::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    RENDER_HINT_ANT(painter);

    painter->setFont(font());
    painter->drawText(__textLBPos,_comNickName);
    painter->drawText(_comNameLBPos,_comName);

    painter->setPen(__mainBodyPen);
    painter->setBrush(__mainBodyBrush);
    painter->drawRoundedRect(-__mainBodySizeHalf.width(),
                             -__mainBodySizeHalf.height(),
                             __mainBodySize.width(),
                             __mainBodySize.height(),4,4);

    painter->restore();
}

AbstractConInterface *RegisterHTickOutput::instanceImpl(long sceneID, QGraphicsItem *parent){
    return new RegisterHTickOutput(sceneID,parent);
}

void RegisterHTickOutput::gnerateItemPainterPath(){
    gnerateItemPainterPathImpl();
}

bool RegisterHTickOutput::loadFromXmlExtendImpl(QXmlStreamReader *root){
    Q_UNUSED(root);
    return true;
}

bool RegisterHTickOutput::saveToXmlExtendImpl(QXmlStreamWriter *root){
    Q_UNUSED(root);
    return true;
}

void RegisterHTickOutput::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen){
    Q_UNUSED(changePtr);
    Q_UNUSED(changedIndex);
    Q_UNUSED(changeLen);

    run();
}

void RegisterHTickOutput::IntialStaticVariable(){
    if(__intialSta) return ;

    __mainBodySize.setWidth(180);
    __mainBodySize.setHeight(270);

    __mainBodySizeHalf.setWidth(80);
    __mainBodySizeHalf.setHeight(120);

    __textLBPos.setX(-__mainBodySizeHalf.width());
    __textLBPos.setY(-__mainBodySizeHalf.height()-8);


    __mainBodyColor.setRgb(255, 255, 255);//Pure white
    __mainBodyPen.setColor(__mainBodyColor);
    __mainBodyPen.setWidth(0);
    __mainBodyBrush.setColor(__mainBodyColor);
    __mainBodyBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __intialSta = true;
}
