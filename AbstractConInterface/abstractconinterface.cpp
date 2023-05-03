#include "abstractconinterface.h"



AbstractConInterface::AbstractConInterface(long sceneID,QGraphicsItem *parent)
    :QGraphicsItem(parent),
    _sceneId(sceneID)
{

}

QRectF AbstractConInterface::boundingRect() const
{
    return QRectF{0,0,0,0};
}

void AbstractConInterface::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    ;
}

void AbstractConInterface::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    this->_mousePressed=true;
    this->_mousePressedPoint=this->scenePos()-event->scenePos();//鼠标点击相对于图元的坐标位置
}

void AbstractConInterface::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    this->_mousePressed=false;
}

void AbstractConInterface::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(_mousePressed && this->_isMoveable)
    {
        this->setPos(event->scenePos()+_mousePressedPoint);
    }
}

void AbstractConInterface::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    ;
}


void AbstractConInterface::tick(TICK_TYPE tickType){
    switch (tickType){
    case TICK_TYPE::HIGH_ZERO:{
        run();
        break;
    }

    case TICK_TYPE::ZERO_HIGH:{
        run();
        break;
    }

    }
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
                this->_conNickName=attrs.value("nick_name").toString();
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
    root->writeAttribute("nick_name",_conNickName);

    root->writeStartElement(ComExtendLabelName);
    if(!saveToXmlExtendImpl(root)){
        root->writeEndElement();
        root->writeEndElement();
        return false;
    }

    root->writeEndElement();
    root->writeEndElement();

    return true;
}

bool AbstractConInterface::saveToXmlExtendImpl(QXmlStreamWriter *root){
    Q_UNUSED(root);


    return true;
}

bool AbstractConInterface::loadFromXmlExtendImpl(QXmlStreamReader *root){
    Q_UNUSED(root);

    return true;
}


long AbstractConInterface::sceneId() const
{
    return _sceneId;
}

void AbstractConInterface::setSceneId(long newScenceId)
{
    _sceneId = newScenceId;
}





bool AbstractConInterface::initial()
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
