#include "abstractconinterface.h"



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
}

bool AbstractConInterface::loadStatusFormXml(QXmlStreamReader *root){
    return loadFromXmlAbstractImpl(root);
}

bool AbstractConInterface::saveStatusToXml(QXmlStreamWriter *root){
    return saveToXmlAbstractImpl(root);
}

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

bool AbstractConInterface::loadFromXmlExtendImpl(QXmlStreamReader *root){
    Q_UNUSED(root);

    return true;
}

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
