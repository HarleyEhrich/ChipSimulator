#include "LedComponent.h"

LedComponent::LedComponent()
    : AbstractConInterface(),
    _lightBallCount(0)
{
    initial();
}

LedComponent::LedComponent(long sceneID, QGraphicsItem *parent, QObject* parentObject)
    : AbstractConInterface(sceneID, parent, parentObject),
    _lightBallCount(0)
{
    initial();

    //todo this is a default num
    setLightBallCount(4);
}

void LedComponent::run()
{
    update();
}

int LedComponent::lightBallCount() const
{
    return _lightBallCount;
}

void LedComponent::setLightBallCount(int newLedCount)
{
    setLightBallCountImpl(newLedCount);
}

void LedComponent::updateAllStauts(){
    generatePosImpl();//Regenerate all lightball pos and uniconnection point pos.

    generateItemPainterPathImpl();

    cacheData();
}

void LedComponent::initial(){
    if(false == __initialStaVar){
        InitialStaticVar();
        IntialComponentInfo(this,
                            "001",
                            "Led",
                            "This is an LED component that can freely change the number. "
                            "You can use the color to visually observe the value of the data.",
                            "Bulid In",
                            "2023-05-01",
                            ""//todo image path not set
                            );
    }

    connect(this,&LedComponent::tellComNickNameChange,this,&LedComponent::updateAllStauts);

    _ledCountSetWidget.reset(new QSpinBox(nullptr));
    connect(_ledCountSetWidget.data(),&QSpinBox::valueChanged,this,[=](int value){
        setLightBallCountImpl(value);
    });
    connect(this,&LedComponent::tellLedLightBallCountChange,_ledCountSetWidget.data(),&QSpinBox::setValue);

    RegisterComWidget(this,
                      _ledCountSetWidget,
                      false,
                      false);

    updateAllStauts();
}

void LedComponent::setLightBallCountImpl(int newLedCount){
    if(newLedCount <= 0 ) return ;
    if(newLedCount == _lightBallCount) return ;

    if(newLedCount > _lightBallCount){
        //add more led light ball
        while(_lightBallCount != newLedCount){
            addLightBallImpl();
            ++_lightBallCount;
        }
    }else{
        //delete some led light ball
        while(_lightBallCount != newLedCount){
            deleteLightBallImpl();
            --_lightBallCount;
        }
    }

    if(!_ledCountSetWidget.isNull()) _ledCountSetWidget->setValue(_lightBallCount);

    updateAllStauts();

    emit tellLedLightBallCountChange(_lightBallCount);
}

bool LedComponent::addLightBallImpl(){
    RegisterConnectionPoint(this,COOR_POS::BELOW,false,QString::number(_lightBallCount));

    _dataCache.push_back(false);

    return true;
}

bool LedComponent::deleteLightBallImpl(){
    UnRegisterConnectionPoint(this,1);

    _dataCache.pop_back();

    return true;
}

void LedComponent::cacheData(int index){
    if(-1 == index){
        //Chace all
        _dataCache.resize(_lightBallCount);
        for(int i=0;i<_lightBallCount;++i){
            _dataCache[i] = getCCPointWPtrById(i).lock()->getDataValue(0);
        }
    }else{
        _dataCache[index] = getCCPointWPtrById(index).lock()->getDataValue(0);
    }

    update();
}

void LedComponent::generatePosImpl(){
    _lightBallCenterPosVec.clear();

    QPoint leftPos{(int)(float)(-_lightBallCount/2)*(__lightBallBaseSize.width() + __lightBallSperateSpace),0};

    _textLBPos.setX(leftPos.x() - __lightBallBaseSizeHalf.width());
    _textLBPos.setY(-__lightBallBaseSizeHalf.height()-8);//Upper then light ball about 8 px;

    int uniCCPointYPos = UniConnectionPoint::mainBodyWH() /2 + __lightBallBaseSize.width()/2 + __lightBallSperateSpace;

    UniConnectionPoint* ccPointPtr;
    UniConnectionPointSPtr ccPointSPtr;
    for(int i = 0;i<_lightBallCount;++i){
        //Do every led light ball
        _lightBallCenterPosVec.append(leftPos);

        ccPointSPtr = getCCPointWPtrById(i).lock();
        ccPointPtr  = ccPointSPtr.data();
        if(nullptr == ccPointPtr){
            continue;
        }
        ccPointPtr->setPos(leftPos.x(),uniCCPointYPos);

        leftPos.setX(leftPos.x() + __lightBallBaseSize.width() + __lightBallSperateSpace);
    }
}

void LedComponent::generateItemPainterPathImpl(){
    _itemPainterPath.clear();

    _itemPainterPath.addText(_textLBPos,_textFont,_comNickName);

    for(int i=0;i<_lightBallCount;++i){
        _itemPainterPath.addEllipse(_lightBallCenterPosVec[i],
                                 __lightBallBaseSizeHalf.width(),
                                 __lightBallBaseSizeHalf.height());
    }

    if(_lightBallCount && !getCCPointWPtrById(0).isNull()){
        QRectF ccPointRect = getCCPointWPtrById(0).lock()->getRealBoudingRect();
        ccPointRect.moveCenter(
            mapFromScene(
                getCCPointWPtrById(0).lock()->getRealItemCenterScenePos()
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

void LedComponent::drawALightBall(QPainter *painter, int indexOfLightBall){
    if(_dataCache[indexOfLightBall]){
        //True--Green
        painter->setPen(__actBasePen);
        painter->setBrush(__actBaseBrush);
        painter->drawEllipse(_lightBallCenterPosVec[indexOfLightBall],__lightBallBaseSizeHalf.width(),__lightBallBaseSizeHalf.height());

        painter->setPen(__actPen);
        painter->setBrush(__actBrush);
        painter->drawEllipse(_lightBallCenterPosVec[indexOfLightBall],__lightBallSizeHalf.width(),__lightBallSizeHalf.height());

    }else{
        //false--red
        painter->setPen(__unActBasePen);
        painter->setBrush(__unActBaseBrush);
        painter->drawEllipse(_lightBallCenterPosVec[indexOfLightBall],__lightBallBaseSizeHalf.width(),__lightBallBaseSizeHalf.height());

        painter->setPen(__unActPen);
        painter->setBrush(__unActBrush);
        painter->drawEllipse(_lightBallCenterPosVec[indexOfLightBall],__lightBallSizeHalf.width(),__lightBallSizeHalf.height());
    }
}




void LedComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    RENDER_HINT_ANT(painter)

//    painter->drawPath(_itemPainterPath);

    painter->setFont(_textFont);
    painter->drawText(_textLBPos,_comNickName);

//    auto rect= generateTextBouding(_comNickName);
//    rect.moveBottomLeft(_textLBPos);
//    painter->drawRect(rect);

    painter->drawRect(_boudingRect);

    for(int i=0;i<_lightBallCount;++i){
        drawALightBall(painter,i);
    }

    painter->restore();
}

AbstractConInterface *LedComponent::instanceImpl(long sceneID, QGraphicsItem *parent)
{
    return new LedComponent(sceneID,parent);
}

void LedComponent::gnerateItemPainterPath()
{
    generateItemPainterPathImpl();
}

bool LedComponent::loadFromXmlExtendImpl(QXmlStreamReader *root)
{
    if(root == nullptr) {
        qCritical()<<"XMl stream reader is a nullptr";
        return false;
    }

    while(!root->atEnd()){
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && __LedXmlLabel == root->name().toString() ){
            QXmlStreamAttributes attrs = root->attributes();
            //read attrs
            if(attrs.hasAttribute("light_ball_count")){
                int lightBallCount=attrs.value("light_ball_count").toInt();
                setLightBallCount(lightBallCount);
            }
        }

        if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
            && __LedXmlLabel == root->name().toString()){
            break;//End read this component
        }

        root->readNext();
    }

    return true;
}

bool LedComponent::saveToXmlExtendImpl(QXmlStreamWriter *root)
{
    root->writeStartElement(__LedXmlLabel);
    root->writeAttribute("light_ball_count",QString::number(_lightBallCount));
    root->writeEndElement();
    return true;
}

void LedComponent::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen)
{
    Q_UNUSED(changedIndex)
    Q_UNUSED(changeLen)

    if(nullptr == changePtr) return;
    cacheData(changePtr->id());
}

void LedComponent::InitialStaticVar(){
    if(true == __initialStaVar) return ;

    __colorLighter  = 80;
    __lightBallSperateSpace = 8;

    __lightBallBaseSize.setHeight(32);
    __lightBallBaseSize.setWidth(32);
    __lightBallSize.setHeight(24);
    __lightBallSize.setWidth(24);

    __lightBallBaseSizeHalf.setHeight(16);
    __lightBallBaseSizeHalf.setWidth(16);
    __lightBallSizeHalf.setHeight(12);
    __lightBallSizeHalf.setWidth(12);

    __actColor.setRgb(21, 183, 59);//Green
    __unActColor.setRgb(208, 22, 26);//Red

    __unActBasePen.setColor(__unActColor.lighter(__colorLighter));
    __unActBasePen.setWidth(0);
    __unActBaseBrush.setColor(__unActColor.lighter(__colorLighter));
    __unActBaseBrush.setStyle(Qt::BrushStyle::SolidPattern);
    __unActPen.setColor(__unActColor);
    __unActPen.setWidth(0);
    __unActBrush.setColor(__unActColor);
    __unActBrush.setStyle(Qt::BrushStyle::SolidPattern);


    __actBasePen.setColor(__actColor.lighter(__colorLighter));
    __actBasePen.setWidth(0);
    __actBaseBrush.setColor(__actColor.lighter(__colorLighter));
    __actBaseBrush.setStyle(Qt::BrushStyle::SolidPattern);
    __actPen.setColor(__actColor);
    __actPen.setWidth(0);
    __actBrush.setColor(__actColor);
    __actBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __initialStaVar = true;
}
