#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    ElecGraphicsControllor* newCon = new ElecGraphicsControllor(this);
    _controlVec.push_back(newCon);
    AmtlGraphicsView* newView = newCon->getNewView().lock().data();



    newView->show();
    ui->page_tab_widget->addPage(newView->getViewBox(),"电路图");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_page_info_spliter_splitterMoved(int pos, int index)
{
    Q_UNUSED(index)

    //todo 事实证明在视觉上是可行的方案，记得考虑一下如何处理能更节省资源
    if(ui->page_info_spliter->handleWidth() && pos == ui->page_info_spliter->height() - ui->page_info_spliter->handleWidth()){
        //Time to hide the handle
        ui->page_info_spliter->setHandleWidth(0);
    }else{
        if(ui->page_info_spliter->handleWidth()==0 && pos <= ui->page_info_spliter->height()-3){
            ui->page_info_spliter->setHandleWidth(1);
        }
    }


}

void MainWindow::init()
{
    initMenu();

//    _sidebarShadow=new QGraphicsDropShadowEffect();
//    _pageStackWidgetContainerShadow=new QGraphicsDropShadowEffect();

//    _pageStackWidgetContainerShadow->setColor(QColor(68, 68, 68));
//    _pageStackWidgetContainerShadow->setBlurRadius(8);
//    _pageStackWidgetContainerShadow->setOffset(0,0);
//    ui->elexc_view_container->setGraphicsEffect(_pageStackWidgetContainerShadow);//remind change this to page_tab_container
//    _sidebarShadow->setColor(QColor(68, 68, 68));
//    _sidebarShadow->setBlurRadius(8);
//    _sidebarShadow->setOffset(0,0);
//    ui->sidebar_container->setGraphicsEffect(_sidebarShadow);





    QTextBrowser* tb =new QTextBrowser();
    tb->setText("2023-04-13 16:38:10-[Debug]{viewcontrollunit.cpp:75, void __cdecl"
"ViewControllUnit::on_lock_btn_clicked(bool)}: on_lock_btn_clicked\n"
"2023-04-13 16:38:11-[Debug]{viewcontrollunit.cpp:75, void __cdecl"
"ViewControllUnit::on_lock_btn_clicked(bool)}: on_lock_btn_clicked\n"
"2023-04-13 16:39:42-[Debug]{viewcontrollunit.cpp:75, void __cdecl"
"ViewControllUnit::on_lock_btn_clicked(bool)}: on_lock_btn_clicked\n"
"2023-04-13 16:39:48-[Debug]{viewcontrollunit.cpp:75, void __cdecl"
"ViewControllUnit::on_lock_btn_clicked(bool)}: on_lock_btn_clicked\n"
"2023-04-13 16:39:49-[Debug]{viewcontrollunit.cpp:75, void __cdecl"
"ViewControllUnit::on_lock_btn_clicked(bool)}: on_lock_btn_clicked\n"
"2023-04-13 16:39:49-[Debug]{viewcontrollunit.cpp:75, void __cdecl"
"ViewControllUnit::on_lock_btn_clicked(bool)}: on_lock_btn_clicked");

    ui->info_tab_widget->addPage(tb,"BUG输出");
    ui->info_tab_widget->addPage(new QWidget(),"消息");

    ui->page_info_spliter->setHandleWidth(0);
    ui->page_info_spliter->handle(1)->setAttribute(Qt::WA_Hover, true);
}


void MainWindow::initMenu()
{
    auto menuItems = findChildren<QMenu*>(Qt::FindChildOption::FindChildrenRecursively);

//    qDebug()<<DEBUGINFO<<menuItems.size();

    for(auto& menu : menuItems){
//        QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(menu);
//        shadow->setOffset(0, 0);
//        shadow->setColor(QColor(68, 68, 68));
        //        shadow->setBlurRadius(8);
        menu->setToolTipsVisible(true);
        menu->setToolTipDuration(2000);
        menu->setWindowFlags(menu->windowFlags()  | Qt::FramelessWindowHint | Qt::NoDropShadowWindowHint);
        menu->setAttribute(Qt::WA_TranslucentBackground,true);
        //        menu->setGraphicsEffect(shadow);
        menu->setStyleSheet("QMenu{"
                            "color:black;background-color:white; border-radius:4px;padding:6px;margin:6px; "
                            "border-top: 1px solid QLinearGradient(y0:0, y1:1,stop: 0 #DADADA, stop: 1 transparent);"
                            "border-left: 1px solid QLinearGradient(x0:0, x1:1,stop: 0 #DADADA, stop: 1 transparent);"
                            "border-bottom: 1px solid QLinearGradient(y0:0, y1:1,stop: 0 transparent, stop: 1  #DADADA);"
                            "border-right: 1px solid QLinearGradient(x0:0, x1:1,stop:  0 transparent, stop: 1 #DADADA); "
                            "}"
                            "QMenu::item:text{ font: 500 8pt \"思源黑体 CN Medium\"; min-width: 72px; padding-left:8px;padding-right:8px; padding-top: 6px; padding-bottom: 6px;}"
                            "QMenu::item:selected{ color:#ffffff;background-color: #ea5455; border-radius:4px;}"
                            "QMenu::separator{height:1px;background:#bbbbbb;margin:5px;margin-left:10px;margin-right:10px;}");
    }

}


void MainWindow::on_component_tbtn_clicked()
{
    //Load
    //todo 在此处测试，后期删除
    QString pluginFilePath=QFileDialog::getOpenFileName(this,"","");
    qDebug()<<"DLL path:" <<pluginFilePath<<"\n";

    QPluginLoader loader(pluginFilePath);
    if (loader.load())
    {
        QObject *obj = loader.instance();
        obj->setObjectName(obj->metaObject()->className());
        qDebug()<<loader.metaData().value("MetaData").toObject();
        if (obj)
        {
            auto pluginIn = qobject_cast<AbstractConInterface*>(obj);
            if (pluginIn)
            {

                auto* led= pluginIn->instance(1,nullptr);
                auto info = led->getComInfo();

                qDebug()<<DEBUGINFO<<info.comId<<info.comName<<info.comAuthor<<info.comImagePath;

                ElecGraphicsControllor* con = _controlVec[0];
                con->scene()->addItem(led);

                connect(led,&AbstractConInterface::tellCCPointBindStatusChanged,con->scene(),&AmtlGraphicsScene::pairUniConnectionPoint);


                auto widgets = led->getComponentWidgtes();


                QFrame* box = new QFrame();
                QVBoxLayout* boxLay = new QVBoxLayout(box);

                for(auto& items : widgets){
                    boxLay->addWidget(items._widgetSPtr.data());
                }

                box->show();

            }else{
                qDebug()<<"Not me";
            }
        }
    }else{
        qDebug()<<loader.errorString()<<"Load fail";
    }
}


//    AmtlGraphicsView* newView = newCon->getNewView();
//    AmtlGraphicsScene* newScene=newCon->scene();

//    newScene->setObjectName("scene");
//    UniConnectionPoint* pointLinkItem = new UniConnectionPoint(2,COOR_POS::RIGHT,true,"输出连接点",1,2);
//    newScene->addItem(pointLinkItem);
//    newScene->registerUniConnectionPoint(pointLinkItem);
//    pointLinkItem->show();
//    UniConnectionPoint* pointLinkItem1 = new UniConnectionPoint(1,COOR_POS::LEFT,false,"输入连接点1");
//    newScene->addItem(pointLinkItem1);
//    newScene->registerUniConnectionPoint(pointLinkItem1);
//    pointLinkItem1->setPos(-140,50);
//    pointLinkItem1->show();
//    UniConnectionPoint* pointLinkItem2 = new UniConnectionPoint(1,COOR_POS::LEFT,false,"输入连接点2");
//    newScene->addItem(pointLinkItem2);
//    newScene->registerUniConnectionPoint(pointLinkItem2);
//    pointLinkItem2->setPos(150,130);
//    pointLinkItem2->show();
//    newView->setScene(newScene);
//    newScene->setSceneRect(-500,-500,1000,1000);

