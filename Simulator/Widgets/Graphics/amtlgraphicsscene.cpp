#include "AmtlGraphicsScene.h"


#include "ControlObj/PluginLoaderController.h"

AmtlGraphicsScene::AmtlGraphicsScene(QObject *parent)
    : QGraphicsScene{parent},
    _curScneId(0)
{

}

void AmtlGraphicsScene::pairUniConnectionPoint(bool linkStatus, UniConnectionPointPtr target)
{
    //保证在下列过程中对象不会被释放掉。
    auto firSharedPtr = _firstPair.lock();
    auto secSharedPtr = target.lock();

    if(target.isNull()) return;

    if(linkStatus == false){
        //只能是取消绑定
        if(secSharedPtr.data() == firSharedPtr.data()){//Reference to the same connetion point.
            _firstPair.clear();
        }
        secSharedPtr->update();
    }else{
        if(_firstPair.isNull()){
            //First pair to this
            _firstPair = target;
        }else{
            if(!firSharedPtr->bindConnectionPoint(secSharedPtr.data())){
                //Bind fail
                firSharedPtr->update();
                secSharedPtr->update();
            }
            _firstPair.clear();
        }
    }
}

bool AmtlGraphicsScene::loadGraphicFromXMl(const QString &filePath, QVector<AbstractConInterface *> &comVec){
    QFile xmlFile{filePath};
    if(!xmlFile.open(QIODevice::ReadOnly)){
        //todo tip file open fail;
        return false;
    }

    QXmlStreamReader reader{&xmlFile};

    reader.readNext();
    QString comID;
    AbstractConInterface* factory=nullptr;
    AbstractConInterface* newComInstance;
    QXmlStreamAttributes attrs;
    while(!reader.atEnd()){

        if(reader.tokenType() != QXmlStreamReader::TokenType::StartElement){
            reader.readNext();
            //Skip every element not a start element;
            continue;
        }

        //Start
        if("Document" == reader.name().toString()
            || "Components" == reader.name().toString()
            || "Links" == reader.name().toString()){
            reader.readNext();
            //Big part start element;
            continue;
        }

        //Graphics basick info
        if(reader.tokenType() == QXmlStreamReader::TokenType::StartElement
            && "Elec" == reader.name().toString() ){
            attrs = reader.attributes();
            if(attrs.hasAttribute("scene_id")){
                _curScneId = attrs.value("scene_id").toLong();
            }
        }

        //Component info--Components
        if(reader.tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComponetXmlLabel == reader.name().toString() ){

            attrs = reader.attributes();
            //read attrs
            if(attrs.hasAttribute("com_id")){
                comID=attrs.value("com_id").toString();
            }

            factory = PluginLoaderController::instance()->getComById(comID);

            if(nullptr != factory){
                newComInstance = factory->instance(-1);
                newComInstance->loadStatusFormXml(&reader);

                addComponentImpl(newComInstance);


                //New add com
                comVec.push_back(newComInstance);
            }
        }

        //Link Info
        if(reader.tokenType() == QXmlStreamReader::TokenType::StartElement
            && ComponentLinkXmlLabel == reader.name().toString()){

            //A component link info start
            QXmlStreamAttributes attrs = reader.attributes();

            //---Read component info start
            long comSceneId = -1;
            if(attrs.hasAttribute("from_com_id")){
                comSceneId = attrs.value("from_com_id").toLong();
            }
            AbstractConInterface* startElement=nullptr;
            if(_sceneIdComMap.contains(comSceneId)){
                startElement = _sceneIdComMap[comSceneId];
            }else{
                qWarning().noquote()DEBUGINFO<<tr("Component info lost, target compoent scene @")<<comSceneId;
            }
            //---Read component info end


            //---Read connection point start
            reader.readNext();
            CHECK_READ_END(reader);//Pass from element.

            int lineNum = -1;
            long fromPointId = -1;
            long toComSceneId = -1;
            long toPointId =-1;

            AbstractConInterface* endElement = nullptr;

            while(!reader.atEnd()){

                //A connection point line info read
                if(reader.tokenType() == QXmlStreamReader::TokenType::StartElement
                    && UniCCPointLineXmlLabel == reader.name().toString()){
                    attrs = reader.attributes();
                    if(attrs.hasAttribute("line_num")){
                        lineNum = attrs.value("line_num").toLong();
                    }

                    reader.readNext();
                    CHECK_READ_END(reader);//pass the CCPointLine element.

                    //---Read line info strat
                    for(int i=0;i<lineNum && !reader.atEnd(); ){

                        if(reader.tokenType() == QXmlStreamReader::TokenType::StartElement
                            && "line" == reader.name().toString()){
                            //connection point satrt
                            attrs = reader.attributes();

                            if(attrs.hasAttribute("from_connection_point_id")){
                                fromPointId = attrs.value("from_connection_point_id").toLong();
                            }

                            if(attrs.hasAttribute("target_parent_scene_id")){
                                toComSceneId = attrs.value("target_parent_scene_id").toLong();
                            }

                            if(attrs.hasAttribute("target_connection_point_id")){
                                toPointId = attrs.value("target_connection_point_id").toLong();
                            }

                            if(_sceneIdComMap.contains(toComSceneId)){
                                endElement = _sceneIdComMap[toComSceneId];
                            }else{
                                endElement = nullptr;
                            }

                            //Point pos
                            QString lineText = reader.readElementText();

                            if(nullptr == endElement || nullptr == startElement){
                                qWarning().noquote()DEBUGINFO<<"Lost component(s) information";
                                reader.readNext();
                                continue;
                            }

                            if(!startElement->loadLinkFormXml(endElement,lineText,toPointId,fromPointId)){
                                qWarning().noquote()DEBUGINFO<<tr("Link line false : ")
                                                               <<"@"<<startElement->getComInfoSPtr()->comName
                                                               <<" @"<<startElement->getSceneId()
                                                               <<" @connection point "
                                                               <<fromPointId<<"\n"
                                                               <<"\t@"<<endElement->getComInfoSPtr()->comName
                                                               <<" @"<<endElement->getSceneId()
                                                               <<" @connection point "
                                                               <<toPointId;
                            }

                            endElement = nullptr;
                            toPointId = -1;
                            fromPointId = -1;
                        }

                        if(reader.tokenType() == QXmlStreamReader::TokenType::EndElement
                            && "line" == reader.name().toString()){
                            ++i;
                        }

                        //Lost infomations.
                        if(reader.tokenType() == QXmlStreamReader::TokenType::EndElement
                            && UniCCPointLineXmlLabel == reader.name().toString()){

                            if(i < lineNum){
                                qWarning()<<tr("There may be loss of information, please check whether your circuit is complete.");
                            }
                            break;
                        }
                        reader.readNext();
                    }
                    //---Read line info end


                    if(reader.tokenType() == QXmlStreamReader::TokenType::EndElement
                        && UniCCPointLineXmlLabel == reader.name().toString()){
                        break;
                    }
                    reader.readNext();
                }



                //Component all connection point link info read end.
                if(reader.tokenType() == QXmlStreamReader::TokenType::EndElement
                    && ComponentLinkXmlLabel == reader.name().toString()){
                    //End one component link read;
                    break;
                }
                reader.readNext();
            }
            //Read connection point end
        }

        reader.readNext();
    }

    return true;
}

bool AmtlGraphicsScene::saveGraphicToXML(const QString &filePath){
    QFile xmlFile{filePath};
    if(!xmlFile.open(QIODevice::WriteOnly | QIODevice::Truncate)){
        return false;
    }

    QXmlStreamWriter writer{&xmlFile};
    writer.setAutoFormatting(true);
    writer.writeStartDocument();

    writer.writeStartElement("Document");

    writer.writeStartElement("Elec");
    writer.writeAttribute("scene_id",QString::number(_curScneId));
    writer.writeEndElement();

    {//Components
        writer.writeStartElement("Components");
        writer.writeComment(">Componnet status strat.<");
        auto itemsList = items();
        for(auto& item : itemsList){
            AbstractConInterface* itemPtr = dynamic_cast<AbstractConInterface*>(item);
            if(itemPtr){
                if(!itemPtr->saveStatusToXml(&writer)){
                    return false;
                }
            }
        }writer.writeEndElement();
    }

    {//Links
        writer.writeStartElement("Links");
        auto itemsList = items();
        for(auto& item : itemsList){
            AbstractConInterface* itemPtr = dynamic_cast<AbstractConInterface*>(item);
            if(itemPtr){
                if(!itemPtr->saveLinkToXml(&writer)){
                    return false;
                }
            }
        }writer.writeEndElement();
    }




    writer.writeEndElement();

    return true;
}

void AmtlGraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(painter);
    Q_UNUSED(rect);
    QGraphicsScene::drawBackground(painter,rect);
    //    static QPen linePen;
    //    linePen.setColor(QColor(60,60,60,120));
    //    linePen.setWidth(0);
    //    linePen.setStyle(Qt::DashLine);

    //    static int lineSpace =64;

    //    qreal left=rect.left();
    //    qreal right=rect.right();
    //    qreal top=rect.top();
    //    qreal bottom=rect.bottom();

    //    painter->save();
    //    painter->setRenderHint(QPainter::Antialiasing);//抗锯齿

    //    painter->setPen(linePen);

    //    //绘制横线
    //    if(abs(top)>abs(bottom)){
    //        //主体偏上
    //        for(int i=0; i>=top ;i-=lineSpace){
    //            painter->drawLine(left,i,right,i);
    //            painter->drawLine(left,-i,right,-i);
    //        }
    //    }else{
    //        for(int i=0; i<=bottom ;i+=lineSpace){
    //            painter->drawLine(left,-i,right,-i);
    //            painter->drawLine(left,i,right,i);
    //        }
    //    }

    //    //绘制竖线

    //    if(abs(left)>abs(right)){
    //        //主体偏左
    //        for(int i=0; i>=left;i-=lineSpace)
    //        {
    //            painter->drawLine(i,top,i,bottom);
    //            painter->drawLine(-i,top,-i,bottom);
    //        }
    //    }else{
    //        for(int i=0;i<=right;i+=lineSpace)
    //        {
    //            painter->drawLine(i,top,i,bottom);
    //            painter->drawLine(-i,top,-i,bottom);
    //        }
    //    }
    //    painter->restore();
}

void AmtlGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);
}

void AmtlGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseDoubleClickEvent(event);
}

void AmtlGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseMoveEvent(event);
}

void AmtlGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mouseReleaseEvent(event);
}

void AmtlGraphicsScene::makeToastInfo(QString infoTitle, QString info, bool autoHide, AMTL::ToastInfoPosition showPos, AMTL::ToastInfoType infoType)
{
    //Re pos this to mainwindow to show this toast info
    emit requestToastInfo(infoTitle,info,autoHide,showPos,infoType);
}

AbstractConInterface *AmtlGraphicsScene::addComponent(AbstractConInterface *comItem){
    return addComponentImpl(comItem);
}

AbstractConInterface* AmtlGraphicsScene::creatComponent(AbstractConInterface* factory){
    return creatComponentImpl(factory);
}

AbstractConInterface *AmtlGraphicsScene::addComponentImpl(AbstractConInterface *comItem){
    qDebug().noquote()DEBUGINFO<<tr("Component component @")<<comItem->getComInfoSPtr()->comName<<"/"<<comItem->getSceneId();

    _sceneIdComMap[comItem->getSceneId()] = comItem;
    _comSceneIdMap[comItem] = comItem->getSceneId();
    addItem(comItem);
    comItem->show();
    //Bind
    connect(comItem,&AbstractConInterface::tellCCPointBindStatusChanged,this,&AmtlGraphicsScene::pairUniConnectionPoint);

    //remove the com when com was delete
    connect(comItem,&AbstractConInterface::tellComAboutDestroy,this,&AmtlGraphicsScene::removeComponentImpl);

    return comItem;
}

void AmtlGraphicsScene::removeComponentImpl(long sceneId, AbstractConInterface *comptr){
    //remind here can't make any ptr opration;
    _sceneIdComMap[sceneId] = nullptr;
    _sceneIdComMap.erase(_sceneIdComMap.constFind(sceneId));

    _comSceneIdMap[comptr] = -1;
    _comSceneIdMap.erase(_comSceneIdMap.constFind(comptr));

}

AbstractConInterface* AmtlGraphicsScene::creatComponentImpl(AbstractConInterface *factory){
    if(nullptr==factory){
        qWarning().noquote()DEBUGINFO<<tr("The target type component does not exist or is not loaded");
        return nullptr;
    }

    AbstractConInterface* com = factory->instance(_curScneId);
    addComponentImpl(com);
    ++_curScneId;
    return com;
}

