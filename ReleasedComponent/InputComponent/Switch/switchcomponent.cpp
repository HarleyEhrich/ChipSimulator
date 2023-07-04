#include "SwitchComponent.h"

#include <QCheckBox>

SwitchComponent::SwitchComponent()
    : AbstractConInterface(),
    _switchStatus(false)
{
    initial();
}

SwitchComponent::SwitchComponent(long sceneID, QGraphicsItem *parent, QObject *parentObject)
    : AbstractConInterface(sceneID, parent, parentObject),
    _switchStatus(false)
{
    initial();
}

SwitchComponent::~SwitchComponent(){
    ;
}

void SwitchComponent::updateAllStatus(){
    gnerateItemPainterPathImpl();
}



void SwitchComponent::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    RENDER_HINT_ANT(painter)

    painter->setFont(_textFont);
    painter->drawText(__textLBPos,_comNickName);

    painter->setPen(__switchPen);
    painter->setBrush(__switchBrush);
    painter->drawRoundedRect(__switchRect,__switchRadius,__switchRadius);

    if(_switchStatus){
        //true
        painter->setPen(__actSwiCenCirPen);
        painter->setBrush(__actSwiCenCirBru);
        painter->drawEllipse(__actCirPos,__switchCenCirSizeHalf.width(),__switchCenCirSizeHalf.height());
    }else{
        painter->setPen(__unactSwiCenCirPen);
        painter->setBrush(__unactSwiCenCirBru);
        painter->drawEllipse(__unactCirPos,__switchCenCirSizeHalf.width(),__switchCenCirSizeHalf.height());
    }

    painter->restore();

}

void SwitchComponent::run()
{
    update();
}

bool SwitchComponent::switchStatus() const
{
    return _switchStatus;
}

void SwitchComponent::setSwitchStatus(bool newSwitchStatus)
{
    _switchStatus = newSwitchStatus;
    if(!getCCPointWPtrById(0).isNull()){
        getCCPointWPtrById(0).lock()->setDataValue(QBitArray{1,newSwitchStatus});
    }
    run();
}

void SwitchComponent::initial(){
    if(false == __intialSta){
        initialStaVar();
        IntialComponentInfo(this,
                            "001",
                            "Switch",
                            "This is a switch assembly through which you can input and output a level signal.",
                            "Bulid In",
                            "2023-05-01",
                            ""//todo image path not set
                            );
    }

    updateAllStatus();//Only need one time

    connect(this,&SwitchComponent::tellComNickNameChange,this,&SwitchComponent::updateAllStatus);

    RegisterConnectionPoint(this,COOR_POS::BELOW,true,"开关输出",1,10);

    QFrame* box = new QFrame();
    QHBoxLayout* boxLay=new QHBoxLayout(box);
    QLabel* switchLab = new QLabel();
    QCheckBox* ck = new QCheckBox();
    switchLab->setText(tr("高电平输出"));
    ck->setTristate(_switchStatus);
    boxLay->addWidget(switchLab);
    boxLay->addWidget(ck);
    boxLay->setStretch(0,3);
    boxLay->setStretch(1,7);

    connect(ck,&QCheckBox::clicked,this,&SwitchComponent::setSwitchStatus);

    QSharedPointer<QWidget> switchCheckBoxSPtr{box};
    RegisterComWidget(this,
                      switchCheckBoxSPtr,
                      false,
                      false);


}

void SwitchComponent::gnerateItemPainterPathImpl(){
    _itemPainterPath.clear();

    _itemPainterPath.addText(__textLBPos,_textFont,_comNickName);

    _itemPainterPath.addRect(__switchRect);

    if(!getCCPointWPtrById(0).isNull()){
        getCCPointWPtrById(0).lock()->setPos(0,__switchSize.height()/2 + UniConnectionPoint::mainBodyWH()/2 + 8);
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



AbstractConInterface *SwitchComponent::instanceImpl(long sceneID, QGraphicsItem *parent)
{
    return new SwitchComponent(sceneID,parent);
}

void SwitchComponent::gnerateItemPainterPath()
{
    gnerateItemPainterPathImpl();
}

bool SwitchComponent::loadFromXmlExtendImpl(QXmlStreamReader *root)
{
    if(root == nullptr) {
        qCritical()<<"XMl stream reader is a nullptr";
        return false;
    }

    while(!root->atEnd()){
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && __xmlLabel == root->name().toString() ){
            QXmlStreamAttributes attrs = root->attributes();
            //read attrs
            if(attrs.hasAttribute("switch_open_status")){
                setSwitchStatus(attrs.value("switch_open_status").toInt());
            }
        }

        if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
            && __xmlLabel == root->name().toString()){
            break;//End read this component
        }

        root->readNext();
    }

    return true;
}

bool SwitchComponent::saveToXmlExtendImpl(QXmlStreamWriter *root)
{
    if(root == nullptr) {
        qCritical()<<"XMl stream writer is a nullptr";
        return false;
    }

    root->writeStartElement(__xmlLabel);
    root->writeAttribute("switch_open_status",QString::number(_switchStatus));
    root->writeEndElement();

    return true;
}

void SwitchComponent::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen)
{
    Q_UNUSED(changePtr);
    Q_UNUSED(changedIndex);
    Q_UNUSED(changeLen);

    //肯定没有的
    run();
}

void SwitchComponent::initialStaVar()
{
    if(true == __intialSta){
        return ;
    }

    __switchRadius = 12;

    __switchSize.setHeight(24);
    __switchSize.setWidth(48);

    __switchCenCirSizeHalf.setHeight(10);
    __switchCenCirSizeHalf.setWidth(10);
    __switchCenCirSize.setHeight(20);
    __switchCenCirSize.setWidth(20);

    __textLBPos.setX(-__switchSize.width()/2);
    __textLBPos.setY(-__switchSize.height()/2-8);

    __unactCirPos.setX(-__switchCenCirSizeHalf.width());
    __unactCirPos.setY(0);
    __actCirPos.setX(__switchCenCirSizeHalf.width());
    __actCirPos.setY(0);

    __switchRect.setX(-__switchSize.width()/2);
    __switchRect.setY(-__switchSize.height()/2);
    __switchRect.setWidth(__switchSize.width());
    __switchRect.setHeight(__switchSize.height());

    __switchColor.setRgb(255, 255, 255);//Pure white
    __switchPen.setColor(__switchColor);
    __switchPen.setWidth(0);
    __switchBrush.setColor(__switchColor);
    __switchBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __unactSwiCenCirColor.setRgb(239, 239, 239);//Gray
    __unactSwiCenCirPen.setColor(__unactSwiCenCirColor);
    __unactSwiCenCirPen.setWidth(0);
    __unactSwiCenCirBru.setColor(__unactSwiCenCirColor);
    __unactSwiCenCirBru.setStyle(Qt::BrushStyle::SolidPattern);

    __actSwiCenCirColor.setRgb(101, 196, 102);//Green
    __actSwiCenCirPen.setColor(__actSwiCenCirColor);
    __actSwiCenCirPen.setWidth(0);
    __actSwiCenCirBru.setColor(__actSwiCenCirColor);
    __actSwiCenCirBru.setStyle(Qt::BrushStyle::SolidPattern);

    __intialSta = true;
}
