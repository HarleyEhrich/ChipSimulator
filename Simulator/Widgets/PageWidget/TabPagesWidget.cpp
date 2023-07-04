#include "TabPagesWidget.h"
#include "ui_TabPagesWidget.h"


TabPagesWidget::TabPagesWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TabPagesWidget)
    , _pageGen(nullptr)
    ,_curFocus(nullptr)
{
    ui->setupUi(this);
    init();
}

TabPagesWidget::~TabPagesWidget()
{

    for(auto* tab : _tabPageVec){
        removePage(tab);
    }

    delete ui;
}


void TabPagesWidget::foucusTab(TabItem* targetTab)
{
    changePageFocus(targetTab);
}

void TabPagesWidget::closeTab(TabItem* targetTab)
{
    removePage(targetTab);
}

void TabPagesWidget::scrollDown()
{

    if(_tabPageVec.empty()){
        return;
    }

    int _curFocusPageIndex = ui->Content->currentIndex();

    ++_curFocusPageIndex;
    _curFocusPageIndex %=_tabPageVec.size();

    changePageFocus(findTabByPage(ui->Content->widget(_curFocusPageIndex)));
}

void TabPagesWidget::scrollUp()
{

    if(_tabPageVec.empty()){
        return;
    }

    int _curFocusPageIndex = ui->Content->currentIndex();

    --_curFocusPageIndex;
    if(_curFocusPageIndex<0) _curFocusPageIndex = _tabPageVec.size()-1;

    changePageFocus(findTabByPage(ui->Content->widget(_curFocusPageIndex)));
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
        on_add_dea_page_btn_clicked();
    }
}



void TabPagesWidget::init()
{
    MAKE_DEA_SHADOW_EFF(_eff,ui->tab_item_box);

    setPageGen(_pageGen);

    //绑定tab 容器鼠标滚动事件
    connect(ui->tabbar_widget, &CustomTabBar::scrolledUp, this, &TabPagesWidget::scrollUp);
    connect(ui->tabbar_widget, &CustomTabBar::scrolledDown, this,&TabPagesWidget::scrollDown);
}


bool TabPagesWidget::removePage(TabItem *tabItem){

    if(nullptr == tabItem){
        return false;
    }

    ui->tabbar_widget->layout()->removeWidget(tabItem);

    ui->Content->removeWidget(tabItem->getPage());//page hide

    QVector<TabItem*>::const_iterator iter = _tabPageVec.constBegin();
    while(iter != _tabPageVec.constEnd()){
        if(*iter == tabItem){
            break;
        }
        iter++;
    }

    if(iter != _tabPageVec.constEnd()){
        _tabPageVec.erase(iter);
    }

    tabItem->getPage()->deleteLater();
    tabItem->deleteLater();
    return true;
}

void TabPagesWidget::changePageFocus(TabItem* newFocus){

    if(nullptr != _curFocus){
        _curFocus->setTabFocused(false);
    }
    _curFocus = newFocus;

    if(nullptr == newFocus){
        return ;
    }

    newFocus->setTabFocused(true);

    WAF::StackedWidgetAnimation::fadeIn(ui->Content,newFocus->getPage());

    emit pageFocusChange();
}


TabItem *TabPagesWidget::findTabByPage(QWidget *page){
    for(int i =0;i<_tabPageVec.size();++i){
        if(_tabPageVec[i]->getPage() == page){
            return _tabPageVec[i];
        }
    }
    return nullptr;
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

    QLayout* tabLay = ui->tabbar_widget->layout();
    QLayoutItem* spacer = nullptr;
    if(tabLay->count()){
        spacer = tabLay->takeAt(tabLay->count()-1);
        tabLay->removeItem(spacer);
    }else{
        spacer = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Expanding);
    }

    tabLay->addWidget(tabItem);
    tabLay->addItem(spacer);

    return true;
}





