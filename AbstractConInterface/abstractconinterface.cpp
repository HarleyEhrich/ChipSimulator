#include "abstractconinterface.h"

AbstractConInterface::AbstractConInterface(long sceneID,QGraphicsItem *parent,QObject* parentObject)
    :UniGraphicsItemObject(parentObject,parent),
    _comNickName(__comName),
    _sceneId(sceneID),
    _tickNew(false),
    _curTickType(TICK_TYPE::NO_TICK)
{
    init();
}

AbstractConInterface::AbstractConInterface(long sceneID, const QString &comName, QGraphicsItem *parent, QObject *parentObject)
    :UniGraphicsItemObject(parentObject,parent),
    _comNickName(comName),
    _sceneId(sceneID),
    _tickNew(false),
    _curTickType(TICK_TYPE::NO_TICK)
{
    init();
}

AbstractConInterface::~AbstractConInterface(){
    ;
}

bool AbstractConInterface::loadStatusFormXml(QXmlStreamReader *root){
    return loadFromXmlAbstractImpl(root);
}

bool AbstractConInterface::saveStatusToXml(QXmlStreamWriter *root){
    return saveToXmlAbstractImpl(root);
}





long AbstractConInterface::sceneId() const
{
    return _sceneId;
}

void AbstractConInterface::setSceneId(long newScenceId)
{
    _sceneId = newScenceId;
}

void AbstractConInterface::preTick(TICK_TYPE tickType){
    Q_UNUSED(tickType);
}

void AbstractConInterface::tick(TICK_TYPE tickType){
    preTick(tickType);
    switch (tickType){
    case TICK_TYPE::HIGH_ZERO:{
        run();
        break;
    }

    case TICK_TYPE::ZERO_HIGH:{
        run();
        break;
    }
    case TICK_TYPE::NO_TICK:{
        run();
        break;
    }
    }
    postTick(tickType);
}

void AbstractConInterface::postTick(TICK_TYPE tickType){
    Q_UNUSED(tickType);
}

bool AbstractConInterface::loadFromXmlAbstractImpl(QXmlStreamReader *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream reader is a nullptr";
        return false;
    }

    while(!root->atEnd()){
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComAbstractLabelName == root->name().toString() ){
            QXmlStreamAttributes attrs = root->attributes();
            //read attrs
            if(attrs.hasAttribute("scene_id")){
                this->_sceneId=attrs.value("scene_id").toLong();
            }

            if(attrs.hasAttribute("scene_pos")){
                QStringList pointValueStrList = attrs.value("scene_pos").toString().split(",");
                if(pointValueStrList.size() != 2){
                    qCritical()<<"The scene position data of the abstract component in the xml file is missing";
                    return false;
                }
                this->setPos(pointValueStrList[0].toLong(),pointValueStrList[1].toLong());
            }

            if(attrs.hasAttribute("nick_name")){
                this->_comNickName=attrs.value("nick_name").toString();
            }

        }

        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComExtendLabelName == root->name().toString()){

            root->readNext();//读取下一节点,进入扩展部分

            if(Q_UNLIKELY(root->atEnd())){

                qCritical()<<"Missing tags in xml file @"<<ComExtendLabelName;
            }

            if(root->tokenType() != QXmlStreamReader::TokenType::EndElement){
                //如果下一节点不为end，就进入读取
                //got text in extend part
                loadFromXmlExtendImpl(root);
            }
        }

        if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
            && ComAbstractLabelName == root->name().toString()){
            break;//End read this component
        }

        //Turn to next element
        root->readNext();
    }

    return true;

}

bool AbstractConInterface::saveToXmlAbstractImpl(QXmlStreamWriter *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream write is a nullptr";
        return false;
    }

    root->writeStartElement(ComAbstractLabelName);
    root->writeAttribute("scene_id",QString::number(this->_sceneId));
    root->writeAttribute("scene_pos",QString("%1,%2").arg(scenePos().x(),scenePos().y()));
    root->writeAttribute("nick_name",_comNickName);

    root->writeStartElement(ComExtendLabelName);
    if(!saveToXmlExtendImpl(root)){
        root->writeEndElement();
        root->writeEndElement();
        return false;
    }

    root->writeEndElement();

    //todo write connection point info to this xml

    root->writeEndElement();
    return true;
}

void AbstractConInterface::customInit(){

}

void AbstractConInterface::gnerateItemPainterPath(){
    _itemPainterPath.addRect(-24,-24,48,48);
    _boudingRect = _itemPainterPath.boundingRect();
}

bool AbstractConInterface::loadFromXmlExtendImpl(QXmlStreamReader *root){
    Q_UNUSED(root);

    return true;
}

bool AbstractConInterface::saveToXmlExtendImpl(QXmlStreamWriter *root){
    Q_UNUSED(root);


    return true;
}

void AbstractConInterface::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen){
    run();
}

void AbstractConInterface::init(){
    this->setFlags(ItemSendsGeometryChanges | ItemIsSelectable | ItemIsMovable | ItemIsFocusable);

    MAKE_DEA_SHADOW_EFF(_shadowEffect,this)

    customInit();
}

int AbstractConInterface::registerConnectionPoint(COOR_POS pos, bool outputPoint, QString pointName, int dataBits, int maxBindItemNumber){
    int newId= _connectPointVec.size();

    UniConnectionPoint* newPoint = new UniConnectionPoint(newId,
                                                          pos,
                                                          outputPoint,
                                                          pointName,
                                                          dataBits,
                                                          maxBindItemNumber,
                                                          this);

    _connectPointVec.append(newPoint);
    _pointDataMap[newPoint] = newPoint->getDataPtr();

    //connect data change
    connect(newPoint,&UniConnectionPoint::tellDataChanged,this,[=](UniConnectionPoint* changePtr,qsizetype changedIndex,int changeLen){
        connectionDataChangeImpl(changePtr,changedIndex,changeLen);
    });

    return newId;
}






QPointF AbstractConInterface::getRealItemCenterScenePos()
{
    return scenePos();
}

QRectF AbstractConInterface::getRealBoudingRect()
{
    return getRealBoudingRect();
}

QRectF AbstractConInterface::boundingRect() const
{
    return _boudingRect;
}

void AbstractConInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPath(_itemPainterPath);
}

void AbstractConInterface::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsView* view= qobject_cast<QGraphicsView*>(event->widget()->parentWidget());
    if(view == nullptr){
        qWarning()<<"The graphics view component does not exist and the context menu cannot be generated.";
        return;
    }


}

void AbstractConInterface::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    _mousePressed=true;
    _mousePressedPoint=this->scenePos()-event->scenePos();//鼠标点击相对于图元的坐标位置
}

void AbstractConInterface::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    _mousePressed=false;
}

void AbstractConInterface::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(_mousePressed && _isMoveable)
    {
        setPos(mapToParent(mapFromScene(event->scenePos()+_mousePressedPoint)));
    }
}

void AbstractConInterface::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    ;
}


bool AbstractConInterface::staInitial()
{
    return __initial;
}

QString AbstractConInterface::comId()
{
    return __comId;
}

QString AbstractConInterface::comName()
{
    return __comName;
}

QString AbstractConInterface::componentDesInfo()
{
    return __comDesInfo;
}

QString AbstractConInterface::comAuthor()
{
    return __comAuthor;
}

QString AbstractConInterface::comCreatTimeStr()
{
    return __comCreatTimeStr;
}

QDateTime AbstractConInterface::comCreatTime()
{
    return __comCreatTime;
}

QString AbstractConInterface::comImagePath()
{
    return __comImagePath;
}

QPixmap AbstractConInterface::comImage()
{
    return __comImage;
}

void AbstractConInterface::intialComponentInfo(const QString &cid, const QString &cName, const QString &cDesInfo, const QString &author, const QString &creatTime, const QString &cImagePath, const QString &timeFormat){

    if(true == __initial) return;

    __comId = cid+author+cName;

    __comName = cName;

    __comDesInfo = cDesInfo;

    __comAuthor = author;


    __comCreatTime.fromString(creatTime,timeFormat);
    if(!__comCreatTime.isValid()){
        __comCreatTime.setDate(QDate{1946,02,04});
    }
    __comCreatTimeStr = __comCreatTime.toString("yy-mm-dd");

    __comImagePath = cImagePath;
    if(!__comImage.load(cImagePath)){
        qDebug()<<"Load component image fail, target file path: "<<cImagePath;
        __comImagePath = ":/default _electronic_component.png";
        __comImage.load(__comImagePath);
    }

    __initial =true;
}

int AbstractConInterface::registerConnectionPoint(AbstractConInterface *targetCom, COOR_POS pos, bool outputPoint, QString pointName, int dataBits, int maxBindItemNumber){
    return targetCom->registerConnectionPoint(pos,outputPoint,pointName,dataBits,maxBindItemNumber);
}



//bool AbstractConInterface::loadFromTextAbstarctImpl(const QString &abText)
//{
//    QXmlStreamReader reader(abText);
//    while(!reader.atEnd()){
//        auto type=reader.tokenType();
//        //明确为类型的xml内容
//        if(type==QXmlStreamReader::StartElement && __comId == reader.name().toString()){
//            //基本数据
//            QXmlStreamAttributes basicAttributes=reader.attributes();
//            if(basicAttributes.hasAttribute("sceneId")){
//                this->_sceneId=basicAttributes.value("sceneId").toLong();
//            }

//            if(basicAttributes.hasAttribute("scenePosX")){
//                this->setPos(basicAttributes.value("scenePosX").toFloat(),this->scenePos().y());
//            }
//            if(basicAttributes.hasAttribute("scenePosY")){
//                this->setPos(this->scenePos().x(), basicAttributes.value("scenePosY").toFloat());
//            }
//            if(basicAttributes.hasAttribute("nickName")){
//                this->_conNickName=basicAttributes.value("nickName").toString();
//            }
//        }else if(type==QXmlStreamReader::StartElement && reader.name().toString() == "extendData"){
//            //扩展数据
//            this->loadStatusFormText(reader.readElementText());
//        }else{
//            ;
//        }

//        reader.readNext();
//    }
//    return true;
//}

//bool AbstractConInterface::saveToTextAbstarctImpl(QString &abText)
//{
//    QString extendDataText;
//    QXmlStreamWriter writer(&abText);
//    writer.setAutoFormatting(true);
//    writer.writeStartDocument("1.0",true);//写入头

//    writer.writeStartElement(__comId);
//    writer.writeAttribute("sceneId",QString::number(this->_sceneId));
//    writer.writeAttribute("scenePosX",QString::number(this->scenePos().x()));
//    writer.writeAttribute("scenePosY",QString::number(this->scenePos().y()));
//    writer.writeAttribute("nickName",this->_conNickName);

//    this->saveStatusToText(extendDataText);

//    writer.writeTextElement("extendData",extendDataText);

//    writer.writeEndElement();

//    return true;
//}


//bool AbstractConInterface::isIntial(){return this->_isInitial;}

//const QString &AbstractConInterface::getConIid(){return this->_conId;}

//const QString &AbstractConInterface::getCreatTime(){return this->_creatTime;}

//const QString &AbstractConInterface::getConName(){return this->_conName;}

//const QString &AbstractConInterface::getAuthor(){return this->_author;}

//const QString &AbstractConInterface::getConImgaePath(){return this->_conImagePath;}

//const QPixmap &AbstractConInterface::getConImage(){return this->_conImage;}

//const QString &AbstractConInterface::getConDescribe(){
//    return this->_conDescribeInfo;
//}

//bool AbstractConInterface::innitial(const QString &creatTime, const QString &author, const QString &conName, const QString &conImagePath){
//    if(_isInitial==true) {
//        emit this->newLog(this->getConDescribe(),tr("The virtual conponent has been initialized and should not be initialized again."),AMTL::WARNING);
//        return false;
//    }

//    this->_creatTime=creatTime;
//    this->_author=author;
//    this->_conName=this->_conNickName=conName;
//    this->_conImagePath=conImagePath;

//    if(!this->_conImage.load(this->_conImagePath)){
//        emit this->newLog(this->getConDescribe(),tr("The virtual conponent description thumbnail failed to load."),AMTL::ERROR);
//        this->_conImagePath=":/default _electronic_component.png";
//        this->_conImage.load(this->_conImagePath);
//    }

//    //gennerate id
//    this->_conId=this->_conName+"-"+this->_author+"-"+this->_creatTime;

//    //gennerate describe info
//    this->_conDescribeInfo=this->_conId+","+this->_conNickName;

//    this->_isInitial=true;

//    //接受鼠标悬浮事件
//    this->setAcceptHoverEvents(true);
//    //可移动，可选择
//    this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

//    return true;
//}






