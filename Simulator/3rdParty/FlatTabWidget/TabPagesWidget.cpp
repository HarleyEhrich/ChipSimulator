#include "TabPagesWidget.h"
#include "ui_TabPagesWidget.h"


TabPagesWidget::TabPagesWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabPagesWidget)
    , _pageGen(nullptr)
{
    ui->setupUi(this);
    init();
}

TabPagesWidget::~TabPagesWidget()
{
    delete ui;
}



void TabPagesWidget::foucusTab(TabItem* targetTab)
{
    changePageFocus(targetTab);
}

void TabPagesWidget::closeTab(TabItem* targetTab)
{

}

void TabPagesWidget::scrollDown()
{
//    if(_pages.empty()){
//        return;
//    }

//    ++_curFocusPageIndex;
//    _curFocusPageIndex %=_pages.size();

//    emit scrolledDown();
////    setCurrentTab(_curFocusPageIndex );

}

void TabPagesWidget::scrollUp()
{
//    if(_pages.empty()){
//        return ;
//    }

//    --_curFocusPageIndex;
//    if(_curFocusPageIndex<0) _curFocusPageIndex = _pages.size()-1;

//    emit scrolledUp();
//    setCurrentTab(_curFocusPageIndex);
}





TabPageGenerator *TabPagesWidget::pageGen() const
{
    return _pageGen;
}

void TabPagesWidget::setPageGen(TabPageGenerator *newPageGen)
{
    _pageGen = newPageGen;
    if(nullptr == _pageGen){
        ui->add_dea_page_btn->hide();
    }else{
        ui->add_dea_page_btn->show();
    }
}



void TabPagesWidget::init()
{
    setPageGen(_pageGen);

    //绑定tab 容器鼠标滚动事件
    connect(ui->tabbar_widget, &CustomTabBar::scrolledUp, this, &TabPagesWidget::scrollUp);
    connect(ui->tabbar_widget, &CustomTabBar::scrolledDown, this,&TabPagesWidget::scrollDown);
}

void TabPagesWidget::changePageFocus(TabItem* newFocus){
    if(_curFocus == nullptr){
        _curFocus->setTabFocused(false);
    }
    _curFocus = newFocus;
    newFocus->setTabFocused(true);
    if(_pageFadeInAni){
        _pageFadeInAni->animateStop();
        _pageFadeInAni = nullptr;
    }
    _pageFadeInAni = WAF::StackedWidgetAnimation::fadeIn(ui->Content,newFocus->getPage());

}

void TabPagesWidget::on_add_dea_page_btn_clicked()
{
    if(_pageGen){
        auto* page = _pageGen->page();
        page->setWindowTitle(tr("新页面")+QString::number(_tabPageVec.size()));
        addPage(page);
    }
}

bool TabPagesWidget::addPage(QWidget *page){
    if(page ==nullptr) return false;
    ui->Content->addWidget(page);

    TabItem* tabItem = new TabItem(page);
    _tabPageVec.append(tabItem);
    //bind focus and close sig
    connect(tabItem,&TabItem::foucusTab,this,&TabPagesWidget::foucusTab);
    connect(tabItem,&TabItem::closeTab,this,&TabPagesWidget::closeTab);


    if(_tabPageVec.empty()){
        foucusTab(tabItem);
    }else{
        tabItem->setTabFocused(false);
    }

    ui->tabbar_widget->layout()->addWidget(tabItem);

    return true;
}

bool TabPagesWidget::removePage(QWidget *page){
    //        QVector<TabItem*>::iterator iter = _tabPageVec.begin();
    //        while(iter != _tabPageVec.constEnd()){
    //            if((*iter)->isYourPage(page)){
    //                break;
    //            }
    //        }
    //        _tabPageVec.erase(iter);

    return true;
}

bool TabPagesWidget::removePage(TabItem *tabItem){
    QVector<TabItem*>::const_iterator iter = _tabPageVec.constBegin();
    while(iter != _tabPageVec.constEnd()){
        if(*iter == tabItem){
            break;
        }
    }
    _tabPageVec.erase(iter);

    return true;
}

