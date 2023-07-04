#include "TabItem.h"
#include "ui_tabitem.h"

#include <QMouseEvent>
#include <QPalette>
#include <QPixmap>

TabItem::TabItem(QWidget* page , QWidget *parent) :
    QWidget(parent),
    _page(page),
    ui(new Ui::TabItem)
{
    ui->setupUi(this);

    setTitle(page->windowTitle());
    connect(page,&QWidget::windowTitleChanged,this,&TabItem::setTitle);
}

TabItem::~TabItem()
{
    delete ui;
}

QWidget *TabItem::getPage(){
    return _page;
}

void TabItem::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(_tabFocused ==false ){
            emit foucusTab(this);
        }
    }
}

void TabItem::mouseDoubleClickEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        if(_tabFocused ==false ){
            emit closeTab(this);
        }
    }
}
void TabItem::setTitle(const QString& newTitle)
{
    ui->title->setText(newTitle);
}

void TabItem::setTabFocused(bool focused){
    _tabFocused =focused;

    if(focused == false){
        this->setStyleSheet(UNFOCUS_STYLE);
    }else{
        this->setStyleSheet(FOCUS_STYLE);
    }
}

void TabItem::on_close_tbtn_clicked()
{
    emit closeTab(this);
}

QString TabItem::getTitle(){
    return ui->title->text();
}

bool TabItem::getTabFocused(){
    return _tabFocused;
}

bool TabItem::isYouPage(QWidget *page){
    return _page == page;
}


