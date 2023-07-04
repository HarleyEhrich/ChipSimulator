#include "ElecPage.h"
#include "ui_ElecPage.h"

#include "ControlObj/ElecPageController.h"

ElecPage::ElecPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ElectPage)
{
    ui->setupUi(this);
}

ElecPage::~ElecPage()
{
    _elecViewSceneControllerSPtr.clear();
    delete ui;
}

void ElecPage::on_new_project_btn_clicked()
{
    ElecSceneViewController* ptr= new ElecSceneViewController(this);
    _elecViewSceneControllerSPtr.reset(ptr);
    ui->stackedWidget->addWidget(ptr->getDeaViewPage());
    ui->stackedWidget->setCurrentIndex(1);
}


void ElecPage::on_open_project_btn_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,
                                                    tr("打开文件"),
                                                    QDir::currentPath(),
                                                    "cspro(*.cspro);;txt(*.txt);;other(*.*)");


    ElecSceneViewController* ptr= new ElecSceneViewController(filePath,this);
    _elecViewSceneControllerSPtr.reset(ptr);
    ui->stackedWidget->addWidget(ptr->getDeaViewPage());
    ui->stackedWidget->setCurrentIndex(1);
}

QWidget *ElecPageGener::page()
{
    ElecPage* newPage =  new ElecPage();
    ElecPageController::_elecPages.push_back(newPage);

    connect(newPage,&ElecPage::destroyed,this,[=](){
        ElecPageController::removePage(newPage);
    });
    return newPage;
}
