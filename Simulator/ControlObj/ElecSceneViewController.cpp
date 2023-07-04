#include "ElecSceneViewController.h"

#include "Widgets/FloatWidgets/ToastInfoWidget.h"

ElecSceneViewController::ElecSceneViewController(QObject *parent):
    QObject(parent)
{
    init();
}

ElecSceneViewController::ElecSceneViewController(QString filePath, QObject *parent):
    QObject(parent),
    _filePath(filePath)
{
    init();
    if(!_filePath.isEmpty()){
        loadGraphicsFromXML();
    }
}

ElecSceneViewController::~ElecSceneViewController(){
    //todo save to file

    for(QWidget* viewBoxItem : _floatViewBoxVec){
        viewBoxItem->hide();
        viewBoxItem->deleteLater();
    }//Delete all float view;

    _scene.clear();
    _view.clear();

    _sceneSetting->hide();
    _sceneSetting.clear();
}

QWidget *ElecSceneViewController::getDeaViewPage(){
    return _view->getViewBox();
}

QWidget *ElecSceneViewController::getNewViewPage(bool floatView){
    AmtlGraphicsView* view = new AmtlGraphicsView(nullptr);
    view->setScene(_scene);

    QWidget* viewBox = view->getViewBox();
    connect(viewBox,&QWidget::destroyed,this,[=](){
        QVector<QWidget*>::const_iterator iter = _floatViewBoxVec.constBegin();
        while(iter!=_floatViewBoxVec.end()){
            if(*iter == viewBox){
                break;
            }
            ++iter;
        }

        if(iter != _floatViewBoxVec.end()) {
            _floatViewBoxVec.erase(iter);
        }
    });

    _floatViewBoxVec.push_back(viewBox);

    if(Q_LIKELY(true == floatView)){
        viewBox->show();
    }

    return viewBox;
}

bool ElecSceneViewController::isMainViewActive(){
    return _view->isVisible();
}

bool ElecSceneViewController::isActiveElec(){
    return _view->isVisible();
}

long ElecSceneViewController::addANewComponnent(AbstractConInterface *factory){
    AbstractConInterface* newComptr =nullptr;
    if(!_scene.isNull()){
        newComptr = _scene->creatComponent(factory);
    }

    if(nullptr == newComptr){
        return -1;
    }

    QFrame* box = makeSettingBox(newComptr);
    addASettingBox(box);
    connect(newComptr,&AbstractConInterface::destroyed,box,&QFrame::deleteLater);

    return newComptr->getSceneId();
}

bool ElecSceneViewController::saveGraphicsToXMl(){
    if(_scene.isNull()){
        return false;
    }

    if(_filePath.isEmpty()){
        _filePath = QFileDialog::getSaveFileUrl(nullptr,
                                                tr("保存工程"),
                                                QUrl{""},
                                                tr("cspro(*.cspro);;txt(*.txt);;other(*.*)")).toLocalFile();
    }


    ToastInfoWidget::quickToast(
        tr("Success!:)"),
        tr("Successfully saved the project, the project file path is :")+_filePath,
        true,
        AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
        AMTL::ToastInfoType::TIP_TIP);

    qInfo().noquote()DEBUGINFO<<tr("Successfully saved the project, the project file path is :")<<_filePath;

    return _scene->saveGraphicToXML(_filePath);
}

bool ElecSceneViewController::loadGraphicsFromXML(){
    if(_scene.isNull()){
        return false;
    }

    if(_filePath.isEmpty()){
        _filePath=QFileDialog::getOpenFileName(nullptr,
                                                 tr("打开文件"),
                                                 QDir::currentPath(),
                                                 "cspro(*.cspro);;xml(*.xml);;txt(*.txt);;other(*.*)");
    }

    qInfo().noquote()DEBUGINFO<<tr("Start opening the project file, file path is: ")<<_filePath;

    QVector<AbstractConInterface*> resComVec;

    bool loadStatus = _scene->loadGraphicFromXMl(_filePath,resComVec);

    if(loadStatus){
        for(AbstractConInterface* com : resComVec){
            QFrame* box = makeSettingBox(com);
            addASettingBox(box);
            connect(com,&AbstractConInterface::destroyed,box,&QFrame::deleteLater);
        }

        ToastInfoWidget::quickToast(
            tr("Open Suc"),
            tr("Successfully open the project file , the project file path is :")+_filePath,
            true,
            AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
            AMTL::ToastInfoType::TIP_TIP);

    }else{
        for(AbstractConInterface* com : resComVec){//Clean the resources
            delete com;
            com = nullptr;

        }

        qWarning().noquote()DEBUGINFO<<tr("Start opening the project file, file path is: ")<<_filePath;
        ToastInfoWidget::quickToast(
            tr("Open Error :("),
            tr("Fail open the project file , the project file path is :")+_filePath,
            true,
            AMTL::ToastInfoPosition::TIP_RIGHT_BOTTOM,
            AMTL::ToastInfoType::TIP_ERROR);
    }


    return loadStatus;
}

AmtlGraphicsSceneSPtr ElecSceneViewController::getScene() const
{
    return _scene;
}

void ElecSceneViewController::init(){
    AmtlGraphicsSceneSPtr sceneSPtr{new AmtlGraphicsScene(nullptr)};
    _scene = sceneSPtr;
    _scene->setSceneRect(-5000,-5000,10000,10000);

    AmtlGraphicsViewSPtr viewSPtr{new AmtlGraphicsView(nullptr)};
    viewSPtr->setScene(_scene);
    viewSPtr->show();
    _view = viewSPtr;

    QFrame* setBox = new QFrame(nullptr);
    QVBoxLayout* setBoxLay= new QVBoxLayout(setBox);
    QScrollArea* setScroll = new QScrollArea(nullptr);
    QWidget* setScroContentWidget = new QWidget();
    QVBoxLayout* setLay = new QVBoxLayout();

    setLay->setContentsMargins(8,8,8,8);
    //todo tick widget

    setLay->addItem(new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Expanding));

    setScroContentWidget->setLayout(setLay);

    setScroll->setWidget(setScroContentWidget);
    setScroll->setWidgetResizable(true);
    setScroll->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setBoxLay->setContentsMargins(0,0,0,0);
    setBoxLay->addWidget(setScroll);

    setBox->setGeometry(setBox->pos().x(),setBox->y(),320,760);
    setBox->setStyleSheet(SETBOX_STYLE_SHEET);

    _scrollContentLay = setLay;
    _scrollptr = setScroll;
    _sceneSetting.reset(setBox);

    setBox->show();


    {
        QFrame* box = new QFrame();
        QVBoxLayout* boxLay = new QVBoxLayout(box);
        QGraphicsDropShadowEffect* eff;
        MAKE_DEA_SHADOW_EFF(eff,box);
        box->setObjectName("component_set_box");

        QHBoxLayout* tickBtnLay = new QHBoxLayout();
        tickBtnLay->addWidget(new QLabel(tr("时序")));

        QPushButton* tickOneBtn = new QPushButton("时序更新单次-低态");
//        QPushButton* tickStay = new QPushButton("时序连续更新");

        tickOneBtn->setCheckable(true);
//        tickStay->setCheckable(true);

        connect(tickOneBtn,&QPushButton::clicked,_scene.data(),&AmtlGraphicsScene::tickOneTime);

        connect(tickOneBtn,&QPushButton::clicked,this,[=](bool checked){
            if(checked){
                tickOneBtn->setText("时序更新单次-高态");
            }else{
                tickOneBtn->setText("时序更新单次-低态");
            }
        });

        tickBtnLay->addWidget(tickOneBtn);
//        tickBtnLay->addWidget(tickStay);


        boxLay->addLayout(tickBtnLay);
        addASettingBox(box);
    }
}

QFrame *ElecSceneViewController::makeSettingBox(AbstractConInterface *comptr){
    QFrame* box = new QFrame();
    QVBoxLayout* boxLay = new QVBoxLayout(box);
    QGraphicsDropShadowEffect* eff;
    MAKE_DEA_SHADOW_EFF(eff,box);
    box->setObjectName("component_set_box");
    for(auto& items : comptr->getComponentWidgtes()){
        if(items._pannelFloat == false){
            boxLay->addWidget(items._widgetSPtr.data());
        }
    }
    return box;
}

void ElecSceneViewController::addASettingBox(QFrame *box){
    if(!_sceneSetting.isNull()){
        QLayoutItem* spacer = _scrollContentLay->takeAt(_scrollContentLay->count()-1);
        _scrollContentLay->addWidget(box);
        _scrollContentLay->addItem(spacer);
    }
}

void ElecSceneViewController::removeASettingBox(QFrame *box){
    if(!_sceneSetting.isNull()){
        _scrollContentLay->removeWidget(box);
    }
}
