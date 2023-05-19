#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGroupBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
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

    _comLoader = PluginLoaderController::instance();
    _listPage = new ComponentListPage(this);
    _listPage->show();
    _listPage->setVisible(false);
    _listPage->updateList();

    _elecPageGener = new ElecPageGener();
    ui->page_tab_widget->setPageGen(_elecPageGener);

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

    ui->info_tab_widget->addPage(tb);
    ui->info_tab_widget->addPage(new QWidget());

    ui->page_info_spliter->setHandleWidth(0);
    ui->page_info_spliter->handle(1)->setAttribute(Qt::WA_Hover, true);
}


void MainWindow::initMenu()
{
    auto menuItems = findChildren<QMenu*>(Qt::FindChildOption::FindChildrenRecursively);
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


void MainWindow::on_component_tbtn_clicked(bool checked)
{
    if(_listPage){
        if(checked){
            _listPage->updateList();
            _listPage->move(ui->component_tbtn->pos().x()+ui->component_tbtn->size().width()+16,16);
        }
        _listPage->setVisible(checked);
    }
}


void MainWindow::on_open_file_tbtn_clicked()
{
    auto curPage = ElecPageController::getCurActPage();
    if(curPage.isNull()){
        return;
    }
    curPage->saveGraphicsToXMl();
}

