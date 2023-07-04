#include "PluginLoaderController.h"

#include <QJsonArray>

PluginLoaderController::PluginLoaderController(QObject *parent)
    : QObject{parent}
{
    init();
}



void PluginLoaderController::scanPluginFolder(bool manualInputPath, QString path){
    if(manualInputPath){
        scanPluginFolderImpl(path);
    }else{


#ifdef QT_DEBUG

        //todo macox
//#ifdef Q_OS_MACOS
//        scanPluginFolderImpl("/Users/lee/Documents/Projects/QT/ChipSimulator/ChipSimulator/ComponentPlugin/debug/bin/");
//#elif
        scanPluginFolderImpl("C:/Users/Lee/Documents/Project/Qt/ChipSimulator/ChipSimulator/ComponentPlugin/debug/bin/");
//#endif

#elif
        scanPluginFolderImpl("./Resources/Plugin/");
#endif
    }

    emit pluginLoadDone(_comNameList);
}

AbstractConInterface *PluginLoaderController::getComById(const QString comId){
    if(_idComponentMap.contains(comId)){
        return _idComponentMap[comId];
    }

    return nullptr;
}

QJsonObject PluginLoaderController::getJsonByComId(const QString comId){
    if(_idJsonMap.contains(comId)){
        return _idJsonMap[comId];
    }

    return QJsonObject{};
}

QJsonObject PluginLoaderController::getMetaDataJsonObjByComId(const QString comId){
    if(_idJsonMap.contains(comId)){
        if(_idJsonMap[comId].contains("MetaData")){
            return _idJsonMap[comId].value("MetaData").toObject();
        }
    }
    return QJsonObject{};
}

QString PluginLoaderController::getComCategory(const QString comId){
    if(_idJsonMap.contains(comId)){
        if(_idJsonMap[comId].contains("MetaData")){
            QJsonObject metaObj = _idJsonMap[comId].value("MetaData").toObject();
            if(metaObj.contains("Category")){
                return metaObj.value("Category").toString();
            }
        }
    }
    return {""};
}

void PluginLoaderController::scanPluginFolderImpl(const QString &path){
    QDir dir{path};
    if(!dir.exists()){
        //
        return;
    }


//#ifdef Q_OS_MACOS
//    QStringList files =  dir.entryList(QStringList() << "*.dylib", QDir::Filter::Files);
//#elif
    QStringList files =  dir.entryList(QStringList() << "*.dll", QDir::Filter::Files);
//#endif

    QStringList scendDirs = dir.entryList(QDir::Filter::Dirs);

    QString msg;
    for(auto& filePath : files){
        if(loadAPlugin(path+filePath,&msg)){
            //Load suc
            qInfo().noquote()DEBUGINFO<<tr("Load component success : ")<<msg;
        }else{
            qWarning().noquote()DEBUGINFO<<tr("Load component fail : ")<<msg;
        }
        msg.clear();
    }

    for(auto& deDirPath : scendDirs){
        if(deDirPath!="." && deDirPath!="..") scanPluginFolderImpl(deDirPath);
    }
}

bool PluginLoaderController::loadAPlugin(const QString &pluginPath, QString *loadMsg){
    QPluginLoader loader{pluginPath};
    if(!loader.load()){
        WRITE_PTR(loadMsg,tr("Load fail due to : ") + loader.errorString());
        return false;
    }

    QObject* targetObj = loader.instance();//This instance will not be delete when the loader been destroy;
    AbstractConInterface* comObj = qobject_cast<AbstractConInterface*>(targetObj);

    //Is this a defined plugin
    if(nullptr == comObj){
        loader.unload();
        WRITE_PTR(loadMsg,targetObj->metaObject()->className() + tr(":The plug-in object is unknown and failed to load"));
        return false;
    }

    //Set obj name
    targetObj->setObjectName(targetObj->metaObject()->className());

    //Componnet initial basic info?
    if(!comObj->isComInfoInitial()){
        //Component info not initial , can use
        WRITE_PTR(loadMsg,comObj->metaObject()->className() + tr(":The plug-in is not initialized and cannot be loaded"));
        return true;
    }

    //If this component already been load.
    auto infoSPtr = comObj->getComInfoSPtr();
    if(true == _idComponentMap.contains(infoSPtr->comId)){
        //Already load
        WRITE_PTR(loadMsg,tr("Plug-in [ID:")+infoSPtr->comId + tr("]; [Name:") +infoSPtr->comName+tr("] already been load"));
        return false;
    }

    //Load info, finish all set
    QJsonObject targetJsonObj = loader.metaData();
    ComponentFullInfoStruct fullInfoStr;

    fullInfoStr.basicInfo = *infoSPtr.data();

    //Insert this component info to the category & read other info
    if(targetJsonObj.contains("MetaData")){
        QJsonObject metaObj = targetJsonObj.value("MetaData").toObject();

        if(metaObj.contains("Category")){
            fullInfoStr.category = metaObj.value("Category").toString();
        }

        if(fullInfoStr.category.isEmpty()){
            fullInfoStr.category = NO_CATEGORY;
        }

        if(metaObj.contains("Tag")){
            QJsonArray tagArray = metaObj.value("Tag").toArray();
            auto tagArrayIter = tagArray.begin();
            while(tagArrayIter!=tagArray.end()){
                fullInfoStr.tags << tagArrayIter->toString();
                tagArrayIter++;
            }
        }
    }


    ComponentUiItemWidgetSPtr uiSPtr{new ComponentUiItemWidget(fullInfoStr)};
    uiSPtr->setComPtr(comObj);

    _comNameList.push_back(infoSPtr->comName);
    _comIdList.push_back(infoSPtr->comId);
    _comFullInfoStructVec.push_back(fullInfoStr);

    _comSelectUiWidget.push_back(uiSPtr);

    _idJsonMap[infoSPtr->comId] = targetJsonObj;
    _idComponentMap[infoSPtr->comId] = comObj;
    //Category
    if(Q_LIKELY(_cateConponentMMap.find(fullInfoStr.category,comObj) == _cateConponentMMap.end())){
        //Not load
        _cateConponentMMap.insert(fullInfoStr.category,comObj);
    }//alredy exits , not posiable to get here

    WRITE_PTR(loadMsg,infoSPtr->comName);
    return true;
}

PluginLoaderController* PluginLoaderController::instance(){
    static PluginLoaderController* controllor = new PluginLoaderController();
    return controllor;
}

QStringList PluginLoaderController::comIdList() const
{
    return _comIdList;
}

QVector<ComponentUiItemWidgetSPtr> PluginLoaderController::getComponentAllItemWidgets(){
    return _comSelectUiWidget;
}

void PluginLoaderController::init(){
    scanPluginFolder();
}

QStringList PluginLoaderController::comNameList() const
{
    return _comNameList;
}
