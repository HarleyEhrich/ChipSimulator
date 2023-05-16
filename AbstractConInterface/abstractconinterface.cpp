#include "abstractconinterface.h"



<<<<<<< HEAD
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
=======
AbstractConInterface::AbstractConInterface()
    : UniGraphicsItemObject(nullptr,nullptr){
    initial();

}

AbstractConInterface::AbstractConInterface(const ComponentInfoStruct &cInfo){
    initial();
    intialComponentInfoImpl(cInfo);
}

AbstractConInterface::AbstractConInterface(long sceneID,QGraphicsItem *parent,QObject* parentObject)
    :UniGraphicsItemObject(parentObject,parent),
    _comInfoSPtr(nullptr),
    _shadowEffect(nullptr),
    _comNickName(""),
    _sceneId(sceneID),
    _tickNew(false),
    _curTickType(TICK_TYPE::NO_TICK)
{
    initial();
}

AbstractConInterface::~AbstractConInterface(){
    //Delete all self control widget
    _comWidgetVec.clear();
>>>>>>> c344d8f (修改接口)
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

<<<<<<< HEAD
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
=======
AbstractConInterface *AbstractConInterface::instance(long sceneID, QGraphicsItem *parent){
    AbstractConInterface* resPtr = instanceImpl(sceneID,parent);
    if(nullptr != resPtr && !_comInfoSPtr.isNull()){
        resPtr->setComNickName(_comInfoSPtr->comName);
        resPtr->_comInfoSPtr = _comInfoSPtr;
    }

    return resPtr;
}

bool AbstractConInterface::isComInfoInitial(){
    return !_comInfoSPtr.isNull();
}

ComponentInfoStruct AbstractConInterface::getComInfo(){
    return *_comInfoSPtr.data();
>>>>>>> c344d8f (修改接口)
}

const QSharedPointer<const ComponentInfoStruct> AbstractConInterface::getComInfoSPtr(){//推荐使用
    return _comInfoSPtr;
}

long AbstractConInterface::getSceneId() const
{
    return _sceneId;
}

QString AbstractConInterface::comNickName() const
{
    return _comNickName;
}

void AbstractConInterface::setComNickName(const QString &newComNickName)
{
    if(_comNickName == newComNickName) return ;

    _comNickName = newComNickName;
    emit tellComNickNameChange(_comNickName);
}

QFont AbstractConInterface::textFont() const
{
    return _textFont;
}

void AbstractConInterface::setTextFont(const QFont &newTextFont)
{
    if(_textFont == newTextFont){
        return;
    }

    _textFont = newTextFont;

    emit tellTextFontChange();
}

const QWeakPointer<const QBitArray> &AbstractConInterface::getDataWPtr(UniConnectionPoint *uni){
    return _pointDataMap[uni];
}

UniConnectionPointPtr AbstractConInterface::getCCPointWPtrById(int id){
    if(id<0 || id>=_connectPointVec.size()){
        return QWeakPointer<UniConnectionPoint>{};
    }

    return _connectPointVec[id];
}

const QVector<UniConnectionPointSPtr>& AbstractConInterface::getCCPointVec() const
{
    return _connectPointVec;
}



const QVector<ComponentWidget> &AbstractConInterface::getComponentWidgtes(){
    return _comWidgetVec;
}

<<<<<<< HEAD
bool AbstractConInterface::innitial(const QString &creatTime, const QString &author, const QString &conName, const QString &conImagePath){
    if(_isInitial==true) {
        emit this->newLog(this->getConDescribe(),tr("The virtual conponent has been initialized and should not be initialized again."),AMTL::WARNING);
=======
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




QRect AbstractConInterface::generateTextBouding(const QString &text){
    QFontMetrics fm{_textFont};
    return fm.boundingRect(text);
}

void AbstractConInterface::setSceneId(long newScenceId)
{
    _sceneId = newScenceId;
}

bool AbstractConInterface::loadFromXmlAbstractImpl(QXmlStreamReader *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream reader is a nullptr";
>>>>>>> c344d8f (修改接口)
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

<<<<<<< HEAD
    //接受鼠标悬浮事件
    this->setAcceptHoverEvents(true);
    //可移动，可选择
    this->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
=======
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

bool AbstractConInterface::loadFromXmlExtendImpl(QXmlStreamReader *root){
    Q_UNUSED(root);
>>>>>>> c344d8f (修改接口)

    return true;
}

<<<<<<< HEAD

=======
bool AbstractConInterface::saveToXmlExtendImpl(QXmlStreamWriter *root){
    Q_UNUSED(root);


    return true;
}

void AbstractConInterface::connectionDataChangeImpl(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen){
    Q_UNUSED(changePtr);
    Q_UNUSED(changedIndex);
    Q_UNUSED(changeLen);
    run();
}

void AbstractConInterface::initial(){
    this->setFlags(ItemSendsGeometryChanges | ItemIsSelectable | ItemIsMovable | ItemIsFocusable);

    MAKE_DEA_SHADOW_EFF(_shadowEffect,this)

    //Nick name widget
    QLineEdit* nickNameEditor = new QLineEdit();
    nickNameEditor->setText(_comNickName);

    connect(nickNameEditor,&QLineEdit::textChanged,this,[=](const QString& text){
        setComNickName(text);
    });

    //Auto set text when this was change;
    connect(this,&AbstractConInterface::tellComNickNameChange,nickNameEditor,&QLineEdit::setText);

    QSharedPointer<QWidget> nickWidgetSPtr{nickNameEditor};
    RegisterComWidget(this,
                      nickWidgetSPtr,
                      false,
                      false);
}

void AbstractConInterface::intialComponentInfoImpl(const ComponentInfoStruct &cInfo){
    intialComponentInfoImpl(cInfo.comId,
                            cInfo.comName,
                            cInfo.comDesInfo,
                            cInfo.comAuthor,
                            cInfo.comCreatTimeStr,
                            cInfo.comImagePath,
                            cInfo.comCreatTimeFormat);
}

void AbstractConInterface::intialComponentInfoImpl(const QString &cid, const QString &cName, const QString &cDesInfo, const QString &author, const QString &creatTime, const QString &cImagePath, const QString &timeFormat){

    if(_comInfoSPtr.isNull() == false){
        //Already initial return ;
        return;
    }

    ComponentInfoStruct* newStruct = new ComponentInfoStruct();
    newStruct->comId = cid+author+cName;
    newStruct->comName = cName;
    newStruct->comDesInfo = cDesInfo;
    newStruct->comAuthor = author;
    newStruct->comCreatTime.fromString(creatTime,timeFormat);

    if(!newStruct->comCreatTime.isValid()){
        newStruct->comCreatTime.setDate(QDate{1946,02,04});
    }
    newStruct->comCreatTimeStr = newStruct->comCreatTime.toString(newStruct->comCreatTimeFormat);

    newStruct->comImagePath = cImagePath;
    newStruct->comImage = new QPixmap();
    if(!newStruct->comImage->load(cImagePath)){
        qDebug()<<"Load component image fail, target file path: "<<cImagePath;
        newStruct->comImagePath = ":/default _electronic_component.png";
        newStruct->comImage->load(newStruct->comImagePath);
    }

    _comInfoSPtr.reset(newStruct);
}

int AbstractConInterface::registerConnectionPointImpl(COOR_POS pos, bool outputPoint, QString pointName, int dataBits, int maxBindItemNumber){

    int newId= _connectPointVec.size();

    UniConnectionPoint* newPoint = new UniConnectionPoint(newId,
                                                          pos,
                                                          outputPoint,
                                                          pointName,
                                                          dataBits,
                                                          maxBindItemNumber,
                                                          this);

    UniConnectionPointSPtr newCCPointSPtr(newPoint);

    _connectPointVec.push_back(newCCPointSPtr);
    _pointDataMap[newPoint] = newPoint->getDataPtr();

    //connect data change
    connect(newPoint,&UniConnectionPoint::tellDataChanged,this,[=](UniConnectionPoint* changePtr,qsizetype changedIndex,int changeLen){
        connectionDataChangeImpl(changePtr,changedIndex,changeLen);
    });

    return newId;
}

bool AbstractConInterface::unRegisterConnectionPointImpl(int size){
    if(size>_connectPointVec.size()){
        return false;
    }

    int startIndex= _connectPointVec.size() - size;
    int len = size;

    UniConnectionPoint* ptr;
    while(size){
        ptr = _connectPointVec.back().data();

        if(ptr){
            ptr->hide();//First hide incase this will be some other sptr outside but this is imposable
        }

        //Erase
        _pointDataMap.erase(_pointDataMap.find(ptr),_pointDataMap.find(ptr));

        _connectPointVec.pop_back();//Auto delete this uniconnection point

        --size;
    }

    emit tellConnectionPointsNumChange(startIndex,len,false);

    return true;
}

ComponentWidget *AbstractConInterface::registerComWidgetImpl(QSharedPointer<QWidget> widget, bool pannel, bool manualReleaseWidget){

    ComponentWidget* newComWidget = new ComponentWidget();
    newComWidget->_widgetComponentPtr = this;
    newComWidget->_widgetSPtr = widget;
    newComWidget->_pannelFloat = pannel;
    newComWidget->_manualReleaseWidget = manualReleaseWidget;

    _comWidgetVec.push_back(*newComWidget);

    return newComWidget;
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
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void AbstractConInterface::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QGraphicsView* view= qobject_cast<QGraphicsView*>(event->widget()->parentWidget());
    if(view == nullptr){
        qWarning()<<"The graphics view component does not exist and the context menu cannot be generated.";
        return;
    }

    QMenu menu;



}

void AbstractConInterface::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->modifiers() & Qt::ShiftModifier && event->button() == Qt::LeftButton){
        event->setModifiers(Qt::ControlModifier | event->modifiers());//将shift转为CTRL，保证shift的使用
    }

    QGraphicsItem::mousePressEvent(event);
}

void AbstractConInterface::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->modifiers() & Qt::ShiftModifier && event->button() == Qt::LeftButton){
        event->setModifiers(Qt::ControlModifier | event->modifiers());//将shift转为CTRL，保证shift的使用
    }

    QGraphicsItem::mouseReleaseEvent(event);
}

void AbstractConInterface::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void AbstractConInterface::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

void AbstractConInterface::IntialComponentInfo(AbstractConInterface *targetCom, const QString &cid, const QString &cName, const QString &cDesInfo, const QString &author, const QString &creatTime, const QString &cImagePath, const QString &timeFormat){
    if(nullptr != targetCom){
        targetCom->intialComponentInfoImpl(cid,cName,cDesInfo,author,creatTime,cImagePath,timeFormat);
    }
}

int AbstractConInterface::RegisterConnectionPoint(
    AbstractConInterface *targetCom,
    COOR_POS pos,
    bool outputPoint,
    QString pointName,
    int dataBits,
    int maxBindItemNumber
    ){

    if(nullptr == targetCom){
        return -1;
    }

    return targetCom->registerConnectionPointImpl(pos,outputPoint,pointName,dataBits,maxBindItemNumber);
}

bool AbstractConInterface::UnRegisterConnectionPoint(
    AbstractConInterface* target,
    int size){

    return target->unRegisterConnectionPointImpl(size);
}

bool AbstractConInterface::RegisterComWidget(
    AbstractConInterface *targetCom,
    QSharedPointer<QWidget> widget,
    bool pannel,
    bool manualReleaseWidget
    ){
    if(nullptr == targetCom){
        return false;
    }
    targetCom->registerComWidgetImpl(widget,pannel,manualReleaseWidget);
    return true;
}
>>>>>>> c344d8f (修改接口)
