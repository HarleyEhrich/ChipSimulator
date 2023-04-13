#include "abstractconinterface.h"



AbstractConInterface::AbstractConInterface(QGraphicsItem *parent)
    :QGraphicsItem(parent)
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

bool AbstractConInterface::isIntial(){return this->_isInitial;}

const QString &AbstractConInterface::getConIid(){return this->_conId;}

const QString &AbstractConInterface::getCreatTime(){return this->_creatTime;}

const QString &AbstractConInterface::getConName(){return this->_conName;}

const QString &AbstractConInterface::getAuthor(){return this->_author;}

const QString &AbstractConInterface::getConImgaePath(){return this->_conImagePath;}

const QPixmap &AbstractConInterface::getConImage(){return this->_conImage;}

const QString &AbstractConInterface::getConDescribe(){
    return this->_conDescribeInfo;
}

bool AbstractConInterface::loadFromTextAbstract(const QString &abText)
{
    QXmlStreamReader reader(abText);
    while(!reader.atEnd()){
        auto type=reader.tokenType();
        //明确为类型的xml内容
        if(type==QXmlStreamReader::StartElement && reader.name().toString() == this->_conId){
            //基本数据
            QXmlStreamAttributes basicAttributes=reader.attributes();
            if(basicAttributes.hasAttribute("sceneId")){
                this->_sceneId=basicAttributes.value("sceneId").toLong();
            }

            if(basicAttributes.hasAttribute("scenePosX")){
                this->setPos(basicAttributes.value("scenePosX").toFloat(),this->scenePos().y());
            }
            if(basicAttributes.hasAttribute("scenePosY")){
                this->setPos(this->scenePos().x(), basicAttributes.value("scenePosY").toFloat());
            }
            if(basicAttributes.hasAttribute("nickName")){
                this->_conNickName=basicAttributes.value("nickName").toString();
            }
        }else if(type==QXmlStreamReader::StartElement && reader.name().toString() == "extendData"){
            //扩展数据
            this->loadStatusFormText(reader.readElementText());
        }else{
            ;
        }

        reader.readNext();
    }
    return true;
}

bool AbstractConInterface::saveToTextAbstract(QString &abText)
{
    QString extendDataText;
    QXmlStreamWriter writer(&abText);
    writer.setAutoFormatting(true);
    writer.writeStartDocument("1.0",true);//写入头
    writer.writeStartElement(this->_conId);
    writer.writeAttribute("sceneId",QString::number(this->_sceneId));
    writer.writeAttribute("scenePosX",QString::number(this->scenePos().x()));
    writer.writeAttribute("scenePosY",QString::number(this->scenePos().y()));
    writer.writeAttribute("nickName",this->_conNickName);

    this->saveStatusToText(extendDataText);
    writer.writeTextElement("extendData",extendDataText);

    writer.writeEndElement();

    return true;
}

bool AbstractConInterface::isMoveable() const
{
    return _isMoveable;
}

void AbstractConInterface::setIsMoveable(bool newIsMoveable)
{
    _isMoveable = newIsMoveable;
}

long AbstractConInterface::sceneId() const
{
    return _sceneId;
}

void AbstractConInterface::setSceneId(long newScenceId)
{
    _sceneId = newScenceId;
}

bool AbstractConInterface::innitial(const QString &creatTime, const QString &author, const QString &conName, const QString &conImagePath){
    if(_isInitial==true) {
        emit this->newLog(this->getConDescribe(),tr("The virtual conponent has been initialized and should not be initialized again."),AMTL::WARNING);
        return false;
    }

    this->_creatTime=creatTime;
    this->_author=author;
    this->_conName=this->_conNickName=conName;
    this->_conImagePath=conImagePath;

    if(!this->_conImage.load(this->_conImagePath)){
        emit this->newLog(this->getConDescribe(),tr("The virtual conponent description thumbnail failed to load."),AMTL::ERROR);
        this->_conImagePath=":/default _electronic_component.png";
        this->_conImage.load(this->_conImagePath);
    }

    //gennerate id
    this->_conId=this->_conName+"-"+this->_author+"-"+this->_creatTime;

    //gennerate describe info
    this->_conDescribeInfo=this->_conId+","+this->_conNickName;

    this->_isInitial=true;

    //接受鼠标悬浮事件
    this->setAcceptHoverEvents(true);
    //可移动，可选择
    this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

    return true;
}


