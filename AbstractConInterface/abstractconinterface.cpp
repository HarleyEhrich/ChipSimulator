#include "abstractconinterface.h"

#include <QDir>

ComponentBasicInfoStruct::ComponentBasicInfoStruct(){
    comCreatTimeFormat = "yy-mm-dd";
}

ComponentBasicInfoStruct::ComponentBasicInfoStruct(const ComponentBasicInfoStruct &other){
    *this= other;
}

ComponentBasicInfoStruct &ComponentBasicInfoStruct::operator=(const ComponentBasicInfoStruct &other){
    comId = other.comId;//component的唯一编号
    comName = other.comName;//组件默认名称

    comDesInfo = other.comDesInfo;//组件的描述信息
    comAuthor = other.comAuthor;//组件作者

    comCreatTimeStr = other.comCreatTimeStr;//时间字符串
    comCreatTimeFormat = other.comCreatTimeFormat;
    comCreatTime = other.comCreatTime;//组件创建时间

    comImagePath = other.comImagePath;//组件图片
    comImage = new QPixmap(*other.comImage);//组件图片

    return *this;
}


AbstractConInterface::AbstractConInterface()
    : UniGraphicsItemObject(nullptr,nullptr){
    initial();

}

AbstractConInterface::AbstractConInterface(const ComponentBasicInfoStruct &cInfo){
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
//    emit tellComAboutDestroy(_sceneId,this);

    _shadowEffect->deleteLater();

    blockSignals(true);

    //Delete all self control widget--释放所有浮动设置面板的存在-安全
    for(auto& setItem : _comSettingInfoVec){
        if(setItem._pannelFloat){
            setItem._widgetSPtr->hide();
        }
        setItem._widgetSPtr.clear();
    }
    _comSettingInfoVec.clear();

    //释放所有连接点资源
    UnRegisterConnectionPoint(this,_connectPointVec.size());

    //至此，所有的资源均被释放，等待释放其父类的资源，完成资源释放。
}

void AbstractConInterface::connectionDataChange(UniConnectionPoint *changePtr, qsizetype changedIndex, int changeLen){
    connectionDataChangeImpl(changePtr,changedIndex,changeLen);
}

void AbstractConInterface::connectionBindStatusChange(bool newStatus, UniConnectionPoint* target){
    emit tellCCPointBindStatusChanged(newStatus,_connectPointVec[target->id()]);
}

bool AbstractConInterface::loadStatusFormXml(QXmlStreamReader *root){
    return loadFromXmlAbstractImpl(root);
}

bool AbstractConInterface::saveStatusToXml(QXmlStreamWriter *root){
    return saveToXmlAbstractImpl(root);
}

bool AbstractConInterface::loadLinkFormXml(AbstractConInterface* targetCom,const QString& lineText,long toPointId,long fromPointId){
    return loadLinkFormXmlImpl(targetCom,lineText,toPointId,fromPointId);
}

bool AbstractConInterface::saveLinkToXml(QXmlStreamWriter *root){
    return saveLinkToXmlImpl(root);
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

ComponentBasicInfoStruct AbstractConInterface::getComInfo(){
    return *_comInfoSPtr.data();
}

const QSharedPointer<const ComponentBasicInfoStruct> AbstractConInterface::getComInfoSPtr(){//推荐使用
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



const QVector<ComponentSettingWidgetInfoStruct> &AbstractConInterface::getComponentWidgtes(){
    return _comSettingInfoVec;
}

void AbstractConInterface::preTick(TICK_TYPE tickType){
    Q_UNUSED(tickType);
}

void AbstractConInterface::tick(TICK_TYPE tickType){
    preTick(tickType);

    //make the new type
    _tickNew = true;
    _curTickType = tickType;

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

    _tickNew =false;

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
    if(_sceneId == newScenceId) return ;

    _sceneId = newScenceId;
    for(auto& CCPointItem : _connectPointVec){
        CCPointItem->setParentItemSceneId(_sceneId);
    }
}

bool AbstractConInterface::loadFromXmlAbstractImpl(QXmlStreamReader *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream reader is a nullptr";
        return false;
    }

    while(!root->atEnd()){

        //Basic info
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComponetXmlLabel == root->name().toString() ){
            QXmlStreamAttributes attrs = root->attributes();
            //read attrs
            if(attrs.hasAttribute("scene_id")){
                setSceneId(attrs.value("scene_id").toLong());
            }
            if(attrs.hasAttribute("scene_pos")){
                QStringList pointValueStrList = attrs.value("scene_pos").toString().split(",");
                if(pointValueStrList.size() != 2){
                    qCritical()<<"The scene position data of the abstract component in the xml file is missing";
                    return false;
                }
                setPos(pointValueStrList[0].toLong(),pointValueStrList[1].toLong());
            }

            if(attrs.hasAttribute("nick_name")){
                _comNickName=attrs.value("nick_name").toString();
            }
        }

        //Extend part read
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComponentExtendXmlLabel == root->name().toString()){

            root->readNext();//读取下一节点,进入扩展部分
            if(Q_UNLIKELY(root->atEnd())){
                qCritical()<<"Missing tags in xml file @"<<ComponentExtendXmlLabel;
            }
            if(root->tokenType() != QXmlStreamReader::TokenType::EndElement){
                //如果下一节点不为扩展节点end，就进入读取
                //got in extend part
                loadFromXmlExtendImpl(root);
            }else{
                root->readNext(); // SKip the extend data part
            }
        }

        //UniConnectionPoint Part read
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComponentCCPointXmlLabel == root->name().toString()){

            //UniConnectionPoint xml part
            QXmlStreamAttributes attrs = root->attributes();

            long pointNum =-1;
            if(attrs.hasAttribute("point_num")){
                pointNum = attrs.value("point_num").toLong();
            }

            if(pointNum!=_connectPointVec.size()){
                assert("Should not get the diferent uniconnectionpoint num");
                return false;
            }

            root->readNext();//读取下一节点,进入连接点部分
            for(int i=0;i<pointNum && !root->atEnd();){
                if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
                    && UniCCPointXmlLabel == root->name().toString()){
                    root->readNext();
                    _connectPointVec[i]->loadFormXml(root);
                }

                if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
                    && UniCCPointXmlLabel == root->name().toString()){
                    ++i;
                }

                root->readNext();
            }

        }

        //该组件的信息加载完毕
        if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
            && ComponetXmlLabel == root->name().toString()){
            break;//End read this component info
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

    //--Component info
    root->writeStartElement(ComponetXmlLabel);

    root->writeAttribute("com_id",_comInfoSPtr->comId);
    root->writeAttribute("scene_id",QString::number(this->_sceneId));
    root->writeAttribute("scene_pos",QString("%1,%2").arg(scenePos().x()).arg(scenePos().y()));
    root->writeAttribute("nick_name",_comNickName);

    {//--Component extend info
        root->writeStartElement(ComponentExtendXmlLabel);
        if(!saveToXmlExtendImpl(root)){
            root->writeEndElement();
            //--Component extend info-end
            root->writeEndElement();
            //--Component basic info-end
            return false;
        }
        root->writeEndElement();
    }//--Component extend info-end


    { //--UniConnectionPoint
        root->writeStartElement(ComponentCCPointXmlLabel);
        root->writeAttribute("point_num",QString::number(_connectPointVec.size()));
        //保存连接点信息
        for(auto& ccpPtr : _connectPointVec){
            ccpPtr->saveToXml(root);
        }
        root->writeEndElement();
    }//--UniConnectionPoint-end


    root->writeEndElement();//--Component info-end
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

bool AbstractConInterface::loadLinkFormXmlImpl(AbstractConInterface* targetCom,const QString& lineText,long toPointId,long fromPointId){
    if(nullptr == targetCom){ return false;}

    UniConnectionPointPtr toConnectionPoint = targetCom->getCCPointWPtrById(toPointId);
    if(toConnectionPoint.isNull()){ return false;}

    if(fromPointId >= _connectPointVec.size()){
        return false;
    }

    return _connectPointVec[fromPointId]->loadLinkFormXml(toConnectionPoint.lock().data(),lineText);
}

bool AbstractConInterface::saveLinkToXmlImpl(QXmlStreamWriter *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream write is a nullptr";
        return false;
    }

    root->writeStartElement(ComponentLinkXmlLabel);
    root->writeAttribute("from_com_id",QString::number(_sceneId));
    for(auto& ccpPtr : _connectPointVec){
        ccpPtr->saveLinkToXml(root);
    }
    root->writeEndElement();
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
    QFrame* box = new QFrame();
    QHBoxLayout* boxLay=new QHBoxLayout(box);
    QLabel* nickLab = new QLabel();
    QLineEdit* nickNameEditor = new QLineEdit();
    nickLab->setText(tr("元件名称"));
    nickNameEditor->setText(_comNickName);
    boxLay->addWidget(nickLab);
    boxLay->addWidget(nickNameEditor);
    boxLay->setStretch(0,3);
    boxLay->setStretch(1,7);

    connect(nickNameEditor,&QLineEdit::textChanged,this,[=](const QString& text){
        setComNickName(text);
    });

    //Auto set text when this was change;
    connect(this,&AbstractConInterface::tellComNickNameChange,nickNameEditor,&QLineEdit::setText);

    QSharedPointer<QWidget> nickBoxSPtr{box};
    RegisterComWidget(this,
                      nickBoxSPtr,
                      false,
                      false);

}

void AbstractConInterface::intialComponentInfoImpl(const ComponentBasicInfoStruct &cInfo){
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

    ComponentBasicInfoStruct* newStruct = new ComponentBasicInfoStruct();
    newStruct->comId = cid+author+cName;
    newStruct->comName = cName;
    newStruct->comDesInfo = cDesInfo;
    newStruct->comAuthor = author;
    newStruct->comCreatTime.fromString(creatTime,timeFormat);

    if(!newStruct->comCreatTime.isValid()){
        newStruct->comCreatTime.setDate(QDate{1946,02,04});
    }
    newStruct->comCreatTimeStr = newStruct->comCreatTime.toString(newStruct->comCreatTimeFormat);



#ifdef QT_DEBUG

    //note macox
//#ifdef Q_OS_MACOS
//    newStruct->comImagePath = "/Users/lee/Documents/Projects/QT/ChipSimulator/ChipSimulator/ComponentPlugin/debug/bin/" +cImagePath;
//#elif
        newStruct->comImagePath = "C:/Users/Lee/Documents/Project/Qt/ChipSimulator/ChipSimulator/ComponentPlugin/debug/bin/" +cImagePath;
//#endif

#elif
    newStruct->comImagePath = "./Resources/Plugin/" + cImagePath;
#endif

    newStruct->comImage = new QPixmap();
    if(!newStruct->comImage->load(newStruct->comImagePath)){
        qWarning().noquote()DEBUGINFO<<tr("Load component image fail, target component image file path: ")<<newStruct->comImagePath;
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

    newPoint->setParentItemSceneId(_sceneId);

    UniConnectionPointSPtr newCCPointSPtr(newPoint);
    _connectPointVec.push_back(newCCPointSPtr);
    _pointDataMap[newPoint] = newPoint->getDataPtr();

    //connect data change
    connect(newPoint,&UniConnectionPoint::tellDataChanged,this,&AbstractConInterface::connectionDataChange);

    connect(newPoint,&UniConnectionPoint::tellParentBindStatusChange,this,&AbstractConInterface::connectionBindStatusChange);

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
        //取出一个连接点
        ptr = _connectPointVec.back().data();

        if(ptr){
            ptr->hide();//First hide incase this will be some other sptr outside but this is imposable
        }

        //断开主要的连接部分
        disconnect(ptr,&UniConnectionPoint::tellDataChanged,this,&AbstractConInterface::connectionDataChange);
        disconnect(ptr,&UniConnectionPoint::tellParentBindStatusChange,this,&AbstractConInterface::connectionBindStatusChange);

        //Erase--释放数据缓冲
        _pointDataMap.erase(_pointDataMap.constFind(ptr),_pointDataMap.constFind(ptr));

        //目前删除的连接点智能指针释放。
        _connectPointVec.back().clear();
        _connectPointVec.pop_back();
        //Auto delete this uniconnection point

        --size;
    }

    emit tellConnectionPointsNumChange(startIndex,len,false);

    return true;
}

ComponentSettingWidgetInfoStruct *AbstractConInterface::registerComWidgetImpl(QSharedPointer<QWidget> widget, bool pannel, bool manualReleaseWidget){

    ComponentSettingWidgetInfoStruct* newComWidget = new ComponentSettingWidgetInfoStruct();
    newComWidget->_componentptr = this;
    newComWidget->_widgetSPtr = widget;
    newComWidget->_pannelFloat = pannel;
    newComWidget->_manualReleaseWidget = manualReleaseWidget;

    _comSettingInfoVec.push_back(*newComWidget);

    return newComWidget;
}


QPointF AbstractConInterface::getRealItemCenterScenePos()
{
    return scenePos();
}

QRectF AbstractConInterface::getRealBoudingRect()
{
    return _boudingRect;
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

    QMenu* menu=new QMenu(view);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(menu);
    menu->setToolTipsVisible(true);
    menu->setToolTipDuration(2000);
    menu->setWindowFlags(menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground,true);
    menu->setGraphicsEffect(shadow);
    menu->setStyleSheet("QMenu{color:black;background-color:white; border-radius:4px;padding:6px;margin:8px;}"
                        "QMenu::item:text{ padding-left:8px;padding-right:8px; padding-top: 8px; padding-bottom: 8px;}"
                        "QMenu::item:selected{ color:#ffffff;background-color: #ea5455; border-radius:4px;}"
                        "QMenu::separator{height:1px;background:#bbbbbb;margin:5px;margin-left:10px;margin-right:10px;}");
    shadow->setOffset(0, 0);
    shadow->setColor(QColor(68, 68, 68));
    shadow->setBlurRadius(10);

    connect(menu,&QMenu::aboutToHide,menu,&QMenu::deleteLater);


    QAction* actDeletCom = new QAction(menu);
    actDeletCom->setText(tr("删除元件"));
    actDeletCom->setToolTip(tr("将该节点从连接线上删除，注意，如果少于2个点将会删除链接"));
    menu->addAction(actDeletCom);
    connect(actDeletCom,&QAction::triggered,this,&AbstractConInterface::deleteLater);

    for(auto& settingInfoItem :_comSettingInfoVec){
        if(true == settingInfoItem._pannelFloat){
            QAction* act = new QAction(menu);
            act->setText(settingInfoItem._widgetSPtr->windowTitle());
            menu->addAction(act);
            connect(act,&QAction::triggered,this,[=](){
                if(false == settingInfoItem._widgetSPtr->isHidden()){
                    settingInfoItem._widgetSPtr->show();
                }else{
                    settingInfoItem._widgetSPtr->setFocus();
                    settingInfoItem._widgetSPtr->activateWindow();
                    settingInfoItem._widgetSPtr->setWindowState((settingInfoItem._widgetSPtr->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
                }
            });
        }
    }

    //Bug will out put UpdateLayeredWindowIndirect failed for ptDst=(868, 552), size=(123x121), dirty=(143x141 -10, -10) (参数错误。)
    menu->exec(QCursor::pos());
}

QVariant AbstractConInterface::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemPositionHasChanged){
        for(auto& ccpItem : _connectPointVec){
            ccpItem->linkLineItemPosHasChanged();
        }
    }

    return value;
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





