#include "UniConnectionPoint.h"

using namespace AMTL;
using namespace AMTL::COLOR;

UniConnectionPoint::UniConnectionPoint()
    : UniGraphicsItemObject(nullptr,nullptr),
    _id(-1),
    _selfPos(COOR_POS::BELOW),
    _outputConnectionPoint(true),
    _pointName(""),
    _linkStautes(UNREQUEST_LINK),//This deafault is fine
    _highResistance(true),
    _dataBitsLen(1),
    _maxBindItemNumber(0),
    _showPointName(true),
    _textDirection(TextDriection::BELOW)
{
    initial();
}

UniConnectionPoint::UniConnectionPoint(int id, COOR_POS pos, bool outputPoint, QString pointName,int dataBits ,int maxBindItemNumber, QGraphicsItem *parent)
    : UniGraphicsItemObject(nullptr,parent),
    _id(id),
    _selfPos(pos),
    _outputConnectionPoint(outputPoint),
    _pointName(pointName),
    _linkStautes(UNREQUEST_LINK),//This deafault is fine
    _highResistance(true),
    _dataBitsLen(dataBits),
    _maxBindItemNumber(maxBindItemNumber),
    _showPointName(true),
    _textDirection(TextDriection::BELOW)
{
    initial();
}

UniConnectionPoint::~UniConnectionPoint()
{
    if(nullptr != _shadowEffect) _shadowEffect->deleteLater();
    _shadowEffect = nullptr;


    blockSignals(true);//信号大多还是只和本组件相关，所以直接断掉--在析构期间全是垃圾信号

    while(_bindPointVec.size()){
        //Unbind all the connection, make sure it will not be any uniconnection connect to a unvalid connection point.
        unBindConnectionPointImpl(_bindPointVec.back());//This will automaticly make sure bind point vec no longer contain this connection point.
    }

}


/************************************************
*
* Slots function definition
*
*************************************************/
void UniConnectionPoint::linkLineItemPoschange(const QPointF& oldPos,const QPointF& newPos)
{
    Q_UNUSED(oldPos);
    Q_UNUSED(newPos);

    //此路径存在问题，由于未完全更新完成，在获取到的pos内仍是旧坐标
}

void UniConnectionPoint::linkLineItemPosHasChanged()
{
    prepareGeometryChange();
    gneratePainterPath();//重新生成路径
}

void UniConnectionPoint::linkLineRequestUnbind(UniLinkLine *targetLineHead)
{
    int targetConnectionPointIndex = findBindConnectionPointIndexByLineHead(targetLineHead);
    if(targetConnectionPointIndex==-1) return;

    unBindConnectionPointImpl(_bindPointVec[targetConnectionPointIndex]);
}



/************************************************
*
* Class function definition
*
*************************************************/
QWeakPointer<const QBitArray> UniConnectionPoint::getDataPtr()
{
    return QWeakPointer{_dataPtrSelf};
}

bool UniConnectionPoint::getDataValue(qsizetype index, bool *ok){
    if(_dataPtrSelf->size() <= index){
        if(nullptr != ok) *ok =false;
        return false;
    }

    if(nullptr != ok) *ok =true;
    return _dataPtrSelf->testBit(index);
}

//Only allow data changed here, if change will notify the parent item to do some jobs;
qsizetype UniConnectionPoint::setDataValue(const QBitArray& value, qsizetype indexStart)
{
    if(_outputConnectionPoint == false){
        qWarning()<<"Setting data to connection points with input attributes is not allowed.";
        return -2;
    }

    if(indexStart>=_dataPtrSelf->size() || indexStart < 0) return -1;

    bool changed=false;
    for(int i=indexStart;i<value.size() && i<_dataPtrSelf->size();++i){
        if(_dataPtrSelf->testBit(i) != value.testBit(i)) {
            changed=true;
            _dataPtrSelf->setBit(i,value.testBit(i));//Trans this bit to the data
        }
    }

    //Only emit sig when there got true change
    if(changed) {
        emit tellDataChanged(this,indexStart,(indexStart+value.size())%_dataPtrSelf->size()-indexStart);

        //Set all the connection data;
        for(int i=0;i<_bindPointVec.size();++i){
            //Only change data when this connection point is a output type point
            _bindPointVec[i]->inputDataValue(value, indexStart);//This change storm will stop when the data won't change
        }

        return (indexStart+value.size())%_dataPtrSelf->size()-indexStart;
    }

    return 0;
}

bool UniConnectionPoint::highResistance() const
{
    return _highResistance;
}

void UniConnectionPoint::setHighResistance(bool newHighResistance)
{
    if(newHighResistance == _highResistance){
        return ;
    }

    _highResistance = newHighResistance;

    if(_outputConnectionPoint){
        //Set all the connection data;
        for(int i=0;i<_bindPointVec.size();++i){
            //Only change data when this connection point is a output type point
            _bindPointVec[i]->setHighResistance(newHighResistance);
        }
    }else{
        //恢复高阻抗时，恢复数据为0，注意到这里会导致产生一个数据变化的信号，在该连接点析构时该信号会被屏蔽，避免将信号发送到了不存在的父对象。
        if(_highResistance) inputDataValue(QBitArray{_dataPtrSelf->size(),0});
    }

    //该信号自由订阅，目前未有使用
    emit tellHighResistanceStatusChange(_highResistance);
}

bool UniConnectionPoint::getLinkStautes() const
{
    return _linkStautes;
}

TextDriection UniConnectionPoint::textDirection() const
{
    return _textDirection;
}

void UniConnectionPoint::setTextDirection(TextDriection newTextDirection)
{
    if(_textDirection == newTextDirection) return ;
    emit(_textDirection,newTextDirection);
    _textDirection = newTextDirection;
    gneratePainterPath();
}

QFont UniConnectionPoint::textFont() const
{
    return _textFont;
}

void UniConnectionPoint::setTextFont(const QFont &newTextFont)
{
    if(_textFont == newTextFont) return;
    emit tellTextFontChange(_textFont,newTextFont);
    _textFont = newTextFont;
    gneratePainterPath();
}

QString UniConnectionPoint::pointName() const
{
    return _pointName;
}

void UniConnectionPoint::setPointName(const QString &newPointName)
{
    if(_pointName == newPointName) return;
    emit tellPointNameChange(_pointName,newPointName);
    _pointName = newPointName;
    gneratePainterPath();
}

long UniConnectionPoint::parentItemSceneId() const
{
    return _parentItemSceneId;
}

void UniConnectionPoint::setParentItemSceneId(long newParentItemSceneId)
{
    _parentItemSceneId = newParentItemSceneId;
}

int UniConnectionPoint::id() const
{
    return _id;
}

COOR_POS UniConnectionPoint::selfPos() const
{
    return _selfPos;
}

void UniConnectionPoint::setSelfPos(COOR_POS newSelfPos)
{
    if(_selfPos == newSelfPos) return;
    emit tellSelfPosChange(_selfPos,newSelfPos);
    _selfPos = newSelfPos;
    gneratePainterPath();
}

bool UniConnectionPoint::isBindThisConnnectionPoint(UniConnectionPoint *target)
{
    if(_bindPointVec.size()==0) return false;
    for(auto& item : _bindPointVec){
        if(target == item) return true;
    }
    return false;
}

int UniConnectionPoint::findBindConnectionPointIndex(UniConnectionPoint *target)
{
    if(target==nullptr) return -1;
    if(_bindPointVec.size()==0) return -1;

    for(int i = 0;i <_bindPointVec.size() ;++i){
        if(target == _bindPointVec[i]) return i;
    }

    return -1;
}

int UniConnectionPoint::findBindConnectionPointIndexByLineHead(UniLinkLine *targetLineHead)
{
    if(targetLineHead==nullptr) return -1;
    if(_lineHeadVec.size()==0) return -1;

    for(int i = 0;i <_lineHeadVec.size() ;++i){
        if(targetLineHead == _lineHeadVec[i]) return i;
    }

    return -1;
}

bool UniConnectionPoint::bindConnectionPoint(UniConnectionPoint *target)
{
    return bindConnectionPointImpl(target);
}

bool UniConnectionPoint::unBindConnectionPoint(UniConnectionPoint *targetPoint)
{
    return unBindConnectionPointImpl(targetPoint);
}

bool UniConnectionPoint::loadFormXml(QXmlStreamReader *root){
    return loadFormXmlImpl(root);
}

bool UniConnectionPoint::saveToXml(QXmlStreamWriter *root){
    return saveToXmlImpl(root);
}

bool UniConnectionPoint::loadLinkFormXml(UniConnectionPoint* targetPoint, const QString& lineText){
    return loadLinkFormXmlImpl(targetPoint,lineText);
}

bool UniConnectionPoint::saveLinkToXml(QXmlStreamWriter *root){
    return saveLinkSToXmlImpl(root);
}

void UniConnectionPoint::setBindStautes(bool newLinkStautes)
{
    if(newLinkStautes == _linkStautes) return;
    _linkStautes = newLinkStautes;
    emit tellParentBindStatusChange(_linkStautes,this);
    update();
}

qsizetype UniConnectionPoint::inputDataValue(QBitArray value, qsizetype indexStart)
{
    if(indexStart>_dataPtrSelf->size() || indexStart <0) return -1;

    bool changed=false;
    for(int i=indexStart;i<value.size() && i<_dataPtrSelf->size();++i){
        if(_dataPtrSelf->testBit(i) != value.testBit(i)) {
            changed=true;
            _dataPtrSelf->setBit(i,value.testBit(i));//Trans this bit to the data
        }
    }

    //Only emit sig when there got true change
    if(changed) {
        emit tellDataChanged(this,indexStart,(indexStart+value.size())%_dataPtrSelf->size()-indexStart);
        return (indexStart+value.size())%_dataPtrSelf->size()-indexStart;
    }

    return 0;
}

QList<QPoint> UniConnectionPoint::gnerateLinePointList(UniConnectionPoint *target)
{
    if(target == nullptr) return {};

    static const int spacer = 40;

    QList<QPoint> res;
    QPoint thisPos= this->scenePos().toPoint();
    QPoint targetPos= target->scenePos().toPoint();


    //同向
    if(_selfPos == target->_selfPos){
        //Same direction
        switch(_selfPos){

        case COOR_POS::ABOVE:{
            res.push_back({thisPos.x(),thisPos.y() < targetPos.y() ? thisPos.y() - 40 : targetPos.y()-40});
            res.push_back({targetPos.x(),thisPos.y() < targetPos.y() ? thisPos.y() - 40 : targetPos.y()-40});
            break;
        }
        case COOR_POS::BELOW:{
            res.push_back({thisPos.x(),thisPos.y() > targetPos.y() ? thisPos.y() + 40 : targetPos.y() + 40});
            res.push_back({targetPos.x(),thisPos.y() > targetPos.y() ? thisPos.y() + 40 : targetPos.y() + 40});
            break;
        }
        case COOR_POS::LEFT:{
            res.push_back({thisPos.x() < targetPos.x() ? thisPos.x() - 40 : targetPos.x() - 40,thisPos.y()});
            res.push_back({thisPos.x() < targetPos.x() ? thisPos.x() - 40 : targetPos.x() - 40,targetPos.y()});
            break;
        }
        case COOR_POS::RIGHT:{
            res.push_back({thisPos.x() > targetPos.x() ? thisPos.x() + 40 : targetPos.x() + 40,thisPos.y()});
            res.push_back({thisPos.x() > targetPos.x() ? thisPos.x() + 40 : targetPos.x() + 40,targetPos.y()});
            break;
        }
        }

        return res;
    }

    //
    if((_selfPos == COOR_POS::ABOVE && target->_selfPos == COOR_POS::BELOW)
        || (_selfPos == COOR_POS::LEFT && target->_selfPos == COOR_POS::RIGHT)
        || (target->_selfPos == COOR_POS::ABOVE && _selfPos == COOR_POS::BELOW)
        || (target->_selfPos == COOR_POS::LEFT && _selfPos == COOR_POS::RIGHT)){
        //Reverse dir
        QPoint midPos;
        switch(_selfPos){
        case COOR_POS::ABOVE:{
            thisPos.setX(thisPos.x());
            thisPos.setY(thisPos.y()-40);
            midPos.setX((thisPos.x()+targetPos.x())/2);
            midPos.setY(thisPos.y());
            res.push_back(thisPos);
            res.push_back(midPos);
            targetPos.setY(targetPos.y() +40);
            midPos.setY(targetPos.y());
            res.push_back(midPos);
            res.push_back(targetPos);
            break;
        }
        case COOR_POS::BELOW:{
            thisPos.setX(thisPos.x());
            thisPos.setY(thisPos.y()+40);
            midPos.setX((thisPos.x()+targetPos.x())/2);
            midPos.setY(thisPos.y());
            res.push_back(thisPos);
            res.push_back(midPos);
            targetPos.setY(targetPos.y()-40);
            midPos.setY(targetPos.y());
            res.push_back(midPos);
            res.push_back(targetPos);
            break;
        }
        case COOR_POS::LEFT:{
            thisPos.setX(thisPos.x()-40);
            res.push_back(thisPos);
            midPos.setX(thisPos.x());
            midPos.setY(thisPos.y()<targetPos.y() ? thisPos.y()-40 : targetPos.y()-40);
            res.push_back(midPos);
            targetPos.setX(targetPos.x() + 40);
            midPos.setX(targetPos.x());
            res.push_back(midPos);
            res.push_back(targetPos);
            break;
        }
        case COOR_POS::RIGHT:{
            thisPos.setX(thisPos.x()+40);
            res.push_back(thisPos);
            midPos.setX(thisPos.x());
            midPos.setY(thisPos.y()>targetPos.y() ? thisPos.y()+40 : targetPos.y()+40);
            res.push_back(midPos);
            targetPos.setX(targetPos.x() - 40);
            midPos.setX(targetPos.x());
            res.push_back(midPos);
            res.push_back(targetPos);
            break;
        }
        }
        return res;
    }






    QPoint tempPoint = thisPos;

//    if(thisPos.x() == targetPos.x()){
//        if(thisPos.y() == targetPos.y()){
//            tempPoint.setX((thisPos.x() + targetPos.x())/2);
//            tempPoint.setY((thisPos.y() + targetPos.y())/2);

//            res.push_back(tempPoint);
//        }else{
//            res.push_back(targetPos);
//        }

//        return res;
//    }else{
//        if(thisPos.y() == targetPos.y()){
//            res.push_back(targetPos);
//        }else{
//            if(takeXFirst){
//                res.push_back({thisPos.x(),targetPos.y()});
//            }else{
//                res.push_back({targetPos.x(),thisPos.y()});
//            }
//            res.push_back(targetPos);
//        }
//    }
//    return res;


    bool takeXFirst =false;
    switch(_selfPos){
    case COOR_POS::ABOVE:{
        tempPoint.setY(thisPos.y()-spacer);
        res.push_back(tempPoint);
        takeXFirst=false;
        break;
    }
    case COOR_POS::BELOW:{
        tempPoint.setY(thisPos.y()+spacer);
        res.push_back(tempPoint);
        takeXFirst=false;
        break;
    }
    case COOR_POS::LEFT:{
        tempPoint.setX(thisPos.x()-spacer);
        res.push_back(tempPoint);
        takeXFirst=true;
        break;
    }
    case COOR_POS::RIGHT:{
        tempPoint.setX(thisPos.x()+spacer);
        res.push_back(tempPoint);
        takeXFirst=true;
        break;
    }
    }

    tempPoint = targetPos;
    switch(target->_selfPos){
    case COOR_POS::ABOVE:{
        tempPoint.setY(targetPos.y()-spacer);
        res.push_back(tempPoint);
        tempPoint.setX(targetPos.x());
        res.push_back(tempPoint);
        break;
    }
    case COOR_POS::BELOW:{
        tempPoint.setY(targetPos.y()+spacer);
        res.push_back(tempPoint);
        tempPoint.setX(targetPos.x());
        res.push_back(tempPoint);
        break;
    }
    case COOR_POS::LEFT:{
        tempPoint.setX(targetPos.x()-spacer);
        res.push_back(tempPoint);
        tempPoint.setY(targetPos.y());
        res.push_back(tempPoint);
        break;
    }
    case COOR_POS::RIGHT:{
        tempPoint.setX(targetPos.x()+spacer);
        res.push_back(tempPoint);
        tempPoint.setY(targetPos.y());
        res.push_back(tempPoint);
        break;
    }
    }
    return res;



}

void UniConnectionPoint::initial()
{
    InitiaStaticVar();

    //Shadow
    MAKE_DEA_SHADOW_EFF(_shadowEffect,this)

    _highResistance = false;

    //Data
    _dataPtrSelf.reset(new QBitArray{_dataBitsLen});

    //Sig connect
    //Make sure every sig will be update
    connect(this,&UniConnectionPoint::requestGenratePath,this,&UniConnectionPoint::gneratePainterPath);//note this should be delete, it should not be connect by this.

    //After init gnerate the first painter path.
    gneratePainterPath();

    //make sure this can be update shape
    this->setFlags(ItemSendsGeometryChanges | ItemIsSelectable);
    this->setFlag(ItemIsMovable,false);//不可移动
}

void UniConnectionPoint::gneratePainterPath()
{
    prepareGeometryChange();

    _itemPainterPath.clear();
    //Link Line
    for(int i=0;i<_bindPointVec.size();++i){
        if(_outputConnectionPoint){//输出端口管理所有的连接线的头部
            //Start by this connection point;
            _itemPainterPath.moveTo(ZERO_POINT);
            _itemPainterPath.lineTo(mapFromScene(_lineHeadVec[i]->scenePos()));
        }else{
            _itemPainterPath.moveTo(ZERO_POINT);
            _itemPainterPath.lineTo(mapFromScene(_lineTailVec[i]->scenePos()));
        }
    }

    //Main body
    _itemPainterPath.moveTo(ZERO_POINT);
    _itemPainterPath.addRect(__mainBodyRectCll);

    //Text
    if(Q_LIKELY(_showPointName)){
        gnerateText();
        _itemPainterPath.addText(_finalTextBLPos,_textFont, _finalText);
    }

    //other
    //Expand this border make sure every thing can be coverd.
    _boudingRect = _itemPainterPath.boundingRect();
    _boudingRect.moveTopLeft({_boudingRect.x()-6,_boudingRect.y()-8});
    _boudingRect.setHeight(_boudingRect.height()+16);
    _boudingRect.setWidth(_boudingRect.width()+12);

    //Update this graphics item.
    update();
}

void UniConnectionPoint::gnerateText()
{

    _finalText = _pointName + QString::number(_dataBitsLen);

    /* + ((_maxBindItemNumber ==1) ? \
     * QString(" (%1)").arg(_dataBitsLen) : \
     * QString(" (%1,%2/%3)").arg(_dataBitsLen).arg(_bindPointVec.size()).arg(_maxBindItemNumber));
    */

    QFontMetrics fm{_textFont};
    QRect finalTextBouding = fm.boundingRect(_finalText);

    switch (_textDirection) {
    case TextDriection::BELOW:{
        _finalTextBLPos.setX(-finalTextBouding.width()/2);
        _finalTextBLPos.setY(finalTextBouding.height()+__mainBodyWH/2);
        break;
    }
    case TextDriection::ABOVE:{
        _finalTextBLPos.setX(-finalTextBouding.width()/2);
        _finalTextBLPos.setY(-__mainBodyWH/2 - fm.descent());

        break;
    }
    case TextDriection::LEFT:{
        _finalTextBLPos.setX(-finalTextBouding.width()-__mainBodyWH/2-4);
        _finalTextBLPos.setY(finalTextBouding.height()/2 - fm.descent());

        break;
    }
    case TextDriection::RIGHT:{
        _finalTextBLPos.setX(__mainBodyWH/2+4);
        _finalTextBLPos.setY(finalTextBouding.height()/2 - fm.descent());
        break;
    }
    }
}

bool UniConnectionPoint::creatNewLine(const QList<QPoint> &pointList, UniLinkLine** lineHead, UniLinkLine** lineTail)
{
    Q_UNUSED(lineHead);
    Q_UNUSED(lineTail);

    if(pointList.size()==0) return false;
    auto lineList = UniLinkLine::creatLineWithPoints(pointList);

    if(lineList.size() !=2){
        assert("返回的列表大小应该为2，请检查输入的pointList是否正确");
    }

    *lineHead = lineList[0];
    *lineTail = lineList[1];

    if(scene() != nullptr){
        auto ptr = *lineHead;
        auto scenePtr=scene();

        while(ptr!=*lineTail){
            scenePtr->addItem(ptr);
            ptr=ptr->getNextItem();
        }
        scenePtr->addItem(ptr);
    }

    return true;
}

bool UniConnectionPoint::deleteLine(UniLinkLine *lineHead, UniLinkLine *lineTail)
{
    if(lineHead == nullptr || lineTail ==nullptr) return false;

    UniLinkLine* ptr;
    while(lineHead && lineHead!=lineTail){
        ptr=lineHead;
        lineHead = lineHead->getNextItem();
        ptr->deleteLater();
    }
    lineTail->deleteLater();
    return true;
}

bool UniConnectionPoint::bindConnectionPointImpl(UniConnectionPoint *targetConnectionPoint)
{
    //sig connect
    //link line position change
    //data change--Will be set when data been set and changed
    //Data set function .this must be the same bits array.--Maybe some time later could add
    //target point deleted sig--Will auotmatic unbind all link relation, no need to care
    if(targetConnectionPoint==nullptr) return false;
    if(isBindThisConnnectionPoint(targetConnectionPoint))return true;
    if(targetConnectionPoint->_outputConnectionPoint == _outputConnectionPoint){
        qWarning()<<"It is not allowed to connect two points with the same input/output attributes together.";

        emit toastInfo(tr("注意"),
                  tr("不允许将具有相同输入/输出的数据连接点连接到一起。"),
                  true,
                  AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                  AMTL::ToastInfoType::TIP_WARNING);

        targetConnectionPoint->_linkStautes = UNREQUEST_LINK;
        targetConnectionPoint->update();

        _linkStautes = UNREQUEST_LINK;
        update();

        return false;
    }
    if((_outputConnectionPoint == false && _bindPointVec.size())
        || (targetConnectionPoint->_outputConnectionPoint ==false && targetConnectionPoint->_bindPointVec.size())){
        qWarning()<<"It is not allowed for one input connection point to connect multiple output endpoints.("<< _id <<":" <<_pointName<<")";

        targetConnectionPoint->_linkStautes = UNREQUEST_LINK;
        targetConnectionPoint->update();

        _linkStautes = UNREQUEST_LINK;
        update();
        return false;
    }
    if(_bindPointVec.size() >= _maxBindItemNumber) return false;

    if(_outputConnectionPoint){
        auto linePointList  = gnerateLinePointList(targetConnectionPoint);
        UniLinkLine* lineHead=nullptr,*lineTail=nullptr;
        if(creatNewLine(linePointList,&lineHead,&lineTail)){
            _bindPointVec.push_back(targetConnectionPoint);
            _lineHeadVec.push_back(lineHead);
            _lineTailVec.push_back(lineTail);
            connect(lineHead,&UniLinkLine::positionChange,this,&UniConnectionPoint::linkLineItemPoschange);
            connect(lineHead,&UniLinkLine::positionHasChanged,this,&UniConnectionPoint::linkLineItemPosHasChanged);
            connect(lineHead,&UniLinkLine::tellUnbind,this,&UniConnectionPoint::linkLineRequestUnbind);

            //Make sure target save all the info
            if(Q_LIKELY(targetConnectionPoint->bindConnctionPointInputImpl(this,lineHead,lineTail))){
                targetConnectionPoint->inputDataValue(*_dataPtrSelf.data());
                ;
            }else{
                assert("Please check head and tail is create?");
            }
        }else{
            qFatal("创建连接点失败，检查输入参数");
            assert("创建连接点失败，检查输入参数");
            return false;
        }
    }else{
        //Give control rights to target point;
        return targetConnectionPoint->bindConnectionPointImpl(this);
    }

    qInfo()<<"The data connection point was successfully bound. Output("<<_id<<":"<<_pointName<<")-Input("<<targetConnectionPoint->_id<<":"<<targetConnectionPoint->_pointName<<")";

    _linkStautes = UNREQUEST_LINK;
    gneratePainterPath();
    return true;
}

bool UniConnectionPoint::bindConnectionPointWithLineTextImpl(UniConnectionPoint *targetConnectionPoint,const QString& lineText){
    //sig connect
    //link line position change
    //data change--Will be set when data been set and changed
    //Data set function .this must be the same bits array.--Maybe some time later could add
    //target point deleted sig--Will auotmatic unbind all link relation, no need to care
    if(targetConnectionPoint==nullptr) return false;
    if(isBindThisConnnectionPoint(targetConnectionPoint))return true;
    if(targetConnectionPoint->_outputConnectionPoint == _outputConnectionPoint){
        qWarning()<<"It is not allowed to connect two points with the same input/output attributes together.";

        emit toastInfo(tr("注意"),
                       tr("不允许将具有相同输入/输出的数据连接点连接到一起。"),
                       true,
                       AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
                       AMTL::ToastInfoType::TIP_WARNING);

        targetConnectionPoint->update();

        update();
        return false;
    }

    if((_outputConnectionPoint == false && _bindPointVec.size())
        || (targetConnectionPoint->_outputConnectionPoint ==false && targetConnectionPoint->_bindPointVec.size())){

        qWarning()<<"It is not allowed for one input connection point to connect multiple output endpoints.("<< _id <<":" <<_pointName<<")";

        targetConnectionPoint->update();

        update();
        return false;
    }
    if(_bindPointVec.size() >= _maxBindItemNumber) return false;

    if(_outputConnectionPoint){

        UniLinkLine* lineHead=nullptr,*lineTail=nullptr;
        auto line = UniLinkLine::loadLineFromText(lineText);

        if(line.size()!=2){
            //line creat fail
            qFatal("创建连接点失败，检查输入参数");
            assert("line should be two");
            return false;
        }

        lineHead = line[0];
        lineTail = line[1];

        if(scene() != nullptr){
            auto ptr = lineHead;
            auto scenePtr=scene();

            while(ptr!=lineTail){
                scenePtr->addItem(ptr);
                ptr=ptr->getNextItem();
            }
            scenePtr->addItem(ptr);
        }

        _bindPointVec.push_back(targetConnectionPoint);
        _lineHeadVec.push_back(lineHead);
        _lineTailVec.push_back(lineTail);

        connect(lineHead,&UniLinkLine::positionChange,this,&UniConnectionPoint::linkLineItemPoschange);
        connect(lineHead,&UniLinkLine::positionHasChanged,this,&UniConnectionPoint::linkLineItemPosHasChanged);
        connect(lineHead,&UniLinkLine::tellUnbind,this,&UniConnectionPoint::linkLineRequestUnbind);

        //Make sure target save all the info
        if(Q_LIKELY(targetConnectionPoint->bindConnctionPointInputImpl(this,lineHead,lineTail))){
            targetConnectionPoint->inputDataValue(*_dataPtrSelf.data());
            ;
        }else{
            assert("Please check head and tail is create?");
        }

    }else{
        //Give control rights to target point;
        return targetConnectionPoint->bindConnectionPointWithLineTextImpl(this,lineText);
    }

    qInfo()<<"The data connection point was successfully bound. Output("<<_id<<":"<<_pointName<<")-Input("<<targetConnectionPoint->_id<<":"<<targetConnectionPoint->_pointName<<")";

    gneratePainterPath();
    return true;
}

bool UniConnectionPoint::unBindConnectionPointImpl(UniConnectionPoint *targetConnectionPoint)
{
    if(targetConnectionPoint == nullptr) return false;
    int index = findBindConnectionPointIndex(targetConnectionPoint);
    if(index==-1) return false;

    if(this->_outputConnectionPoint){
        UniLinkLine* lineHead,*lineTail;

        lineHead = _lineHeadVec[index];
        lineTail = _lineTailVec[index];

        //Pop out all resources stored here.-safe

        _bindPointVec.erase(_bindPointVec.constBegin()+index);
        _lineHeadVec.erase(_lineHeadVec.constBegin()+index);
        _lineTailVec.erase(_lineTailVec.constBegin()+index);
//        auto bindStart = _bindPointVec.constBegin();
//        auto lineHeadStart = _lineHeadVec.constBegin();
//        auto lineTailStart = _lineTailVec.constBegin();
//        _bindPointVec.erase(bindStart+index);
//        _lineHeadVec.erase(lineHeadStart+index);
//        _lineTailVec.erase(lineTailStart+index);

        //release all the line elements;-safe
        deleteLine(lineHead,lineTail);

        //The target link to unload the data, note here it might be a input point strat a unbind and back here, but now it's parent component might be delete so it will be a nullptr problem.
        targetConnectionPoint->unBindConnectionPointInputImpl(this);
    }else{
        //Dame this is the problem
        //Give control rights to output points;
        return targetConnectionPoint->unBindConnectionPointImpl(this);
    }

    gneratePainterPath();
    return false;
}

bool UniConnectionPoint::bindConnctionPointInputImpl(UniConnectionPoint *target, UniLinkLine *lineHead, UniLinkLine *lineTail)
{
    if(target==nullptr || lineHead == nullptr || lineTail==nullptr ) {
        qWarning()<<"It is not allowed to bind a connection point that does not exist to this input connection point.("<< _id <<":" <<_pointName<<")";
        return false;
    }

    setHighResistance(target->_highResistance);//设定其高阻抗状态为目前连接到的输出点的阻抗状态

    _bindPointVec.push_back(target);
    _lineHeadVec.push_back(lineHead);
    _lineTailVec.push_back(lineTail);

    connect(lineTail,&UniLinkLine::positionChange,this,&UniConnectionPoint::linkLineItemPoschange);
    connect(lineTail,&UniLinkLine::positionHasChanged,this,&UniConnectionPoint::linkLineItemPosHasChanged);
    _linkStautes = false;
    gneratePainterPath();
    return true;
}

bool UniConnectionPoint::unBindConnectionPointInputImpl(UniConnectionPoint *targetPoint)
{
    //找到目标解绑的连接点
    int index = findBindConnectionPointIndex(targetPoint);
    if(index==-1) return false;

    setHighResistance(true);//恢复高阻抗状态

    //Pop out all resources stored here.
    _bindPointVec.erase(_bindPointVec.constBegin()+index);
    _lineHeadVec.erase(_lineHeadVec.constBegin()+index);
    _lineTailVec.erase(_lineTailVec.constBegin()+index);

    //重新生成路径
    gneratePainterPath();
    return true;
}

bool UniConnectionPoint::loadFormXmlImpl(QXmlStreamReader *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream write is a nullptr";
        return false;
    }

    while(!root->atEnd()){

        //UniConnectionPoint Part read
        if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
            && UniCCPointXmlLabel == root->name().toString()){
            //UniConnectionPoint xml part

            //Basic info just ignore
            if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
                && UniCCPointXmlLabel == root->name().toString()){
                QXmlStreamAttributes attr = root->attributes();
                if(attr.hasAttribute("high_resistance")){
                    _highResistance = attr.value("high_resistance").toInt();
                }
            }

            //Data
            if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
                && UniCCPointDataXmlLabel == root->name().toString()){

                QXmlStreamAttributes attrs = root->attributes();
                long bits_len= -1 ;
                if(attrs.hasAttribute("data_bits_len")){
                    bits_len = attrs.value("data_bits_len").toLong();
                }
                if(bits_len != _dataBitsLen){
                    assert("data bits len should be the same");
                    return false;
                }

                //Start read uniconnection data
                root->readNext();
                for(int i=0;i<bits_len && !root->atEnd() ;){
                    if(root->tokenType() == QXmlStreamReader::TokenType::StartElement
                        && UniCCPointBDataXmlLabel == root->name().toString()){
                        attrs = root->attributes();
                        if(attrs.hasAttribute("data")){
                            _dataPtrSelf->setBit(i,(bool)attrs.value("value").toInt());
                        }
                    }

                    if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
                        && UniCCPointBDataXmlLabel == root->name().toString()){
                        ++i;
                    }

                    root->readNext();
                }//Read end;

            }

        }

        if(root->tokenType() == QXmlStreamReader::TokenType::EndElement
            && UniCCPointXmlLabel == root->name().toString()){
            break;
        }

        root->readNext();
    }

    return true;
}

bool UniConnectionPoint::saveToXmlImpl(QXmlStreamWriter *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream write is a nullptr";
        return false;
    }

    root->writeStartElement(UniCCPointXmlLabel);

    root->writeAttribute("id",QString::number(_id));
    root->writeAttribute("self_pos",QString::number((int)_selfPos));
    root->writeAttribute("output_connection_point",QString::number(_outputConnectionPoint));
    root->writeAttribute("point_name",_pointName);
    root->writeAttribute("high_resistance",QString::number(_highResistance));

    {//Data-bits start
        root->writeStartElement(UniCCPointDataXmlLabel);
        root->writeAttribute("data_bits_len",QString::number(_dataBitsLen));
        for(int i=0;i<_dataBitsLen; ++i){
            root->writeStartElement(UniCCPointBDataXmlLabel);
            root->writeAttribute("value",QString::number(_dataPtrSelf->testBit(i)));
            root->writeEndElement();
        }
        root->writeEndElement();
    }//UNiCCPoint data end;

    root->writeEndElement();//UniCCPoint end;

    return true;
}

bool UniConnectionPoint::loadLinkFormXmlImpl(UniConnectionPoint* targetPoint, const QString& lineText){
    if(nullptr == targetPoint) {return false;}

    return bindConnectionPointWithLineTextImpl(targetPoint,lineText);
}

bool UniConnectionPoint::saveLinkSToXmlImpl(QXmlStreamWriter *root){
    if(root == nullptr) {
        qCritical()<<"XMl stream write is a nullptr";
        return false;
    }

    root->writeStartElement(UniCCPointLineXmlLabel);
    if(_outputConnectionPoint){
        root->writeAttribute("parent_scene_id",QString::number(_parentItemSceneId));
        root->writeAttribute("line_num",QString::number(_bindPointVec.size()));
        for(int i = 0;i<_bindPointVec.size();++i){
            root->writeStartElement("line");
            root->writeAttribute("from_connection_point_id",QString::number(_id));

            root->writeAttribute("target_parent_scene_id",QString::number(_bindPointVec[i]->_parentItemSceneId));
            root->writeAttribute("target_connection_point_id",QString::number(_bindPointVec[i]->_id));
            root->writeCharacters(UniLinkLine::saveLineToText(_lineHeadVec[i]));
            root->writeEndElement();
        }
    }else{
        root->writeAttribute("parent_scene_id",QString::number(_parentItemSceneId));
        root->writeAttribute("line_num",QString::number(0));
    }

    root->writeEndElement();

    return true;
}






/************************************************
*
* Class Interface and override function definition
*
*************************************************/


QPointF UniConnectionPoint::getRealItemCenterScenePos()
{
    return mapToScene(AMTL::ZERO_POINTF);
}
QRectF UniConnectionPoint::getRealBoudingRect()
{
    QPainterPath path;
    QRectF realBouding;

    path.moveTo(ZERO_POINT);
    path.addRect(__mainBodyRectCll);

    //Text
    if(Q_LIKELY(_showPointName)){
        path.addText(_finalTextBLPos,_textFont, _finalText);
    }

    //other
    //Expand this border make sure every thing can be coverd.
    realBouding = path.boundingRect();
    realBouding.moveTopLeft({realBouding.x()-6,realBouding.y()-8});
    realBouding.setHeight(realBouding.height()+16);
    realBouding.setWidth(realBouding.width()+12);

    return realBouding;
}

QRectF UniConnectionPoint::boundingRect() const
{
    return _boudingRect;
}

void UniConnectionPoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);//抗锯齿

//    if(isSelected()){
//        painter->setPen(Qt::DashDotLine);
//        painter->drawRoundedRect(_boudingRect,8,8);
//    }

    //Link Line
    painter->setPen(__uniNorPen);
    painter->setBrush(__uniNorBrush);
    for(int i=0;i<_bindPointVec.size();++i){
        if(_outputConnectionPoint){
            //Start by this connection point;
            painter->drawLine(ZERO_POINT, mapFromScene(_lineHeadVec[i]->scenePos()));
        }else{
            painter->drawLine(ZERO_POINT,mapFromScene(_lineTailVec[i]->scenePos()));
        }
    }

    //main body always draw
    painter->setPen(__mainBodyPen);
    painter->setBrush(__mainBodyBrush);
    painter->drawEllipse(__mainBodyRect);

    if(_linkStautes){
        painter->setPen(Qt::DashLine);
        painter->drawEllipse(__mainBodyRectCll);
    }

    //when got a link make sure draw a circle in  the center to show the item is alreay been linked.
    if(_bindPointVec.size()){
        painter->setPen(__centerCirclePen);
        painter->setBrush(__centerCircleBrush);
        painter->drawEllipse(__centerCircleRect);
    }

    //show the name of this link point
    if(_showPointName){
        painter->setPen(__textPen);
        painter->setBrush(__textBrush);
        painter->setFont(_textFont);
        painter->drawText(_finalTextBLPos,_finalText);
    }

    painter->restore();
}

QPainterPath UniConnectionPoint::shape() const
{
    return _itemPainterPath;
}

void UniConnectionPoint::contextMenuEvent(QGraphicsSceneContextMenuEvent *event){
    QGraphicsView* view= qobject_cast<QGraphicsView*>(event->widget()->parentWidget());
    if(view == nullptr){
        qWarning()<<"The graphics view component does not exist and the context menu cannot be generated.";
        return;
    }

    QMenu* menu=new QMenu(view);
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(menu);

    shadow->setOffset(0, 0);
    shadow->setColor(QColor(68, 68, 68));
    shadow->setBlurRadius(10);
    menu->setToolTipsVisible(true);
    menu->setToolTipDuration(2000);
    menu->setWindowFlags(menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
    menu->setAttribute(Qt::WA_TranslucentBackground,true);
    menu->setGraphicsEffect(shadow);
    menu->setStyleSheet("QMenu{color:black;background-color:white; border-radius:4px;padding:6px;margin:8px;}"
                        "QMenu::item:text{ padding-left:8px;padding-right:8px; padding-top: 8px; padding-bottom: 8px;}"
                        "QMenu::item:selected{ color:#ffffff;background-color: #ea5455; border-radius:4px;}"
                        "QMenu::separator{height:1px;background:#bbbbbb;margin:5px;margin-left:10px;margin-right:10px;}");

    if(_outputConnectionPoint){
        menu->addAction("输出连接点");
    }else{
        menu->addAction("输入连接点");
    }
    menu->addAction(_pointName);
    menu->addSeparator();
    menu->addAction("Data Bits Len "+ QString::number(_dataBitsLen));
    menu->addAction("Data max link num " + QString::number(_maxBindItemNumber));
    menu->addAction("Cur link num " + QString::number(_bindPointVec.size()));
    menu->addSeparator();
    for(int i=0;i<_dataBitsLen && i<5 ;++i){
        menu->addMenu("Data "+QString::number(i)+"-"+QString::number(_dataPtrSelf->testBit(i)));
    }
    if(_dataBitsLen >5 ){
        menu->addAction("...");
    }

    connect(menu,&QMenu::aboutToHide,menu,&QMenu::deleteLater);

    //Bug will out put UpdateLayeredWindowIndirect failed for ptDst=(868, 552), size=(123x121), dirty=(143x141 -10, -10) (参数错误。)
    menu->exec(QCursor::pos());
}

QVariant UniConnectionPoint::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if(change == GraphicsItemChange::ItemPositionHasChanged){
        gneratePainterPath();
    }
    if(GraphicsItemChange::ItemSelectedHasChanged ==change){
        if(false == value.toBool()){
            setBindStautes(false);
        }
    }
    return value;
}

void UniConnectionPoint::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton /*&& event->modifiers() == Qt::ControlModifier*/ && __mainBodyRectCll.contains(event->pos())){
        //Link request
        if(_bindPointVec.size() < _maxBindItemNumber){
            setBindStautes(!_linkStautes);
        }
    }
    QGraphicsItem::mousePressEvent(event);
}

void UniConnectionPoint::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}



/************************************************
*
* Class static function definition
*
*************************************************/
int UniConnectionPoint::mainBodyWH()
{
    return __mainBodyWH;
}

void UniConnectionPoint::InitiaStaticVar()
{
    static bool init=false;

    if (init) return ;

    __mainBodyWH=16;//主体长宽
    __centerCircleWH = 12;

    __uniLineWidth=2;//正常边界线粗细
    __mainBodyLineWidth = 2;//中心圆的绘制线
    __centerCircleLineWidth = 1;

    __uniNorColor = MAIN_COLOR;
    __uniActColor = NOTIFY_COLOR;

    __mainBodyColor = MAIN_COLOR ;
    __mainBodyBorderColor= MAIN_COLOR.darker(24) ;

    __centerCircleColor = NOTIFY_COLOR;
    __centerCircleBorderColor = NOTIFY_COLOR.darker(24);


    __mainBodyRect.setTopLeft(QPointF{(qreal)(-__mainBodyWH /2),(qreal)(-__mainBodyWH/2)});
    __mainBodyRect.setWidth(__mainBodyWH);
    __mainBodyRect.setHeight(__mainBodyWH);

    __mainBodyRectCll.setTopLeft(QPointF{(qreal)(-__mainBodyWH),(qreal)(-__mainBodyWH)});
    __mainBodyRectCll.setWidth(__mainBodyWH*2);
    __mainBodyRectCll.setHeight(__mainBodyWH*2);

    __centerCircleRect.setTopLeft(QPointF{(qreal)(-__centerCircleWH /2),(qreal)(-__centerCircleWH/2)});
    __centerCircleRect.setWidth(__centerCircleWH);
    __centerCircleRect.setHeight(__centerCircleWH);

    //通用无状态画笔
    __uniNorPen.setColor(__uniNorColor);
    __uniNorPen.setWidth(__uniLineWidth);
    __uniNorBrush.setStyle(Qt::BrushStyle::NoBrush);

    __uniActPen.setColor(__uniActColor);
    __uniActPen.setWidth(__uniLineWidth);
    __uniActBrush.setColor(__uniActColor);
    __uniActBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __mainBodyPen.setColor(__mainBodyBorderColor);
    __mainBodyPen.setWidth(__uniLineWidth);
    __mainBodyBrush.setColor(__mainBodyColor);
    __mainBodyBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __centerCirclePen.setColor(__centerCircleBorderColor);
    __centerCirclePen.setWidth(__centerCircleLineWidth);
    __centerCircleBrush.setColor(__centerCircleColor);
    __centerCircleBrush.setStyle(Qt::BrushStyle::SolidPattern);

    __textPen.setColor(Qt::black);
    __textPen.setWidth(__uniLineWidth);
    //    __textBrush.setColor(__mainBodyColor);
    __textBrush.setStyle(Qt::BrushStyle::NoBrush);

    init=true;
}


//int UniConnectionPoint::__mainBodyWH;//主体长宽
//int UniConnectionPoint::__centerCircleWH;//中心圆的大小
//int UniConnectionPoint::__uniLineWidth;//通用线粗细
//int UniConnectionPoint::__mainBodyLineWidth;//主体绘制线粗细
//int UniConnectionPoint::__centerCircleLineWidth;//中心圆绘制线粗细
//QColor UniConnectionPoint::__uniNorColor;//普通颜色
//QColor UniConnectionPoint::__uniActColor;//激活颜色
//QColor UniConnectionPoint::__mainBodyColor;//主要主体颜色
//QColor UniConnectionPoint::__mainBodyBorderColor;//主要主体边界颜色
//QColor UniConnectionPoint::__centerCircleColor;//中心圆主体颜色
//QColor UniConnectionPoint::__centerCircleBorderColor;//中心圆边界颜色
//QColor UniConnectionPoint::__shadowColor;
//QRectF UniConnectionPoint::__mainBodyRect;
//QRectF UniConnectionPoint::__centerCircleRect;
//QPen UniConnectionPoint::__uniNorPen;//通用激活状态画笔
//QBrush UniConnectionPoint::__uniNorBrush;//通用激活状态画刷
//QPen UniConnectionPoint::__uniActPen;//通用激活状态画笔
//QBrush UniConnectionPoint::__uniActBrush;//通用激活状态画刷
//QPen UniConnectionPoint::__mainBodyPen;//主体画笔
//QBrush UniConnectionPoint::__mainBodyBrush;//主体画刷
//QPen UniConnectionPoint::__centerCirclePen;//画笔
//QBrush UniConnectionPoint::__centerCircleBrush;//画刷
//QPen UniConnectionPoint::__textPen;//画笔
//QBrush UniConnectionPoint::__textBrush;//画刷






