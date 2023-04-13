#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QList>
#include <QWidget>

#include "include/project_include.h"

#include "Widgets/Graphics/amtlgraphicsscene.h"
#include "Widgets/FloatWidgets/ToastInfoWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);




    ToastInfoWidget* testInfo = new ToastInfoWidget(this);
    testInfo->move(10,50);
    testInfo->show();

    AmtlGraphicsScene* newScene=new AmtlGraphicsScene;
    newScene->setObjectName("scene");

    UniConnectionPoint* pointLinkItem = new UniConnectionPoint(2,COOR_POS::RIGHT,true,"输出连接点",1,2);
    newScene->addItem(pointLinkItem);
    newScene->registerUniConnectionPoint(pointLinkItem);
    pointLinkItem->show();


    UniConnectionPoint* pointLinkItem1 = new UniConnectionPoint(1,COOR_POS::LEFT,false,"输入连接点1");
    newScene->addItem(pointLinkItem1);
    newScene->registerUniConnectionPoint(pointLinkItem1);
    pointLinkItem1->setPos(-140,50);
    pointLinkItem1->show();

    UniConnectionPoint* pointLinkItem2 = new UniConnectionPoint(1,COOR_POS::LEFT,false,"输入连接点2");
    newScene->addItem(pointLinkItem2);
    newScene->registerUniConnectionPoint(pointLinkItem2);
    pointLinkItem2->setPos(150,130);
    pointLinkItem2->show();


//    auto res=ConLinkLine::storeLineToText(newItem1);
//    qDebug()<< res;
//    auto resItem=ConLinkLine::creatLineWithText(res);
//    qDebug()<<resItem.size();
//    for(ConLinkLine* header=resItem.at(0);header!=nullptr;header=header->getNextItem()){
//        newScene->addItem(header);
//        qDebug()<<header->scenePos();
//    }


//    QGraphicsLineItem* axisX=new QGraphicsLineItem();
//    QGraphicsLineItem* axisY=new QGraphicsLineItem();
//    axisX->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
//    axisY->setFlags(QGraphicsItem::ItemIsMovable| QGraphicsItem::ItemIsSelectable );
//    axisX->setLine(-200,0,200,0);
//    axisY->setLine(0,-200,0,200);
//    newScene->addItem(axisX);
//    newScene->addItem(axisY);

    this->ui->elec_view->setScene(newScene);

    this->ui->elec_view->show();



//Not test part

    _sidebarShadow=new QGraphicsDropShadowEffect();
    _mainContentShadow=new QGraphicsDropShadowEffect();

    _mainContentShadow->setColor(QColor(68, 68, 68));
    _mainContentShadow->setBlurRadius(8);
    _mainContentShadow->setOffset(0,0);
    ui->main_container_widget->setGraphicsEffect(_mainContentShadow);

    _sidebarShadow->setColor(QColor(68, 68, 68));
    _sidebarShadow->setBlurRadius(8);
    _sidebarShadow->setOffset(0,0);
    ui->sidebar_container->setGraphicsEffect(_sidebarShadow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

